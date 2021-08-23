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
    tree*find(int x,tree*p);//�����㷨
    tree*findmax(tree*p);//�������ֵ
    tree*findmin(tree*p);//������Сֵ
    void perish(tree*p);//���ٶ�����
    void midLook(tree*p);//�������
    void frontLook(tree*p);//ǰ�����
    int getBalance(tree*p);//��ȡ�ڵ��ƽ���
    int HeightofTree(tree*p);//����һ�����ĸ߶�
    tree*SingleRotate_LL(tree*p2);//LL���͵ĵ�����ת
    tree*SingleRotate_RR(tree*p2);//RR���͵ĵ�����ת
    tree*DoubleRotate_LR(tree*p);//LR���͵�˫����ת
    tree*DoubleRotate_RL(tree*p);//RL���͵�˫����ת
    tree*create(vector<int>&data,tree*p);//����������
    tree*insert(int x,tree*p);//�����㷨
    tree*Delete(int x,tree*p);//ɾ���㷨
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
    cout<<"��ǰ�������������";
    midLook(root);
    cout<<endl;
    cout<<"��ǰ����ǰ�������";
    frontLook(root);
}
void AVL::search(int x)
{
    tree*dd=find(x,root);
    if(dd!=nullptr)
    {
        cout<<"�Ѿ�������Ŀ��ֵ!"<<endl;
        cout<<"Ŀ��ֵ��"<<dd->data<<endl;
    }
    else
    {
        cout<<"Ŀ��ֵ�������У�"<<endl;
    }
}
void AVL::Extremum()
{
    tree*dd=findmax(root);
    cout<<"��ǰ���е����ֵ��";
    cout<<dd->data<<endl;
    dd=findmin(root);
    cout<<"��ǰ���е���Сֵ��";
    cout<<dd->data<<endl;
}
void AVL::add(int x)
{
    cout<<"��ƽ������������Ԫ��"<<x<<endl;
    insert(x,root);
}
void AVL::sub(int x)
{
    cout<<"ɾ��ƽ��������е�Ԫ��"<<x<<endl;
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
//�����ĸ߶ȡ�������ĸ߶�Ĭ�Ͽսڵ�߶�Ϊ0����һ��Ҷ�ӽڵ�߶�Ϊ1�������ڵ�ĸ߶�Ϊ�����������߶����ֵ+1������ͬ��Ľڵ�߶Ȳ�һ����ͬ����
int AVL::HeightofTree(tree*p)
{
    if(p==nullptr)
        return 0;
    else
        return p->height;
}
//LL���͵ĵ�����ת
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
//RR���͵ĵ�����ת
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
//LR���͵�˫����ת
tree*AVL::DoubleRotate_LR(tree*p)
{
    p->left=SingleRotate_RR(p->left);
    return SingleRotate_LL(p);
}
//RL���͵�˫����ת
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
    //���x==p->data.˵��x��ֵ�Ѿ������У�����������
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
        cout<<"����û��Ҫɾ����ֵ!"<<endl;
        return nullptr;
    }
    if(x<p->data)//Ŀ��ֵС�ڽڵ�ֵ��ȥ���Ѱ��
    {
        p->left=Delete(x,p->left);
    }
    else if(x>p->data)//Ŀ��ֵ���ڽڵ�ֵ��ȥ�ұ�Ѱ��
    {
        p->right=Delete(x,p->right);
    }
    else//Ŀ��ֵ���ڽڵ�ֵ����ʼִ��ɾ������
    {
        if((p->left!=nullptr)&&(p->right!=nullptr))//�����������ǿ�
        {
            //�ڸ߶ȸ�����Ǹ����Ͻ���ɾ������
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
        else//�����������пյ�
        {
            /*
              ����Ĵ���Ƚ�����������
              1.�����Ϊ�գ���ô�õ�ǰ�ڵ��������������ɾ����ǰ�ڵ��λ��
              2.�����Ϊ�գ���ô�õ�ǰ�ڵ��������������ɾ����ǰ�ڵ��λ��
              3.�������������Ϊ�յĻ�����ô���������ı��ʽ�ͻ�ʹp����p->right��ͬ��Ϊ��
            */
            tree*temp=p;
            p=p->left?p->left:p->right;
            delete temp;
        }
    }
    if(p==nullptr)
        return nullptr;
    //���½ڵ�߶�����
    p->height=max(HeightofTree(p->left),HeightofTree(p->right))+1;
    //���㵱ǰ�ڵ��ƽ���
    int balance=getBalance(p);
    //ʹ���ָ�ƽ��
    if(balance>1&&getBalance(p->left)>=0)//��������������ߵĶർ�µĲ�ƽ�⣬�������ӵ���������Ȼ������������Ҫ�ߣ�˵����LL����
        return SingleRotate_LL(p);
    if(balance>1&&getBalance(p->left)<0)//��������������ߵĶർ�µĲ�ƽ�⣬�������ӵ�������������������Ҫ�ߣ�˵����LR����
        return DoubleRotate_LR(p);
    if(balance<-1&&getBalance(p->right)<=0)//��������������ߵĶർ�µĲ�ƽ�⣬�����Һ��ӵ���������Ȼ����������Ҫ�ߣ�˵����RR����
        return SingleRotate_RR(p);
    if(balance<-1&&getBalance(p->right)>0)//��������������ߵĶർ�µĲ�ƽ�⣬�����Һ��ӵ�������������������Ҫ�ߣ�˵����RL����
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
