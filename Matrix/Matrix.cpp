#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#define MAXSIZE 100
using namespace std;
//对特殊矩阵的操作
class spematrix
{
public:
    //保存上三角
    void saveup(vector<vector<int>>&mtx,int mu)
    {
        int len=mtx.size();
        vector<int>res((len+1)*len/2+1);
        int i=0,j=0;
        for(i=0; i<len; i++)
            for(j=i; j<len; j++)
            {
                res[i*(2*len-i+1)/2+j-i]=mtx[i][j];
                cout<<mtx[i][j]<<"   ";
            }
        cout<<endl;
        //再把下三角的常数部分保存
        if(mu==0)//mu是0代表是三角矩阵，否则是对称矩阵
            res[len*(len+1)/2]=mtx[len-1][0];
        for(i=0; i<(len+1)*len/2; i++)
            cout<<res[i]<<"   ";
    }
    //保存下三角
    void savedown(vector<vector<int>>&mtx,int mu)
    {
        int len=mtx.size();
        vector<int>res((len+1)*len/2+1);
        int i=0,j=0;
        for(i=0; i<len; i++)
            for(j=0; j<=i; j++)
            {
                res[i*(i+1)/2+j]=mtx[i][j];
                cout<<mtx[i][j]<<"   ";
            }
        cout<<endl;
        //再把上三角的常数部分保存
        if(mu==0)
            res[len*(len+1)/2]=mtx[0][len-1];
        for(i=0; i<(len+1)*len/2; i++)
            cout<<res[i]<<"   ";
    }
    //保存对角矩阵
    void saveline(vector<vector<int>>&mtx)
    {
        int len=mtx.size();
        int oth_len=3*len-2;
        int i=0,j=0;
        vector<int>res(oth_len);
        for(i=0; i<len; i++)
        {
            if(i==0)
            {
                res[0]=mtx[0][0];
                res[1]=mtx[0][1];
                cout<<mtx[0][0]<<"   "<<mtx[0][1]<<"   ";
            }
            if(i==len-1)
            {
                res[oth_len-2]=mtx[len-1][len-2];
                res[oth_len-1]=mtx[len-1][len-1];
                cout<<mtx[len-1][len-2]<<"   "<<mtx[len-1][len-1]<<"   ";
            }
            if(i!=0&&i!=len-1)
            {
                for(j=i-1; j<i+2; j++)
                {
                    res[2*i+j]=mtx[i][j];
                    cout<<mtx[i][j]<<"   ";
                }
            }
        }
        cout<<endl;
        for(i=0; i<oth_len; i++)
            cout<<res[i]<<"   ";
    }
};
//对稀疏矩阵的操作
/*三元组法*/
typedef struct ThreeThing
{
    int data;//数据
    int row;//行
    int col;//列
} ThreeThing;
typedef struct matrixdata
{
    ThreeThing op[MAXSIZE];
    int m_row;//原数组的行数
    int m_col;//原数组的列数
    int NO_num;//非零元素的个数
} matrixdata;
/*十字链表法——只是存储右边和下边非零的地址*/
//普通节点
typedef struct mtxnode
{
    int row;//非零元素的行
    int col;//非零元素的列
    int data;//非零元素的值
    struct mtxnode*right;//同一行右边的非零节点
    struct mtxnode*down;//同一列下遍的非零节点
    mtxnode(int x,int y,int z):row(x),col(y),data(z),right(nullptr),down(nullptr) {}
} mtxnode,*Listnode;
//头节点
typedef struct mtxheadprivate
{
    int mtx_row;//矩阵的行
    int mtx_col;//矩阵的列
    int mtx_nonum;//矩阵的非零元素的个数
    vector<Listnode>row_head;//一个行指针数组
    vector<Listnode>col_head;//一个列指针数组
    /*Listnode*row_head;
    Listnode*col_head;*/
} mtxhead;
class sparsematrix
{
private:
    int value(matrixdata&mtx,int r,int c)//寻找矩阵mtx的第r行，第c列的值是否是非零值，如果是非零值，那么就返回非零值，否则返回0
    {
        int k=0;
        while(k<mtx.NO_num)
        {
            if(mtx.op[k].row==r&&mtx.op[k].col==c)
            {
                return mtx.op[k].data;
            }
            k++;
        }
        return 0;
    }
public:
    //三元组表示法下的矩阵乘法
    void ChainMatrix(matrixdata&m1,matrixdata&m2)
    {
        //一定要使得m1的列数和m2的行数相等
        matrixdata res;
        int i,j,k;
        int index=0;
        int res_row=m1.m_row;//结果矩阵的行数
        int res_col=m2.m_col;//结果矩阵的列数
        res.m_row=res_row;
        res.m_col=res_col;
        int sum=0;
        for(i=0; i<res_row; i++)
        {
            for(j=0; j<res_col; j++)
            {
                sum=0;
                for(k=0; k<m1.m_col; k++)
                {
                    sum=sum+value(m1,i,k)*value(m2,k,j);
                }
                if(sum!=0)
                {
                    res.op[index].row=i;
                    res.op[index].col=j;
                    res.op[index].data=sum;
                    index++;
                }
            }
        }
        res.NO_num=index;
        cout<<"稀疏矩阵的行数："<<res.m_row<<endl;
        cout<<"稀疏矩阵的列数："<<res.m_col<<endl;
        cout<<"稀疏矩阵非零的元素个数："<<res.NO_num<<endl;
        cout<<"行 列 值"<<endl;
        for(i=0; i<index; i++)
            cout<<res.op[i].row<<"  "<<res.op[i].col<<"  "<<res.op[i].data<<endl;
    }
    //三元组表示法下的矩阵加法
    void AddMatrix(matrixdata&m1,matrixdata&m2)
    {
        int i,j;
        int nums=0;
        matrixdata res;
        int flag=1;
        int number=m1.NO_num+m2.NO_num;
        res.m_row=m1.m_row;
        res.m_col=m1.m_col;
        for(i=0; i<m1.NO_num; i++)
        {
            flag=1;
            for(j=0; j<m2.NO_num; j++)
            {
                if(m1.op[i].row==m2.op[j].row&&m1.op[i].col==m2.op[j].col)
                {
                    flag=0;
                    if((m1.op[i].data+m2.op[j].data)!=0)
                    {
                        res.op[nums].data=m1.op[i].data+m2.op[j].data;
                        res.op[nums].row=m1.op[i].row;
                        res.op[nums].col=m1.op[i].col;
                        nums++;
                        number--;
                    }
                }
            }
            if(flag==1)
            {
                res.op[nums].data=m1.op[i].data;
                res.op[nums].row=m1.op[i].row;
                res.op[nums].col=m1.op[i].col;
                nums++;
            }
        }
        res.NO_num=number;
        for(i=0; i<m2.NO_num; i++)
        {
            flag=1;
            for(j=0; j<m1.NO_num; j++)
            {
                if(m2.op[i].row==m1.op[j].row&&m2.op[i].col==m1.op[j].col)
                    flag=0;
            }
            if(flag==1)
            {
                res.op[nums].data=m2.op[i].data;
                res.op[nums].row=m2.op[i].row;
                res.op[nums].col=m2.op[i].col;
                nums++;
            }
        }
        cout<<"两个矩阵m1*m2后的结果矩阵res："<<endl;
        cout<<"矩阵的行："<<res.m_row<<endl;
        cout<<"矩阵的列："<<res.m_col<<endl;
        cout<<"矩阵的非零个数："<<res.NO_num<<endl;
        cout<<"行 列 值"<<endl;
        for(i=0; i<res.NO_num; i++)
            cout<<res.op[i].row<<"  "<<res.op[i].col<<"  "<<res.op[i].data<<endl;
    }
    //十字链表储存
    void crosssave(vector<vector<int>>&mtx)
    {
        cout<<"十字链表储存法---------************"<<endl;
        //建立十字链表
        mtxhead matrix;
        Listnode pointer;
        Listnode op;
        int no_nums=0;
        int mrow,mcol;
        mrow=mtx.size();
        mcol=mtx[0].size();
        matrix.mtx_row=mrow;
        matrix.mtx_col=mcol;
        int i=0,j=0;
        for(i=0; i<mrow; i++)
            matrix.row_head.push_back(nullptr);
        for(j=0; j<mcol; j++)
            matrix.col_head.push_back(nullptr);
        for(i=0; i<mrow; i++)
        {
            for(j=0; j<mcol; j++)
            {
                if(mtx[i][j]!=0)
                {
                    pointer=new mtxnode(i,j,mtx[i][j]);
                    no_nums++;
                    if(matrix.row_head[i]==nullptr)//如果是当前行指针的第一个
                        matrix.row_head[i]=pointer;
                    else//如果不是当前行指针的第一个
                    {
                        //那么就从当前行的头指针一直找到链表尾
                        op=matrix.row_head[i];
                        while(op->right!=nullptr)
                        {
                            op=op->right;
                        }
                        op->right=pointer;
                    }
                    if(matrix.col_head[j]==nullptr)//如果是当前列指针的第一个
                        matrix.col_head[j]=pointer;
                    else//如果不是当前列指针的第一个
                    {
                        //那么就从当前列的头指针一直找到链表尾
                        op=matrix.col_head[j];
                        while(op->down!=nullptr)
                        {
                            op=op->down;
                        }
                        op->down=pointer;
                    }
                }
            }

        }
        matrix.mtx_nonum=no_nums;
        //打印十字链表
        cout<<"稀疏矩阵的行："<<matrix.mtx_row<<endl;
        cout<<"系数矩阵的列："<<matrix.mtx_col<<endl;
        cout<<"系数矩阵的非零元素个数："<<matrix.mtx_nonum<<endl;
        //根据行头节点进行打印
        cout<<"行  列 值"<<endl;
        for(i=0; i<mrow; i++)
        {
            op=matrix.row_head[i];
            while(op!=nullptr)
            {
                cout<<op->row<<"  ";
                cout<<op->col<<"  ";
                cout<<op->data<<endl;
                op=op->right;
            }
        }
        //释放new的空间
        for(i=0; i<mrow; i++)
        {
            op=matrix.row_head[i];
            while(op!=nullptr)
            {
                pointer=op;
                op=op->right;
                delete pointer;
            }
        }
    }
    //三元组储存
    matrixdata Three(vector<vector<int>>&mtx)
    {
        cout<<"三元组表示法-----------************"<<endl;
        int i=0,j=0,nums=0,index=0;
        matrixdata ak;
        int len_row=mtx.size();
        int len_col=mtx[0].size();
        for(i=0; i<len_row; i++)
            for(j=0; j<len_col; j++)
            {
                if(mtx[i][j]!=0)
                {
                    ak.op[nums].col=j;
                    ak.op[nums].row=i;
                    ak.op[nums].data=mtx[i][j];
                    nums++;
                }
            }
        ak.NO_num=nums;
        ak.m_col=len_col;
        ak.m_row=len_row;
        cout<<"稀疏矩阵的行数："<<ak.m_row<<endl;
        cout<<"稀疏矩阵的列数："<<ak.m_col<<endl;
        cout<<"稀疏矩阵非零的元素个数："<<ak.NO_num<<endl;
        cout<<"行 列 值"<<endl;
        for(i=0; i<nums; i++)
            cout<<ak.op[i].row<<"  "<<ak.op[i].col<<"  "<<ak.op[i].data<<endl;
        return ak;
    }
};
int main()
{
    cout<<"特殊矩阵："<<endl;
    spematrix s;
    //对称矩阵
    vector<vector<int>>sym_matrix(4,vector<int>(4));
    sym_matrix= {{1,2,4,7},{2,3,5,8},{4,5,6,9},{7,8,9,10}};
    cout<<"对称矩阵："<<endl;
    s.savedown(sym_matrix,1);
    cout<<endl;
    //上三角矩阵
    vector<vector<int>>upth_matrix(4,vector<int>(4));
    upth_matrix= {{1,2,3,4}, {0,5,6,7}, {0,0,8,9}, {0,0,0,10}};
    cout<<"上三角："<<endl;
    s.saveup(upth_matrix,0);
    cout<<endl;
    //下三角矩阵
    vector<vector<int>>downth_matrix(4,vector<int>(4));
    downth_matrix= {{1,0,0,0},{2,3,0,0},{4,5,6,0},{7,8,9,10}};
    cout<<"下三角矩阵："<<endl;
    s.savedown(downth_matrix,0);
    cout<<endl;
    //对角矩阵
    vector<vector<int>>opp_matrix(5,vector<int>(5));
    opp_matrix= {{1,2,0,0,0},{3,4,5,0,0},{0,6,7,8,0},{0,0,9,10,11},{0,0,0,12,13}};
    cout<<"对角矩阵："<<endl;
    s.saveline(opp_matrix);
    cout<<endl;
    sparsematrix k;
    cout<<"稀疏矩阵："<<endl;
    vector<vector<int>>spamatrix1(4,vector<int>(4));
    vector<vector<int>>spamatrix2(4,vector<int>(4));
    spamatrix1= {{0,0,0,1},{0,0,3,2},{1,0,0,0},{0,2,0,0}};
    spamatrix2= {{0,0,0,3},{2,0,0,3},{0,2,0,8},{1,2,0,0}};
    matrixdata vn,zedd;
    //十字链表法
    k.crosssave(spamatrix1);
    //三元组法
    vn=k.Three(spamatrix1);
    zedd=k.Three(spamatrix2);
    //两个三元组相加
    k.AddMatrix(vn,zedd);
    //两个三元组相乘
    k.ChainMatrix(vn,zedd);
    return 0;
}
