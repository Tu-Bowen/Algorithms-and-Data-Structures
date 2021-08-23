#include<iostream>
#include<vector>
#include<climits>
#include<cstdbool>
#include<algorithm>
using namespace std;
//邻接矩阵
class Matrix_Data
{
private:
    vector<vector<int>>Adjacency_Matrix;
    vector<int>Picture_Node;
    vector<int>visited_mark;
    void check_node(const int u,const int v,bool&flag,const vector<vector<int>>&op,const int n);
public:
    void Create_Adjacency_Matrix(const vector<int>&data,const int Line_nums);
    void Printf_Adjacency_Matrix();
    void Reset_mark();
    void Prim_Matrix(const int start);
    void Kruskal_Matrix();

};
void Matrix_Data::Create_Adjacency_Matrix(const vector<int>&data,const int Line_nums)
{
    int i,j,k;
    int weight;
    int data_len=data.size();
    cout<<"请输入"<<Line_nums<<"条弧,以及弧的权重"<<endl;
    for(i=0; i<data_len; i++)
    {
        Picture_Node.push_back(data[i]);
        Adjacency_Matrix.push_back(vector<int>(data_len,INT_MAX));
        visited_mark.push_back(0);
    }
    for(k=0; k<Line_nums; k++)
    {
        cout<<"———请输入弧的两端节点————"<<endl;
        cin>>i;
        cin>>j;
        cout<<"————请输入弧的权重————"<<endl;
        cin>>weight;
        Adjacency_Matrix[i][j]=weight;
        Adjacency_Matrix[j][i]=weight;
    }
}
void Matrix_Data::Printf_Adjacency_Matrix()
{
    int i,j;
    int len=Picture_Node.size();
    cout<<"无向网图————————"<<endl;
    for(i=0; i<len; i++)
    {
        for(j=0; j<len; j++)
        {
            if(Adjacency_Matrix[i][j]==INT_MAX)
                cout<<"∞"<<" ";
            else
                cout<<Adjacency_Matrix[i][j]<<" ";
        }
        cout<<endl;
    }
}
//最小生成树的节点，存储弧的信息
typedef struct Line_node
{
    //弧的两头节点
    int head;
    int tail;
    //弧的权重
    int weight;
    Line_node(int x,int y,int z):head(x),tail(y),weight(z) {}
    //不是很明白为什么这里无法正确排序
    /*bool operator<(Line_node*s)
    {
        return weight<s->weight;
    }*/
    bool operator<(const Line_node&s)
    {
        return weight<s.weight;
    }
} Line_node;
void Matrix_Data::Prim_Matrix(const int start)
{
    int i,j,idx,k;
    int node_num=Picture_Node.size();
    vector<Line_node*>MST_Pointer_Array;
    Line_node*p;
    vector<int>node_set;
//先把源节点进入集合
    visited_mark[start]=1;
    node_set.push_back(start);
//需要构建node_num-1条弧
    for(i=0; i<node_num-1; i++)
    {
        p=new Line_node(-1,-1,INT_MAX);
        MST_Pointer_Array.push_back(p);
        //在节点集合中寻找所有节点最短的弧,节点集合中的点都是搜索过了的
        for(j=0; j<node_set.size(); j++)
        {
            idx=node_set[j];
            //遍历当前点的邻接点位
            for(k=0; k<node_num; k++)
            {
                if(Adjacency_Matrix[idx][k]!=INT_MAX&&Adjacency_Matrix[idx][k]<(p->weight)&&visited_mark[k]==0)
                {
                    //选择这条线
                    p->head=idx;
                    p->tail=k;
                    p->weight=Adjacency_Matrix[idx][k];
                }
            }
        }
        //把这条线的尾点加入集合
        visited_mark[p->tail]=1;
        node_set.push_back(p->tail);
    }
//打印出最小生成树
    cout<<"最小生成树——————————Prim算法"<<endl;
    for(i=0; i<node_num-1; i++)
    {
        cout<<MST_Pointer_Array[i]->head<<"————————"<<MST_Pointer_Array[i]->tail<<"  权重为："<<MST_Pointer_Array[i]->weight<<endl;
    }
//释放空间
    for(i=0; i<node_num-1; i++)
        delete MST_Pointer_Array[i];
}
void Matrix_Data::Reset_mark()
{
    int i;
    for(i=0; i<visited_mark.size(); i++)
        visited_mark[i]=0;
}
void Matrix_Data::check_node(const int u,const int v,bool&flag,const vector<vector<int>>&op,const int n)
{
    int i;
    visited_mark[u]=1;
    for(i=0; i<n; i++)
    {
        if(op[u][i]==INT_MAX)//把生成树看作一个新生成的图，检测u与i点之间不相连，就检查下一个点位
            continue;
        if(i==v)
        {
            flag=true;
            return;
        }
        else if(visited_mark[i]==0)
        {
            check_node(i,v,flag,op,n);
        }
    }
}
void Matrix_Data::Kruskal_Matrix()
{
    bool flag;
    int i,j;
    vector<Line_node>MST_Pointer_Array;//存储生成树每一条弧节点的信息
    vector<Line_node>MST_temp;//存储图所有弧的信息，方便比较弧之间的权重大小
    Line_node*p;
    int node_num=Picture_Node.size();
    vector<vector<int>>tree_node_matrix(node_num,vector<int>(node_num,INT_MAX));
//把图的所有弧输入进数组中
    for(i=0; i<node_num; i++)
    {
        for(j=i; j<node_num; j++)
        {
            if(Adjacency_Matrix[i][j]!=INT_MAX)
            {
                MST_temp.push_back(Line_node(i,j,Adjacency_Matrix[i][j]));
            }
        }
    }
//按照权重大小排序
    sort(MST_temp.begin(),MST_temp.end());
//从小到大遍历所有的弧
    for(i=0; i<MST_temp.size(); i++)
    {
        Reset_mark();
        flag=false;
        check_node(MST_temp[i].head,MST_temp[i].tail,flag,tree_node_matrix,node_num);
        if(!flag)
        {
            MST_Pointer_Array.push_back(MST_temp[i]);
            int x=MST_temp[i].head;
            int y=MST_temp[i].tail;
            tree_node_matrix[x][y]=MST_temp[i].weight;
            tree_node_matrix[y][x]=MST_temp[i].weight;
        }
    }
//打印最小生成树
    cout<<"最小生成树——————————Kruskal算法"<<endl;
    for(i=0; i<MST_Pointer_Array.size(); i++)
    {
        cout<<MST_Pointer_Array[i].head<<"————————"<<MST_Pointer_Array[i].tail<<"  权重为："<<MST_Pointer_Array[i].weight<<endl;
    }
}
//邻接表
//边表节点
typedef struct ArcNode
{
    int Adjvex;
    int weight;
    ArcNode*next=nullptr;
    ArcNode(int x,int y,ArcNode*p):Adjvex(x),weight(y),next(p) {}
} ArcNode;
//顶点表节点
typedef struct VerNode
{
    int Vervex;
    ArcNode*First_Edge;
    VerNode(int x,ArcNode*p):Vervex(x),First_Edge(p) {}
} VerNode;
class Adjacency_List
{
private:
    vector<VerNode*>VerNode_List;
    vector<int>Visited_Mark;
public:
    Adjacency_List() {}
    void Paint_Exist_In_Adjacency_List(const vector<int>data,const int Road_Nums);
    void Print_The_Adjacency_List();
    void PAL_DFS(const int v);
    void Reset_mark();
    void isPath(const int u,const int v,bool&flag,vector<VerNode>&op);
    void Prim_List(const int v);
    void Kruskal_List();
    ~Adjacency_List();
};
void Adjacency_List::Paint_Exist_In_Adjacency_List(const vector<int>data,const int Road_Nums)
{
    VerNode*Node_Pointer_temp;
    ArcNode*Arc_Pointer;
    int i,j,k,weight;
    int Data_Len=data.size();
    cout<<"请输入"<<Road_Nums<<"条弧,以及弧的权重"<<endl;
    for(i=0; i<Data_Len; i++)
    {
        Node_Pointer_temp=new VerNode(data[i],nullptr);
        VerNode_List.push_back(Node_Pointer_temp);
        Visited_Mark.push_back(0);
    }
    for(k=0; k<Road_Nums; k++)
    {
        cout<<"请输入弧的两端节点"<<endl;
        cin>>i;
        cin>>j;
        cout<<"请输入弧的权重："<<endl;
        cin>>weight;
        //不用担心弧被重复计数的情况，检查函数会把他排除
        Arc_Pointer=new ArcNode(j,weight,VerNode_List[i]->First_Edge);
        VerNode_List[i]->First_Edge=Arc_Pointer;
        Arc_Pointer=new ArcNode(i,weight,VerNode_List[j]->First_Edge);
        VerNode_List[j]->First_Edge=Arc_Pointer;
    }
}
void Adjacency_List::Print_The_Adjacency_List()
{
    ArcNode*s;
    int i;
    for(i=0; i<VerNode_List.size(); i++)
    {
        cout<<VerNode_List[i]->Vervex;
        s=VerNode_List[i]->First_Edge;
        while(s!=nullptr)
        {
            cout<<"——————"<<s->Adjvex;
            s=s->next;
        }
        cout<<endl;
    }
}
void Adjacency_List::PAL_DFS(const int v)
{
    ArcNode*p;
    int idx;
    cout<<VerNode_List[v]->Vervex<<" ";
    Visited_Mark[v]=1;
    for(p=VerNode_List[v]->First_Edge; p!=nullptr; p=p->next)
    {
        idx=p->Adjvex;
        if(Visited_Mark[idx]!=1)
            PAL_DFS(idx);
    }
}
void Adjacency_List::Reset_mark()
{
    int i=0;
    for(i=0; i<Visited_Mark.size(); i++)
        Visited_Mark[i]=0;
}
//判断一个用邻接表图中从u到v是否存在一条简单路径,借助DFS算法来实现
void Adjacency_List::isPath(const  int u,const int v,bool&flag,vector<VerNode>&op)
{
    int w;
    ArcNode*p;
    Visited_Mark[u]=1;
    p=op[u].First_Edge;
    while(p!=nullptr)
    {
        w=p->Adjvex;
        if(w==v)
        {
            flag=true;
            return ;
        }
        else if(Visited_Mark[w]==0)
        {
            isPath(w,v,flag,op);
        }
        p=p->next;
    }

}

void Adjacency_List::Prim_List(const int v)
{
    int i,j,idx,w;
    int node_num=VerNode_List.size();
    vector<Line_node*>Line_array;
    Line_node*p;
    ArcNode*q;
    vector<int>node_set;
    Visited_Mark[v]=1;
    node_set.push_back(v);
    for(i=0; i<node_num-1; i++)
    {
        p=new Line_node(-1,-1,INT_MAX);
        Line_array.push_back(p);
        for(j=0; j<node_set.size(); j++)
        {
            idx=node_set[j];
            for(q=VerNode_List[idx]->First_Edge; q!=nullptr; q=q->next)
            {
                w=q->Adjvex;
                if(Visited_Mark[w]==0&&(q->weight)<(p->weight))
                {
                    p->head=idx;
                    p->tail=w;
                    p->weight=(q->weight);
                }
            }
        }
        //Visited_Mark[w]=1;w的值会在循环中改变，所以不能用w来代替进入集合的点
        //node_set.push_back(w);
        Visited_Mark[p->tail]=1;
        node_set.push_back(p->tail);
        cout<<endl;
    }
    cout<<"最小生成树——————————Prim算法"<<endl;
    for(i=0; i<node_num-1; i++)
        cout<<Line_array[i]->head<<"————————"<<Line_array[i]->tail<<"  权重为："<<Line_array[i]->weight<<endl;
    for(i=0; i<node_num-1; i++)
        delete Line_array[i];
}


void Adjacency_List::Kruskal_List()
{
    bool flag;
    int i,j;
    vector<Line_node>MST_Pointer_Array;//存储生成树每一条弧节点的信息
    vector<Line_node>MST_temp;//存储图所有弧的信息，方便比较弧之间的权重大小
    Line_node*p;
    ArcNode*flx;
    ArcNode*q;
    int node_num=VerNode_List.size();
    vector<VerNode>VerList;
    //把图的所有弧输入进数组中,顺便建立一个生成树的邻接表的顶点节点
    for(i=0; i<node_num; i++)
    {
        for(flx=VerNode_List[i]->First_Edge; flx!=nullptr; flx=flx->next)
        {
            MST_temp.push_back(Line_node(i,flx->Adjvex,flx->weight));
        }
        VerList.push_back(VerNode(VerNode_List[i]->Vervex,nullptr));
    }
    //按照权重大小排序
    sort(MST_temp.begin(),MST_temp.end());
    //从小到大遍历所有的弧
    for(i=0; i<MST_temp.size(); i++)
    {
        Reset_mark();
        flag=false;
        isPath(MST_temp[i].head,MST_temp[i].tail,flag,VerList);
        if(!flag)
        {
            MST_Pointer_Array.push_back(MST_temp[i]);
            int x=MST_temp[i].head;
            int y=MST_temp[i].tail;
            flx = new ArcNode(y,MST_temp[i].weight,VerList[x].First_Edge);
            VerList[x].First_Edge=flx;
            flx=new ArcNode(x,MST_temp[i].weight,VerList[y].First_Edge);
            VerList[y].First_Edge=flx;
        }
    }
    //打印最小生成树
    cout<<"最小生成树——————————Kruskal算法"<<endl;
    for(i=0; i<MST_Pointer_Array.size(); i++)
    {
        cout<<MST_Pointer_Array[i].head<<"————————"<<MST_Pointer_Array[i].tail<<"  权重为："<<MST_Pointer_Array[i].weight<<endl;
    }
    //释放空间
    for(i=0; i<VerList.size(); i++)
    {
        flx=VerList[i].First_Edge;
        while(flx!=nullptr)
        {
            q=flx;
            flx=flx->next;
            delete q;
        }
    }
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
int main()
{
    vector<int>data= {0,1,2,3,4,5};
    Matrix_Data mt1;
    cout<<"创建邻接矩阵"<<endl;
    mt1.Create_Adjacency_Matrix(data,10);
    cout<<endl;
    mt1.Printf_Adjacency_Matrix();
    cout<<endl;
    mt1.Prim_Matrix(0);
    cout<<endl;
    mt1.Reset_mark();
    mt1.Kruskal_Matrix();


    Adjacency_List mt2;
    cout<<"创建邻接表"<<endl;
    mt2.Paint_Exist_In_Adjacency_List(data,10);
    cout<<endl;
    mt2.Print_The_Adjacency_List();
    cout<<endl;
    mt2.Prim_List(0);
    cout<<endl;
    mt2.Reset_mark();
    mt2.Kruskal_List();
    return 0;
}
