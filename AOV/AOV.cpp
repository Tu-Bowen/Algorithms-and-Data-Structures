#include<iostream>
#include<vector>
#include<stack>
using namespace std;
//边表节点
typedef struct ADTnode
{
    int node;
    ADTnode*next;
    ADTnode(int x,ADTnode*p):node(x),next(p) {}
}ADTnode;
//顶点表节点
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
        cout<<"请输入有向图的路径i->j"<<endl;
        cout<<"请输入i:  ";
        cin>>i;
        cout<<endl<<"请输入j:  ";
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
        cout<<" 当前节点的入度为："<<nodelist[i]->in;
        cout<<endl;
    }

}
int AOV::Topusort_AOV()
{
    stack<int>in_is_null;
    int i;
    ADTnode*p;
    //先遍历所有节点，把节点中入度为0的节点都放入栈中
    for(i=0;i<nodelist.size();i++)
    {
        if(nodelist[i]->in==0)
            in_is_null.push(i);
    }
    int num=0;//统计打印出的节点的个数
    int idx;
    while(!in_is_null.empty())
    {
        idx=in_is_null.top();
        in_is_null.pop();
        cout<<nodelist[idx]->node<<" ";
        num++;
        //遍历完节点之后，就把节点和节点的出度弧全部删除
        for(p=nodelist[idx]->first;p!=nullptr;p=p->next)
        {
            i=p->node;
            (nodelist[i]->in)--;
            //其他节点的与当前遍历节点有关的入度减一
            if(nodelist[i]->in==0)//判断如果其他节点的入度有为0的，就把节点入栈
                in_is_null.push(i);
        }
    }
    if(num==nodelist.size())
        return 0;//如果形成回路的图的话，那么最外层循环的次数就不会和节点数相匹配，因为形成回路的那一段的节点是不会进入栈中的，因为他们的入度不会是0
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
