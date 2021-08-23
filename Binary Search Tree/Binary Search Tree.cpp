#include<iostream>
#include<vector>
using namespace std;
typedef struct tree
{
    int data;
    tree*left;
    tree*right;
} tree;
class ADT
{
public:
    ADT();
    ~ADT();
    void Look();
    void anther_way_create_tree(vector<int>&dat);
    void dataMax();
    void dataMin();
    void add(int x);
    void sub(int x);
    void search(int x);
private:
    tree*root;
    tree*insert(int x,tree*p);//插入
    tree*Delete(int x,tree*p);//删除
    tree*find(int x,tree*p);//查找
    tree*findmax(tree*p);//树中最大值
    tree*findmin(tree*p);//树中最小值
    void perish(tree*p);//销毁二叉树
    tree*create(tree*p);//创建二叉树
    void midLook(tree*p);//中序遍历
};
ADT::ADT()
{
    cout<<"创建二叉搜索树——请输入数据"<<endl;
    root=create(root);
}
ADT::~ADT()
{
    perish(root);
}
void ADT::Look()
{
    midLook(root);
}
void ADT::dataMax()
{
    tree*dd=findmax(root);
    cout<<"当前树中的最大值"<<endl;
    cout<<dd->data<<endl;
}
void ADT::dataMin()
{
    tree*dd=findmin(root);
    cout<<"当前树中的最小值"<<endl;
    cout<<dd->data<<endl;
}
void ADT::add(int x)
{
    insert(x,root);
}
void ADT::sub(int x)
{
    Delete(x,root);
}
void ADT::search(int x)
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
tree* ADT::insert(int x,tree*p)
{
    if(p==nullptr)
    {
        p=new tree;
        p->data=x;
        p->left=nullptr;
        p->right=nullptr;
    }
    else if(x<(p->data))
        p->left=insert(x,p->left);
    else if(x>(p->data))
        p->right=insert(x,p->right);
    //找到与插入值相等的节点什么都不做
    return p;
}
tree*ADT::find(int x,tree*p)
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
//非递归，可以了解整个二叉排序树的最大值一定是在最右边的那一个叶子节点，最小值同理可知
tree*ADT::findmax(tree*p)
{
    if(p!=nullptr)
        while(p->right!=nullptr)
            p=p->right;
    return p;
}
//递归
tree*ADT::findmin(tree*p)
{
    if(p==nullptr)
        return nullptr;
    else if(p->left==nullptr)
        return p;
    else if(p->left!=nullptr)
        return findmin(p->left);
}
tree*ADT::create(tree*p)
{
    int x;
    cin>>x;
    if(x<=0)
    {
        return nullptr;
    }
    p=new tree;
    p->data=x;
    p->left=create(p->left);
    p->right=create(p->right);
    return p;
}
void ADT::perish(tree*p)
{
    if(p==nullptr)
        return ;
    perish(p->left);
    perish(p->right);
    delete p;
}
tree*ADT::Delete(int x,tree*p)
{
    if(p==nullptr)
    {
        cout<<"树中没有要删除的值"<<endl;
        return nullptr;
    }
    if(x<p->data)//如果目标值小于当前节点，去左子树中操作
        p->left=Delete(x,p->left);
    else if(x>p->data)//如果目标值大于当前节点，去右子树中操作
        p->right=Delete(x,p->right);
    else//如果目标值等于当前节点，开始操作
    {
        if(p->left!=nullptr&&p->right!=nullptr)//如果目标值含有两个孩子
        {
            tree*ser=findmin(p->right);//寻找当前节点右子树中最小的节点
            p->data=ser->data;//这里的操作是换值，并不是真正的交换节点
            p->right=Delete(ser->data,p->right);//换完值之后把原来节点删除，并把当前节点的右子树换成删除之后的右子树
        }
        else//只有一个孩子或者没有孩子
        {
            tree*other=p;//换一个指针指向当前节点，方便直接删除
            if(p->left==nullptr)//有右孩子
                p=p->right;
            else if(p->right==nullptr)//有左孩子
                p=p->left;
            else//是叶子节点
                p=nullptr;
            delete other;

        }
    }
    return p;
}
void ADT::midLook(tree*p)
{
    if(p==nullptr)
        return;
    midLook(p->left);
    cout<<p->data<<"   ";
    midLook(p->right);
}
void ADT::anther_way_create_tree(vector<int>&dat)
{
    int n=dat.size();
    for(int i=0;i<n;i++)
    {
        insert(dat[i],root);
    }
}
int main()
{
    ADT a;
    a.Look();
    a.add(98);
    cout<<endl;
    a.Look();
    cout<<endl;
    a.dataMax();
    a.dataMin();
    a.sub(90);
    a.Look();
    cout<<endl;
    a.search(90);
    return 0;
}
