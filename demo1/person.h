#include <iostream>
#include <string>

using namespace std;

class person {
    public:
    string m_name;
    string m_gender;
    int m_age;
    int& an_age;

    person(int age = 20, string name="tony",  string gender="male");
    void display();
};