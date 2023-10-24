#ifndef SHARE_MEMORY_H_
#define SHARE_MEMORY_H_

#pragma once
#include <sys/ipc.h>
#include <sys/shm.h>

const char RandX = 'x';

class ShareMemory
{
public:
    ShareMemory(int key);// 打开共享内存
    ShareMemory(int key,int size);// 创建共享内存
    ShareMemory(const char* name);
    ShareMemory(const char* name,int size);
    virtual ~ShareMemory();

    void* mapShm();
    int unmapShm();
    int delShm();

private:
    int getShmID(key_t key,int shmSize,int flag);
    int m_shmID;
    void* m_shmAddr;

};

#endif