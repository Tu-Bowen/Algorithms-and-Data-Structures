#include<iostream>
using namespace std;
class Stack
{
public:
    Stack();//���캯������ʼ��һ��ջ�Ĵ�С
    ~Stack();//��������

    int*data;//��ʼ��ַ
    int top=-1;//ջ��Ԫ��
    int i=0;
    const int MAXN=10;//ջ���������

    void push(int x);//��ջ����
    int pop();//��ջ����
    int GetTop();//���ջ��Ԫ��
    bool IsEmpty();//ջ�Ƿ�Ϊ��
    bool IsFull();//ջ�Ƿ�Ϊ��
    void PrintStack();//��ӡջ
};
Stack::Stack()
{
    data=new int[MAXN];
};
//���캯��

Stack::~Stack()
{
    delete [] data;
    data=NULL;
};
//��������

void Stack::push(int x)
{
    data[i]=x;
    i++;
    top=i-1;
};
//��ջ����������

int Stack::pop()
{
    i=i-1;
    top=top-1;
    return data[top];
};
//��ջ�е�������

int Stack::GetTop()
{
    return data[top];
};
//�õ�ջ��������

bool Stack::IsEmpty()
{
    return top==-1;
}
//�ж�ջ�Ƿ�Ϊ��
bool Stack::IsFull()
{
    return top==MAXN-1;
}
//�ж�ջ�Ƿ�Ϊ��
void Stack::PrintStack()
{
    int j=0;
    for(j=0; j<=top; j++)
        cout<<data[j]<<endl;
}
//��ӡջ
int main()
{
    Stack s;

    //��ջ����
    //cout<<"1��ջ��"<<endl;
    s.push(1);
    //cout<<"10��ջ��"<<endl;
    s.push(10);
    //cout<<"20��ջ��"<<endl;
    s.push(20);
    //cout<<"100��ջ��"<<endl;
    s.push(100);

    //��ȡջ��Ԫ��

    cout<<"ջ������ֵΪ��"<<s.GetTop()<<endl;

    //��ӡջ
    s.PrintStack();

    //��ջ�������Ƚ����

    int t_a=s.pop();
    cout<<"��ʱ��ջ��Ԫ��Ϊ��"<<t_a<<endl;

    //�ٴ���ջ
    //cout<<"500��ջ��"<<endl;
    s.push(500);
    s.PrintStack();
    //��ȡջ��Ԫ��
     cout<<"ջ������ֵΪ��"<<s.GetTop()<<endl;

    return 0;
}
