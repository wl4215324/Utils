#include <iostream>
#include <memory>
#include <atomic>

#include "person.h"

void foo(std::shared_ptr<int> i) {
    (*i)++;
    std::cout<<"i: "<<*i<<endl;
}

int main(int argc, char* argv[])
{
    // auto pointer = std::make_shared<int>(10);
    // std::cout<<pointer.use_count()<<endl;
    // auto pointer2 = pointer;
    // std::cout<<pointer.use_count()<<endl;
    // foo(pointer);
    // std::cout << *pointer << std::endl; // 11
    // person test_man(30);
    // test_man.display();
    // cout<<"an_age:"<<test_man.an_age<<" m_age:"<<test_man.m_age<<endl;

    // int i = 128;
    // cout <<"i hex print: 0x"<<hex<<i<<std::endl;
#if 0
    string *s1 = new string("s1");
    shared_ptr<string> ps1(s1);
    std::cout<<"ps1.unique: "<<ps1.unique()<<endl;    //0
    shared_ptr<string> ps2;
    ps2 = ps1;

    std::cout<<"ps1.use_count: "<<ps1.use_count()<<endl;    //2
    std::cout<<"ps2.use_count: "<<ps2.use_count()<<endl;    //2
    std::cout << ps1.unique()<<endl;    //0

    string *s3 = new string("s3");
    shared_ptr<string> ps3(s3);

    cout << (ps1.get()) << endl;    //033AEB48
    cout << ps3.get() << endl;    //033B2C50
    swap(ps1, ps3);    //交换所拥有的对象
    cout << (ps1.get())<<endl;    //033B2C50
    cout << ps3.get() << endl;    //033AEB48

    cout << ps1.use_count()<<endl;    //1
    cout << ps2.use_count() << endl;    //2
    ps2 = ps1;
    cout << ps1.use_count()<<endl;    //2
    cout << ps2.use_count() << endl;    //2
    ps1.reset();    //放弃ps1的拥有权，引用计数的减少
    cout << ps1.use_count()<<endl;    //0
    cout << ps2.use_count()<<endl;    //1
#endif
    std::atomic <int> test {0};
    std::cout << "test: " << test.fetch_add(1) << std::endl;
    std::cout << "test: " << test.load() << std::endl;

    return 0;
}