#include<iostream>
#include<vector>
#include<cstdbool>
using namespace std;

class Tries
{
private:
    Tries* next[26]= {nullptr};
    bool flag;
    void Delete(Tries*p);
public:
    Tries();
    void insert(const string&s);
    bool search(const string&s);
    void delTree();
};
Tries::Tries()
{
    flag=false;
}
void Tries::insert(const string&s)
{
    Tries*cur=this;
    for(int i=0; i<s.size(); i++)
    {
        int index=s[i]-'a';
        if(cur->next[index]==nullptr)
        {
            cur->next[index]=new Tries;
        }
        cur=cur->next[index];
    }
    cur->flag=true;
}
bool Tries::search(const string&s)
{
    Tries*cur=this;
    for(int i=0; i<s.size(); i++)
    {
        int index=s[i]-'a';
        if(cur->next[index]==nullptr)
        {

            return false;
        }
        cur=cur->next[index];
    }
    if(cur->flag)
        return true;
    return false;
}
void Tries::Delete(Tries*p)
{
    for(int i=0; i<26; i++)
    {
        if(p->next[i]!=nullptr)
        {
            Delete(p->next[i]);
        }
    }
    delete p;
}
void Tries::delTree()
{
    for(int i=0; i<26; i++)
    {
        if(this->next[i]!=nullptr)
            Delete(this->next[i]);
    }
}
int main()
{
    Tries ok;
    string s="love";
    ok.insert(s);
    cout<<ok.search(s);
    ok.delTree();
    return 0;
}
