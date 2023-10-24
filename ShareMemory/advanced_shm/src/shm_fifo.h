#ifndef SHM_FIFO_H
#define SHM_FIFO_H

#include <sys/ipc.h>
#include <sys/shm.h>
#include <iostream>
#include <string.h>

#include "shm_head.h"

class ShmFIFO 
{
public:
	ShmFIFO(int key, int blksize, int blocks);
	ShmFIFO();
	virtual ~ShmFIFO();
	// 创建和销毁
	bool ShmInit(int key, int blksize, int blocks);
	void destroy(void);
	static void ShmDestroy(int key); //静态删除共享内存方法

	// 打开和关闭
	bool ShmOpen(int key, int blksize, int blocks);
	void ShmClose(void);

	//读取和存储
	void ShmWrite(const void *buf);
	void ShmRead(void *buf);

protected:
	//进程控制信息块
	bool m_open;
	void *m_shmhead;		// 共享内存头部指针
	char *m_payload;	    // 有效负载的起始地址
};


#endif