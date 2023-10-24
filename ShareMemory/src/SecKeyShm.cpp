#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "SecKeyShm.h"
using namespace std;

/**
 * @brief  Construct a new Sec Key Shm:: Sec Key Shm object
 * @param  key: 
 */
SecKeyShm::SecKeyShm(int key):ShareMemory(key)
{

}

// maxNode 表示要传递的结构体个数
SecKeyShm::SecKeyShm(int key, int maxNode):
    ShareMemory(key, sizeof(int) + maxNode * sizeof(NodeSHMInfo)), m_maxNode(maxNode)
{
    // 连接共享内存
    void* p = mapShm();
    if(p != NULL) {
        // 初始化共享内存区
        memset(p, 0x00, (sizeof(int) + sizeof(NodeSHMInfo) * maxNode));
        // 将maxNode写入共享内存的头4个字节中
        memcpy(p, &maxNode, sizeof(int));
        // 断开与共享内存
        unmapShm();
    }
}

SecKeyShm::SecKeyShm(const char* pathName, int maxNode):
    ShareMemory(pathName, sizeof(int) + maxNode*sizeof(NodeSHMInfo)), m_maxNode(maxNode)
{
    // 连接共享内存
    void* p = mapShm();
    if(p != NULL) {
        // 初始化共享内存区
        memset(p, 0x00, sizeof(int) + sizeof(NodeSHMInfo)*maxNode);
        // 将maxNode写入共享内存的头4个字节中
        memcpy(p, &maxNode, sizeof(int));
        // 断开与共享内存
        unmapShm();
    }
}

/**
 * @brief  Destroy the Sec Key Shm:: Sec Key Shm object
 */
SecKeyShm::~SecKeyShm()
{

}

/**
 * @brief  向共享内存写入数据，会根据clientID和serverID确定共享内存区块位置
 * @param  pNodeInfo: 数据源，向共享内存写入的数据
 * @return int: 0，成功；-1，失败
 */
int SecKeyShm::shmWrite(NodeSHMInfo* pNodeInfo)
{
    // 连接共享内存
    void *p = mapShm();
    
    // 从头4个字节获取maxNode
    memcpy(&m_maxNode, p, sizeof(int));
	cout << "maxNode:" << m_maxNode << endl;
    NodeSHMInfo *pNode = (NodeSHMInfo *)((char *)p + sizeof(int));
	
    //  根据pNodeInfo中clientID、serverID查找共享内存是否有相同的
	int i = 0;
	for(i=0; i<m_maxNode; i++) {
		if(strcmp(pNodeInfo->clientID, pNode[i].clientID)==0 &&
		   strcmp(pNodeInfo->serverID, pNode[i].serverID)==0) {
			memcpy(&pNode[i], pNodeInfo, sizeof(NodeSHMInfo));
			break;
		}
	}

    // 表示没有原有的
	NodeSHMInfo tmp;
	memset(&tmp, 0x00, sizeof(NodeSHMInfo));
	if(i == m_maxNode) { // 如果共享内存中没有指定对象
		for(i = 0; i < m_maxNode; i++) {
            if(memcmp(&pNode[i], &tmp, sizeof(NodeSHMInfo))==0) { // 找到共享内存中空闲的区块，把pNodeInfo指定内容写入该区块
                memcpy(&pNode[i], pNodeInfo, sizeof(NodeSHMInfo));
                break;
            }
        }
	}

    // 断开共享内存的关联
    unmapShm();

    // 如果共享内存没有空闲区块可用，那么返回错误
    if(i == m_maxNode) {
        cout<<"no space to use"<<endl;
        return -1;
    }
    return 0;
}

/**
 * @brief  从指定共享内存中读取数据
 * @param  clientID: 指定读取数据的clientID
 * @param  serverID: 指定读取数据的serverID
 * @param  pNodeInfo: 数据目的地址，从共享内存中读取到的数据
 * @return int: 0, 成功；-1， 失败
 */
int SecKeyShm::shmRead(const char* clientID, const char* serverID, NodeSHMInfo* pNodeInfo)
{
    // 连接共享内存
    void* p = mapShm();
    
    // 从头4个字节获取maxNode
    memcpy(&m_maxNode, p, sizeof(int));
    cout<<"m_maxNode:"<<m_maxNode<<endl;
    NodeSHMInfo* pNode = (NodeSHMInfo*)((char*)p + sizeof(int));
    
    int i=0;
    for(; i<m_maxNode; i++) { /* 找到指定共享内存区块位置 */
        if(strcmp(clientID, pNode[i].clientID)==0 && strcmp(serverID, pNode[i].serverID)==0) {
            memcpy(pNodeInfo, &pNode[i], sizeof(NodeSHMInfo));
            break;
        }
    }

    //  断开
    unmapShm();
    // 没有找到节点
    if(i == m_maxNode) {
        cout<<"not found"<<endl;
        return -1;
    }

    return 0;
}

/**
 * @brief  打印共享内存区块内容
 */
void SecKeyShm::printShm()
{
	void *p = mapShm();
	
	memcpy(&m_maxNode, p, sizeof(int));
	cout << "maxNode:" << m_maxNode << endl;
	
	NodeSHMInfo *pNode = (NodeSHMInfo *)((char *)p + sizeof(int));
	
	int i = 0;
	for(i=0; i<m_maxNode; i++) {
		cout << "-------" << i << "-------" << endl;
		cout << "status:" << pNode[i].status << endl;
		cout << "seckeyID:" << pNode[i].seckeyID << endl;
		cout << "clientID:" << pNode[i].clientID << endl;
		cout << "serverID:" << pNode[i].serverID << endl;
		cout << "seckey:" << pNode[i].seckey << endl;
	}
	
	return;
}
