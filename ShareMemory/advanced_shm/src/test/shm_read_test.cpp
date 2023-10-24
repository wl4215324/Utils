#include "shm_fifo.h"
#include <string.h>
#include <chrono>         // std::chrono::seconds

typedef struct user         //定义用户数据包体
{
    char UserName[32];
    char PassWord[32];
} USER_T;


int main(void)
{
	USER_T user;
	ShmFIFO shm(1234, sizeof(USER_T), 3);
	
	while (true) {
		memset(&user, 0, sizeof(USER_T));
		shm.ShmRead(&user);
		printf("ShmRead success\n");
		printf("UserName = %s, PassWord = %s\n", user.UserName, user.PassWord);
		std::cout << "毫秒:" << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()<< std::endl;
	}
	
	return 0;
}
