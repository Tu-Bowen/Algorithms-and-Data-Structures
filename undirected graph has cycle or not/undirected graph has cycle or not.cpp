#include<iostream>
#include<vector>
#include<cstdbool>
#include<stack>
using namespace std;
//并查集
class union_set
{
private:
    vector<int>parents;
public:
    union_set(int len);
    int find_parents(int index);
    void make_union(int index1,int index2);
};
union_set::union_set(int len)
{
    int i;
    for(i=0;i<len;i++)
        parents.push_back(i);
}
int union_set::find_parents(int index)
{
    if(index==parents[index])
        return index;
    parents[index]=find_parents(parents[index]);
    return parents[index];
}
void union_set::make_union(int index1,int index2)
{
    parents[find_parents(index1)]=find_parents(index2);
}


typedef struct ArcNode
{
    int Adjvex;
    ArcNode*next=nullptr;
    ArcNode(int x,ArcNode*p):Adjvex(x),next(p) {}
} ArcNode;
//顶点表节点
typedef struct VerNode
{
    int Vervex;
    int du;
    ArcNode*First_Edge;
    VerNode(int x,ArcNode*p,int y):Vervex(x),First_Edge(p),du(y) {}
} VerNode;
class Adjacency_List
{
private:
    vector<VerNode*>VerNode_List;
    vector<int>Visited_Mark;
    vector<int>color;//节点的颜色标记，-1代表没有访问，0代表正在访问，1代表访问结束
    int line;//弧的个数
    int node;//节点的个数
public:
    Adjacency_List() {}
    void create(const vector<int>data,const int Road_Nums);
    void output();
    void Reset_mark();
    bool Cycle_or_not();//剪枝法判断此无向图是否有环成功
    //void DFS_Cycle(bool&flag,const int u);//深度优先遍历判断无向图是否有环————存疑，无法实现
    //bool use_unionset_cycle_or_not();//使用并查集判断无向图是否有环————同样存疑，无法实现
    ~Adjacency_List();
};
void Adjacency_List::create(const vector<int>data,const int Road_Nums)
{
    line=Road_Nums;
    node=data.size();
    VerNode*Node_Pointer_temp;
    ArcNode*Arc_Pointer;
    int i,j,k,weight;
    int Data_Len=data.size();
    cout<<"请输入"<<Road_Nums<<"条弧,以及弧的权重"<<endl;
    for(i=0; i<Data_Len; i++)
    {
        Node_Pointer_temp=new VerNode(data[i],nullptr,0);
        VerNode_List.push_back(Node_Pointer_temp);
        Visited_Mark.push_back(0);
        color.push_back(-1);
    }
    for(k=0; k<Road_Nums; k++)
    {
        cout<<"请输入弧的两端节点"<<endl;
        cin>>i;
        cin>>j;
        //不用担心弧被重复计数的情况，检查函数会把他排除
        Arc_Pointer=new ArcNode(j,VerNode_List[i]->First_Edge);
        VerNode_List[i]->First_Edge=Arc_Pointer;
        VerNode_List[i]->du++;
        Arc_Pointer=new ArcNode(i,VerNode_List[j]->First_Edge);
        VerNode_List[j]->First_Edge=Arc_Pointer;
        VerNode_List[j]->du++;
    }
}
void Adjacency_List::output()
{
    ArcNode*s;
    int i;
    for(i=0; i<VerNode_List.size(); i++)
    {
        cout<<VerNode_List[i]->Vervex;
        cout<<" 当前节点的度是 "<<VerNode_List[i]->du<<" ";
        s=VerNode_List[i]->First_Edge;
        while(s!=nullptr)
        {
            cout<<"——————"<<s->Adjvex;
            s=s->next;
        }
        cout<<endl;
    }
}

void Adjacency_List::Reset_mark()
{
    int i=0;
    for(i=0; i<Visited_Mark.size(); i++)
        Visited_Mark[i]=0;
}
Adjacency_List::~Adjacency_List()
{
    ArcNode*s;
    ArcNode*q;
    int i;
    for(i=0; i<VerNode_List.size(); i++)
    {
        s=VerNode_List[i]->First_Edge;
        delete VerNode_List[i];
        while(s!=nullptr)
        {
            q=s;
            s=s->next;
            delete q;
        }
    }
}
bool Adjacency_List::Cycle_or_not()
{
    stack<int>s;
    if(line>=node)//根据图论知识，如果弧的个数大于节点的个数，那么该图一定有环
        return true;
    int i,idx,num=0;
    int k;
    ArcNode*p;
    for(i=0; i<node; i++)
    {
        if(VerNode_List[i]->du<2)//把所有的度小于2的节点入栈，因为在环中的
            s.push(i);
    }
    //由于在下列循环中，无向图中回路的几个节点无法进入栈，所以num如果小于节点数，说明有回路
    while(!s.empty())
    {
        idx=s.top();
        s.pop();
        Visited_Mark[idx]=1;//从栈中弹出一个节点，就把这个节点和他周围的弧删了，标记数组代表删除
        num++;
        for(p=VerNode_List[idx]->First_Edge; p!=nullptr; p=p->next)
        {
            k=p->Adjvex;
            cout<<k<<" ";
            VerNode_List[k]->du--;
            if(VerNode_List[k]->du<2&&Visited_Mark[k]!=1)
                s.push(k);
        }
        cout<<endl;
    }
    if(num<node)
        return true;
    return false;
}
int main()
{
    vector<int>w= {0,1,2,3,4,5,6};
    Adjacency_List AL;
    AL.create(w,6);
    AL.output();
    cout<<endl<<AL.Cycle_or_not()<<endl;
    AL.Reset_mark();//重置节点的访问状态
    //目前无法使用DFS判断回路
    //bool flag=false;
    //AL.DFS_Cycle(flag,0);
    //cout<<endl<<flag<<endl;
    //我吐了，DFS的算法判断回路和并查集算法判断回路都出现了问题
    //cout<<endl<<AL.use_unionset_cycle_or_not()<<endl;
    return 0;
}
