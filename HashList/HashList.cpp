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
    void print();//�鿴ɢ�б��е�����
    bool isEmpty();//�ж�ɢ�б��Ƿ�Ϊ��
    bool containes(const string&s);//�ж��Ƿ�������ַ���
    void insert(const string&s);//������
    void remove(const string&s);//ɾ����
    node*find(const string&s);//�������ֲ���������
    ~detach_link();
private:
    vector<node*>theLists;//������������,��ʼ����Ϊ100
    int length;//���鳤��
    int number;//������Ԫ�صĸ���
    int hash(const string&key,int tableSize);//ɢ�к���
    void makeEmpty();//�������ɢ�б�
    //void rehash();��ɢ�С������������Ҫ���Ҿ���n�����һ����������ɢ��,���ҷ���������ɢ�к�Ѱ�Ҿ���n�����һ��������Ŀ����Ϊ�����̳���Ĳ���ʱ�䣬�е�߶˲������ҿ�һ�������Ĳ���ѧ����^_^!!
    //int nextPrime(int n);�����n�����һ������
};
//��ʼ������ĳ���Ϊ100������ȫ����Ϊ��ָ��
detach_link::detach_link()
{
    theLists.resize(100,nullptr);
    length=100;
    number=0;
}
//���ٿռ�
detach_link::~detach_link()
{
    makeEmpty();
}
//���ĳ��Ԫ���Ƿ���������
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
//�������в��ҽڵ�
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
//�ж�ɢ�б��Ƿ�Ϊ��
bool detach_link::isEmpty()
{
    if(number==0)
        return true;
    return false;
}
//�鿴ɢ�б��е�����
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
//�����ַ�����һ��ɢ�к�����������������
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
//����
void detach_link::insert(const string&s)
{
    int index=hash(s,length);

    if(containes(s))//���Ҫ��ӵ����Ѿ��ڼ����оͲ���Ҫִ����Ӳ�����
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
//ɾ��
void detach_link::remove(const string&s)
{
    if(!containes(s))
    {
        cout<<"û��Ҫɾ��������"<<endl;
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
//�������ɢ�б�
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
        cout<<"ɢ�б�Ϊ��"<<endl;
    use.insert(string("TuBoWen"));
    use.insert(string("Iverson"));
    use.insert(string("Curry"));
    use.insert(string("Kid"));
    use.insert(string("Irving"));
    use.insert(string("Paul"));
    use.print();
    cout<<"����ɹ�����"<<endl;
    use.remove("Kid");
    use.remove("TuBoWen");
    use.print();
    cout<<"ɾ���ɹ�������"<<endl;
    if(use.isEmpty())
        cout<<"ɢ�б�Ϊ��"<<endl;
    cout<<"�������ݣ�Iverson"<<endl;
    if(use.find("Iverson")!=nullptr)
        cout<<use.find("Iverson")->name<<endl;
    return 0;
}
