#include<stdio.h>
//汉诺塔问题
//递归：先想定义的函数意义是什么
//Hanoi的作用是，借助B柱将A柱上的盘子移到C柱
void Hanoi(int n,char A,char B,char C)
{
    if(n==1)
        printf("%c->%c\n",n,A,C);//如果只有一个盘子，那么就直接把当前盘子移动到c盘
    else
    {
        Hanoi(n-1,A,C,B);//先将n-1个盘子从A柱借助C柱移到B柱
        printf("%c->%c\n",A,C);//移动最大的那个盘子
        Hanoi(n-1,B,A,C);//让在B杆上的n-1个盘子到C杆上
    }
}
int main()
{
    int n;
    char A,B,C;
    A='A';
    B='B';
    C='C';
    printf("请输入盘子的个数：");
    scanf("%d",&n);
    Hanoi(n,A,B,C);
    return 0;
}
