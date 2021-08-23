#include<iostream>
#include<cstdlib>
using namespace std;
//����һ����������
typedef struct Queuenode
{
    int   data;//������
    struct Queuenode*next;//ָ����
} Qnode; //�������ӽڵ�


class LinkQueue
{
public:
    LinkQueue();//���캯��
    ~LinkQueue();//��������
    void push(int x);//��Ӻ���
    void pop();//���Ӻ���
    bool IsEmpty();//�������Ƿ�Ϊ��
    void print();//��ӡ����

    Qnode*first;//��¼���׵ĵ�ַ
    Qnode*last;//��¼��β�ĵ�ַ
    Qnode*head;//ͷ�ڵ�
    Qnode*pointer;//����ڵ�
};
LinkQueue::LinkQueue()//��ʼ��ͷ�ڵ�
{
    first=NULL;
    last=NULL;
    head=new Qnode;
    head->data=0;
    head->next=NULL;
}
LinkQueue::~LinkQueue()//�ͷ��������ӵĿռ�
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
    Qnode*p;//��ʵ�ڵ�
    p=new Qnode;
    if(IsEmpty())//����ǿ�����
    {
        head->next=p;
        p->data=x;
        p->next=NULL;
        pointer=p;
        first=p;//��¼���׽ڵ�
    }
    else
    {
        pointer->next=p;
        p->data=x;
        p->next=NULL;
        pointer=p;
        last=p;//��¼��β�ڵ�
    }
}
void LinkQueue::pop()
{
    if(IsEmpty())//����ǿ�����
    {
        cout<<"����Ϊ�գ�"<<endl;
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
void LinkQueue::print()//��ӡ����
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
    cout<<"1������"<<endl;
    s.push(1);
    cout<<"10������"<<endl;
    s.push(10);
    cout<<"100������"<<endl;
    s.push(100);
    cout<<"��ʱ����Ԫ��Ϊ��"<<endl;
    s.print();
    return 0;
}
