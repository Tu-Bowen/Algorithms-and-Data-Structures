/*//������
#include<iostream>
#include<queue>
#include<stack>
using namespace std;
//�������ڵ㣨������Ȼ���������ݣ�
//�������ڵ�
typedef struct TreeNode_th
{
    int data;//������
    TreeNode_th*leftchild;//����
    TreeNode_th*rightchild;//�Һ���
    TreeNode_th*parents;//��ĸ�ڵ�
    TreeNode_th(int x):data(x){};//������ֵ
}TreeNode_th;
//�������ڵ�
typedef struct TreeNode
{
    int data;//������
    TreeNode*leftchild;//����
    TreeNode*rightchild;//�Һ���
    TreeNode(int x):data(x){};//������ֵ
}TreeNode;
class Tree
{
public:
    //���ĵݹ����
    TreeNode*RQA_CreateTree_Two(TreeNode*op);//�ݹ鴴��������������������
    void RQA_PreOrder(TreeNode*op);//�ݹ�ǰ��������������
    void RQA_InOrder(TreeNode*op);//�ݹ�����������������
    void RQA_PostOrder(TreeNode*op);//�ݹ�����������������
    int LeavesNums(TreeNode*op);//�ݹ������������Ҷ�ӽڵ�
    int AllNums(TreeNode*op);//�ݹ�����������нڵ�
    int TreeDepth(TreeNode*op);//�ݹ�����������
    void CopyTree(TreeNode*op1,TreeNode*op2);//�ݹ鸴��һ�ö�����
    TreeNode*SwapLRTree(TreeNode*op1,TreeNode*op2);//�ݹ龵��������������ؽ���������������������������Ķ�����,ԭ���ṹ����
    int CountK(TreeNode*op,int k);//�ݹ�����������ֵ��k�Ľڵ�ĸ���
    void ReleaseTree(TreeNode*op);//�ݹ�ɾ��������
    TreeNode* ParentNode(TreeNode*op,int k);//�ݹ�Ѱ�Ҷ�����������һ���ڵ�ĸ��ڵ�
    TreeNode*InExchangeTree(TreeNode*op);//�ݹ龵��������������ؽ���������������������������Ķ�����,ԭ���ṹ�ı�
    void DeletexTree(TreeNode*op,int x);//�ݹ�ɾ��������xΪ���ڵ����
    int*TranstoArray(TreeNode*op,int*res,int index);//�ݹ�Ѷ�����תΪ��̬����˳�򴢴�
    //���ķǵݹ����
    void PreOrder(TreeNode*op);//�ǵݹ�ǰ��������������
    void InOrder(TreeNode*op);//�ǵݹ�����������������
    void PostOrder(TreeNode*op);//�ǵݹ�����������������
    void Queue_LeverOrder(TreeNode*op);//���в���������������
    void SwapTree(TreeNode*op1,TreeNode*op2);//�ǵݹ�Ľ������ö������е�����
};
//�ݹ顪������������������������
TreeNode*Tree::RQA_CreateTree_Two(TreeNode*op)
{
    int Ai;
    cin>>Ai;
    if(Ai<0)
        op=nullptr;
    op=new TreeNode(Ai);
    op->leftchild=RQA_CreateTree_Two(op->leftchild);
    op->rightchild=RQA_CreateTree_Two(op->rightchild);
    return op;
}
//�ݹ顪��ǰ��
void Tree::RQA_PreOrder(TreeNode*op)
{
    if(op==nullptr)
        return;
    cout<<op->data;
    RQA_PreOrder(op->leftchild);
    RQA_PreOrder(op->rightchild);
}
//�ݹ顪������
void Tree::RQA_InOrder(TreeNode*op)
{
    if(op==nullptr)
        return;
    RQA_InOrder(op->leftchild);
    cout<<op->data;
    RQA_InOrder(op->rightchild);
}
//�ݹ顪������
void Tree::RQA_PostOrder(TreeNode*op)
{
    if(op==nullptr)
        return ;
    RQA_PostOrder(op->leftchild);
    RQA_PostOrder(op->rightchild);
    cout<<op->data;
}
//���С�������
void Tree::Queue_LeverOrder(TreeNode*op)
{
    queue<TreeNode*>oop;
    TreeNode*front_q;
    oop.push(op);
    while(!oop.empty())
    {
        front_q=oop.front();
        oop.pop();
        if(front_q->leftchild!=nullptr)
            oop.push(front_q->leftchild);
        if(front_q->rightchild!=nullptr)
            oop.push(front_q->rightchild);
        cout<<front_q->data;
    }
}
//�ǵݹ顪��ǰ�򡪡�ջ
void Tree::PreOrder(TreeNode*op)
{
     stack<TreeNode*> s;
     TreeNode*cur,*top;
     cur=op;
     while(cur!=nullptr||!s.empty())
     {
         while(cur!=nullptr)
         {
             cout<<cur->data;
             s.push(cur);
             cur=cur->leftchild;
         }
         top=s.top();
         s.pop();
         cur=top->rightchild;
     }
}
//�ǵݹ顪�����򡪡�ջ
void Tree::InOrder(TreeNode*op)
{
    stack<TreeNode*>s;
    TreeNode*cur,*top;
    cur=op;
    while(cur!=nullptr||!s.empty())
    {
        while(cur!=nullptr)
        {
            s.push(cur);
            cur=cur->leftchild;
        }
        top=s.top();
        s.pop();
        cout<<top->data;
        cur=top->rightchild;
    }
}
//�ǵݹ顪�����򡪡�ջ
void Tree::PostOrder(TreeNode*op)
{
    stack<TreeNode*>s;
    TreeNode*cur,*top;
    TreeNode*last=nullptr;
    cur=op;
    while(cur!=nullptr||s.empty())
    {
        while(cur!=nullptr)
        {
            s.push(cur);
            cur=cur->leftchild;
        }
        top=s.top();
        if(top->rightchild==nullptr||top->rightchild==last)//����ýڵ�������������ڣ����߸ýڵ��������Ѿ�����������
        {
            s.pop();//�����ýڵ�
            cout<<top->data;//����ڵ�
            last=top;//��¼����ڵ��Ѿ�����������
        }
        else
        {
            cur=top->rightchild;
        }
    }
}
//����Ҷ�ӽڵ�ĸ��������ݹ�
int Tree::LeavesNums(TreeNode*op)
{
    if(op==nullptr)
        return 0;
    if(op->leftchild==nullptr&&op->rightchild==nullptr)
        return 1;
    int num_left=0,num_right=0;
    num_left=LeavesNums(op->leftchild);
    num_right=LeavesNums(op->rightchild);
    return (num_left+num_right);
}
//���Ľڵ�����������ݹ�
int Tree::AllNums(TreeNode*op)
{
    if(op==nullptr)
        return 0;
    return AllNums(op->leftchild)+AllNums(op->rightchild)+1;
}
//������ȡ����ݹ�
int Tree::TreeDepth(TreeNode*op)
{
    if(op==nullptr)
        return 0;
    int left_depth=TreeDepth(op->leftchild);//�������������
    int right_depth=TreeDepth(op->rightchild);//�������������
    //ȡ������������Ƚϴ����һ������
    if(left_depth>right_depth)
        return left_depth+1;//���ϸ��ڵ�����
    else
        return right_depth+1;
}
//k�Ľڵ�ĸ��������ݹ�
int Tree::CountK(TreeNode*op,int k)
{
    if(op==nullptr)
        return 0;
    if(op->data==k)
        return(CountK(op->leftchild,k)+CountK(op->rightchild,k)+1);
    return(CountK(op->leftchild,k)+CountK(op->rightchild,k));
}
//����һ�ö����������ݹ顪����op1���Ƶ�op2��
void Tree::CopyTree(TreeNode*op1,TreeNode*op2)
{
    if(op1==nullptr)
        op2=nullptr;
    //op2->data=op1->data;//ע�������ﲻ��op2����ڵ�ռ��ǲ��еģ�������Ļ��ͻ��޷�ʹ��data��leftchild��rightchild�Ƚڵ�Ԫ��
    op2=new TreeNode(op1->data);
    CopyTree(op1->leftchild,op2->leftchild);
    CopyTree(op1->rightchild,op2->rightchild);
}
//��������������ݹ顪��op2��op1����֮�����
TreeNode* Tree::SwapLRTree(TreeNode*op1,TreeNode*op2)
{
    if(op1==nullptr)
        return nullptr;
    op2=new TreeNode(op1->data);
    SwapLRTree(op1->leftchild,op2->rightchild);//op1����������op2��������
    SwapLRTree(op1->rightchild,op2->leftchild);//op1����������op2��������
}
//ɾ�������������ݹ�
void Tree::ReleaseTree(TreeNode*op)
{
    if(op==nullptr)
        return;//�ݹ���ֹ����
    ReleaseTree(op->leftchild);
    ReleaseTree(op->rightchild);
    delete op;
}
//Ѱ������һ���ڵ�ĸ��ڵ�,Ѱ��ֵΪk�Ľڵ�ĸ��ڵ�
TreeNode* Tree::ParentNode(TreeNode*op,int k)
{
    if(op==nullptr)
        return nullptr;
    if(op->data==k)//������ڵ��ֵ��k
        return nullptr;
    if((op->leftchild!=nullptr&&op->leftchild->data==k)||(op->rightchild!=nullptr&&op->rightchild->data))//����ҵ���һ�����Һ�������kֵ�ģ����ص�ǰ�ڵ�
        return op;
    TreeNode*res=nullptr;
    res=ParentNode(op->leftchild,k);
    res=ParentNode(op->rightchild,k);
    return res;//������˳�������������k��ĸ�ڵ�Ϊ���ȷ��أ�������������˶�û���ҵ���ֱ�ӷ���һ����ָ��
}
//����������������ݹ�
TreeNode* Tree::InExchangeTree(TreeNode*op)
{
    if(op==nullptr)
        return nullptr;
    TreeNode*temp;
    temp=op->leftchild;
    op->leftchild=op->rightchild;
    op->rightchild=temp;
    if(op->leftchild!=nullptr)
        InExchangeTree(op->leftchild);
    if(op->rightchild)
        InExchangeTree(op->rightchild);
    return op;
}
//ɾ����xΪ���ڵ���������ݹ�
void Tree::DeletexTree(TreeNode*op,int x)
{
    if(op==nullptr)
        return ;
    if(op->data==x)
    {
        ReleaseTree(op);
        op=nullptr;
    }
    //�����㷨˳���֪�����������������������xΪ���ڵ����ɾ��
    DeletexTree(op->leftchild,x);
    DeletexTree(op->rightchild,x);
}
//�Ѷ�����תΪ��̬����˳�򴢴桪���ݹ顪����Ȼ����ʹ��vector����
int* Tree::TranstoArray(TreeNode*op,int*res,int index)
{
    if(op==nullptr)
        return nullptr;
    res[index]=op->data;
    index++;
    TranstoArray(op->leftchild,res,index);
    TranstoArray(op->rightchild,res,index);
    return res;
    //�Ĵ��ɻ�
    /*if(op!=nullptr)
    {
        res[index]=op->data;
        TranstoArray(op->leftchild,res,2*index);
        TranstoArray(op->rightchild,res,2*index+1);
    }
    else
    {
        A[index]=-1;//���Ϊ�սڵ㣡
    }
    return res;*/
/*}
//�������ö������е����ݡ��������Ѷ���ĺ��������ǵݹ飨ע��һ�°������Ժ���ʱ��Ҫ�޸İ�������������
void Tree::SwapTree(TreeNode*op1,TreeNode*op2)
{
    TreeNode*temp;

    CopyTree(op1,temp);
    ReleaseTree(op1);

    CopyTree(op2,op1);
    ReleaseTree(op2);

    CopyTree(temp,op2);
    ReleaseTree(temp);
}
int main()
{
    return 0;
}
