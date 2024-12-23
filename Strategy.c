#include "head.h"

//判断是否有相同折扣条件
Strategy*  search_equvial(Strategy *root,Strategy *p)
{
    Strategy *temp=root;
    while(temp)
    {
        if(temp->origin>p->origin)
        {
            temp=temp->right;
        }
        else if(temp->origin==p->origin)
        {
            return temp;
        }
        else
        {
            temp=temp->left;
        }
    }
    return NULL;
}
//加入策略
void insert_strategy(Strategy** p)
{
      Strategy *new=(Strategy*)malloc(sizeof(Strategy));
      printf("输入折扣条件(须达到的价格):");
      scanf("%lf",&new->origin);
      printf("折扣多少钱：");
      scanf("%lf",&new->discont);
      new->left=new->right=NULL;
      //还要判断是否有相同折扣条件
      Strategy *temp;
      if(*p==NULL)
      {
           *p=new;
           return;
      }
      else if((temp=search_equvial(*p,new)))
      {
          printf("已有相同折扣条件\n");
                return;
      }
            search_insert(*p,new);
            printf("插入成功\n");
  }
//删除策略
void delete_strategy(Strategy **p)
{
    printf("你要删除的策略所具有的条件：");
    double n;
    scanf("%lf",&n);
    Strategy *head=*p;
    Strategy *old=head;
    int i=-1;
    while(head)
    {
          if(head->origin>n)
          {
             i=0;
             old=head;
             head=head->right;
          }
          else if(head->origin<n)
          {
             i=1;
             old=head;
             head=head->left;
          }
          else break;
    }
      if(head==NULL)
      {
            printf("没有这个策略\n");
            return;
      }
    Strategy *temp=head;
    if(i==-1)
    {
        if(head->left)
        {
            temp=head->left;
            while(temp->right!=NULL)
            temp=temp->right;
            temp->right=head->right;
            *p=head->left;
        }
        else
            *p=head->right;
            printf("删除成功\n");
            free(head);
            return;
    }
    if(i==0)
    {
            if(temp->left)
            {     
                  temp=temp->left;
                  while(temp->right!=NULL)
                  temp=temp->right;
                  old->right=head->left;
                  temp->right=head->right;
            }
            else
                old->right=head->right;
    
        }
      else
      {
            if(temp->right)
            {
                  temp=temp->right;
               while(temp->left!=NULL)
               temp=temp->left;
               old->left=head->right;
               temp->left=head->left;
            }
            else
                  old->left=head->left;     
      }
      free(head);
      printf("删除成功\n");
}
void modify_strategy(Strategy *p)
{
    printf("你要修改的策略所具有的条件：");
    double n;
    scanf("%lf",&n);
    Strategy *head=p;
    Strategy *old=head;
        while(head)
    {
          if(head->origin>n)
          {
             old=head;
             head=head->right;
          }
          else if(head->origin<n)
          {
             old=head;
             head=head->left;
          }
          else if(head->origin==n)break;
    }
      if(head==NULL)
      {
            printf("没有这个策略\n");
            return;
      }
      printf("输入折扣条件(须达到的价格):");
      scanf("%lf",&head->origin);
      printf("折扣多少钱：");
      scanf("%lf",&head->discont);
      while(search_equvial(p,head)!=head&&search_equvial(p,head)!=NULL)
      {
            printf("已有相同折扣条件\n");
          printf("输入折扣条件(须达到的价格):");
          scanf("%lf",&head->origin);
          printf("折扣多少钱：");
          scanf("%lf",&head->discont);
      }
      printf("修改成功\n");
}
//查看策略
void print_strategy(Strategy *p)
{
    if(p==NULL)
    {
        printf("没有策略\n");
        return;
    }
    //中序遍历
     typedef struct stack
    {
        Strategy *data;
        struct stack *next;
    }stack;
      stack *s=NULL;
     while(p!=NULL||s!=NULL)
        {
            //p不为空，则入栈(头插法）。
            if(p)
            {
                 stack* new=(stack*)malloc(sizeof(stack));
                 new->next=s;
                 s=new;
                 s->data=p;
                 p=p->left;
            }
            //p为空，出栈同时输出该值。
            else{
               printf("满%.2lf减%.2lf\n",
                     s->data->origin,
                     s->data->discont);
               p=s->data->right;
               stack *new=s;
               s=s->next;
               free(new);
            }
        }       
    
}