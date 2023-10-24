#ifndef SHM_HEADER_H_
#define SHM_HEADER_H_

#include <semaphore.h>

/* 共享内存管理内存块 */
typedef struct shmhead_st
{
	int shmid;					// 共享内存ID

	unsigned int blksize;		// 块大小
	unsigned int blocks;		// 总块数
	unsigned int rd_index;		// 读索引
	unsigned int wr_index;		// 写索引

	// 必须放在共享内存内部才行
	sem_t sem_mutex;			// 用来互斥用的信号量
	sem_t sem_full;				// 用来控制共享内存是否满的信号量
	sem_t sem_empty;			// 用来控制共享内存是否空的信号量

} shmhead_t;



#endif