#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#define MAXSIZE 100
using namespace std;
//���������Ĳ���
class spematrix
{
public:
    //����������
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
        //�ٰ������ǵĳ������ֱ���
        if(mu==0)//mu��0���������Ǿ��󣬷����ǶԳƾ���
            res[len*(len+1)/2]=mtx[len-1][0];
        for(i=0; i<(len+1)*len/2; i++)
            cout<<res[i]<<"   ";
    }
    //����������
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
        //�ٰ������ǵĳ������ֱ���
        if(mu==0)
            res[len*(len+1)/2]=mtx[0][len-1];
        for(i=0; i<(len+1)*len/2; i++)
            cout<<res[i]<<"   ";
    }
    //����ԽǾ���
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
//��ϡ�����Ĳ���
/*��Ԫ�鷨*/
typedef struct ThreeThing
{
    int data;//����
    int row;//��
    int col;//��
} ThreeThing;
typedef struct matrixdata
{
    ThreeThing op[MAXSIZE];
    int m_row;//ԭ���������
    int m_col;//ԭ���������
    int NO_num;//����Ԫ�صĸ���
} matrixdata;
/*ʮ����������ֻ�Ǵ洢�ұߺ��±߷���ĵ�ַ*/
//��ͨ�ڵ�
typedef struct mtxnode
{
    int row;//����Ԫ�ص���
    int col;//����Ԫ�ص���
    int data;//����Ԫ�ص�ֵ
    struct mtxnode*right;//ͬһ���ұߵķ���ڵ�
    struct mtxnode*down;//ͬһ���±�ķ���ڵ�
    mtxnode(int x,int y,int z):row(x),col(y),data(z),right(nullptr),down(nullptr) {}
} mtxnode,*Listnode;
//ͷ�ڵ�
typedef struct mtxheadprivate
{
    int mtx_row;//�������
    int mtx_col;//�������
    int mtx_nonum;//����ķ���Ԫ�صĸ���
    vector<Listnode>row_head;//һ����ָ������
    vector<Listnode>col_head;//һ����ָ������
    /*Listnode*row_head;
    Listnode*col_head;*/
} mtxhead;
class sparsematrix
{
private:
    int value(matrixdata&mtx,int r,int c)//Ѱ�Ҿ���mtx�ĵ�r�У���c�е�ֵ�Ƿ��Ƿ���ֵ������Ƿ���ֵ����ô�ͷ��ط���ֵ�����򷵻�0
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
    //��Ԫ���ʾ���µľ���˷�
    void ChainMatrix(matrixdata&m1,matrixdata&m2)
    {
        //һ��Ҫʹ��m1��������m2���������
        matrixdata res;
        int i,j,k;
        int index=0;
        int res_row=m1.m_row;//������������
        int res_col=m2.m_col;//������������
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
        cout<<"ϡ������������"<<res.m_row<<endl;
        cout<<"ϡ������������"<<res.m_col<<endl;
        cout<<"ϡ���������Ԫ�ظ�����"<<res.NO_num<<endl;
        cout<<"�� �� ֵ"<<endl;
        for(i=0; i<index; i++)
            cout<<res.op[i].row<<"  "<<res.op[i].col<<"  "<<res.op[i].data<<endl;
    }
    //��Ԫ���ʾ���µľ���ӷ�
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
        cout<<"��������m1*m2��Ľ������res��"<<endl;
        cout<<"������У�"<<res.m_row<<endl;
        cout<<"������У�"<<res.m_col<<endl;
        cout<<"����ķ��������"<<res.NO_num<<endl;
        cout<<"�� �� ֵ"<<endl;
        for(i=0; i<res.NO_num; i++)
            cout<<res.op[i].row<<"  "<<res.op[i].col<<"  "<<res.op[i].data<<endl;
    }
    //ʮ��������
    void crosssave(vector<vector<int>>&mtx)
    {
        cout<<"ʮ�������淨---------************"<<endl;
        //����ʮ������
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
                    if(matrix.row_head[i]==nullptr)//����ǵ�ǰ��ָ��ĵ�һ��
                        matrix.row_head[i]=pointer;
                    else//������ǵ�ǰ��ָ��ĵ�һ��
                    {
                        //��ô�ʹӵ�ǰ�е�ͷָ��һֱ�ҵ�����β
                        op=matrix.row_head[i];
                        while(op->right!=nullptr)
                        {
                            op=op->right;
                        }
                        op->right=pointer;
                    }
                    if(matrix.col_head[j]==nullptr)//����ǵ�ǰ��ָ��ĵ�һ��
                        matrix.col_head[j]=pointer;
                    else//������ǵ�ǰ��ָ��ĵ�һ��
                    {
                        //��ô�ʹӵ�ǰ�е�ͷָ��һֱ�ҵ�����β
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
        //��ӡʮ������
        cout<<"ϡ�������У�"<<matrix.mtx_row<<endl;
        cout<<"ϵ��������У�"<<matrix.mtx_col<<endl;
        cout<<"ϵ������ķ���Ԫ�ظ�����"<<matrix.mtx_nonum<<endl;
        //������ͷ�ڵ���д�ӡ
        cout<<"��  �� ֵ"<<endl;
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
        //�ͷ�new�Ŀռ�
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
    //��Ԫ�鴢��
    matrixdata Three(vector<vector<int>>&mtx)
    {
        cout<<"��Ԫ���ʾ��-----------************"<<endl;
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
        cout<<"ϡ������������"<<ak.m_row<<endl;
        cout<<"ϡ������������"<<ak.m_col<<endl;
        cout<<"ϡ���������Ԫ�ظ�����"<<ak.NO_num<<endl;
        cout<<"�� �� ֵ"<<endl;
        for(i=0; i<nums; i++)
            cout<<ak.op[i].row<<"  "<<ak.op[i].col<<"  "<<ak.op[i].data<<endl;
        return ak;
    }
};
int main()
{
    cout<<"�������"<<endl;
    spematrix s;
    //�Գƾ���
    vector<vector<int>>sym_matrix(4,vector<int>(4));
    sym_matrix= {{1,2,4,7},{2,3,5,8},{4,5,6,9},{7,8,9,10}};
    cout<<"�Գƾ���"<<endl;
    s.savedown(sym_matrix,1);
    cout<<endl;
    //�����Ǿ���
    vector<vector<int>>upth_matrix(4,vector<int>(4));
    upth_matrix= {{1,2,3,4}, {0,5,6,7}, {0,0,8,9}, {0,0,0,10}};
    cout<<"�����ǣ�"<<endl;
    s.saveup(upth_matrix,0);
    cout<<endl;
    //�����Ǿ���
    vector<vector<int>>downth_matrix(4,vector<int>(4));
    downth_matrix= {{1,0,0,0},{2,3,0,0},{4,5,6,0},{7,8,9,10}};
    cout<<"�����Ǿ���"<<endl;
    s.savedown(downth_matrix,0);
    cout<<endl;
    //�ԽǾ���
    vector<vector<int>>opp_matrix(5,vector<int>(5));
    opp_matrix= {{1,2,0,0,0},{3,4,5,0,0},{0,6,7,8,0},{0,0,9,10,11},{0,0,0,12,13}};
    cout<<"�ԽǾ���"<<endl;
    s.saveline(opp_matrix);
    cout<<endl;
    sparsematrix k;
    cout<<"ϡ�����"<<endl;
    vector<vector<int>>spamatrix1(4,vector<int>(4));
    vector<vector<int>>spamatrix2(4,vector<int>(4));
    spamatrix1= {{0,0,0,1},{0,0,3,2},{1,0,0,0},{0,2,0,0}};
    spamatrix2= {{0,0,0,3},{2,0,0,3},{0,2,0,8},{1,2,0,0}};
    matrixdata vn,zedd;
    //ʮ������
    k.crosssave(spamatrix1);
    //��Ԫ�鷨
    vn=k.Three(spamatrix1);
    zedd=k.Three(spamatrix2);
    //������Ԫ�����
    k.AddMatrix(vn,zedd);
    //������Ԫ�����
    k.ChainMatrix(vn,zedd);
    return 0;
}
