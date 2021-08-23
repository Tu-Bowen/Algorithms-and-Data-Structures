#include<iostream>
/*队列初始条件：队头指针=队尾指针=NULL
  队列满条件：队尾指针=m（设当前队列容量为m）
  队列空条件：队头指针=队尾指针*/
using namespace std;
class Queue
{
protected:
    int*Qadd;//起始位置
    int first;//记录队首的位置
    int last;//记录队尾的位置
    int come;//帮助对队列进行入队操作
    int MAXM;//记录队列的最大容量
public:
    Queue();//构造函数
    ~Queue();//析构函数
    void push_tail(int x);//队尾入队函数
    void pop_head();//队首出队函数
    bool IsEmpty();//判断队列是否为空函数
    bool IsFull();//判断队列是否为满函数
    int GetFirst();//得到队首元素的函数
    int GetLast();//得到队尾元素的函数
};
Queue::Queue()//构造函数
{
    come=0;
    first=0;
    last=0;
    MAXM=4;
    Qadd=new  int[MAXM];
}
Queue::~Queue()//析构函数
{
    cout<<"基类空间已经被析构函数释放"<<endl;
    delete [] Qadd;
    Qadd=NULL;
}
void Queue::push_tail(int x)//队尾入队函数
{
    if(IsFull())
    {
        cout<<"队列已满"<<endl;
        return ;
    }
    Qadd[come]=x;
    come=come+1;
    last=come-1;
}
void Queue::pop_head()//队首出队函数
{
    if(IsEmpty())
    {
        cout<<"队列为空"<<endl;
        return ;
    }
    cout<<"出队元素为："<<Qadd[first]<<endl;
    int i;
    for(i=first; i<=last; i++)
    {
        if(i!=MAXM-1)
            Qadd[i]=Qadd[i+1];
    }
    last=last-1;
    come=come-1;
}
bool Queue::IsFull()//判断是否为满的函数
{
    return last==MAXM-1;
}
bool Queue::IsEmpty()//判断是否为空的函数
{
    return first==last;
}
int Queue::GetFirst()//得到位于队首的元素
{
    return Qadd[first];
}
int Queue::GetLast()//得到队尾的元素
{
    return Qadd[last];
}


//双向队列
class DoubleQueue:public Queue
{
//我没有定义子类的构造函数和析构函数
//程序会自己先构造出父类
//再使用子类默认的构造函数造出子类对象
//然后结束时先使用子类默认的析构函数释放子类对象
//再调用父类的析构函数来释放父类空间
public:
    void push_head(int x);//队首入队函数
    void pop_tail();//队尾出队函数
};
void DoubleQueue::push_head(int x)//队首入队函数
{
    if(IsFull())
    {
        cout<<"队列已满"<<endl;
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
void DoubleQueue::pop_tail()//队尾出队函数
{
    if(IsEmpty())
    {
        cout<<"队列为空"<<endl;
        return ;
    }
    last=last-1;
    come=come-1;
}
int main()
{
    DoubleQueue s;
    cout<<"先从队尾插入"<<endl;
    s.push_tail(1);
    cout<<"再从队首插入"<<endl;
    s.push_head(2);
    cout<<"获得队首元素："<<s.GetFirst()<<endl;
    cout<<"获得队尾元素："<<s.GetLast()<<endl;
    cout<<"从队首弹出元素"<<endl;
    s.pop_head();
    cout<<"此时再获得队首元素"<<s.GetFirst()<<endl;
    return 0;
}
