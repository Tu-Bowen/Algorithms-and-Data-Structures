#include<stdio.h>
#define line  8
//八皇后问题
//回溯算法：如果目标未达到预期，结束此阶段的函数调用，返回上一阶段，执行该递归语句后面的命令
int chess[line][line];
int time=0;
int xx,yy;

//检查函数(错误)
/*int chek(int i,int j)
{
    int k;
    for(k=0; k<line; k++)
    {
        if(chess[i][k]==1)
            return 1;
        else
            return 0;//每次在检查行时，chek检查函数一定会返回一个值，从而下面的函数体都不被执行
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
            return 1;//0=不能放

    }

    for(k=0; k<line; k++)
    {

        if(chess[k][j]==1)
            return 1;

    }

    for(k=-line; k<=line; k++) //两对角线
    {

        if(i+k>=0&&i+k<line&&j+k>=0&&j+k<line)//从左上到右下对角线

            if(chess[i+k][j+k]==1)
                return 1;



        if(i-k>=0&&i-k<line&&j+k>=0&&j+k<line)//从左下到右上对角线

            if(chess[i-k][j+k]==1)
                return 1;

    }

    return 0;

}

}*/
//检查函数（正确）
int check(int i,int j)
{

    int k;
    for(k=0; k<line; k++)//列行
    {
        if(chess[i][k]==1)
            return 1;//1=不能放
        if(chess[k][j]==1)
            return 1;
    }
    for(k=-line; k<=line; k++) //两对角线
    {

        if(i+k>=0&&i+k<line&&j+k>=0&&j+k<line)//从左上到右下对角线

            if(chess[i+k][j+k]==1)
                return 1;



        if(i-k>=0&&i-k<line&&j+ printf("NO.%d printf("NO.%d",time);",time);k>=0&&j+k<line)//从左下到右上对角线

            if(chess[i-k][j+k]==1)
                return 1;

    }

    return 0;//这样写，程序会把上述检查到有错误，或者都检查正确才会有返回值
}


void queen(int i,int j)//在第i行放皇后，从第j列开始尝试
{
    if(j>line-1)
        return ;


    if(check(i,j)==0)//检查通过
    {
        chess[i][j]=1;
        if(i==line-1)//最后一行，记录情况
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
            queen(i+1,0);//如果不是最后一行，那么换下一行,从头开始
        //其次，在这个递归代码中，如果不把递归算法执行完，是不会执行下面的语句的
        //意味着，在这条语句前，八皇后就会有自己的位置
    }//如果第i行检查了8列都无法站皇后，那么该阶段的函数会终结，退回上一层的递归函数
    //再执行下面的代码，将上一层赋值为1的位置，从新赋值为0，如此往复



    chess[i][j]=0;//1.如果不通过，就不会执行上述代码，该位置归0，并且用下一行代码尝试下一列
    //2.如果通过，就代表棋盘皇后都有了位置，上述代码都执行了，那就把皇后拿走执行其他情况
    queen(i,j+1);//1.如果检查不通过，换下一列
    //2.如果所有皇后都有了位置，那么就删除最后一行的皇后，尝试旁边的位置，如果这一行都没有其他合适的位置，结束此阶段的函数调用，返回上一阶段的函数，将上一行的皇后也清空，在上一行尝试其他的位置，以此往复
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
    }//将数组初始化为0，0表示没有皇后，1表示有皇后


    queen(0,0);
    printf("%d",time);
    return 0;
}

