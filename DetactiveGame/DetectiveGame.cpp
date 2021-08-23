#include<iostream>
#include<cstring>
#include<string>
using namespace std;
/*1.I am guilty 我是罪犯
  2.I am not guilty我不是罪犯
  3.XXX is guilty  XXX是罪犯
  4.XXX is not guilty XXX 不是罪犯
  5.Today is XXX 今天是XXX(周一~周日)
*/
class determine
{
public:
    int M;//参加游戏的人数
    int N;//始终说谎的人数
    int P;//证言的总数
    string str[7]=
    {
        "Today is Monday",
        "Today is Tuesday",
        "Today is Wednesday",
        "Today is Thursday",
        "Today is Friday",
        "Today is Saturday",
        "Today is Sunday",
    }
    string name[20];
    string Sb_say_Sth[100];
    void scnf();//输入内容
    void judge_lier();//判断说谎者
};
void determine::scnf()
{
    cin>>M;//输入参加游戏的人数
    cin>>N;//输入始终说谎的人数
    cin>>P;//输入证言的总数
    for(int i=0;i<M;i++)//输入人名字
        cin>>name[i];
    for(int i+0;i<P;i++)//输入证词
        cin>>Sb_say_Sth[i];
}
void determine::judge_lier()
{

}
int main()
{
    determine s;
    s.scnf();
    return 0;
}
