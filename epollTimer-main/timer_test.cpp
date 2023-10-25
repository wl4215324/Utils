// #include <timer.hpp>
#include "timer.hpp"
#include <iostream>
#include <atomic>
#include <chrono>

using namespace std;
using namespace Timer;

void hello(void *args) {
    cout << "hello" << endl;
    std::cout << "毫秒:" << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() \
        << std::endl;
}

void d2333(void *args) {
    cout << "2333" << endl;
}

int main(int argc, char const *argv[]) {
    timerManager tm;
    tm.loopstart();
    int a;
    while (cin >> a) {
        if (a == 1) {
            time_t t = time(&t);
            tm.addTimer(t + 15, &d2333);
        } else if (a == 2) {
            time_t t = time(&t);
            tm.addTimer(t + 5, &hello, NULL, TimerType::Cycle);
        } else if (a == -1) {
            tm.loopbreak();
            break;
        }
    }
    return 0;
}
