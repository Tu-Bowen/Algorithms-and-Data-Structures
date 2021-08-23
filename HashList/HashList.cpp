#include<iostream>
#include<vector>
#include<list>
#include<cstdbool>
using namespace std;
typedef struct node
{
    string name=" ";
    node*next=nullptr;
    node(const string&s,node*p):name(s),next(p) {}
} node;
class detach_link
{
public:
    detach_link();
    void print();//查看散列表中的内容
    bool isEmpty();//判断散列表是否为空
    bool containes(const string&s);//判断是否包含此字符串
    void insert(const string&s);//插入项
    void remove(const string&s);//删除项
    node*find(const string&s);//根据名字查找数据项
    ~detach_link();
private:
    vector<node*>theLists;//存放链表的数组,初始长度为100
    int length;//数组长度
    int number;//集合中元素的个数
    int hash(const string&key,int tableSize);//散列函数
    void makeEmpty();//清空销毁散列表
    //void rehash();再散列——这里可能需要查找距离n最近的一个素数来再散列,而且分离链接再散列和寻找距离n最近的一个素数的目的是为了缩短程序的查找时间，有点高端操作，我看一个博主的操作学不来^_^!!
    //int nextPrime(int n);求距离n最近的一个素数
};
//初始化数组的长度为100，并且全部置为空指针
detach_link::detach_link()
{
    theLists.resize(100,nullptr);
    length=100;
    number=0;
}
//销毁空间
detach_link::~detach_link()
{
    makeEmpty();
}
//检查某个元素是否在数组中
bool detach_link::containes(const string&s)
{
    int index=hash(s,length);
    //cout<<index<<"  "<<s<<endl;
    for(node*p=theLists[index]; p!=nullptr; p=p->next)
    {
        if((p->name)==s)
            return true;
    }
    return false;
}
//在链表中查找节点
node*detach_link::find(const string&s)
{
    int index=hash(s,length);
    for(node*p=theLists[index]; p!=nullptr; p=p->next)
    {
        if((p->name)==s)
            return p;
    }
    return nullptr;
}
//判断散列表是否为空
bool detach_link::isEmpty()
{
    if(number==0)
        return true;
    return false;
}
//查看散列表中的内容
void detach_link::print()
{
    for(int i=0; i<length; i++)
    {
        for(node*cur=theLists[i]; cur!=nullptr; cur=cur->next)
        {
            cout<<cur->name<<endl;
        }
    }
}
//处理字符串的一种散列函数——除留余数法
int detach_link::hash(const string&key,int tableSize)
{
    int hashVal=0;
    for(int i=0; i<key.size(); i++)
        hashVal=(hashVal*32)+key[i];
    //cout<<hashVal<<endl;
    hashVal=hashVal%tableSize;
    if(hashVal<0)
        hashVal=hashVal+tableSize;
    return hashVal;
}
//插入
void detach_link::insert(const string&s)
{
    int index=hash(s,length);

    if(containes(s))//如果要添加的项已经在集合中就不需要执行添加操作了
        return;
    if(theLists[index]==nullptr)
        theLists[index]=new node(s,nullptr);
    else
    {
        node*cur=new node(s,theLists[index]->next);
        theLists[index]->next=cur;
    }
    number++;
}
//删除
void detach_link::remove(const string&s)
{
    if(!containes(s))
    {
        cout<<"没有要删除的内容"<<endl;
        return;
    }
    int index=hash(s,length);
    if(theLists[index]->name==s)
    {
        node*q=theLists[index];
        theLists[index]=theLists[index]->next;
        delete q;
        return;
    }
    for(node*p=theLists[index]; p->next!=nullptr; p=p->next)
    {
        if(p->next->name==s)
        {
            node*q=p->next;
            p->next=p->next->next;
            delete q;
            break;
        }
    }
}
//清空销毁散列表
void detach_link::makeEmpty()
{
    for(int i=0; i<length; i++)
    {
        node*cur=theLists[i];
        while(cur!=nullptr)
        {
            node*p=cur->next;
            delete cur;
            cur=p;
        }
    }
}
int main()
{
    detach_link use;
    if(use.isEmpty())
        cout<<"散列表为空"<<endl;
    use.insert(string("TuBoWen"));
    use.insert(string("Iverson"));
    use.insert(string("Curry"));
    use.insert(string("Kid"));
    use.insert(string("Irving"));
    use.insert(string("Paul"));
    use.print();
    cout<<"插入成功！！"<<endl;
    use.remove("Kid");
    use.remove("TuBoWen");
    use.print();
    cout<<"删除成功！！！"<<endl;
    if(use.isEmpty())
        cout<<"散列表为空"<<endl;
    cout<<"查找数据：Iverson"<<endl;
    if(use.find("Iverson")!=nullptr)
        cout<<use.find("Iverson")->name<<endl;
    return 0;
}
