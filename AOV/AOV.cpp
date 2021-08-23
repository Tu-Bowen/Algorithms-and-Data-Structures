#include<iostream>
#include<vector>
#include<stack>
using namespace std;
//�߱�ڵ�
typedef struct ADTnode
{
    int node;
    ADTnode*next;
    ADTnode(int x,ADTnode*p):node(x),next(p) {}
}ADTnode;
//�����ڵ�
typedef struct upnode
{
    int node;
    ADTnode*first;
    int in;
    upnode(int x,ADTnode*p,int y):node(x),first(p),in(y){}
}upnode;

class AOV
{
private:
    vector<upnode*>nodelist;
public:
    AOV(){};
    void Create_AOV(const vector<int>&data,int Line_num);
    void Print_AOV();
    int Topusort_AOV();
    ~AOV();
};
void AOV::Create_AOV(const vector<int>&data,int Line_num)
{
    upnode*up_p;
    ADTnode*ADT_p;
    int i,j,k;
    int Data_Len=data.size();
    for(i=0; i<Data_Len; i++)
    {
        up_p=new upnode(data[i],nullptr,0);
        nodelist.push_back(up_p);
    }
    for(k=0; k<Line_num; k++)
    {
        cout<<"����������ͼ��·��i->j"<<endl;
        cout<<"������i:  ";
        cin>>i;
        cout<<endl<<"������j:  ";
        cin>>j;
        cout<<endl;
        ADT_p=new ADTnode(j,nodelist[i]->first);
        nodelist[i]->first=ADT_p;
        nodelist[j]->in++;
    }
}
void AOV::Print_AOV()
{
    ADTnode*s;
    int i;
    for(i=0; i<nodelist.size(); i++)
    {
        cout<<nodelist[i]->node;
        s=nodelist[i]->first;
        while(s!=nullptr)
        {
            cout<<"->"<<s->node;
            s=s->next;
        }
        cout<<" ��ǰ�ڵ�����Ϊ��"<<nodelist[i]->in;
        cout<<endl;
    }

}
int AOV::Topusort_AOV()
{
    stack<int>in_is_null;
    int i;
    ADTnode*p;
    //�ȱ������нڵ㣬�ѽڵ������Ϊ0�Ľڵ㶼����ջ��
    for(i=0;i<nodelist.size();i++)
    {
        if(nodelist[i]->in==0)
            in_is_null.push(i);
    }
    int num=0;//ͳ�ƴ�ӡ���Ľڵ�ĸ���
    int idx;
    while(!in_is_null.empty())
    {
        idx=in_is_null.top();
        in_is_null.pop();
        cout<<nodelist[idx]->node<<" ";
        num++;
        //������ڵ�֮�󣬾Ͱѽڵ�ͽڵ�ĳ��Ȼ�ȫ��ɾ��
        for(p=nodelist[idx]->first;p!=nullptr;p=p->next)
        {
            i=p->node;
            (nodelist[i]->in)--;
            //�����ڵ���뵱ǰ�����ڵ��йص���ȼ�һ
            if(nodelist[i]->in==0)//�ж���������ڵ�������Ϊ0�ģ��Ͱѽڵ���ջ
                in_is_null.push(i);
        }
    }
    if(num==nodelist.size())
        return 0;//����γɻ�·��ͼ�Ļ�����ô�����ѭ���Ĵ����Ͳ���ͽڵ�����ƥ�䣬��Ϊ�γɻ�·����һ�εĽڵ��ǲ������ջ�еģ���Ϊ���ǵ���Ȳ�����0
    return -1;
}
AOV::~AOV()
{
    ADTnode*s;
    ADTnode*q;
    int i;
    for(i=0; i<nodelist.size(); i++)
    {
        s=nodelist[i]->first;
        delete nodelist[i];
        while(s!=nullptr)
        {
            q=s;
            s=s->next;
            delete q;
        }
    }

}
int main()
{
    vector<int>data={0,1,2,3,4,5,6};
    AOV aov;
    aov.Create_AOV(data,12);
    cout<<endl;
    aov.Print_AOV();
    cout<<endl;
    aov.Topusort_AOV();
    return 0;
}
