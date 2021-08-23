#include<iostream>
#include<string>
using namespace std;
class Stack
{
private:
    string Expression;
    double numbers[1000];
    int c_top=-1;//运算符栈顶元素下标
    int c_i=0;
    int d_top=-1;//数值栈顶元素下标
    int d_j=0;
public:

    //运算符栈
    void c_push(char x);//运算符入栈函数
    char c_pop();//运算符出栈函数出栈函数
    char c_GetTop();//获得运算符栈顶元素

    //数值栈
    void d_push(double x);//运算符入栈函数
    double d_pop();//运算符出栈函数出栈函数
    double d_GetTop();//获得运算符栈顶元素

    //表达式处理函数
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
//向栈里输入数据
char Stack::c_pop()
{
    c_i=c_i-1;
    c_top=c_top-1;
    return Expression[c_top+1];//返回弹出的元素
}
//从栈中调出数据
char Stack::c_GetTop()
{
    return Expression[c_top];
}
//得到栈顶的数字
void Stack::d_push(double x)
{
    numbers[d_j]=x;
    d_j++;
    d_top=d_j-1;
}
//向栈里输入数据
double Stack::d_pop()
{
    d_j=d_j-1;
    d_top=d_top-1;
    return numbers[d_top+1];//返回弹出的元素
}
//从栈中调出数据
double Stack::d_GetTop()
{
    return numbers[d_top];
}
//得到栈顶的数字
int Stack::judge(char ch)//判断运算等级
{
    switch(ch)
    {
        case '*':return 2;
        case '/':return 2;
        case '+':return 1;
        case '-':return 1;
        case '(':return 0;//如果少考虑了'(',那么可能左括号中的运算符放不进去
        case '#':return -1;
    }
}
//要搞清楚运算前后顺序！！
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
    c_push('#');//先给运算符栈压入等级最低的符号
    int i=0;
    double nums=0;
    double res=0;
    while(i<s.size())
    {
        //如果是空格的话，不做任何处理，直接加一
        //符号栈只能高级运算在低级运算上面
        if(s[i]=='(')//如果是左括号时,直接放入符号栈
        {
            c_push(s[i]);//不做任何判断
        }
        if(s[i]==')')//如果是右括号，就弹出一个符号，对应弹出两个数字进行计算，结果入栈，直到符号栈栈顶元素是‘（’
        {
            while(c_GetTop()!='(')
            {
                res=play(d_pop(),d_pop(),c_pop());
                d_push(res);
            }
            //如果此时的栈顶元素是‘（’，只把‘（’弹出就好了
            c_pop();
        }

        if(s[i]=='*'||s[i]=='/'||s[i]=='+'||s[i]=='-')//如果是运算符
        {
            if(judge(c_GetTop())>=judge(s[i]))//如果栈顶运算符优先级大于或等于入栈元素的优先级
            {
                res=play(d_pop(),d_pop(),c_pop());//弹出数值栈顶的两个元素和操作符栈的两个元素
                d_push(res);//把结果再次压入栈中
                c_push(s[i]);//再把符号压入符号栈
            }
            if(judge(c_GetTop())<judge(s[i]))//如果栈顶运算符优先级小于入栈元素的优先级
            {
                c_push(s[i]);//直接入栈
            }
        }

        if('0'<=s[i]&&s[i]<='9')//如果是数字,将字符串的字符数字转化为实型
        {
            //尝试多位数的运算
            nums=nums*10+(s[i]-'0');
            if(s[i+1]<'0'||s[i+1]>'9'||i+1==s.size())//如果下一个字符不是数字，或者是最后的字符
            {
                d_push(nums);
                nums=0;
            }
            //我先尝试个位数的运算，逻辑捋顺了在尝试多位数的运算
            /*nums=s[i]-'0';
            d_push(nums);*/
        }
        i++;
    }
    //按照上面的处理之后，符号栈中只有自顶向下的*，/，+，-，并且优先级自上向下
    //只用按照弹出一运算符，弹出一数字的顺序计算，在把结果压入栈中
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
