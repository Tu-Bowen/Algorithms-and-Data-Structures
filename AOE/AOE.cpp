#include<iostream>
#include<vector>
#include<stack>
#include<climits>
using namespace std;
//�߱�ڵ�
typedef struct ADTnode
{
    int node;
    ADTnode*next;
    int time;
    ADTnode(int x,ADTnode*p,int y):node(x),next(p),time(y) {}
}ADTnode;
//�����ڵ�
typedef struct upnode
{
    int node;
    ADTnode*first;
    int in;
    upnode(int x,ADTnode*p,int y):node(x),first(p),in(y){}
}upnode;

class AOE
{
private:
    vector<upnode*>nodelist;
    vector<int>sort_vector;//��������������
    vector<int>ve;//ve[i]��ʾ�¼�i����ķ���ʱ��
    vector<int>vl;//vl[i]��ʾ�¼�i������ʱ��
    int Topusort_AOE();
public:
    AOE(){}
    void Create_AOE(const vector<int>&data,int Line_num);
    void Print_AOE();
    void Critialpath_AOE();
    ~AOE();
};
void AOE::Create_AOE(const vector<int>&data,int Line_num)
{
    upnode*up_p;
    ADTnode*ADT_p;
    int i,j,k,weight;
    int Data_Len=data.size();
    for(i=0; i<Data_Len; i++)
    {
        up_p=new upnode(data[i],nullptr,0);
        ve.push_back(INT_MIN);
        vl.push_back(INT_MAX);
        nodelist.push_back(up_p);
    }
    for(k=0; k<Line_num; k++)
    {
        cout<<"����������ͼ��·��i->j"<<endl;
        cout<<"������i:  ";
        cin>>i;
        cout<<endl<<"������j:  ";
        cin>>j;
        cout<<endl<<"������·����Ȩ�أ�";
        cin>>weight;
        ADT_p=new ADTnode(j,nodelist[i]->first,weight);
        nodelist[i]->first=ADT_p;
        nodelist[j]->in++;
    }
}
void AOE::Print_AOE()
{
    ADTnode*s;
    int i;
    for(i=0; i<nodelist.size(); i++)
    {
        s=nodelist[i]->first;
        while(s!=nullptr)
        {
            cout<<"  "<<nodelist[i]->node<<"->"<<s->node<<"("<<s->time<<")   ";
            s=s->next;
        }
        cout<<" ��ǰ�ڵ�����Ϊ��"<<nodelist[i]->in;
        cout<<endl;
    }

}
int AOE::Topusort_AOE()
{
    stack<int>in_is_null;
    int i;
    ADTnode*p;
    for(i=0;i<nodelist.size();i++)
    {
        if(nodelist[i]->in==0)
            in_is_null.push(i);
        ve[i]=0;
    }
    int num=0;
    int idx;
    cout<<"������������ve�������"<<endl;
    while(!in_is_null.empty())
    {
        idx=in_is_null.top();
        in_is_null.pop();
        sort_vector.push_back(nodelist[idx]->node);
        num++;
        for(p=nodelist[idx]->first;p!=nullptr;p=p->next)
        {
            i=p->node;
            (nodelist[i]->in)--;
            if(nodelist[i]->in==0)
            {
                in_is_null.push(i);
            }
            //�����������������˳����������ָ�¼������ķ���ʱ��
            //��������������и��µ�ԭ��Ϊ��ȷ���ڸ��µ�ǰ��ʱ��ָ��ǰ��֮ǰ��һ�����veֵ�Ǳ����¹�����
            if((ve[idx]+p->time)>ve[i])
            {
                cout<<i<<"�Žڵ�veֵ��"<<idx<<"�Žڵ��veֵ"<<" "<<ve[idx]<<" + "<<p->time<<" ����"<<endl;
                ve[i]=(ve[idx]+p->time);
            }
        }
    }
    cout<<endl<<"sort_vector"<<endl;
    for(i=0;i<sort_vector.size();i++)
    {
        cout<<sort_vector[i]<<" ";
    }
    if(num==nodelist.size())
        return 0;
    return -1;
}
void AOE::Critialpath_AOE()
{
    //�ȶ�ͼ������������
    //�����������ͬʱ�����˶�ÿһ���¼���췢��ʱ��ļ���
    int flag=Topusort_AOE();
    if(flag==-1)
    {
        cout<<"��ͼ�к��л�·��ERROR��"<<endl;
        return ;
    }

    int i,idx,k;
    ADTnode*p;
    int node_nums=nodelist.size();
    vl[node_nums-1]=ve[node_nums-1];
    //�����������������������һ��ͼ
    cout<<endl<<"���vl�������"<<endl;
    for(i=node_nums-2;i>=0;i--)
    {
        idx=sort_vector[i];
        for(p=nodelist[idx]->first;p!=nullptr;p=p->next)
        {
            k=p->node;
            if(vl[idx]>(vl[k]-p->time))
            {
                cout<<idx<<"�Žڵ�vlֵ��"<<k<<"�Žڵ��veֵ"<<" "<<vl[k]<<" - "<<p->time<<" ����"<<endl;
                vl[idx]=(vl[k]-p->time);
            }
        }
    }
    cout<<endl;
    cout<<"ve"<<endl;
    for(i=0;i<ve.size();i++)
        cout<<ve[i]<<" ";
    cout<<endl;
    cout<<"vl"<<endl;
    for(i=0;i<vl.size();i++)
        cout<<vl[i]<<" ";
    cout<<endl;
    int e,l;
    int time;
    //ʹ��e��l�������ؼ��
    cout<<"�ؼ�·��"<<endl;
    for(i=0;i<node_nums;i++)
    {
        for(p=nodelist[i]->first;p!=nullptr;p=p->next)
        {
            idx=p->node;
            time=p->time;
            e=ve[i];
            l=vl[idx]-time;
            if(e==l)
                cout<<i<<"->"<<idx<<" ";
        }
    }
}
AOE::~AOE()
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
    vector<int>data={0,1,2,3,4,5,6,7,8};
    AOE aoe;
    aoe.Create_AOE(data,12);
    cout<<endl;
    aoe.Print_AOE();
    cout<<endl;
    aoe.Critialpath_AOE();
    return 0;
}
