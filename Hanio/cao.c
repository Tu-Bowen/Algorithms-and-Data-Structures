#include<stdio.h>
//��ŵ������
//�ݹ飺���붨��ĺ���������ʲô
//Hanoi�������ǣ�����B����A���ϵ������Ƶ�C��
void Hanoi(int n,char A,char B,char C)
{
    if(n==1)
        printf("%c->%c\n",n,A,C);//���ֻ��һ�����ӣ���ô��ֱ�Ӱѵ�ǰ�����ƶ���c��
    else
    {
        Hanoi(n-1,A,C,B);//�Ƚ�n-1�����Ӵ�A������C���Ƶ�B��
        printf("%c->%c\n",A,C);//�ƶ������Ǹ�����
        Hanoi(n-1,B,A,C);//����B���ϵ�n-1�����ӵ�C����
    }
}
int main()
{
    int n;
    char A,B,C;
    A='A';
    B='B';
    C='C';
    printf("���������ӵĸ�����");
    scanf("%d",&n);
    Hanoi(n,A,B,C);
    return 0;
}
