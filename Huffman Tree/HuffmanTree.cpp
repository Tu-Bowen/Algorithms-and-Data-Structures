/*数组形式的哈夫曼树*/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
typedef struct HuffmanTree
{
    int weight;//当前节点的权值
    int parents;//双亲结点
    int lchild;//左孩子
    int rchild;//右孩子

}HuffmanTree;
typedef struct Hufman_Search_Index
{
    int index;
    int val;
    inline bool operator <(const Hufman_Search_Index &other)
    {
        return val<other.val;
    }
}Hufman_Search_Index;
vector<int> Select_Two_Lower_index(vector<HuffmanTree>&op,int len,int Serch_len)
{
    int i;
    Hufman_Search_Index ft[Serch_len];
    vector<int>ans(2);
    int idx=0;
    for(i=0;i<len;i++)
    {
        if(op[i].parents==-1)
        {
            ft[idx]={i,op[i].weight};
            idx++;
        }
    }
    sort(ft,ft+Serch_len);
    ans[0]=ft[0].index;
    ans[1]=ft[1].index;
    return ans;
}
void Creat_Node_Array(vector<HuffmanTree>&op,vector<int>&ts)
{
    int i;
    int n=ts.size();
    int Serch_len=n;
    for(i=0;i<2*n-1;i++)
    {
        op[i].parents=-1;
        op[i].lchild=-1;
        op[i].rchild=-1;
    }
    for(i=0;i<n;i++)
    {
        op[i].weight=ts[i];
    }
    int s1,s2;
    for(i=n;i<2*n-1;i++)
    {
        vector<int>temp=Select_Two_Lower_index(op,i,Serch_len);
        Serch_len--;
        s1=temp[0];
        s2=temp[1];
        op[i].weight=op[s1].weight+op[s2].weight;
        op[s1].parents=i;
        op[s2].parents=i;
        op[i].lchild=s1;
        op[i].rchild=s2;
    }
}
void Huf_Tree_Print(vector<HuffmanTree>&op)
{
    int i;
    int n=op.size();
    cout<<"index weight parent lchild rchild"<<endl;
    for(i=0;i<n;i++)
    {
        cout<<"  "<<i<<"   ";
        cout<<"  "<<op[i].weight<<"   ";
        cout<<"  "<<op[i].parents<<"   ";
        cout<<"   "<<op[i].lchild<<"   ";
        cout<<"  "<<op[i].rchild<<endl;
    }
}
int main()
{
    vector<int>Ts_Array={2,4,5,3};
    int n=Ts_Array.size();
    vector<HuffmanTree>Op_Array(2*n-1);
    Creat_Node_Array(Op_Array,Ts_Array);
    Huf_Tree_Print(Op_Array);
    return 0;
}
