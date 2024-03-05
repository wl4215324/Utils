#include <iostream>
#include <string>
#include <cstdint>

using namespace std;

class Person 
{
public:
    Person(string name ="tony", int age = 20, string gender = "male");
    void Display();
    virtual ~Person() = default;
    virtual void DisplayInfo();

private:
    std::string m_name;
    std::string m_gender;
    int m_age;
    int& an_age;
};

class Student:public Person
{
public:
    using Person::Person;
    Student(string name, int age, string gender, string school, string grade, string classNo, string familyAddr): Person(name, age, gender), 
    school_(school), grade_(grade), class_(classNo), familyAddr_(familyAddr) { std::cout << "in Student Constructor " << std::endl; }
    void Display();
    void DisplayInfo();

private:
    std::string school_;
    std::string grade_;
    std::string class_;
    std::string familyAddr_;
};

void PersonTest();