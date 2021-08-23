#include<iostream>
#include<vector>
#include<cstdbool>
using namespace std;
typedef struct Hybrid
{
    string name="";
    int status=0;//������λ�õ�2��״̬
    Hybrid(string x,int s):name(x),status(s) {}
} Hybrid;
class Open_Adress
{
private:
    vector<Hybrid*>data;//�洢���ݣ���ʼ����Ϊ10
    int value;//����ɢ�б����ֵ�ĸ���
    void makeEmpty();//���ɢ�б�
    int hash(const string&key,int tableSize);//ɢ�к���
    int findPos(const string&x);//Ϊ����Ԫ��Ѱ��λ��
    void destroy();
    void rehash();//��ɢ�в�������ɢ�б�ռ䲻����ʱ������ɢ�б�ռ䡪����Ӧ������ ��ӽ�oldSize*2������ ���ȵ��³��ȣ������������ޣ���������д������
public:
    Open_Adress();
    void insert(const string&x);//��ɢ�б��в���x
    bool contain(const string&x);//���ɢ�б����Ƿ����x
    void remove(const string&x);//��ɢ�б���ɾ��x
    void print();//��ӡɢ�б�������
    bool isEmpty();//�ж�ɢ�б��Ƿ�Ϊ��
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
            cout<<i<<"����"<<data[i]->name<<endl;
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
    //������Ϣ
    vector<string>oldName;
    for(int i=0;i<oldLen;i++)
    {
        if(data[i]->status==1)
            oldName.push_back(data[i]->name);
    }
    //����ռ�Ϊԭ����2��
    for(int i=0;i<oldLen;i++)
    {
        Hybrid*p=new Hybrid("",0);
        data.push_back(p);
    }
    makeEmpty();//���ԭɢ�б�
    //����ɢ�б�
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
        cout<<"��Ԫ�ز�������ɢ�б��У���"<<endl;
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

    //����̽��
    /*while(data[index].status!=0&&data[index]->name!=x)
    {
        index=(index+1)%data.size();
    }*/


    /*//����˫ɢ�з���˫ɢ�з���R��ѡ��ȽϿ��̣�R������һ����ӽ�data.size()��������������Ԥѡλ�þ��п�����ǰ���꣬����prePrime�Ҳ���д����
    while(data[index].status!=0&&data[index]->name!=x)
    {
        index=(index+(prePrime(data.size())-hash(x,data.size())%prePrime(data.size()))  )%data.size();
    }*/


    //ƽ��̽��,������Ԫ�ظ��������б���һ���ʱ����Ҫ��ɢ�в���
    //����ҵ��˿�λ�þͷ��ظ�Ԫ�ص�λ�ñ��
    //����ҵ��˸�Ԫ��x���򷵻ظ�Ԫ�ص�λ�ñ��
    int clash=1;//����λ��ʱ�����ĳ�ͻ�Ĵ���
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
    if(data[index]->status==1)//˵��x�Ѿ���ɢ�б��в������
        return;
    data[index]->name=x;
    data[index]->status=1;
    value++;
    if(value>(data.size()/2))//�������Ԫ�صĸ��������˳��ȵ�һ��
        rehash();//��ɢ��
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
        cout<<"ɢ�б�Ϊ�գ���"<<endl;
    oad.insert("TuBowen");
    oad.insert("Nash");
    oad.insert("Curry");
    oad.insert("Iverson");
    oad.print();
    cout<<"����ɹ�����"<<endl;
    oad.insert("Kid");
    oad.insert("Morant");
    oad.print();
    cout<<"��ɢ�гɹ������������˸�����ɢ�в������Ͼ���������������"<<endl;
    if(oad.isEmpty())
        cout<<"ɢ�б�Ϊ�գ���"<<endl;
    if(oad.contain("TuBowen"))
        cout<<"TuBowen"<<endl;
    cout<<"���Ҳ����ɹ�����"<<endl;
    oad.remove("TuBowen");
    oad.print();
    cout<<"ɾ�������ɹ�����"<<endl;
    if(oad.contain("TuBowen"))
        cout<<"TuBowen"<<endl;
    return 0;
}
