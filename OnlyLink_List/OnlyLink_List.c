#include<stdio.h>//单向链表--尾插法
#include<stdlib.h>
//定义链表的
typedef struct  link_node
{
    int data;
    struct link_node*next;
} node;



node*create(node*head)//链表创建函数
{
    int num;
    node*p1=NULL,*p2=NULL;//p2是记忆节点，p1是真实节点
    printf("请输入整数:\n");
    scanf("%d",&num);//链表中只能装正整数
    while(num>0)
    {
        p1=(node*)malloc(sizeof(node));//p1每次循环都获得一个新的地址
        p1->data=num;
        p1->next=NULL;
        if(head==NULL)
            head=p1;//说明是空链表，只有第一个写入元素的循环会执行
        else
            p2->next=p1;
        p2=p1;//此时让p2与p1指向同一地址
        scanf("%d",&num);
    }
    return head;
}




//定义打印链表的函数
void print(node*head)
{
    node*temp;  //定义一个节点的指针,因为head的指针位置无法改变，否则链表会出问题
    temp=head;
    while(temp!=NULL)
    {
        printf("%d",temp->data);
        temp=temp->next;//temp下移一个节点
    }
}




int main()
{
    node*head=NULL;//设置头指针
    head=create(head);//创建一个单链表
    //调出链表
    print(head);
    return 0;
}
