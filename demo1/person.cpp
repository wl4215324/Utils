#include "person.h"
#include "woman.h"

person::person(int age, string name, string gender): m_name(name), an_age(m_age), m_gender(gender)
{
    m_age = age;
    cout << "an_age:" <<an_age << endl;
}

void person::display()
{
    cout << "gender:" <<m_gender << endl;
    cout << "an_age:" <<an_age << endl;
    cout << "m_age:" <<m_age << endl;

    PrintNum test_print(an_age);
    test_print.display_num();
}