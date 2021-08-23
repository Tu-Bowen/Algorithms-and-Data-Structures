#include<iostream>
#include<cstdlib>
using namespace std;
//创建一个单向链队
typedef struct Queuenode
{
    int   data;//数据域
    struct Queuenode*next;//指针域
} Qnode; //定义链队节点


class LinkQueue
{
public:
    LinkQueue();//构造函数
    ~LinkQueue();//析构函数
    void push(int x);//入队函数
    void pop();//出队函数
    bool IsEmpty();//检测队列是否为空
    void print();//打印链队

    Qnode*first;//记录队首的地址
    Qnode*last;//记录队尾的地址
    Qnode*head;//头节点
    Qnode*pointer;//记忆节点
};
LinkQueue::LinkQueue()//初始化头节点
{
    first=NULL;
    last=NULL;
    head=new Qnode;
    head->data=0;
    head->next=NULL;
}
LinkQueue::~LinkQueue()//释放整个链队的空间
{
    Qnode*det1=first;
    Qnode*det2=first->next;
    delete head;
    while(det1!=NULL&&det2!=NULL)
    {
        delete det1;
        det1=det2->next;
        delete det2;
        det2=det1->next;
    }
}
void LinkQueue::push(int x)
{
    Qnode*p;//真实节点
    p=new Qnode;
    if(IsEmpty())//如果是空链队
    {
        head->next=p;
        p->data=x;
        p->next=NULL;
        pointer=p;
        first=p;//记录队首节点
    }
    else
    {
        pointer->next=p;
        p->data=x;
        p->next=NULL;
        pointer=p;
        last=p;//记录队尾节点
    }
}
void LinkQueue::pop()
{
    if(IsEmpty())//如果是空链队
    {
        cout<<"链队为空！"<<endl;
    }
    else
    {
        head->next=first->next;
        first=head->next;
    }
}
bool LinkQueue::IsEmpty()
{
    return head->next==NULL;
}
void LinkQueue::print()//打印链队
{
    Qnode*prnt=first;
    while(prnt!=NULL)
    {
        cout<<prnt->data;
        prnt=prnt->next;
    }
}
int main()
{
    LinkQueue s;
    cout<<"1入链队"<<endl;
    s.push(1);
    cout<<"10入链队"<<endl;
    s.push(10);
    cout<<"100入链队"<<endl;
    s.push(100);
    cout<<"此时链队元素为："<<endl;
    s.print();
    return 0;
}
