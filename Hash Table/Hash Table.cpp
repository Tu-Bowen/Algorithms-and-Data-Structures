#include<iostream>
#include<vector>
#include<math.h>
using namespace std;
const int a=1;
const int b=0;
const int p=51;
const double A=0.3;
const int m=64;
class Hash
{
private:
    int direct_difine(int key);//ֱ��Ѱַ��
    int division(int key);//����������
    int analyse_number(int key);//���ַ��������������ڵ绰����,�绰����ǰ������ֲַ������ȣ����������λ���ֲ����ȣ�ȡ������λ��Ϊ�±�
    int pow_use_mid(int key);//ƽ��ȡ�з�
    int chain(int key);//�˷�ɢ�з�
};
int Hash::direct_difine(int key)
{
   return a*key+b;
}
int Hash::division(int key)
{
    return key%p;
}
int Hash::analyse_number(int key)
{
    int n=key;
    int res=0;
    for(int i=0;i<4;i++)
    {
        res=res*10+(n%10);
        n=n/10;
    }
    return res;
}
int Hash::pow_use_mid(int key)
{
    int res=0;
    int n=key*key;
    for(int i=0;i<4;i++)
    {
        if(i>0)
            res=res*10+(n%10);
        n=n/10;
    }
    return res;
}
int Hash::chain(int key)
{
    double num=key*A;
    while(num>1)//ȡС������
    {
        num--;
    }
    return floor(num*m);//����ȡ��
}
