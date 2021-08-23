#include<iostream>
#include<string>
using namespace std;
class Stack
{
private:
    string Expression;
    double numbers[1000];
    int c_top=-1;//�����ջ��Ԫ���±�
    int c_i=0;
    int d_top=-1;//��ֵջ��Ԫ���±�
    int d_j=0;
public:

    //�����ջ
    void c_push(char x);//�������ջ����
    char c_pop();//�������ջ������ջ����
    char c_GetTop();//��������ջ��Ԫ��

    //��ֵջ
    void d_push(double x);//�������ջ����
    double d_pop();//�������ջ������ջ����
    double d_GetTop();//��������ջ��Ԫ��

    //���ʽ������
    double calculate(string&s);
    double play(double x,double y,char z);
    int judge(char ch);
};
void Stack::c_push(char x)
{
    Expression[c_i]=x;
    c_i++;
    c_top=c_i-1;
}
//��ջ����������
char Stack::c_pop()
{
    c_i=c_i-1;
    c_top=c_top-1;
    return Expression[c_top+1];//���ص�����Ԫ��
}
//��ջ�е�������
char Stack::c_GetTop()
{
    return Expression[c_top];
}
//�õ�ջ��������
void Stack::d_push(double x)
{
    numbers[d_j]=x;
    d_j++;
    d_top=d_j-1;
}
//��ջ����������
double Stack::d_pop()
{
    d_j=d_j-1;
    d_top=d_top-1;
    return numbers[d_top+1];//���ص�����Ԫ��
}
//��ջ�е�������
double Stack::d_GetTop()
{
    return numbers[d_top];
}
//�õ�ջ��������
int Stack::judge(char ch)//�ж�����ȼ�
{
    switch(ch)
    {
        case '*':return 2;
        case '/':return 2;
        case '+':return 1;
        case '-':return 1;
        case '(':return 0;//����ٿ�����'(',��ô�����������е�������Ų���ȥ
        case '#':return -1;
    }
}
//Ҫ���������ǰ��˳�򣡣�
double Stack::play(double x,double y,char z)
{
    if(z=='+')
        return x+y;
    if(z=='-')
        return x-y;
    if(z=='*')
        return x*y;
    if(z=='/')
        return x/y;
}
double Stack::calculate(string&s)
{
    c_push('#');//�ȸ������ջѹ��ȼ���͵ķ���
    int i=0;
    double nums=0;
    double res=0;
    while(i<s.size())
    {
        //����ǿո�Ļ��������κδ���ֱ�Ӽ�һ
        //����ջֻ�ܸ߼������ڵͼ���������
        if(s[i]=='(')//�����������ʱ,ֱ�ӷ������ջ
        {
            c_push(s[i]);//�����κ��ж�
        }
        if(s[i]==')')//����������ţ��͵���һ�����ţ���Ӧ�����������ֽ��м��㣬�����ջ��ֱ������ջջ��Ԫ���ǡ�����
        {
            while(c_GetTop()!='(')
            {
                res=play(d_pop(),d_pop(),c_pop());
                d_push(res);
            }
            //�����ʱ��ջ��Ԫ���ǡ�������ֻ�ѡ����������ͺ���
            c_pop();
        }

        if(s[i]=='*'||s[i]=='/'||s[i]=='+'||s[i]=='-')//����������
        {
            if(judge(c_GetTop())>=judge(s[i]))//���ջ����������ȼ����ڻ������ջԪ�ص����ȼ�
            {
                res=play(d_pop(),d_pop(),c_pop());//������ֵջ��������Ԫ�غͲ�����ջ������Ԫ��
                d_push(res);//�ѽ���ٴ�ѹ��ջ��
                c_push(s[i]);//�ٰѷ���ѹ�����ջ
            }
            if(judge(c_GetTop())<judge(s[i]))//���ջ����������ȼ�С����ջԪ�ص����ȼ�
            {
                c_push(s[i]);//ֱ����ջ
            }
        }

        if('0'<=s[i]&&s[i]<='9')//���������,���ַ������ַ�����ת��Ϊʵ��
        {
            //���Զ�λ��������
            nums=nums*10+(s[i]-'0');
            if(s[i+1]<'0'||s[i+1]>'9'||i+1==s.size())//�����һ���ַ��������֣������������ַ�
            {
                d_push(nums);
                nums=0;
            }
            //���ȳ��Ը�λ�������㣬�߼���˳���ڳ��Զ�λ��������
            /*nums=s[i]-'0';
            d_push(nums);*/
        }
        i++;
    }
    //��������Ĵ���֮�󣬷���ջ��ֻ���Զ����µ�*��/��+��-���������ȼ���������
    //ֻ�ð��յ���һ�����������һ���ֵ�˳����㣬�ڰѽ��ѹ��ջ��
    while(c_GetTop()!='#')
    {
        res=play(d_pop(),d_pop(),c_pop());
        d_push(res);
    }
    return res;
}
int main()
{
    double result;
    string Ex;
    cin>>Ex;
    Stack a;
    result=a.calculate(Ex);
    cout<<result;
    return 0;
}
