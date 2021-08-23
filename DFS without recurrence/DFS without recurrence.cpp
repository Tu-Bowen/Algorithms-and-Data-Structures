#include<iostream>
#include<stack>
#include<vector>
using namespace std;
//边表节点
typedef struct ADTnode
{
    int node;
    ADTnode*next;
    ADTnode(int x,ADTnode*p):node(x),next(p) {}
} ADTnode; //顶点表节点
typedef struct upnode
{
    int node;
    ADTnode*first;
    upnode(int x,ADTnode*p):node(x),first(p) {}
} upnode;
class inlist
{
private:
    vector<upnode*>nodelist;
    vector<int>mark;
public:
    void Create_list(const vector<int>&data,int Line_num);
    void Print_list();
    void DFS(int v);
};
void inlist::Create_list(const vector<int>&data,int Line_num)
{
    upnode*up_p;
    ADTnode*ADT_p;
    int i,j,k;
    int Data_Len=data.size();
    for(i=0; i<Data_Len; i++)
    {
        up_p=new upnode(data[i],nullptr);
        nodelist.push_back(up_p);
        mark.push_back(0);
    }
    for(k=0; k<Line_num; k++)
    {
        cout<<"请输入有向图的路径i->j"<<endl;
        cout<<"请输入i:  ";
        cin>>i;
        cout<<endl<<"请输入j:  ";
        cin>>j;
        cout<<endl;
        ADT_p=new ADTnode(j,nodelist[i]->first);
        nodelist[i]->first=ADT_p;
    }
}
void inlist::Print_list()
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
        cout<<endl;
    }
}
void inlist::DFS(int v)
{
    int x;
    int uzi;
    int flag;
    int idx;
    stack<int>s;
    ADTnode*p;
    cout<<nodelist[v]->node<<" ";
    mark[v]=1;
    s.push(v);
    while(!s.empty())
    {
        x=s.top();
        flag=0;
        for(p=nodelist[x]->first; p!=nullptr; p=p->next)
        {
            uzi=p->node;
            if(mark[uzi]==0)
            {
                cout<<nodelist[uzi]->node<<" ";
                s.push(uzi);
                mark[uzi]=1;
                flag=1;
                break;
            }
        }
        if(flag==0)
        {
            s.pop();
        }
    }
}
class inmatrix
{
private:
    vector<int>up_list;
    vector<vector<int>>adt_list;
    vector<int>mark;
public:
    void create(vector<int>&data,int Road_Nums);
    void output();
    void DFS(int v);
};
void inmatrix::create(vector<int>&data,int Road_Nums)
{
    int i,j,k;
    int n=data.size();
    for(i=0; i<n; i++)
    {
        up_list.push_back(data[i]);
        mark.push_back(0);
        adt_list.push_back(vector<int>(n,0));
    }
    for(k=0; k<Road_Nums; k++)
    {
        cin>>i>>j;
        adt_list[i][j]=1;
        adt_list[j][i]=1;
    }
}
void inmatrix::output()
{
    int i,j;
    for(i=0; i<up_list.size(); i++)
        cout<<up_list[i]<<"  ";
    cout<<endl<<endl;
    for(i=0; i<adt_list.size(); i++)
    {
        for(j=0; j<adt_list[0].size(); j++)
            cout<<adt_list[i][j]<<"  ";
        cout<<endl;
    }
}
void inmatrix::DFS(int v)
{
    int x;
    int flag;
    int idx;
    int i;
    int num=up_list.size();
    stack<int>s;
    cout<<up_list[v]<<" ";
    mark[v]=1;
    s.push(v);
    while(!s.empty())
    {
        x=s.top();
        flag=0;
        for(i=0;i<num;i++)
        {
            if(mark[i]==0&&adt_list[x][i]==1)
            {
                cout<<up_list[i]<<" ";
                s.push(i);
                mark[i]=1;
                flag=1;
                break;
            }
        }
        if(flag==0)
        {
            s.pop();
        }
    }
}
int main()
{
    vector<int>ove= {0,1,2,3};
    inlist HA;
    HA.Create_list(ove,4);
    cout<<endl;
    HA.Print_list();
    cout<<endl;
    HA.DFS(0);
    inmatrix HU;
    HU.create(ove,4);
    cout<<endl;
    HU.output();
    cout<<endl;
    HU.DFS(0);
    return 0;
}
