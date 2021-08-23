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
    int direct_difine(int key);//直接寻址法
    int division(int key);//除留余数法
    int analyse_number(int key);//数字分析法——适用于电话号码,电话号码前面的数字分布不均匀，而后面的四位数分布均匀，取后面四位数为下标
    int pow_use_mid(int key);//平方取中法
    int chain(int key);//乘法散列法
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
    while(num>1)//取小数部分
    {
        num--;
    }
    return floor(num*m);//向下取整
}
