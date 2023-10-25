/**
 * @file epoll_timer.hpp
 * @author xueweiwujxw (xueweiwujxw@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2021-12-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once
#include <functional>
#include <algorithm>
#include <queue>
#include <vector>
#include <iostream>
#include <atomic>
#include <sys/epoll.h>
#include <future>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define _MAJOR_VERSION_ 0
#define _MINOR_VERSION_ 0
#define _REVISION_VERSION_ 0
#define _STATUS_VERSION_ "Alpha"
#define AUX_STR_EXP(__A) #__A
#define AUX_STR(__A) AUX_STR_EXP(__A)

#ifndef EPOLLTIMER_VERSION
#define EPOLLTIMER_VERSION AUX_STR(_MAJOR_VERSION_) "." AUX_STR(_MINOR_VERSION_) "." AUX_STR(_REVISION_VERSION_) " " _STATUS_VERSION_
#endif

namespace Timer
{
    enum TimerType {
        Once = 0, // 执行一次
        Cycle = 1, // 循环定时器
    };

    /**
     * @brief  
     */
    class timer
    {
    private:
        std::function<void(void *)> fun; // 定时器回调
        unsigned long long expire_time;
        void *args; // 该指针指向的内存空间由外部分配，该类内部不会申请和释放
        TimerType m_timer_type; // 定时器类型
        unsigned long long m_interval;

    public:
        timer(unsigned long long expire, std::function<void(void *)> fun, void *args, TimerType timer_type) : expire_time(expire), fun(fun), args(args), m_timer_type(timer_type) 
        {
            if (timer_type == TimerType::Cycle) { /* is period ? */
                time_t now = time(&now); // get current system time
                m_interval = expire_time - now; // calculate timeval
            } else {
                m_interval = 0;
            }
        }

        inline void active()
        {
            /* 执行定时任务 */
            this->fun(this->args);
        }
        inline unsigned long long getExpire() const { return this->expire_time; }

        inline void setExpire(unsigned long long expireTime)
        { 
            this->expire_time = expireTime; 
        }

        inline TimerType getType() const { return this->m_timer_type; }
        inline unsigned long long getInterval() const { return this->m_interval; }
        inline std::function<void(void *)> GetTimerCbk()
        {
            return this->fun;
        }
        inline void* GetArgs() 
        {
             return args; 
        }

        ~timer() {}
    };

    class timerManager
    {
    private:
        struct cmp
        {
            bool operator()(timer *&a, timer *&b) const {
                return a->getExpire() > b->getExpire();
            }
        };
        /* 定时器任务队列 */
        std::priority_queue<timer *, std::vector<timer *>, cmp> timerQueue;
        std::atomic<bool> is_running;
        std::future<void> m_future;
        int pipefd[2];
        int readfd;
        int writefd;
        char buf[2];

        /**
         * @brief 定时器监听循环，整改定时器队列管理调度
         * 
         */
        void dispatch() 
        {
            struct epoll_event ev, events[10];
            int epollfd = epoll_create(10);
            ev.events = EPOLLIN | EPOLLET;
            ev.data.fd = this->readfd;
            std::cout << epoll_ctl(epollfd, EPOLL_CTL_ADD, this->readfd, &ev) << std::endl;
            while (this->is_running) {
                epoll_wait(epollfd, events, 10, this->getRecentTimeout()); // 找到最近的定时任务，进行定时
                this->activeTimeout(); // 定时时间到，执行定时回调
            }
        }

        /**
         * @brief 获取最小的超时时间定时任务
         * 
         * @return unsigned long long 
         */
        unsigned long long getRecentTimeout() 
        {
            unsigned long long timeout = -1;
            if (this->timerQueue.empty()) {
                return timeout;
            }
                
            unsigned long long now = this->getCurrentSecs();
            timeout = this->timerQueue.top()->getExpire() - now;
            if (timeout < 0) {
                timeout = 0;
            }
                
            return timeout;
        }

        /**
         * @brief 激活超时的回调
         * 
         */
        void activeTimeout() 
        {
            unsigned long long now = this->getCurrentSecs();
            while (!this->timerQueue.empty()) {
                timer *timerPtr = this->timerQueue.top();
                if (timerPtr->getExpire() <= now) {
                    timerPtr->active(); // 执行定时任务回调
                    if (timerPtr->getType() == TimerType::Cycle) {
                        this->addTimer(timerPtr->getInterval() + this->getCurrentSecs(), timerPtr->GetTimerCbk(), timerPtr->GetArgs(), timerPtr->getType());
                    } else {
                        delete timerPtr;
                    }
                    // printf("%p\n\n", timerPtr);
                    this->timerQueue.pop();
                    continue;
                }
                return;
            }
        }

    public:
        timerManager() 
        {
            if (pipe(this->pipefd) < 0) {
                std::cerr << "init pipe failed" << std::endl;
                this->~timerManager();
            }
            this->readfd = this->pipefd[0];
            this->writefd = this->pipefd[1];
        }
        ~timerManager() {}

        /**
         * @brief 获取当前时间，unix时间戳，秒计数
         * 
         * @return unsigned long long 
         */
        unsigned long long getCurrentSecs() 
        {
            time_t t = time(&t);
            return t;
        }

        /**
         * @brief 创建定时器并加入定时任务列表
         * 
         * @param expire_time 超时时间（unix 时间戳）
         * @param fun 回调函数
         * @param args 其他参数
         * @return timer* 
         */
        timer *addTimer(int expire_time, std::function<void(void *)> fun, void *args = nullptr, TimerType timer_type = TimerType::Once) 
        {
            if (expire_time < this->getCurrentSecs()) {
                return nullptr;
            }
            timer *t = new timer(expire_time, fun, args, timer_type);
            if (this->timerQueue.empty()) {
                write(this->writefd, buf, 2);
            }
            this->timerQueue.push(t);
            return t;
        }

        /**
         * @brief 删除一个定时器
         * 
         * @param t 
         */
        void delTimer(timer *t) 
        {
            std::priority_queue<timer *, std::vector<timer *>, cmp> newqueue;
            while (!this->timerQueue.empty()) {
                timer *top = this->timerQueue.top();
                this->timerQueue.pop();
                if (top != t) {
                    newqueue.push(top);
                }
                    
            }
            this->timerQueue = newqueue;
        }

        /**
         * @brief 开启定时，启动定时器任务线程
         * 
         */
        void loopstart() 
        {
            this->is_running = true;
            this->m_future = std::async(&timerManager::dispatch, this);
        }

        /**
         * @brief 结束定时，停止线程标志置位、等待调度线程退出&清空定时任务队列
         * 
         */
        void loopbreak() 
        {
            this->is_running = false;
            if (this->timerQueue.empty()) {
                write(this->writefd, buf, 2);
            }
            this->m_future.wait(); // 等待定时器任务调度线程结束
            /* 清空定时器任务队列 */
            while (!this->timerQueue.empty()) {
                timer *t = this->timerQueue.top();
                delete t;
                this->timerQueue.pop();
            }
        }
    };

} // namespace Timer
