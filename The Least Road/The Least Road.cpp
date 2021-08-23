#include<iostream>
#include<vector>
#include<queue>
#include<climits>
using namespace std;
//边表节点
typedef struct ArcNode
{
    int Adjvex;
    ArcNode*next=nullptr;
    int wet;
    ArcNode(int x,ArcNode*p,int y):Adjvex(x),next(p),wet(y) {}
} ArcNode;
//顶点表节点
typedef struct VerNode
{
    int Vervex;
    ArcNode*First_Edge;
    VerNode(int x,ArcNode*p):Vervex(x),First_Edge(p) {}
} VerNode;
class chart
{
private:
    vector<VerNode*>VerNode_List;//存储图的每一个节点数据
    vector<int>Visited_Mark;//存储访问数据的情况

    vector<int>Parent;//存储节点的上一个父亲节点
    vector<int>Distance;//存储源节点到每一个节点的最短距离
public:
    chart() {}
    void make(vector<int>data,int Road_Nums);
    void Print();
    void BFS(int v,int u);//这是一个对无权最短路径计算不完全的算法，很有局限性
    void Reset();
    void Dijkstra(int u);
    void Floyd();
    ~chart();
};
void chart::make(vector<int>data,int Road_Nums)
{
    VerNode*Node_Pointer_temp;
    ArcNode*Arc_Pointer;
    int i,j,k,w;
    int Data_Len=data.size();
    for(i=0; i<Data_Len; i++)
    {
        Node_Pointer_temp=new VerNode(data[i],nullptr);
        VerNode_List.push_back(Node_Pointer_temp);
        Visited_Mark.push_back(0);
        Parent.push_back(-1);
        Distance.push_back(INT_MAX);
    }
    for(k=0; k<Road_Nums; k++)
    {
        cout<<"请输入无向图的路径i——j，以及权重"<<endl;
        cout<<"请输入i:  ";
        cin>>i;
        cout<<endl<<"请输入j:  ";
        cin>>j;
        cout<<endl<<"请输入i——j之间弧的权重";
        cin>>w;
        cout<<endl;
        Arc_Pointer=new ArcNode(j,VerNode_List[i]->First_Edge,w);
        VerNode_List[i]->First_Edge=Arc_Pointer;
        Arc_Pointer=new ArcNode(i,VerNode_List[j]->First_Edge,w);
        VerNode_List[j]->First_Edge=Arc_Pointer;
    }
}
void chart::Print()
{
    ArcNode*s;
    int i;
    for(i=0; i<VerNode_List.size(); i++)
    {
        //cout<<VerNode_List[i]->Vervex;
        s=VerNode_List[i]->First_Edge;
        while(s!=nullptr)
        {
            cout<<" "<<VerNode_List[i]->Vervex<<"——"<<s->Adjvex<<" ";
            s=s->next;
        }
        cout<<endl;
    }
}
chart::~chart()
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
void chart::BFS(int v,int u)//说实话，这段算法其实很有局限性嗷
{
    int node=VerNode_List.size();

    //第一遍遍历时，存储各个节点到v节点的最短路径长度
    vector<int>first(node);
    //v节点到自身的距离为0
    first[v]=0;

    VerNode*t;//定点表指针
    ArcNode*tu;//边表指针
    int idx;//记录相连节点下标

    queue<VerNode*>op;
    int q_len;//队列长度

    Visited_Mark[v]=1;
    op.push(VerNode_List[v]);

    int floor=0;//记录离源点的最小层数

    while(!op.empty())
    {
        q_len=op.size();
        floor++;
        for(int i=0; i<q_len; i++)
        {
            t=op.front();
            op.pop();
            for(tu=t->First_Edge; tu!=nullptr; tu=tu->next)
            {
                idx=tu->Adjvex;
                if(Visited_Mark[idx]!=1)
                {
                    Visited_Mark[idx]=1;
                    first[idx]=floor;
                    op.push(VerNode_List[idx]);
                }
            }
        }
    }

    //第一次层序遍历没有问题
    cout<<endl<<"我先打印一下最短的路径长度："<<first[u]<<endl;


    //重置节点状态
    Reset();
    floor=0;
    //存储最短路径的数组
    vector<int>res;
    res.push_back(u);
    //再从u开始往回遍历
    Visited_Mark[u]=1;
    op.push(VerNode_List[u]);
     while(!op.empty())
    {
        q_len=op.size();
        floor++;
        for(int i=0; i<q_len; i++)
        {
            t=op.front();
            op.pop();
            for(tu=t->First_Edge; tu!=nullptr; tu=tu->next)
            {
                idx=tu->Adjvex;
                if(Visited_Mark[idx]!=1)
                {
                    Visited_Mark[idx]=1;
                    op.push(VerNode_List[idx]);
                    if((first[u]-floor)==first[idx])
                    {
                        res.push_back(idx);
                    }
                }
            }
        }
    }
    cout<<"最短路径"<<endl;
    for(int i=0;i<res.size();i++)
        cout<<res[i]<<" ";
}
void chart::Reset()
{
    int i=0;
    for(i=0; i<Visited_Mark.size(); i++)
    {
        Visited_Mark[i]=0;
        Parent[i]=-1;
        Distance[i]=INT_MAX;
    }
}
void chart::Dijkstra(int u)
{
    int node=Parent.size();//节点数
    queue<VerNode*> s;

    s.push(VerNode_List[u]);
    Parent[u]=-1;
    Distance[u]=0;

    while(!s.empty())
    {
        int idx=s.front()->Vervex;
        Visited_Mark[idx]=1;
        int last=-1;//记录最后要入队的那个节点的下标
        int last_wt=INT_MAX;
        for(ArcNode*p=VerNode_List[idx]->First_Edge;p!=nullptr;p=p->next)
        {
            int pls=p->Adjvex;
            if(Visited_Mark[pls]==0)//没有被访问过
            {
                if(((p->wet)+Distance[idx])<Distance[pls])
                {
                    Distance[pls]=((p->wet)+Distance[idx]);
                    Parent[pls]=idx;
                }
                if((p->wet)<last_wt)
                {
                    last=pls;
                    last_wt=(p->wet);
                }
            }
        }
        if(last!=-1)//如果最终选中的节点下标等于-1，那么说明没有与当前节点相连的节点了
        {
            s.push(VerNode_List[last]);
        }
        s.pop();
    }
    cout<<endl<<"当前的源节点是"<<u<<endl;
    //打印出各个数组存储的数据

    cout<<"Distance数组："<<endl;
    for(int i=0;i<node;i++)
    {
        cout<<Distance[i]<<" ";
    }
    cout<<endl<<"Parent数组："<<endl;
    for(int i=0;i<node;i++)
    {
        cout<<Parent[i]<<" ";
    }
}
void chart::Floyd()
{
    int node=Parent.size();
    //Floyd算法所需数组
    vector<vector<int>>Dist(node,vector<int>(node,INT_MAX-50));//距离数组
    vector<vector<int>>Plain(node,vector<int>(node));//顺序数组

    //初始化顺序数组
    for(int i=0; i<node; i++)
        for(int j=0; j<node; j++)
        {
            if(i==j)
            {
                Plain[i][j]=-1;
            }
            else
            {
                Plain[i][j]=j;
            }
        }

    /*先打印初始化的顺序数组*/
    cout<<"——初始化的顺序数组——"<<endl;
    for(int i=0; i<node; i++)
    {
        for(int j=0; j<node; j++)
            cout<<Plain[i][j]<<"  ";
        cout<<endl;
    }
    //初始化距离数组
    for(int i=0; i<node; i++)
    {
        int x=VerNode_List[i]->Vervex;
        for(ArcNode*p=VerNode_List[i]->First_Edge; p!=nullptr; p=p->next)
        {
            int y=p->Adjvex;
            Dist[x][y]=p->wet;
        }
    }


    //距离数组对角线
    for(int i=0; i<node; i++)
        for(int j=0; j<node; j++)
        {
            if(i==j)
                Dist[i][j]=0;
        }
    /*打印初始化的距离数组*/
    cout<<"——初始化的距离数组——"<<endl;
    for(int i=0; i<node; i++)
    {
        for(int j=0; j<node; j++)
        {
            if(i==j)
            {
                cout<<"-  ";
                continue;
            }
            if(Dist[i][j]==(INT_MAX-50))//
                cout<<"∞"<<"  ";
            else
                cout<<Dist[i][j]<<"  ";
        }
        cout<<endl;
    }

    //三层循环
    for(int k=0; k<node; k++)
    {
        for(int i=0; i<node; i++)
        {
            if(i==k)
                continue;
            for(int j=0; j<node; j++)
            {
                if(j==k)
                    continue;
                if(i==j)
                    continue;

                /*cout<<"Dist["<<i<<"]["<<k<<"]: ";
                if(Dist[i][k]==INT_MAX-50)
                    cout<<"∞"<<"  ";
                else
                    cout<<Dist[i][k]<<"  ";
                cout<<"Dist["<<k<<"]["<<j<<"]:  ";
                if(Dist[k][j]==INT_MAX-50)
                    cout<<"∞"<<"  ";
                else
                    cout<<Dist[k][j]<<"  ";
                cout<<"Dist["<<i<<"]["<<j<<"]:  ";
                if(Dist[i][j]==INT_MAX-50)
                    cout<<"∞"<<"  ";
                else
                    cout<<Dist[i][j]<<"  ";
                    cout<<endl;*/



                if((Dist[i][k]+Dist[k][j])<Dist[i][j]&&(Dist[i][k]!=(INT_MAX-50)&&Dist[k][j]!=(INT_MAX-50)))//
                {
                    Dist[i][j]=(Dist[i][k]+Dist[k][j]);
                    Plain[i][j]=Plain[i][k];
                }
            }
        }
        cout<<"——中间节点为"<<k<<"之后距离矩阵的更新——"<<endl;
        for(int i=0; i<node; i++)
        {
            for(int j=0; j<node; j++)
            {
                if(i==j)
                {
                    cout<<"-  ";
                    continue;
                }
                if(Dist[i][j]==INT_MAX-50)
                    cout<<"∞"<<"  ";
                else
                    cout<<Dist[i][j]<<"  ";
            }
            cout<<endl;
        }

    }

    //打印距离数组
    cout<<"——距离数组——"<<endl;
    for(int i=0; i<node; i++)
    {
        for(int j=0; j<node; j++)
        {
            if(i==j)
            {
                cout<<"-  ";
                continue;
            }
            if(Dist[i][j]==INT_MAX-50)
                cout<<"∞"<<"  ";
            else
                cout<<Dist[i][j]<<"  ";
        }
        cout<<endl;
    }


    //打印顺序数组
    cout<<"——顺序数组——"<<endl;
    for(int i=0; i<node; i++)
    {
        for(int j=0; j<node; j++)
            cout<<Plain[i][j]<<"  ";
        cout<<endl;
    }
}

int main()
{
    vector<int>qaq= {0,1,2,3,4};
    chart wow;
    wow.make(qaq,9);
    wow.Print();
    wow.BFS(0,4);
    wow.Reset();
    wow.Dijkstra(0);
    wow.Floyd();
    return 0;
}
