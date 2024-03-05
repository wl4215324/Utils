#include "person.h"
#include "woman.h"

Person::Person(string name, int age, string gender): m_name(name), an_age(m_age), m_gender(gender)
{
    m_age = age;
    std::cout << "in Person constructor, an_age:" << an_age << std::endl;
}

void Person::Display()
{
    std::cout << "in Person::Display" << std::endl;
    std::cout << "m_name: " << m_name << ", gender:" << m_gender << std::endl;
    std::cout << "an_age:" << an_age << std::endl;
    std::cout << "m_age:" << m_age << std::endl;

    PrintNum test_print(an_age);
    test_print.display_num();
}

void Person::DisplayInfo()
{
    std::cout << "In father DisplayInfo" << std::endl;
    std::cout << "m_name: " << m_name << ", m_age: " << m_age << ", m_gender: " << m_gender << std::endl;
}

/**
 * @brief  
 */
void Student::Display()
{
    std::cout << "Student::Display" << std::endl;
    std::cout << "school_: " << school_ << ", grade_: " << grade_ << ", class_: " << class_ << ", familyAddr_: " << familyAddr_ << std::endl;
    // Display();
}

void Student::DisplayInfo()
{
    std::cout << "In son DisplayInfo" << std::endl;
    std::cout << "school_: " << school_ << ", grade_: " << grade_ << ", class_: " << class_ << ", familyAddr_: " << familyAddr_ << std::endl;
}

void PersonTest()
{
    Person *ptrPersonTest1 = new Student("LiLei", 20, "male", "highschool", "one", "two", "HePingStreet");
    // Person *ptrPersonTest1 = new Student("LiLei", 20, "male");
    ptrPersonTest1->Display();
    ptrPersonTest1->DisplayInfo();

    Student *ptrStudent = dynamic_cast<Student*>(ptrPersonTest1);
    ptrStudent->Display();
    ptrStudent->DisplayInfo();
}