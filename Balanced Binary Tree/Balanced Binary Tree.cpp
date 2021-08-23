#include<iostream>
#include<cstdlib>
#include<vector>
using namespace std;
typedef struct tree
{
    int data;
    int height;
    tree*left;
    tree*right;
} tree;
class AVL
{
private:
    tree*root;
    tree*find(int x,tree*p);//查找算法
    tree*findmax(tree*p);//树中最大值
    tree*findmin(tree*p);//树中最小值
    void perish(tree*p);//销毁二叉树
    void midLook(tree*p);//中序遍历
    void frontLook(tree*p);//前序遍历
    int getBalance(tree*p);//获取节点的平衡度
    int HeightofTree(tree*p);//计算一棵树的高度
    tree*SingleRotate_LL(tree*p2);//LL类型的单向旋转
    tree*SingleRotate_RR(tree*p2);//RR类型的单向旋转
    tree*DoubleRotate_LR(tree*p);//LR类型的双向旋转
    tree*DoubleRotate_RL(tree*p);//RL类型的双向旋转
    tree*create(vector<int>&data,tree*p);//创建二叉树
    tree*insert(int x,tree*p);//插入算法
    tree*Delete(int x,tree*p);//删除算法
public:
    AVL(vector<int > & data);
    void Look();
    void search(int x);
    void Extremum();
    void add(int x);
    void sub(int x);
    ~AVL();
};
AVL::AVL(vector<int>&data)
{
    root=nullptr;
    root=create(data,root);
}
void AVL::Look()
{
    cout<<"当前树的中序遍历：";
    midLook(root);
    cout<<endl;
    cout<<"当前树的前序遍历：";
    frontLook(root);
}
void AVL::search(int x)
{
    tree*dd=find(x,root);
    if(dd!=nullptr)
    {
        cout<<"已经搜索到目标值!"<<endl;
        cout<<"目标值："<<dd->data<<endl;
    }
    else
    {
        cout<<"目标值不在树中！"<<endl;
    }
}
void AVL::Extremum()
{
    tree*dd=findmax(root);
    cout<<"当前树中的最大值：";
    cout<<dd->data<<endl;
    dd=findmin(root);
    cout<<"当前树中的最小值：";
    cout<<dd->data<<endl;
}
void AVL::add(int x)
{
    cout<<"向平衡二叉树中添加元素"<<x<<endl;
    insert(x,root);
}
void AVL::sub(int x)
{
    cout<<"删除平衡二叉树中的元素"<<x<<endl;
    Delete(x,root);
}
AVL::~AVL()
{
    if(root!=nullptr)
        perish(root);
}
tree*AVL::findmax(tree*p)
{
    if(p!=nullptr)
        while(p->right!=nullptr)
            p=p->right;
    return p;
}
tree*AVL::find(int x,tree*p)
{
    if(p==nullptr)
        return nullptr;
    if(x<(p->data))
        return find(x,p->left);
    else if(x>(p->data))
        return find(x,p->right);
    else
        return p;
}
tree*AVL::findmin(tree*p)
{
    if(p==nullptr)
        return nullptr;
    else if(p->left==nullptr)
        return p;
    else if(p->left!=nullptr)
        return findmin(p->left);
}
void AVL::perish(tree*p)
{
    if(p==nullptr)
        return ;
    perish(p->left);
    perish(p->right);
    delete p;
}
void AVL::midLook(tree*p)
{
    if(p==nullptr)
        return;
    midLook(p->left);
    cout<<p->data<<"   ";
    midLook(p->right);
}
void AVL::frontLook(tree*p)
{
    if(p==nullptr)
        return;
    cout<<p->data<<"   ";
    frontLook(p->left);
    frontLook(p->right);
}
//求树的高度——这里的高度默认空节点高度为0，单一的叶子节点高度为1，其他节点的高度为其左右子树高度最大值+1，所以同层的节点高度不一定相同！！
int AVL::HeightofTree(tree*p)
{
    if(p==nullptr)
        return 0;
    else
        return p->height;
}
//LL类型的单向旋转
tree*AVL::SingleRotate_LL(tree*p2)
{
    tree*p1;
    p1=p2->left;
    p2->left=p1->right;
    p1->right=p2;
    p2->height=max(HeightofTree(p2->left),HeightofTree(p2->right))+1;
    p1->height=max(HeightofTree(p1->left),HeightofTree(p1->right))+1;
    return p1;
}
//RR类型的单向旋转
tree*AVL::SingleRotate_RR(tree*p2)
{
    tree*p1;
    p1=p2->right;
    p2->right=p1->left;
    p1->left=p2;
    p2->height=max(HeightofTree(p2->left),HeightofTree(p2->right))+1;
    p1->height=max(HeightofTree(p1->left),HeightofTree(p1->right))+1;
    return p1;
}
//LR类型的双向旋转
tree*AVL::DoubleRotate_LR(tree*p)
{
    p->left=SingleRotate_RR(p->left);
    return SingleRotate_LL(p);
}
//RL类型的双向旋转
tree*AVL::DoubleRotate_RL(tree*p)
{
    p->right=SingleRotate_LL(p->right);
    return SingleRotate_RR(p);
}
int AVL::getBalance(tree*p)
{
    if(p==nullptr)
        return 0;
    return HeightofTree(p->left)-HeightofTree(p->right);
}
tree*AVL::insert(int x,tree*p)
{
    if(p==nullptr)
    {
        p=new tree;
        p->data=x;
        p->height=1;
        p->left=nullptr;
        p->right=nullptr;
    }
    else if(x<p->data)
    {
        p->left=insert(x,p->left);
        if(HeightofTree(p->left)-HeightofTree(p->right)==2)
        {
            if(x<(p->left->data))
                p=SingleRotate_LL(p);
            else
                p=DoubleRotate_LR(p);
        }
    }
    else if(x>p->data)
    {
        p->right=insert(x,p->right);
        if(HeightofTree(p->right)-HeightofTree(p->left)==2)
        {
            if(x>(p->right->data))
                p=SingleRotate_RR(p);
            else
                p=DoubleRotate_RL(p);
        }
    }
    //如果x==p->data.说明x的值已经在树中，不用做处理
    p->height=max(HeightofTree(p->left),HeightofTree(p->right))+1;
    return p;
}
tree* AVL::create(vector<int>&data,tree*p)
{
    for(int i=0; i<data.size(); i++)
    {
        p=insert(data[i],p);
    }
    return p;
}
tree* AVL::Delete(int x,tree*p)
{
    if(p==nullptr)
    {
        cout<<"树中没有要删除的值!"<<endl;
        return nullptr;
    }
    if(x<p->data)//目标值小于节点值，去左边寻找
    {
        p->left=Delete(x,p->left);
    }
    else if(x>p->data)//目标值大于节点值，去右边寻找
    {
        p->right=Delete(x,p->right);
    }
    else//目标值等于节点值，开始执行删除操作
    {
        if((p->left!=nullptr)&&(p->right!=nullptr))//左右子树都非空
        {
            //在高度更大的那个树上进行删除操作
            if(HeightofTree(p->left)>HeightofTree(p->right))
            {
                p->data=findmax(p->left)->data;
                p->left=Delete(p->data,p->left);
            }
            else
            {
                p->data=findmin(p->right)->data;
                p->right=Delete(p->data,p->right);
            }
        }
        else//左右子树中有空的
        {
            /*
              这里的处理比较巧妙，三种情况
              1.如果左为空，那么用当前节点的右子树来代替删除后当前节点的位置
              2.如果右为空，那么用当前节点的左子树来代替删除后当前节点的位置
              3.如果左右子树都为空的话，那么“？：”的表达式就会使p等于p->right，同样为空
            */
            tree*temp=p;
            p=p->left?p->left:p->right;
            delete temp;
        }
    }
    if(p==nullptr)
        return nullptr;
    //跟新节点高度数据
    p->height=max(HeightofTree(p->left),HeightofTree(p->right))+1;
    //计算当前节点的平衡度
    int balance=getBalance(p);
    //使树恢复平衡
    if(balance>1&&getBalance(p->left)>=0)//如果左树比右树高的多导致的不平衡，并且左孩子的左子树仍然比他的右子树要高，说明是LL类型
        return SingleRotate_LL(p);
    if(balance>1&&getBalance(p->left)<0)//如果左树比右树高的多导致的不平衡，并且左孩子的右子树比他的左子树要高，说明是LR类型
        return DoubleRotate_LR(p);
    if(balance<-1&&getBalance(p->right)<=0)//如果右树比左树高的多导致的不平衡，并且右孩子的右子树仍然比他左子树要高，说明是RR类型
        return SingleRotate_RR(p);
    if(balance<-1&&getBalance(p->right)>0)//如果右树比左树高的多导致的不平衡，并且右孩子的左子树比他的右子树要高，说明是RL类型
        return DoubleRotate_RL(p);
    return p;
}
int main()
{
    vector<int>data={16,3,7,11,9,26,18,14,15};
    AVL avl(data);
    avl.Look();
    cout<<endl;
    avl.Extremum();
    avl.search(14);

    avl.add(20);
    avl.Look();
    cout<<endl;
    avl.Extremum();
    avl.search(20);

    avl.sub(20);
    avl.Look();
    cout<<endl;
    avl.Extremum();
    avl.search(20);
    return 0;
}
