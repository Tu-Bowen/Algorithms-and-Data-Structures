#include<stdio.h>//��������--β�巨
#include<stdlib.h>
//���������
typedef struct  link_node
{
    int data;
    struct link_node*next;
} node;



node*create(node*head)//����������
{
    int num;
    node*p1=NULL,*p2=NULL;//p2�Ǽ���ڵ㣬p1����ʵ�ڵ�
    printf("����������:\n");
    scanf("%d",&num);//������ֻ��װ������
    while(num>0)
    {
        p1=(node*)malloc(sizeof(node));//p1ÿ��ѭ�������һ���µĵ�ַ
        p1->data=num;
        p1->next=NULL;
        if(head==NULL)
            head=p1;//˵���ǿ�����ֻ�е�һ��д��Ԫ�ص�ѭ����ִ��
        else
            p2->next=p1;
        p2=p1;//��ʱ��p2��p1ָ��ͬһ��ַ
        scanf("%d",&num);
    }
    return head;
}




//�����ӡ����ĺ���
void print(node*head)
{
    node*temp;  //����һ���ڵ��ָ��,��Ϊhead��ָ��λ���޷��ı䣬��������������
    temp=head;
    while(temp!=NULL)
    {
        printf("%d",temp->data);
        temp=temp->next;//temp����һ���ڵ�
    }
}




int main()
{
    node*head=NULL;//����ͷָ��
    head=create(head);//����һ��������
    //��������
    print(head);
    return 0;
}
