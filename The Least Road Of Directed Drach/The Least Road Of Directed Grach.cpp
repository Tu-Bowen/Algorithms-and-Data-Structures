//����ͼ
#include<iostream>
#include<vector>
#include<queue>
#include<climits>
using namespace std;
//�߱�ڵ�
typedef struct ArcNode
{
    int Adjvex;
    int wet;
    ArcNode*next=nullptr;
    ArcNode(int x,ArcNode*p,int y):Adjvex(x),next(p),wet(y) {}
} ArcNode;
//�����ڵ�
typedef struct VerNode
{
    int Vervex;
    ArcNode*First_Edge;
    VerNode(int x,ArcNode*p):Vervex(x),First_Edge(p) {}
} VerNode;
class d_chart
{
private:
    vector<VerNode*>VerNode_List;//�ڵ�

    vector<int>Visited_Mark;//���ʼ�¼

    //Dijkstra�㷨��������
    vector<int>Parent;//�洢�ڵ����һ�����׽ڵ�
    vector<int>Distance;//�洢Դ�ڵ㵽ÿһ���ڵ����̾���

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
        cout<<"����������ͼ��·��i����>j,�Լ�����Ȩ��"<<endl;
        cout<<"������i:  ";
        cin>>i;
        cout<<endl<<"������j:  ";
        cin>>j;
        cout<<endl<<"������i->j����Ȩ��";
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
            cout<<" "<<VerNode_List[i]->Vervex<<"����>"<<s->Adjvex<<" ";
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
    int node=Parent.size();//�ڵ���
    queue<VerNode*> s;

    s.push(VerNode_List[u]);
    Parent[u]=-1;
    Distance[u]=0;

    while(!s.empty())
    {
        int idx=s.front()->Vervex;
        //cout<<"��ǰ�ڵ㡪��"<<idx<<endl;
        Visited_Mark[idx]=1;
        int last=-1;//��¼���Ҫ��ӵ��Ǹ��ڵ���±�
        int last_wt=INT_MAX;
        for(ArcNode*p=VerNode_List[idx]->First_Edge; p!=nullptr; p=p->next)
        {
            int pls=p->Adjvex;
            if(Visited_Mark[pls]==0)//û�б����ʹ�
            {
                //cout<<"����ѡ��Ľڵ�****"<<pls<<endl;
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
        //cout<<"����ѡ��Ľڵ�++++"<<last<<endl<<endl;
        if(last!=-1)//�������ѡ�еĽڵ��±����-1����ô˵��û���뵱ǰ�ڵ������Ľڵ���
        {
            s.push(VerNode_List[last]);
        }
        s.pop();
    }
    cout<<endl<<"��ǰ��Դ�ڵ���"<<u<<endl;
    //��ӡ����������洢������

    cout<<"Distance���飺"<<endl;
    for(int i=0; i<node; i++)
    {
        cout<<Distance[i]<<" ";
    }
    cout<<endl<<"Parent���飺"<<endl;
    for(int i=0; i<node; i++)
    {
        cout<<Parent[i]<<" ";
    }
}
void d_chart::Floyd()
{
    int node=Parent.size();
    //Floyd�㷨��������
    vector<vector<int>>Dist(node,vector<int>(node,INT_MAX-50));//��������
    vector<vector<int>>Plain(node,vector<int>(node));//˳������

    //��ʼ��˳������
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

    /*�ȴ�ӡ��ʼ����˳������*/
    cout<<"������ʼ����˳�����顪��"<<endl;
    for(int i=0; i<node; i++)
    {
        for(int j=0; j<node; j++)
            cout<<Plain[i][j]<<"  ";
        cout<<endl;
    }
    //��ʼ����������
    for(int i=0; i<node; i++)
    {
        int x=VerNode_List[i]->Vervex;
        for(ArcNode*p=VerNode_List[i]->First_Edge; p!=nullptr; p=p->next)
        {
            int y=p->Adjvex;
            Dist[x][y]=p->wet;
        }
    }


    //��������Խ���
    for(int i=0; i<node; i++)
        for(int j=0; j<node; j++)
        {
            if(i==j)
                Dist[i][j]=0;
        }
    /*��ӡ��ʼ���ľ�������*/
    cout<<"������ʼ���ľ������顪��"<<endl;
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
                cout<<"��"<<"  ";
            else
                cout<<Dist[i][j]<<"  ";
        }
        cout<<endl;
    }

    //����ѭ��
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
                    cout<<"��"<<"  ";
                else
                    cout<<Dist[i][k]<<"  ";
                cout<<"Dist["<<k<<"]["<<j<<"]:  ";
                if(Dist[k][j]==INT_MAX-50)
                    cout<<"��"<<"  ";
                else
                    cout<<Dist[k][j]<<"  ";
                cout<<"Dist["<<i<<"]["<<j<<"]:  ";
                if(Dist[i][j]==INT_MAX-50)
                    cout<<"��"<<"  ";
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
        cout<<"�����м�ڵ�Ϊ"<<k<<"֮��������ĸ��¡���"<<endl;
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
                    cout<<"��"<<"  ";
                else
                    cout<<Dist[i][j]<<"  ";
            }
            cout<<endl;
        }

    }

    //��ӡ��������
    cout<<"�����������顪��"<<endl;
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
                cout<<"��"<<"  ";
            else
                cout<<Dist[i][j]<<"  ";
        }
        cout<<endl;
    }


    //��ӡ˳������
    cout<<"����˳�����顪��"<<endl;
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
