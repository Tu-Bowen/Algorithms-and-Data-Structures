#include<iostream>
#include<vector>
#include<cstdbool>
using namespace std;
typedef struct Hybrid
{
    string name="";
    int status=0;//数组中位置的2种状态
    Hybrid(string x,int s):name(x),status(s) {}
} Hybrid;
class Open_Adress
{
private:
    vector<Hybrid*>data;//存储数据，初始长度为10
    int value;//插入散列表的数值的个数
    void makeEmpty();//清空散列表
    int hash(const string&key,int tableSize);//散列函数
    int findPos(const string&x);//为插入元素寻找位置
    void destroy();
    void rehash();//再散列操作，当散列表空间不够的时候扩充散列表空间——理应扩充至 最接近oldSize*2的素数 长度的新长度，但是能力有限！！！函数写不出来
public:
    Open_Adress();
    void insert(const string&x);//向散列表中插入x
    bool contain(const string&x);//检查散列表中是否包含x
    void remove(const string&x);//从散列表中删除x
    void print();//打印散列表中内容
    bool isEmpty();//判断散列表是否为空
    ~Open_Adress();
};

Open_Adress::Open_Adress()
{
    for(int i=0;i<10;i++)
    {
        Hybrid*p=new Hybrid("",0);
        data.push_back(p);
    }
    value=0;
}
int Open_Adress::hash(const string&key,int tableSize)
{
    int hashVal=0;
    for(int i=0; i<key.size(); i++)
        hashVal=(hashVal*32)+key[i];
    hashVal=hashVal%tableSize;
    if(hashVal<0)
        hashVal=hashVal+tableSize;
    return hashVal;
}
void Open_Adress::print()
{
    for(int i=0;i<data.size();i++)
    {
        if(data[i]->status==1)
            cout<<i<<"——"<<data[i]->name<<endl;
    }
}
bool Open_Adress::contain(const string&x)
{
    int index=findPos(x);
    if(data[index]->status==1)
        return true;
    return false;
}
void Open_Adress::rehash()
{
    int oldLen=data.size();
    //复制信息
    vector<string>oldName;
    for(int i=0;i<oldLen;i++)
    {
        if(data[i]->status==1)
            oldName.push_back(data[i]->name);
    }
    //扩充空间为原来的2倍
    for(int i=0;i<oldLen;i++)
    {
        Hybrid*p=new Hybrid("",0);
        data.push_back(p);
    }
    makeEmpty();//清空原散列表
    //复制散列表
    for(int i=0;i<oldName.size();i++)
    {
        insert(oldName[i]);
    }
}
void Open_Adress::remove(const string&x)
{
    int index=findPos(x);
    if(data[index]->status==0)
    {
        cout<<"该元素不存在于散列表中！！"<<endl;
        return;
    }
    data[index]->name="";
    data[index]->status=0;
    value--;
    return;
}
bool Open_Adress::isEmpty()
{
    return value==0;
}
int Open_Adress::findPos(const string&x)
{
    int index=hash(x,data.size());

    //线性探测
    /*while(data[index].status!=0&&data[index]->name!=x)
    {
        index=(index+1)%data.size();
    }*/


    /*//！！双散列法，双散列法对R的选择比较苛刻，R必须是一个最接近data.size()的素数，否则表的预选位置就有可能提前用完，但是prePrime我不会写！！
    while(data[index].status!=0&&data[index]->name!=x)
    {
        index=(index+(prePrime(data.size())-hash(x,data.size())%prePrime(data.size()))  )%data.size();
    }*/


    //平方探测,当插入元素个数超过列表长度一半的时候需要再散列操作
    //如果找到了空位置就返回该元素的位置编号
    //如果找到了该元素x，则返回该元素的位置编号
    int clash=1;//在找位置时发生的冲突的次数
    while(data[index]->status!=0&&data[index]->name!=x)
    {
        index=(index+2*clash-1)%data.size();
        clash++;
    }
    return index;
}
void Open_Adress::insert(const string&x)
{
    int index=findPos(x);
    if(data[index]->status==1)//说明x已经在散列表中插入过了
        return;
    data[index]->name=x;
    data[index]->status=1;
    value++;
    if(value>(data.size()/2))//如果数组元素的个数超过了长度的一般
        rehash();//再散列
}
void Open_Adress::makeEmpty()
{
    for(int i=0;i<data.size();i++)
    {
        data[i]->name="";
        data[i]->status=0;
    }
    value=0;
}
void Open_Adress::destroy()
{
    for(int i=0;i<data.size();i++)
    {
        delete data[i];
    }
}
Open_Adress::~Open_Adress()
{
    this->destroy();
}
int main()
{
    Open_Adress oad;
    if(oad.isEmpty())
        cout<<"散列表为空！！"<<endl;
    oad.insert("TuBowen");
    oad.insert("Nash");
    oad.insert("Curry");
    oad.insert("Iverson");
    oad.print();
    cout<<"插入成功！！"<<endl;
    oad.insert("Kid");
    oad.insert("Morant");
    oad.print();
    cout<<"再散列成功！！不过是阉割版的再散列操作，毕竟不会找素数！！"<<endl;
    if(oad.isEmpty())
        cout<<"散列表为空！！"<<endl;
    if(oad.contain("TuBowen"))
        cout<<"TuBowen"<<endl;
    cout<<"查找操作成功！！"<<endl;
    oad.remove("TuBowen");
    oad.print();
    cout<<"删除操作成功！！"<<endl;
    if(oad.contain("TuBowen"))
        cout<<"TuBowen"<<endl;
    return 0;
}
