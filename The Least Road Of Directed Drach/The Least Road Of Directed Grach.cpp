//有向图
#include<iostream>
#include<vector>
#include<queue>
#include<climits>
using namespace std;
//边表节点
typedef struct ArcNode
{
    int Adjvex;
    int wet;
    ArcNode*next=nullptr;
    ArcNode(int x,ArcNode*p,int y):Adjvex(x),next(p),wet(y) {}
} ArcNode;
//顶点表节点
typedef struct VerNode
{
    int Vervex;
    ArcNode*First_Edge;
    VerNode(int x,ArcNode*p):Vervex(x),First_Edge(p) {}
} VerNode;
class d_chart
{
private:
    vector<VerNode*>VerNode_List;//节点

    vector<int>Visited_Mark;//访问记录

    //Dijkstra算法所需数组
    vector<int>Parent;//存储节点的上一个父亲节点
    vector<int>Distance;//存储源节点到每一个节点的最短距离

public:
    d_chart() {}
    void make(vector<int>data,int Road_Nums);
    void Print();
    void Reset();
    void Dijkstra(int u);
    void Floyd();
    ~d_chart();
};
void d_chart::make(vector<int>data,int Road_Nums)
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
        cout<<"请输入有向图的路径i——>j,以及弧的权重"<<endl;
        cout<<"请输入i:  ";
        cin>>i;
        cout<<endl<<"请输入j:  ";
        cin>>j;
        cout<<endl<<"请输入i->j弧的权重";
        cin>>w;
        cout<<endl;
        Arc_Pointer=new ArcNode(j,VerNode_List[i]->First_Edge,w);
        VerNode_List[i]->First_Edge=Arc_Pointer;
    }
}
void d_chart::Print()
{
    ArcNode*s;
    int i;
    for(i=0; i<VerNode_List.size(); i++)
    {
        //cout<<VerNode_List[i]->Vervex;
        s=VerNode_List[i]->First_Edge;
        while(s!=nullptr)
        {
            cout<<" "<<VerNode_List[i]->Vervex<<"——>"<<s->Adjvex<<" ";
            s=s->next;
        }
        cout<<endl;
    }
}
d_chart::~d_chart()
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
void d_chart::Reset()
{
    int i=0;
    for(i=0; i<Visited_Mark.size(); i++)
    {
        Visited_Mark[i]=0;
        Parent[i]=-1;
        Distance[i]=INT_MAX;
    }
}
void d_chart::Dijkstra(int u)
{
    int node=Parent.size();//节点数
    queue<VerNode*> s;

    s.push(VerNode_List[u]);
    Parent[u]=-1;
    Distance[u]=0;

    while(!s.empty())
    {
        int idx=s.front()->Vervex;
        //cout<<"当前节点——"<<idx<<endl;
        Visited_Mark[idx]=1;
        int last=-1;//记录最后要入队的那个节点的下标
        int last_wt=INT_MAX;
        for(ArcNode*p=VerNode_List[idx]->First_Edge; p!=nullptr; p=p->next)
        {
            int pls=p->Adjvex;
            if(Visited_Mark[pls]==0)//没有被访问过
            {
                //cout<<"可以选择的节点****"<<pls<<endl;
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
        //cout<<"最终选择的节点++++"<<last<<endl<<endl;
        if(last!=-1)//如果最终选中的节点下标等于-1，那么说明没有与当前节点相连的节点了
        {
            s.push(VerNode_List[last]);
        }
        s.pop();
    }
    cout<<endl<<"当前的源节点是"<<u<<endl;
    //打印出各个数组存储的数据

    cout<<"Distance数组："<<endl;
    for(int i=0; i<node; i++)
    {
        cout<<Distance[i]<<" ";
    }
    cout<<endl<<"Parent数组："<<endl;
    for(int i=0; i<node; i++)
    {
        cout<<Parent[i]<<" ";
    }
}
void d_chart::Floyd()
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
    vector<int> p= {0,1,2,3,4};
    d_chart cool;
    cool.make(p,9);
    cool.Print();
    cool.Dijkstra(0);
    cool.Reset();
    cool.Floyd();
    return 0;
}
