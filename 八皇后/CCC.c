#include<stdio.h>
#define line  8
//�˻ʺ�����
//�����㷨�����Ŀ��δ�ﵽԤ�ڣ������˽׶εĺ������ã�������һ�׶Σ�ִ�иõݹ������������
int chess[line][line];
int time=0;
int xx,yy;

//��麯��(����)
/*int chek(int i,int j)
{
    int k;
    for(k=0; k<line; k++)
    {
        if(chess[i][k]==1)
            return 1;
        else
            return 0;//ÿ���ڼ����ʱ��chek��麯��һ���᷵��һ��ֵ���Ӷ�����ĺ����嶼����ִ��
    }
    for(k=0; k<line; k++)
    {
        if(chess[k][j]==1)
            return 1;
        else
            return 0;
    }
    for(k=-line; k<=line; k++)
    {
        if(i+k>=0&&i+k<=7&&j+k>=0&&j+k<=7)
        {
            if(chess[i+k][j+k]==1)
                return 1;
            else
                return 0;
        }
    }
    for(k=-line; k<=line; k++)
    {
        if(i+k>=0&&i+k<=7&&j-k>=0&&j-k<=7)
        {
            if(chess[i+k][j-k]==1)
                return 1;
            else
                return 0;
        }
    }int check(int i,int j)
{

    int k;



    for(k=0; k<line; k++)
    { printf("NO.%d",time);

        if(chess[i][k]==1)
            return 1;//0=���ܷ�

    }

    for(k=0; k<line; k++)
    {

        if(chess[k][j]==1)
            return 1;

    }

    for(k=-line; k<=line; k++) //���Խ���
    {

        if(i+k>=0&&i+k<line&&j+k>=0&&j+k<line)//�����ϵ����¶Խ���

            if(chess[i+k][j+k]==1)
                return 1;



        if(i-k>=0&&i-k<line&&j+k>=0&&j+k<line)//�����µ����϶Խ���

            if(chess[i-k][j+k]==1)
                return 1;

    }

    return 0;

}

}*/
//��麯������ȷ��
int check(int i,int j)
{

    int k;
    for(k=0; k<line; k++)//����
    {
        if(chess[i][k]==1)
            return 1;//1=���ܷ�
        if(chess[k][j]==1)
            return 1;
    }
    for(k=-line; k<=line; k++) //���Խ���
    {

        if(i+k>=0&&i+k<line&&j+k>=0&&j+k<line)//�����ϵ����¶Խ���

            if(chess[i+k][j+k]==1)
                return 1;



        if(i-k>=0&&i-k<line&&j+ printf("NO.%d printf("NO.%d",time);",time);k>=0&&j+k<line)//�����µ����϶Խ���

            if(chess[i-k][j+k]==1)
                return 1;

    }

    return 0;//����д��������������鵽�д��󣬻��߶������ȷ�Ż��з���ֵ
}


void queen(int i,int j)//�ڵ�i�зŻʺ󣬴ӵ�j�п�ʼ����
{
    if(j>line-1)
        return ;


    if(check(i,j)==0)//���ͨ��
    {
        chess[i][j]=1;
        if(i==line-1)//���һ�У���¼���
        {
            time=time+1;
            printf("NO.%d\n",time);
            for (xx=0; xx<8; xx++)
                for(yy=0; yy<8; yy++)
                {
                    printf("%d",chess[xx][yy]);
                    if(yy==7)
                        printf("\n");
                }
            printf("\n");
        }
        else
            queen(i+1,0);//����������һ�У���ô����һ��,��ͷ��ʼ
        //��Σ�������ݹ�����У�������ѵݹ��㷨ִ���꣬�ǲ���ִ�����������
        //��ζ�ţ����������ǰ���˻ʺ�ͻ����Լ���λ��
    }//�����i�м����8�ж��޷�վ�ʺ���ô�ý׶εĺ������սᣬ�˻���һ��ĵݹ麯��
    //��ִ������Ĵ��룬����һ�㸳ֵΪ1��λ�ã����¸�ֵΪ0���������



    chess[i][j]=0;//1.�����ͨ�����Ͳ���ִ���������룬��λ�ù�0����������һ�д��볢����һ��
    //2.���ͨ�����ʹ������̻ʺ�����λ�ã��������붼ִ���ˣ��ǾͰѻʺ�����ִ���������
    queen(i,j+1);//1.�����鲻ͨ��������һ��
    //2.������лʺ�����λ�ã���ô��ɾ�����һ�еĻʺ󣬳����Աߵ�λ�ã������һ�ж�û���������ʵ�λ�ã������˽׶εĺ������ã�������һ�׶εĺ���������һ�еĻʺ�Ҳ��գ�����һ�г���������λ�ã��Դ�����
}
int main()
{
    int i,j;
    for(i=0; i<8; i++)
    {
        for(j=0; j<8; j++)
        {
            chess[i][j]=0;
        }
    }//�������ʼ��Ϊ0��0��ʾû�лʺ�1��ʾ�лʺ�


    queen(0,0);
    printf("%d",time);
    return 0;
}

