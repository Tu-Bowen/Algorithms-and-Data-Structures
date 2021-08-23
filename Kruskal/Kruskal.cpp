#include<iostream>
#include<vector>
#include<climits>
#include<cstdbool>
#include<algorithm>
using namespace std;
//���鼯
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



//�洢������Ϣ
typedef struct Line_node
{
    int head;
    int tail;
    int weight;
    Line_node(int x,int y,int z):head(x),tail(y),weight(z) {}
    bool operator<(const Line_node&s)
    {
        return weight<s.weight;
    }

} Line_node;
//�߱�ڵ�
typedef struct ArcNode

{
    int Adjvex;
    int weight;
    ArcNode*next=nullptr;
    ArcNode(int x,int y,ArcNode*p):Adjvex(x),weight(y),next(p) {}

} ArcNode;
//�����ڵ�
typedef struct VerNode

{
    int Vervex;
    ArcNode*First_Edge;
    VerNode(int x,ArcNode*p):Vervex(x),First_Edge(p) {}
} VerNode;
class adjlist
{
private:
    vector<VerNode*>VerNode_List;
public:
    adjlist() {}
    void create(const vector<int>data,const int Road_Nums);
    void output();
    ~adjlist();
    void Kruskal();
};
//�����ڽӱ�
void adjlist::create(const vector<int>data,const int Road_Nums)
{
    VerNode*Node_Pointer_temp;
    ArcNode*Arc_Pointer;
    int i,j,k,weight;
    int Data_Len=data.size();
    cout<<"������"<<Road_Nums<<"����,�Լ�����Ȩ��"<<endl;
    for(i=0; i<Data_Len; i++)
    {
        Node_Pointer_temp=new VerNode(data[i],nullptr);
        VerNode_List.push_back(Node_Pointer_temp);
    }
    for(k=0; k<Road_Nums; k++)
    {
        cout<<"�����뻡�����˽ڵ�"<<endl;
        cin>>i;
        cin>>j;
        cout<<"�����뻡��Ȩ�أ�"<<endl;
        cin>>weight;
        //���õ��Ļ����ظ��������������麯��������ų�
        Arc_Pointer=new ArcNode(j,weight,VerNode_List[i]->First_Edge);
        VerNode_List[i]->First_Edge=Arc_Pointer;
        Arc_Pointer=new ArcNode(i,weight,VerNode_List[j]->First_Edge);
        VerNode_List[j]->First_Edge=Arc_Pointer;
    }
}
//��ӡ�ڽӱ�
void adjlist::output()
{
    ArcNode*s;
    int i;
    for(i=0; i<VerNode_List.size(); i++)
    {
        cout<<VerNode_List[i]->Vervex;
        s=VerNode_List[i]->First_Edge;
        while(s!=nullptr)
        {
            cout<<"������������"<<s->Adjvex;
            s=s->next;
        }
        cout<<endl;
    }
}

void adjlist::Kruskal()
{
    int i;
    vector<Line_node>MST_temp;//�洢ͼ���л�����Ϣ������Ƚϻ�֮���Ȩ�ش�С
    vector<Line_node>MST_Pointer_Array;//�洢������ÿһ�����ڵ����Ϣ
    int node_num=VerNode_List.size();//�ڵ�����
    union_set us(node_num);
    ArcNode*f;
    //��ͼ�����л������������,˳�㽨��һ�����������ڽӱ�Ķ���ڵ�
    for(i=0; i<node_num; i++)
    {
        for(f=VerNode_List[i]->First_Edge; f!=nullptr; f=f->next)
        {
            MST_temp.push_back(Line_node(i,f->Adjvex,f->weight));
        }
    }
    //����Ȩ�ش�С����
    sort(MST_temp.begin(),MST_temp.end());
    //����Ȩ�ش�С���������
    for(i=0;i<MST_temp.size();i++)
    {
        int o1=MST_temp[i].head;
        int o2=MST_temp[i].tail;
        if(us.find_parents(o1)==us.find_parents(o2))
            continue;
        MST_Pointer_Array.push_back(Line_node(o1,o2,MST_temp[i].weight));
        us.make_union(o1,o2);
    }
    //��ӡ��С������
    cout<<"��С��������������������������Kruskal�㷨"<<endl;
    for(i=0; i<MST_Pointer_Array.size(); i++)
    {
        cout<<MST_Pointer_Array[i].head<<"����������������"<<MST_Pointer_Array[i].tail<<"  Ȩ��Ϊ��"<<MST_Pointer_Array[i].weight<<endl;
    }
}
//�ͷſռ�
adjlist::~adjlist()

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
    adjlist mt2;
    cout<<"�����ڽӱ�"<<endl;
    mt2.create(data,10);
    cout<<endl;
    mt2.output();
    cout<<endl;
    mt2.Kruskal();
    return 0;
}
