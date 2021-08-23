#include<iostream>
#include<vector>
#include<cstdbool>
#include<stack>
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


typedef struct ArcNode
{
    int Adjvex;
    ArcNode*next=nullptr;
    ArcNode(int x,ArcNode*p):Adjvex(x),next(p) {}
} ArcNode;
//�����ڵ�
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
    vector<int>color;//�ڵ����ɫ��ǣ�-1����û�з��ʣ�0�������ڷ��ʣ�1������ʽ���
    int line;//���ĸ���
    int node;//�ڵ�ĸ���
public:
    Adjacency_List() {}
    void create(const vector<int>data,const int Road_Nums);
    void output();
    void Reset_mark();
    bool Cycle_or_not();//��֦���жϴ�����ͼ�Ƿ��л��ɹ�
    //void DFS_Cycle(bool&flag,const int u);//������ȱ����ж�����ͼ�Ƿ��л������������ɣ��޷�ʵ��
    //bool use_unionset_cycle_or_not();//ʹ�ò��鼯�ж�����ͼ�Ƿ��л���������ͬ�����ɣ��޷�ʵ��
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
    cout<<"������"<<Road_Nums<<"����,�Լ�����Ȩ��"<<endl;
    for(i=0; i<Data_Len; i++)
    {
        Node_Pointer_temp=new VerNode(data[i],nullptr,0);
        VerNode_List.push_back(Node_Pointer_temp);
        Visited_Mark.push_back(0);
        color.push_back(-1);
    }
    for(k=0; k<Road_Nums; k++)
    {
        cout<<"�����뻡�����˽ڵ�"<<endl;
        cin>>i;
        cin>>j;
        //���õ��Ļ����ظ��������������麯��������ų�
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
        cout<<" ��ǰ�ڵ�Ķ��� "<<VerNode_List[i]->du<<" ";
        s=VerNode_List[i]->First_Edge;
        while(s!=nullptr)
        {
            cout<<"������������"<<s->Adjvex;
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
    if(line>=node)//����ͼ��֪ʶ��������ĸ������ڽڵ�ĸ�������ô��ͼһ���л�
        return true;
    int i,idx,num=0;
    int k;
    ArcNode*p;
    for(i=0; i<node; i++)
    {
        if(VerNode_List[i]->du<2)//�����еĶ�С��2�Ľڵ���ջ����Ϊ�ڻ��е�
            s.push(i);
    }
    //����������ѭ���У�����ͼ�л�·�ļ����ڵ��޷�����ջ������num���С�ڽڵ�����˵���л�·
    while(!s.empty())
    {
        idx=s.top();
        s.pop();
        Visited_Mark[idx]=1;//��ջ�е���һ���ڵ㣬�Ͱ�����ڵ������Χ�Ļ�ɾ�ˣ�����������ɾ��
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
    AL.Reset_mark();//���ýڵ�ķ���״̬
    //Ŀǰ�޷�ʹ��DFS�жϻ�·
    //bool flag=false;
    //AL.DFS_Cycle(flag,0);
    //cout<<endl<<flag<<endl;
    //�����ˣ�DFS���㷨�жϻ�·�Ͳ��鼯�㷨�жϻ�·������������
    //cout<<endl<<AL.use_unionset_cycle_or_not()<<endl;
    return 0;
}
