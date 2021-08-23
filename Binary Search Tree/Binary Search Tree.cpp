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
    tree*insert(int x,tree*p);//����
    tree*Delete(int x,tree*p);//ɾ��
    tree*find(int x,tree*p);//����
    tree*findmax(tree*p);//�������ֵ
    tree*findmin(tree*p);//������Сֵ
    void perish(tree*p);//���ٶ�����
    tree*create(tree*p);//����������
    void midLook(tree*p);//�������
};
ADT::ADT()
{
    cout<<"����������������������������"<<endl;
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
    cout<<"��ǰ���е����ֵ"<<endl;
    cout<<dd->data<<endl;
}
void ADT::dataMin()
{
    tree*dd=findmin(root);
    cout<<"��ǰ���е���Сֵ"<<endl;
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
        cout<<"�Ѿ�������Ŀ��ֵ!"<<endl;
        cout<<"Ŀ��ֵ��"<<dd->data<<endl;
    }
    else
    {
        cout<<"Ŀ��ֵ�������У�"<<endl;
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
    //�ҵ������ֵ��ȵĽڵ�ʲô������
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
//�ǵݹ飬�����˽��������������������ֵһ���������ұߵ���һ��Ҷ�ӽڵ㣬��Сֵͬ���֪
tree*ADT::findmax(tree*p)
{
    if(p!=nullptr)
        while(p->right!=nullptr)
            p=p->right;
    return p;
}
//�ݹ�
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
        cout<<"����û��Ҫɾ����ֵ"<<endl;
        return nullptr;
    }
    if(x<p->data)//���Ŀ��ֵС�ڵ�ǰ�ڵ㣬ȥ�������в���
        p->left=Delete(x,p->left);
    else if(x>p->data)//���Ŀ��ֵ���ڵ�ǰ�ڵ㣬ȥ�������в���
        p->right=Delete(x,p->right);
    else//���Ŀ��ֵ���ڵ�ǰ�ڵ㣬��ʼ����
    {
        if(p->left!=nullptr&&p->right!=nullptr)//���Ŀ��ֵ������������
        {
            tree*ser=findmin(p->right);//Ѱ�ҵ�ǰ�ڵ�����������С�Ľڵ�
            p->data=ser->data;//����Ĳ����ǻ�ֵ�������������Ľ����ڵ�
            p->right=Delete(ser->data,p->right);//����ֵ֮���ԭ���ڵ�ɾ�������ѵ�ǰ�ڵ������������ɾ��֮���������
        }
        else//ֻ��һ�����ӻ���û�к���
        {
            tree*other=p;//��һ��ָ��ָ��ǰ�ڵ㣬����ֱ��ɾ��
            if(p->left==nullptr)//���Һ���
                p=p->right;
            else if(p->right==nullptr)//������
                p=p->left;
            else//��Ҷ�ӽڵ�
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
