#include<iostream>
#include<cstring>
#include<string>
using namespace std;
/*1.I am guilty �����ﷸ
  2.I am not guilty�Ҳ����ﷸ
  3.XXX is guilty  XXX���ﷸ
  4.XXX is not guilty XXX �����ﷸ
  5.Today is XXX ������XXX(��һ~����)
*/
class determine
{
public:
    int M;//�μ���Ϸ������
    int N;//ʼ��˵�ѵ�����
    int P;//֤�Ե�����
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
    void scnf();//��������
    void judge_lier();//�ж�˵����
};
void determine::scnf()
{
    cin>>M;//����μ���Ϸ������
    cin>>N;//����ʼ��˵�ѵ�����
    cin>>P;//����֤�Ե�����
    for(int i=0;i<M;i++)//����������
        cin>>name[i];
    for(int i+0;i<P;i++)//����֤��
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
