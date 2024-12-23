#include "head.h"

Queue *init_queue(Data *q)
{
    Queue *p=(Queue*)malloc(sizeof(Queue)*Max_table);
    q->list=p;
    q->head=q->tail=0;
}
//入队
void insert_queue(Data *q)
{
     if(q->menu->next==NULL)
     {
        printf("菜单为空，错误！\n");
        return ;
     }

    if(q->tail-q->head<Max_table)
    {
       int n=q->tail%Max_table;
       printf("输入点餐信息:\n");
       printf("输入用户编号：");
       scanf("%s",q->list[n].ID);
       printf("输入要点几道菜：\n");
       scanf("%d",&q->list[n].NUM_foods);
    
    //分配空间给点餐的菜品Id
        q->list[n].foos_id=(int *)malloc(sizeof(int)*q->list[n].NUM_foods);
          for(int i=0;i<q->list[n].NUM_foods;i++)
       {
           printf("输入第%d道菜的ID:",i+1);
           scanf("%d",&q->list[n].foos_id[i]);
           Menu *s;
           if(!(s=search_foods(q->list[n].foos_id[i],q->menu)))
           {
               printf("没有该菜品！\n");
               i--;
               continue;
           }
            if(search_ingredient(q->Igd,s))
            {
                modify_ingredient(q->Igd,s);
            }
            else{
                printf("原料不足！\n");
                i--;
                continue;
            }
      }
         printf("点餐成功！现在前方还有%d个人在排队\n",q->tail-q->head);
         q->tail++;
    }
else printf("抱歉，本餐厅已满人！\n");
}
Menu *search_foods(int ID,Menu *p)
{
    p=p->next;
    while(p)
    {
         if(p->foodsinfo->food_id==ID)
         {
            return p;
         }
         p=p->next;
    }
    printf("没有该菜品！\n");
    return NULL;
}
//查找策略,返回满足条件的策略
Strategy *search_strategy(double origin,Strategy *p)
{
    typedef struct stack
    {
         Strategy *data;
         struct stack *next;
    }stack;
    stack *top=NULL;
    while(p||top)
    {
      //入栈
      if(p)
      {
         stack *s=(stack*)malloc(sizeof(stack));
         s->data=p;
         s->next=top;
         top=s;
         p=p->left;
      }
      //出栈
      else
      {
          stack *s=top;
          top=top->next;
          
          if(s->data->origin<=origin)
          {
              return s->data;
          }
          p=s->data->right;
          free(s);
      }

    }
    return NULL;
}
//出队
void pop_queue(Data* q)
{
     if(q->head==q->tail)
     {
        printf("错误！餐厅里面没有顾客！\n");
        return ;
     }
     else{
        int n=q->head%Max_table;//桌号
        int m=q->list[n].NUM_foods;
        double Sum=0;
        for(int i=0;i<m;i++)
        {
               Menu *s=search_foods(q->list[n].foos_id[i],q->menu);
               printf("菜品：%s         价格：%.2lf\n",s->foodsinfo->food_name,s->foodsinfo->price);
               Sum+=s->foodsinfo->price;
        }
        printf("原价总计：%.2lf\n ",Sum);
        Strategy *p;
        if(p=search_strategy(Sum,q->strategy))
        {
            printf("优惠政策：满%.2lf减%.2lf\n",p->origin,p->discont);
            Sum-=p->discont;
        }            
        double sum=Sum;
        printf("是否是会员？(1代表是/0代表不是)\n");
        scanf("%d",&q->list[n].status);
        if(q->list[n].status)
        {
            printf("您是会员，将采用会员支付！\n");
            User *temp;
            temp=logIn(q->users);
            if(temp)
            {
                if(temp->grade=='A')
                {
                    Sum*=0.95;
                    printf("会员优惠:95折\n");
                }
                else if(temp->grade=='B')
                {
                    Sum*=0.97;
                    printf("会员优惠:97折\n");
                }
                if(temp->surplus<Sum)
                {
                    printf("余额不足！\n");
                    return ;
                }
                printf("会员支付成功！实付款：%.2lf\n",Sum);
                temp->surplus-=Sum;
                q->res->res_turnover+=Sum;
                printf("当前余额为%.2lf\n",temp->surplus);
            }
            else printf("会员支付失败！\n");
        }
         else{
               printf("实付款：%.2lf\n",sum);
               q->res->res_turnover+=sum;
         }
        q->head++;
     }
}
//原料库修改
void modify_ingredient(Ingredient *p,Menu *q)
{
   int n=q->foodsinfo->NUM_source;
   Source *s=q->foodsinfo->source;
         for(int i=0;i<n;i++)
         {
               p[s[i].source_Id-1].Igd_amount-=s[i].source_amount;
         }
}
//原料库查找,返回1表示原料足够，返回0表示原料不足
int search_ingredient(Ingredient *p,Menu *q)
{
   int n=q->foodsinfo->NUM_source;
   Source *s=q->foodsinfo->source;
         for(int i=0;i<n;i++)
         {
               if(p[s[i].source_Id-1].Igd_amount<s[i].source_amount)
               {
                   return 0;
               }
         }
         return 1;
}

