#include "shm_fifo.h"

#include <stdlib.h>
#include <thread>         // std::thread, std::thread::id, std::this_thread::get_id
#include <chrono>         // std::chrono::seconds
#include <iostream>

typedef struct user         //定义用户数据包体
{
    char UserName[32];
    char PassWord[32];
} USER_T;

int main(void)
{
	ShmFIFO shm(1234, sizeof(USER_T), 3);

	USER_T user1 = {"admin", "123456"};
	USER_T user2 = {"lili", "654321"};
	USER_T user3 = {"tom&jerry", "****####???"};
	int n = 6;
	
	while (true) {
		shm.ShmWrite(&user1);
		printf("ShmWrite success \n");
        std::this_thread::sleep_for(std::chrono::seconds(1));
		shm.ShmWrite(&user2);
		printf("ShmWrite success \n");
 		std::this_thread::sleep_for(std::chrono::seconds(1));
		shm.ShmWrite(&user3);
		printf("ShmWrite success \n");
 		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	return 0;
}

