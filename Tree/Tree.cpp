/*//二叉树
#include<iostream>
#include<queue>
#include<stack>
using namespace std;
//二叉树节点（储存自然数整形数据）
//三叉链节点
typedef struct TreeNode_th
{
    int data;//数据域
    TreeNode_th*leftchild;//左孩子
    TreeNode_th*rightchild;//右孩子
    TreeNode_th*parents;//父母节点
    TreeNode_th(int x):data(x){};//数据域赋值
}TreeNode_th;
//二叉链节点
typedef struct TreeNode
{
    int data;//数据域
    TreeNode*leftchild;//左孩子
    TreeNode*rightchild;//右孩子
    TreeNode(int x):data(x){};//数据域赋值
}TreeNode;
class Tree
{
public:
    //树的递归操作
    TreeNode*RQA_CreateTree_Two(TreeNode*op);//递归创建二叉树——二叉链表
    void RQA_PreOrder(TreeNode*op);//递归前序遍历输出二叉树
    void RQA_InOrder(TreeNode*op);//递归中序遍历输出二叉树
    void RQA_PostOrder(TreeNode*op);//递归后续遍历输出二叉树
    int LeavesNums(TreeNode*op);//递归计算树的所有叶子节点
    int AllNums(TreeNode*op);//递归计算树的所有节点
    int TreeDepth(TreeNode*op);//递归计算树的深度
    void CopyTree(TreeNode*op1,TreeNode*op2);//递归复制一棵二叉树
    TreeNode*SwapLRTree(TreeNode*op1,TreeNode*op2);//递归镜像二叉树——返回交换二叉树的左子树和右子树后的二叉树,原树结构不变
    int CountK(TreeNode*op,int k);//递归计算二叉树中值是k的节点的个数
    void ReleaseTree(TreeNode*op);//递归删除二叉树
    TreeNode* ParentNode(TreeNode*op,int k);//递归寻找二叉树的任意一个节点的父节点
    TreeNode*InExchangeTree(TreeNode*op);//递归镜像二叉树——返回交换二叉树的左子树和右子树后的二叉树,原树结构改变
    void DeletexTree(TreeNode*op,int x);//递归删除以数据x为根节点的树
    int*TranstoArray(TreeNode*op,int*res,int index);//递归把二叉树转为静态数组顺序储存
    //树的非递归操作
    void PreOrder(TreeNode*op);//非递归前序遍历输出二叉树
    void InOrder(TreeNode*op);//非递归中序遍历输出二叉树
    void PostOrder(TreeNode*op);//非递归后续遍历输出二叉树
    void Queue_LeverOrder(TreeNode*op);//队列层序遍历输出二叉树
    void SwapTree(TreeNode*op1,TreeNode*op2);//非递归的交换两棵二叉树中的内容
};
//递归——创建二叉树——二叉链表
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
//递归——前序
void Tree::RQA_PreOrder(TreeNode*op)
{
    if(op==nullptr)
        return;
    cout<<op->data;
    RQA_PreOrder(op->leftchild);
    RQA_PreOrder(op->rightchild);
}
//递归——中序
void Tree::RQA_InOrder(TreeNode*op)
{
    if(op==nullptr)
        return;
    RQA_InOrder(op->leftchild);
    cout<<op->data;
    RQA_InOrder(op->rightchild);
}
//递归——后序
void Tree::RQA_PostOrder(TreeNode*op)
{
    if(op==nullptr)
        return ;
    RQA_PostOrder(op->leftchild);
    RQA_PostOrder(op->rightchild);
    cout<<op->data;
}
//队列——层序
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
//非递归——前序——栈
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
//非递归——中序——栈
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
//非递归——后序——栈
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
        if(top->rightchild==nullptr||top->rightchild==last)//如果该节点的右子树不存在，或者该节点右子树已经被遍历过了
        {
            s.pop();//弹出该节点
            cout<<top->data;//输出节点
            last=top;//记录这个节点已经被遍历过了
        }
        else
        {
            cur=top->rightchild;
        }
    }
}
//树的叶子节点的个数——递归
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
//树的节点的总数——递归
int Tree::AllNums(TreeNode*op)
{
    if(op==nullptr)
        return 0;
    return AllNums(op->leftchild)+AllNums(op->rightchild)+1;
}
//树的深度——递归
int Tree::TreeDepth(TreeNode*op)
{
    if(op==nullptr)
        return 0;
    int left_depth=TreeDepth(op->leftchild);//求左子树的深度
    int right_depth=TreeDepth(op->rightchild);//求右子树的深度
    //取两棵子树中深度较大的那一棵子树
    if(left_depth>right_depth)
        return left_depth+1;//加上根节点的深度
    else
        return right_depth+1;
}
//k的节点的个数——递归
int Tree::CountK(TreeNode*op,int k)
{
    if(op==nullptr)
        return 0;
    if(op->data==k)
        return(CountK(op->leftchild,k)+CountK(op->rightchild,k)+1);
    return(CountK(op->leftchild,k)+CountK(op->rightchild,k));
}
//复制一棵二叉树——递归——把op1复制到op2中
void Tree::CopyTree(TreeNode*op1,TreeNode*op2)
{
    if(op1==nullptr)
        op2=nullptr;
    //op2->data=op1->data;//注意在这里不给op2申请节点空间是不行的，不申请的话就会无法使用data，leftchild，rightchild等节点元素
    op2=new TreeNode(op1->data);
    CopyTree(op1->leftchild,op2->leftchild);
    CopyTree(op1->rightchild,op2->rightchild);
}
//镜像二叉树——递归——op2是op1镜像之后的树
TreeNode* Tree::SwapLRTree(TreeNode*op1,TreeNode*op2)
{
    if(op1==nullptr)
        return nullptr;
    op2=new TreeNode(op1->data);
    SwapLRTree(op1->leftchild,op2->rightchild);//op1的左子树是op2的右子树
    SwapLRTree(op1->rightchild,op2->leftchild);//op1的右子树是op2的左子树
}
//删除二叉树——递归
void Tree::ReleaseTree(TreeNode*op)
{
    if(op==nullptr)
        return;//递归终止条件
    ReleaseTree(op->leftchild);
    ReleaseTree(op->rightchild);
    delete op;
}
//寻找任意一个节点的父节点,寻找值为k的节点的父节点
TreeNode* Tree::ParentNode(TreeNode*op,int k)
{
    if(op==nullptr)
        return nullptr;
    if(op->data==k)//如果根节点的值是k
        return nullptr;
    if((op->leftchild!=nullptr&&op->leftchild->data==k)||(op->rightchild!=nullptr&&op->rightchild->data))//如果找到了一个左右孩子中有k值的，返回当前节点
        return op;
    TreeNode*res=nullptr;
    res=ParentNode(op->leftchild,k);
    res=ParentNode(op->rightchild,k);
    return res;//这样的顺序会以右子树的k父母节点为优先返回，如果遍历树玩了都没有找到就直接返回一个空指针
}
//自身镜像二叉树——递归
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
//删除以x为根节点的树——递归
void Tree::DeletexTree(TreeNode*op,int x)
{
    if(op==nullptr)
        return ;
    if(op->data==x)
    {
        ReleaseTree(op);
        op=nullptr;
    }
    //根据算法顺序可知，这样会把左右子树所有以x为根节点的树删除
    DeletexTree(op->leftchild,x);
    DeletexTree(op->rightchild,x);
}
//把二叉树转为静态数组顺序储存——递归——显然这里使用vector更好
int* Tree::TranstoArray(TreeNode*op,int*res,int index)
{
    if(op==nullptr)
        return nullptr;
    res[index]=op->data;
    index++;
    TranstoArray(op->leftchild,res,index);
    TranstoArray(op->rightchild,res,index);
    return res;
    //心存疑惑
    /*if(op!=nullptr)
    {
        res[index]=op->data;
        TranstoArray(op->leftchild,res,2*index);
        TranstoArray(op->rightchild,res,2*index+1);
    }
    else
    {
        A[index]=-1;//标记为空节点！
    }
    return res;*/
/*}
//交换两棵二叉树中的内容——调用已定义的函数——非递归（注意一下啊！！以后有时间要修改啊！！！！！）
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
