
class PrintNum {
    public:
    int& age;

    PrintNum(int&);
    void display_num();
};

PrintNum::PrintNum(int& input_num): age(input_num)
{

}

void PrintNum::display_num()
{
    cout<<"display_num: "<<age<<endl;
    cout<<"display_num: "<<++age<<endl;
}