#ifndef SEC_KEY_SHM_H_
#define SEC_KEY_SHM_H_

#pragma once
#include "ShareMemory.h"

#include <iostream>

using namespace std;

/**
 * 共享内存空间分布如下：
 * ---------------------------------------
 * m_maxNode：int 4字节，节点总数量
 * ---------------------------------------
 * NodeSHMInfo[0]--|int status
 *                 |int seckeyID
 *                 |char clientID[12]
 *                 |char serverID[12]
 *                 |char seckey[128]
 * ---------------------------------------
 * NodeSHMInfo[1]
 * ...
 * NodeSHMInfo[m_maxNode-1]
 * ---------------------------------------
 */


/**@class NodeSHMInfo
 * @brief  共享内存中存放数据节点类型定义
 */
class NodeSHMInfo
{
public:
    int status;
    int seckeyID;
    char clientID[12];
    char serverID[12];
    char seckey[128];
};

/**@class SecKeyShm
 * @brief  上层共享内存使用类
 */
class SecKeyShm: public ShareMemory
{
public:
    SecKeyShm(int key);
    SecKeyShm(int key, int maxNode);
    SecKeyShm(const char* pathName);
    SecKeyShm(const char* pathName, int maxNode);
    ~SecKeyShm();

    int shmWrite(NodeSHMInfo* pNodeInfo);
    int shmRead(const char* clientID,const char* serverID,NodeSHMInfo* pNodeInfo);

    // for test
    void printShm();
private:
    int m_maxNode;
};



#endif