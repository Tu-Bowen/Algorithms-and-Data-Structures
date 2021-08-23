#include<iostream>
using namespace std;
class Stack
{
public:
    Stack();//构造函数，初始化一个栈的大小
    ~Stack();//析构函数

    int*data;//起始地址
    int top=-1;//栈顶元素
    int i=0;
    const int MAXN=10;//栈的最大容量

    void push(int x);//入栈函数
    int pop();//出栈函数
    int GetTop();//获得栈顶元素
    bool IsEmpty();//栈是否为空
    bool IsFull();//栈是否为满
    void PrintStack();//打印栈
};
Stack::Stack()
{
    data=new int[MAXN];
};
//构造函数

Stack::~Stack()
{
    delete [] data;
    data=NULL;
};
//析构函数

void Stack::push(int x)
{
    data[i]=x;
    i++;
    top=i-1;
};
//向栈里输入数据

int Stack::pop()
{
    i=i-1;
    top=top-1;
    return data[top];
};
//从栈中调出数据

int Stack::GetTop()
{
    return data[top];
};
//得到栈顶的数字

bool Stack::IsEmpty()
{
    return top==-1;
}
//判断栈是否为空
bool Stack::IsFull()
{
    return top==MAXN-1;
}
//判断栈是否为满
void Stack::PrintStack()
{
    int j=0;
    for(j=0; j<=top; j++)
        cout<<data[j]<<endl;
}
//打印栈
int main()
{
    Stack s;

    //入栈操作
    //cout<<"1入栈！"<<endl;
    s.push(1);
    //cout<<"10入栈！"<<endl;
    s.push(10);
    //cout<<"20入栈！"<<endl;
    s.push(20);
    //cout<<"100入栈！"<<endl;
    s.push(100);

    //获取栈顶元素

    cout<<"栈顶的数值为："<<s.GetTop()<<endl;

    //打印栈
    s.PrintStack();

    //出栈操作，先进后出

    int t_a=s.pop();
    cout<<"此时的栈顶元素为："<<t_a<<endl;

    //再次入栈
    //cout<<"500入栈！"<<endl;
    s.push(500);
    s.PrintStack();
    //获取栈顶元素
     cout<<"栈顶的数值为："<<s.GetTop()<<endl;

    return 0;
}
