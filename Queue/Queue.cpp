#include<iostream>
/*���г�ʼ��������ͷָ��=��βָ��=NULL
  ��������������βָ��=m���赱ǰ��������Ϊm��
  ���п���������ͷָ��=��βָ��*/
using namespace std;
class Queue
{
protected:
    int*Qadd;//��ʼλ��
    int first;//��¼���׵�λ��
    int last;//��¼��β��λ��
    int come;//�����Զ��н�����Ӳ���
    int MAXM;//��¼���е��������
public:
    Queue();//���캯��
    ~Queue();//��������
    void push_tail(int x);//��β��Ӻ���
    void pop_head();//���׳��Ӻ���
    bool IsEmpty();//�ж϶����Ƿ�Ϊ�պ���
    bool IsFull();//�ж϶����Ƿ�Ϊ������
    int GetFirst();//�õ�����Ԫ�صĺ���
    int GetLast();//�õ���βԪ�صĺ���
};
Queue::Queue()//���캯��
{
    come=0;
    first=0;
    last=0;
    MAXM=4;
    Qadd=new  int[MAXM];
}
Queue::~Queue()//��������
{
    cout<<"����ռ��Ѿ������������ͷ�"<<endl;
    delete [] Qadd;
    Qadd=NULL;
}
void Queue::push_tail(int x)//��β��Ӻ���
{
    if(IsFull())
    {
        cout<<"��������"<<endl;
        return ;
    }
    Qadd[come]=x;
    come=come+1;
    last=come-1;
}
void Queue::pop_head()//���׳��Ӻ���
{
    if(IsEmpty())
    {
        cout<<"����Ϊ��"<<endl;
        return ;
    }
    cout<<"����Ԫ��Ϊ��"<<Qadd[first]<<endl;
    int i;
    for(i=first; i<=last; i++)
    {
        if(i!=MAXM-1)
            Qadd[i]=Qadd[i+1];
    }
    last=last-1;
    come=come-1;
}
bool Queue::IsFull()//�ж��Ƿ�Ϊ���ĺ���
{
    return last==MAXM-1;
}
bool Queue::IsEmpty()//�ж��Ƿ�Ϊ�յĺ���
{
    return first==last;
}
int Queue::GetFirst()//�õ�λ�ڶ��׵�Ԫ��
{
    return Qadd[first];
}
int Queue::GetLast()//�õ���β��Ԫ��
{
    return Qadd[last];
}


//˫�����
class DoubleQueue:public Queue
{
//��û�ж�������Ĺ��캯������������
//������Լ��ȹ��������
//��ʹ������Ĭ�ϵĹ��캯������������
//Ȼ�����ʱ��ʹ������Ĭ�ϵ����������ͷ��������
//�ٵ��ø���������������ͷŸ���ռ�
public:
    void push_head(int x);//������Ӻ���
    void pop_tail();//��β���Ӻ���
};
void DoubleQueue::push_head(int x)//������Ӻ���
{
    if(IsFull())
    {
        cout<<"��������"<<endl;
        return ;
    }
    int i;
    for(i=first; i<=last; i++)
    {
        Qadd[i+1]=Qadd[i];
    }
    last=last+1;
    come=come+1;
    Qadd[first]=x;
}
void DoubleQueue::pop_tail()//��β���Ӻ���
{
    if(IsEmpty())
    {
        cout<<"����Ϊ��"<<endl;
        return ;
    }
    last=last-1;
    come=come-1;
}
int main()
{
    DoubleQueue s;
    cout<<"�ȴӶ�β����"<<endl;
    s.push_tail(1);
    cout<<"�ٴӶ��ײ���"<<endl;
    s.push_head(2);
    cout<<"��ö���Ԫ�أ�"<<s.GetFirst()<<endl;
    cout<<"��ö�βԪ�أ�"<<s.GetLast()<<endl;
    cout<<"�Ӷ��׵���Ԫ��"<<endl;
    s.pop_head();
    cout<<"��ʱ�ٻ�ö���Ԫ��"<<s.GetFirst()<<endl;
    return 0;
}
