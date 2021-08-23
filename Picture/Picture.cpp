#include<iostream>
#include<vector>
#include<stack>
#include<queue>
using namespace std;
//邻接表的节点声明与定义
//边表节点
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
    ArcNode*First_Edge;
    VerNode(int x,ArcNode*p):Vervex(x),First_Edge(p) {}
} VerNode;


//邻接矩阵储存无向图
class Paint_Adjacency_Matrix
{
private:
    vector<int>vertex;
    vector<vector<int>>arctex;
    vector<int>Visited_Mark;
public:
    void Paint_Exit_In_Adjacency_Matrix(vector<int>data,int Road_Nums);
    void Print_The_Adjacency_Matrix();
    void Mat_To_List();
    void PAM_DFS(int v);//递归
    void Retting_Node();
    void PAM_BFS(int v);//非递归
    bool connect_or_not();//判断当前无向图是否连通
};
void Paint_Adjacency_Matrix::Paint_Exit_In_Adjacency_Matrix(vector<int>data,int Road_Nums)
{
    int i,j,k;
    int Vec_Len=data.size();
    for(i=0; i<Vec_Len; i++)
    {
        vertex.push_back(data[i]);
        Visited_Mark.push_back(0);
        arctex.push_back(vector<int>(Vec_Len,0));
    }
    for(k=0; k<Road_Nums; k++)
    {
        cin>>i>>j;
        arctex[i][j]=1;
        arctex[j][i]=1;
    }
}
void Paint_Adjacency_Matrix::Print_The_Adjacency_Matrix()
{
    int i,j;
    for(i=0; i<vertex.size(); i++)
        cout<<vertex[i]<<"  ";
    cout<<endl<<endl;

    for(i=0; i<arctex.size(); i++)
    {
        for(j=0; j<arctex[0].size(); j++)
            cout<<arctex[i][j]<<"  ";
        cout<<endl;
    }
}
void Paint_Adjacency_Matrix::Mat_To_List()
{
    int i,j,k;
    VerNode*Ver_Node;
    ArcNode*Arc_Node;
    vector<VerNode*>Ver_Node_Array;
    for(i=0; i<vertex.size(); i++)
    {
        Ver_Node=new VerNode(vertex[i],nullptr);
        Ver_Node_Array.push_back(Ver_Node);
    }
    for(i=0; i<vertex.size(); i++)
    {
        for(j=0; j<vertex.size(); j++)
        {
            if(arctex[i][j]!=0)
            {
                Arc_Node=new ArcNode(j,Ver_Node_Array[i]->First_Edge);
                Ver_Node_Array[i]->First_Edge=Arc_Node;
            }
        }
    }
    cout<<"打印转换后的邻接表——————"<<endl;
    for(i=0;i<vertex.size();i++)
    {
        cout<<Ver_Node_Array[i]->Vervex<<"  ";
        Arc_Node=Ver_Node_Array[i]->First_Edge;
        delete Ver_Node_Array[i];
        while(Arc_Node!=nullptr)
        {
            ArcNode*p=Arc_Node;
            cout<<Arc_Node->Adjvex<<"  ";
            Arc_Node=Arc_Node->next;
            delete p;
        }
        cout<<endl;
    }
}
void Paint_Adjacency_Matrix::PAM_DFS(int v)
{
    int j;
    cout<<vertex[v]<<" ";
    Visited_Mark[v]=1;
    for(j=0; j<vertex.size(); j++)
    {
        if(arctex[v][j]==1&&Visited_Mark[j]==0)
            PAM_DFS(j);
    }
}
void Paint_Adjacency_Matrix::Retting_Node()
{
    int i;
    for(i=0; i<Visited_Mark.size(); i++)
        Visited_Mark[i]=0;
}
void Paint_Adjacency_Matrix::PAM_BFS(int v)
{
    int idx;
    int i;
    queue<int>Index_Queue;
    cout<<vertex[v]<<" ";
    Visited_Mark[v]=1;
    Index_Queue.push(v);
    while(!Index_Queue.empty())
    {
        idx=Index_Queue.front();
        Index_Queue.pop();
        for(i=0; i<vertex.size(); i++)
        {
            if(arctex[idx][i]==1&&Visited_Mark[i]==0)
            {
                cout<<vertex[i]<<" ";
                Visited_Mark[i]=1;
                Index_Queue.push(i);
            }
        }
    }
}
//判断一个使用邻接矩阵存储的无向图是否是连通图
//思路：先使用DFS或者BFS遍历图，
//遍历完之后检测标记数组是否节点已经全部遍历完成
//全部遍历到说明是连通图，否则不是
bool Paint_Adjacency_Matrix::connect_or_not()
{
    Retting_Node();
    //先深度优先遍历（或者广度优先遍历）一遍整个图
    PAM_DFS(0);
    //深度优先遍历完之后，遍历标记数组，看看是否有没有遍历的节点
    int i;
    for(i=0;i<Visited_Mark.size();i++)
    {
        if(Visited_Mark[i]==0)
            return false;
    }
    return true;
}
//邻接表储存有向图
class Paint_Adjacency_List
{
private:
    vector<VerNode*>VerNode_List;
    vector<int>Visited_Mark;
public:
    Paint_Adjacency_List() {}
    void Paint_Exist_In_Adjacency_List(vector<int>data,int Road_Nums);
    void Print_The_Adjacency_List();
    void List_To_Mat();
    void PAL_DFS(int v);
    void PAL_BFS(int v);
    void Reset_PAL();
    void isPath(int u,int v,bool&flag);
    void Find_Path(int u,int v,vector<int>&path);
    ~Paint_Adjacency_List();
};
void Paint_Adjacency_List::Paint_Exist_In_Adjacency_List(vector<int>data,int Road_Nums)
{
    VerNode*Node_Pointer_temp;
    ArcNode*Arc_Pointer;
    int i,j,k;
    int Data_Len=data.size();
    for(i=0; i<Data_Len; i++)
    {
        Node_Pointer_temp=new VerNode(data[i],nullptr);
        VerNode_List.push_back(Node_Pointer_temp);
        Visited_Mark.push_back(0);
    }
    for(k=0; k<Road_Nums; k++)
    {
        cout<<"请输入有向图的路径i->j"<<endl;
        cout<<"请输入i:  ";
        cin>>i;
        cout<<endl<<"请输入j:  ";
        cin>>j;
        cout<<endl;
        Arc_Pointer=new ArcNode(j,VerNode_List[i]->First_Edge);
        VerNode_List[i]->First_Edge=Arc_Pointer;
    }
}
void Paint_Adjacency_List::Print_The_Adjacency_List()
{
    ArcNode*s;
    int i;
    for(i=0; i<VerNode_List.size(); i++)
    {
        cout<<VerNode_List[i]->Vervex;
        s=VerNode_List[i]->First_Edge;
        while(s!=nullptr)
        {
            cout<<"->"<<s->Adjvex;
            s=s->next;
        }
        cout<<endl;
    }
}
Paint_Adjacency_List::~Paint_Adjacency_List()
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
void Paint_Adjacency_List::List_To_Mat()
{
    int n=VerNode_List.size();
    ArcNode*p;
    vector<int>Up_Array;
    vector<vector<int>>Link_Array(n,vector<int>(n,0));
    int i,j;
    for(i=0; i<n; i++)
        Up_Array.push_back(VerNode_List[i]->Vervex);
    for(i=0; i<n; i++)
    {
        p=VerNode_List[i]->First_Edge;
        while(p!=nullptr)
        {
            j= p->Adjvex;
            Link_Array[i][j]=1;
            p=p->next;
        }
    }
    cout<<"打印邻接表转换为的邻接矩阵————————"<<endl;
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            cout<<Link_Array[i][j]<<" ";
        }
        cout<<endl;
    }
}
//广度优先遍历和深度优先遍历对于有向图来说，如果随便输入一个节点开始遍历，有可能无法遍历到所有的节点
void Paint_Adjacency_List::PAL_DFS(int v)
{
    ArcNode*p;
    int idx;
    cout<<VerNode_List[v]->Vervex<<" ";
    Visited_Mark[v]=1;
    //p=VerNode_List[v]->First_Edge;
    for(p=VerNode_List[v]->First_Edge; p!=nullptr; p=p->next)
    {
        idx=p->Adjvex;
        if(Visited_Mark[idx]!=1)
            PAL_DFS(idx);
    }
}
void Paint_Adjacency_List::PAL_BFS(int v)
{
    VerNode*t;
    ArcNode*tu;
    int idx;
    queue<VerNode*>op;
    cout<<VerNode_List[v]->Vervex<<" ";
    Visited_Mark[v]=1;
    op.push(VerNode_List[v]);
    while(!op.empty())
    {
        t=op.front();
        op.pop();
        tu=t->First_Edge;
        while(tu!=nullptr)
        {
            idx=tu->Adjvex;
            if(Visited_Mark[idx]!=1)
            {
                cout<<idx<<" ";
                Visited_Mark[idx]=1;
                op.push(VerNode_List[idx]);
            }
            tu=tu->next;
        }
    }
}
void Paint_Adjacency_List::Reset_PAL()
{
    int i=0;
    for(i=0; i<Visited_Mark.size(); i++)
        Visited_Mark[i]=0;
}
//判断一个用邻接表图中从u到v是否存在一条简单路径
//借助DFS算法来实现
void Paint_Adjacency_List::isPath(int u,int v,bool&flag)
{
    //参数flag初始值是false
    int w;
    ArcNode*p;
    Visited_Mark[u]=1;
    p=VerNode_List[u]->First_Edge;
    while(p!=nullptr)
    {
        w=p->Adjvex;
        if(w==v)//如果找到了最后的目标节点
        {
            flag=true;
            return ;
        }
        else if(Visited_Mark[w]==0)//没有找到就以临边未访问的节点来继续访问
        {
            isPath(w,v,flag);
        }
        p=p->next;
    }
}
//打印从u到v的一条简单路径，借助DFS算法
void Paint_Adjacency_List::Find_Path(int u,int v,vector<int>&path)
{
    int w,i;
    ArcNode*p;
    Visited_Mark[u]=1;
    path.push_back(u);
    if(u==v)
    {
        cout<<"简单路径："<<endl;
        for(i=0;i<path.size();i++)
            cout<<path[i]<<"->";
        cout<<endl;
        return;
    }
    p=VerNode_List[u]->First_Edge;
    while(p!=nullptr)
    {
        w=p->Adjvex;
        if(Visited_Mark[w]==0)
            Find_Path(w,v,path);
        p=p->next;
    }
}
//十字链表存储有向图
//边表节点
typedef struct ad_list
{
    int headvex;
    int tailvex;
    ad_list*hilk;
    ad_list*tilk;
    ad_list(int x,int y,ad_list*p1,ad_list*p2):headvex(x),tailvex(y),hilk(p1),tilk(p2) {}
} ad_list;
//顶点表节点
typedef struct up_list
{
    int vertex;
    ad_list*firstin;//入边表指针
    ad_list*firstout;//出边表指针
    up_list(int x,ad_list*p1,ad_list*p2):vertex(x),firstin(p1),firstout(p2) {}
} up_list;
class Paint_Cross
{
private:
    vector<up_list*>Up_List_temp;
public:
    Paint_Cross() {}
    void Paint_In_Cross_List(vector<int>data,int Road_Len);
    void Print_The_Cross_List();
    ~Paint_Cross();
};
void Paint_Cross::Paint_In_Cross_List(vector<int>data,int Road_Len)
{
    up_list*Up_Pointer_temp;
    ad_list*Ad_Pointer_temp;
    int i,j,k;
    int data_len=data.size();
    for(i=0; i<data_len; i++)
    {
        Up_Pointer_temp=new up_list(data[i],nullptr,nullptr);
        Up_List_temp.push_back(Up_Pointer_temp);
    }
    for(k=0; k<Road_Len; k++)
    {
        cout<<"请输入有向图的路径i->j"<<endl;
        cout<<"请输入i:  ";
        cin>>i;
        cout<<endl<<"请输入j:  ";
        cin>>j;
        cout<<endl;
        Ad_Pointer_temp=new ad_list(i,j,Up_List_temp[j]->firstin,Up_List_temp[i]->firstout);
        Up_List_temp[j]->firstin=Ad_Pointer_temp;
        Up_List_temp[i]->firstout=Ad_Pointer_temp;
    }
}
void Paint_Cross::Print_The_Cross_List()
{
    int i;
    for(i=0; i<Up_List_temp.size(); i++)
    {
        ad_list*s=Up_List_temp[i]->firstout;
        while(s!=nullptr)
        {
            cout<<s->headvex<<"->"<<s->tailvex<<endl;
            s=s->tilk;
        }
        s=Up_List_temp[i]->firstin;
        while(s!=nullptr)
        {
            cout<<s->headvex<<"->"<<s->tailvex<<endl;
            s=s->hilk;
        }
    }
}
/*有向图的十字链表不会出问题的原因是在存储的时候就把头和尾的链表已经分清了，
只顺着每一个节点的作为尾巴的指针或者作为头的指针走下去即可，
就不会出现交叉的情况，而且顶点链表的节点拥有两个指针分别管理！！*/
Paint_Cross::~Paint_Cross()
{
    int i;
    ad_list*q;
    for(i=0; i<Up_List_temp.size(); i++)
    {
        ad_list*s=Up_List_temp[i]->firstout;
        delete Up_List_temp[i];
        while(s!=nullptr)
        {
            q=s;
            s=s->tilk;
            delete q;
        }
    }
}
//邻接多重表存储无向图
//边表节点
typedef struct Ad_More_Node
{
    int ivex;
    int jvex;
    Ad_More_Node*ilink;
    Ad_More_Node*jlink;
    Ad_More_Node(int x,int y,Ad_More_Node*p1,Ad_More_Node*p2):ivex(x),jvex(y),ilink(p1),jlink(p2){}
} Ad_More_Node;
//顶点表节点
typedef struct Up_More_Node
{
    int Updata;
    Ad_More_Node*First_Node;
    Up_More_Node(int x,Ad_More_Node*p):Updata(x),First_Node(p) {}
}Up_More_Node;
class Paint_More_Adjacency_List
{
private:
    vector<Up_More_Node*>Up_More_Node_Array;
public:
    //Paint_More_Adjacency_List() {};
    void Paint_Exit_In_More_Adjacency_List(vector<int>data,int Road_Nums);
    void Print_The_More_Adjacency_List();
    //~Paint_More_Adjacency_List();
};
void Paint_More_Adjacency_List::Paint_Exit_In_More_Adjacency_List(vector<int>data,int Road_Nums)
{
    Up_More_Node*Up_temp;
    Ad_More_Node*Ad_temp;
    int i,j,k;
    int data_len=data.size();
    for(i=0; i<data_len; i++)
    {
        Up_temp=new Up_More_Node(data[i],nullptr);
        Up_More_Node_Array.push_back(Up_temp);
    }
    for(k=0; k<Road_Nums; k++)
    {
        cin>>i>>j;
        Ad_temp=new Ad_More_Node(i,j,Up_More_Node_Array[i]->First_Node,Up_More_Node_Array[j]->First_Node);
        Up_More_Node_Array[i]->First_Node=Ad_temp;
        Up_More_Node_Array[j]->First_Node=Ad_temp;
    }
}
void Paint_More_Adjacency_List::Print_The_More_Adjacency_List()
{
    Ad_More_Node*s;
    Ad_More_Node*t;
    int i;
    for(i=0; i<Up_More_Node_Array.size(); i++)
    {
        cout<<"包含点"<<Up_More_Node_Array[i]->Updata<<"的弧："<<endl;
        s=Up_More_Node_Array[i]->First_Node;
        //显示BUG出现在这里，因为多个链表公用节点，所以节点的下一步走向很难判断，输出内容就会有问题
        while(s!=nullptr)
        {
            cout<<s->ivex<<"——————"<<s->jvex<<"之间有一条弧"<<endl;
            t=s;
            s=s->ilink;
            if(s!=nullptr&&s->ivex!=Up_More_Node_Array[i]->Updata&&s->jvex!=Up_More_Node_Array[i]->Updata)
            {
                s=t->jlink;
                continue;
            }
            if(s==nullptr)
            {
                s=t->jlink;
                if(s!=nullptr&&s->ivex!=Up_More_Node_Array[i]->Updata&&s->jvex!=Up_More_Node_Array[i]->Updata)
                    break;
            }
        }
        cout<<endl;
    }
}
//由于每一个链表都有公用节点，重复释放会造成错误————出BUG了，需要调试
//顶点链表只有一个指针管理所以难免交叉释放
/*Paint_More_Adjacency_List::~Paint_More_Adjacency_List()
{
    Ad_More_Node*s;
    Ad_More_Node*q;
    int i;
    for(i=0; i<Up_More_Node_Array.size(); i++)
    {
        s=Up_More_Node_Array[i]->First_Node;
        delete Up_More_Node_Array[i];
        while(s!=nullptr)
        {
            q=s;
            s=s->One;
            delete q;
        }
    }
}*/
int main()
{
    vector<int>res= {0,1,2,3};
    cout<<"邻接矩阵存储无向图——————-"<<endl;
    Paint_Adjacency_Matrix PAM;
    PAM.Paint_Exit_In_Adjacency_Matrix(res,4);
    PAM.Print_The_Adjacency_Matrix();
    cout<<endl;
    cout<<"广度优先遍历图的邻接矩阵——————"<<endl;
    PAM.PAM_BFS(0);
    PAM.Retting_Node();
    cout<<endl;
    cout<<"深度优先遍历图的邻接矩阵——————"<<endl;
    PAM.PAM_DFS(0);
    cout<<endl;
    cout<<"邻接矩阵存储转换为邻接表存储——————"<<endl;
    PAM.Mat_To_List();
    cout<<"邻接表储存有向图————————"<<endl;
    Paint_Adjacency_List PAL;
    PAL.Paint_Exist_In_Adjacency_List(res,4);
    PAL.Print_The_Adjacency_List();
    cout<<endl;
    cout<<"邻接表转换为邻接矩阵储存————————"<<endl;
    PAL.List_To_Mat();
    cout<<endl;
    cout<<"邻接表的深度优先遍历————————"<<endl;
    PAL.PAL_DFS(0);
    cout<<endl;
    PAL.Reset_PAL();
    cout<<"邻接表的广度优先遍历————————"<<endl;
    PAL.PAL_BFS(0);
    cout<<endl;
    cout<<"十字链表存储有向图————————"<<endl;
    Paint_Cross PC;
    PC.Paint_In_Cross_List(res,5);
    PC.Print_The_Cross_List();
    cout<<"邻接多重链表存储无向图————————"<<endl;
    Paint_More_Adjacency_List PMAL;
    PMAL.Paint_Exit_In_More_Adjacency_List(res,5);
    PMAL.Print_The_More_Adjacency_List();
    return 0;
}
