#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

#include "ShareMemory.h"

/**
 * @brief  Construct a new Share Memory:: Share Memory object
 *  基于key查询当前已申请的共享内存
 * @param  key: 
 */
ShareMemory::ShareMemory(int key)
{
    // 打开共享内存
    m_shmID = getShmID(key, 0, IPC_CREAT|IPC_EXCL); 
}

/**
 * @brief  Construct a new Share Memory:: Share Memory object
 * 根据用户传入的key和size 申请共享内存
 * @param  key: 用户传入key值
 * @param  size: 用户指定申请共享内存大小
 */
ShareMemory::ShareMemory(int key, int size)
{
    // 创建共享内存
    m_shmID = getShmID(key, size, IPC_CREAT|0755); 
}

ShareMemory::ShareMemory(const char* name)
{
    // 通过路文件名连接共享内存
    key_t key = ftok(name, RandX);
    m_shmID = getShmID(key, 0, IPC_CREAT|IPC_EXCL);
}

ShareMemory::ShareMemory(const char* name, int size)
{
    // 通过路文件名创建
    key_t key = ftok(name, RandX);
    m_shmID = getShmID(key, size, IPC_CREAT|0755);

}

/**
 * @brief  Destroy the Share Memory:: Share Memory object
 */
ShareMemory::~ShareMemory()
{

}

/**
 * @brief  把共享内存区对象映射到调用进程的地址空间
 * @return void*: 返回映射到调用进程的地址空间
 */
void* ShareMemory::mapShm()
{
    m_shmAddr = shmat(m_shmID, NULL, 0);
    if(m_shmAddr == (void*)-1) {
        // 日志
        return NULL;
    }
    return m_shmAddr;
}

/**
 * @brief  解除共享内存与调用进程的绑定
 * @return int: 
 */
int ShareMemory::unmapShm()
{
    int ret = shmdt(m_shmAddr);
    return ret;
}

/**
 * @brief  删除已申请共享内存
 * @return int: 
 */
int ShareMemory::delShm()
{
    int ret = shmctl(m_shmID, IPC_RMID, NULL);
    return ret;
}

int ShareMemory::getShmID(key_t key, int shmSize, int flag)
{
    m_shmID = shmget(key, shmSize, flag);
    if(m_shmID < 0) {
        // 打印日志
        return -1; 
    }
    return m_shmID;
}

