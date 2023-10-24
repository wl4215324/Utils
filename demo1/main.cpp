#include <iostream>
#include <memory>
#include <atomic>
#include <functional>

#include "person.h"

void foo(std::shared_ptr<int> i) {
    (*i)++;
    std::cout<<"i: "<<*i<<endl;
}

class A
{
public:
    A() { std::cout << "A()" << std::endl; }
    A(int a) { std::cout << "A(int a)" << std::endl; }
    A(const A &) { std::cout << "A(const A &)" << std::endl; }
};

// Object类
class Object
{
public:
	Object* self()
	{
		return this;
	}

	std::function<Object* (void)>  m_sender;
};

// 槽对象类3
class SlotObject3 :public Object
{
public:
	SlotObject3() {}

public:
	void slotMember(int signal)
	{
		if (m_sender) {
			std::cout << "sender:" << m_sender() << std::endl;
		}
		std::cout << "signal:" << signal << " recv:" << this << std::endl;
	}
};

// 信号对象类3
class SignalObject3 :public Object
{
public:
	void connect(SlotObject3* recver, std::function<void(SlotObject3*, int)> slot)
	{
		m_recver = recver;
		m_callFun = slot;
	}
	void emitSignal(int signal)
	{
        std::cout << "m_recver:" << m_recver << std::endl;
		m_recver->m_sender = std::bind(&SlotObject3::self, this);
        std::cout << "m_sender:" << m_recver->m_sender() << std::endl;
		m_callFun(m_recver, signal);
		m_recver->m_sender = NULL;
	}

private:
	SlotObject3* m_recver;
	std::function<void(SlotObject3*, int)>  m_callFun;
};



int main(int argc, char* argv[])
{
	SignalObject3 signalObject3;
	SlotObject3   slotObject3;

	std::cout << "signalObject3:" << &signalObject3 << std::endl;
	std::cout << "slotObject3:" << &slotObject3 << std::endl;

	// 连接信号槽
	std::function<void(SlotObject3*, int)> slot3 = &SlotObject3::slotMember;
	signalObject3.connect(&slotObject3, slot3);

	// 发射信号
	signalObject3.emitSignal(3);

    // A a1(10);
    // A a2(a1);
    // A a3 = a2;
    // A a4 = 2;
    // A a5 = A(3);

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