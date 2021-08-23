#include<iostream>
#include<vector>
#include<stack>
#include<climits>
using namespace std;
//边表节点
typedef struct ADTnode
{
    int node;
    ADTnode*next;
    int time;
    ADTnode(int x,ADTnode*p,int y):node(x),next(p),time(y) {}
}ADTnode;
//顶点表节点
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
    vector<int>sort_vector;//拓扑排序后的数组
    vector<int>ve;//ve[i]表示事件i最早的发生时期
    vector<int>vl;//vl[i]表示事件i最晚发生时期
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
        cout<<"请输入有向图的路径i->j"<<endl;
        cout<<"请输入i:  ";
        cin>>i;
        cout<<endl<<"请输入j:  ";
        cin>>j;
        cout<<endl<<"请输入路径的权重：";
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
        cout<<" 当前节点的入度为："<<nodelist[i]->in;
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
    cout<<"检查拓扑排序的ve数组更新"<<endl;
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
            //根据拓扑排序出来的顺序来更新所指事件的最快的发生时间
            //根据拓扑排序进行更新的原因：为了确保在更新当前点时，指向当前点之前的一个点的ve值是被更新过的了
            if((ve[idx]+p->time)>ve[i])
            {
                cout<<i<<"号节点ve值由"<<idx<<"号节点的ve值"<<" "<<ve[idx]<<" + "<<p->time<<" 更新"<<endl;
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
    //先对图进行拓扑排序
    //并且在排序的同时进行了对每一个事件最快发生时间的计算
    int flag=Topusort_AOE();
    if(flag==-1)
    {
        cout<<"此图中含有回路，ERROR！"<<endl;
        return ;
    }

    int i,idx,k;
    ADTnode*p;
    int node_nums=nodelist.size();
    vl[node_nums-1]=ve[node_nums-1];
    //再逆着沿拓扑排序数组遍历一遍图
    cout<<endl<<"检查vl数组更新"<<endl;
    for(i=node_nums-2;i>=0;i--)
    {
        idx=sort_vector[i];
        for(p=nodelist[idx]->first;p!=nullptr;p=p->next)
        {
            k=p->node;
            if(vl[idx]>(vl[k]-p->time))
            {
                cout<<idx<<"号节点vl值由"<<k<<"号节点的ve值"<<" "<<vl[k]<<" - "<<p->time<<" 更新"<<endl;
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
    //使用e和l的来求解关键活动
    cout<<"关键路径"<<endl;
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
