#include "head.h"
//将Igd数据库进行更新
void push_Igd(Ingredient *p)
{
    FILE *fp;
    if((fp=fopen(Igd_filename,"w"))==NULL)
    {
        printf("无法打开%s文件!\n",Igd_filename);
        return;
    }
    else{
        for(int i=0;i<current_Igd;i++)
        {
            fprintf(fp,"%s\n",p[i].Igd_name);
            fprintf(fp,"%d\n",p[i].Igd_amount);
        }
        printf("原料数据库已更新完毕!\n");
    }

    fclose(fp);
}
//更新菜单数据库
void push_Menu(Menu* p)
{
   FILE* fp;
    if((fp=fopen(Foods_filename,"w"))==NULL)
    {
        printf("无法打开%s文件!\n",Foods_filename);
        return;
    }
    else{
        p=p->next;
        info_foods *s;
        while(p)
        {
            s=p->foodsinfo;
            fprintf(fp,"%s\n",s->food_name);
            fprintf(fp,"%d\n",s->food_id);
            fprintf(fp,"%lf ",s->price);
            fprintf(fp,"%d\n",s->NUM_source);
            for(int i=0;i<s->NUM_source;i++)
            {
                fprintf(fp,"%d %d\n",s->source[i].source_Id,s->source[i].source_amount);
            }
            fprintf(fp,"%s\n",s->food_description);
           p=p->next;
        }
        printf("菜单数据库已更新完毕!\n");

    }

    fclose(fp);
} 
//更新用户数据库
void push_user(User *p)
{
    FILE *fp;
    if((fp=fopen(User_filename,"w"))==NULL)
    {
        printf("无法打开%s文件!\n",User_filename);
        return ;
    }
    else{
         p=p->next;
         while(p)
         {
            fprintf(fp,"%s\n",p->ID);
            fprintf(fp,"%s\n",p->code);
            fprintf(fp,"%c\n",p->grade);
            fprintf(fp,"%.2lf\n",p->surplus);
            fprintf(fp,"%.2lf\n",p->consumption);
            p=p->next;
         }
         printf("用户数据库已更新完毕！\n");
    }
    fclose(fp);
}
//中序遍历更新策略数据库
void push_strategy(Strategy* p)
{
    if(p==NULL)
    {
        printf("没有策略\n");
        return;
    }
    typedef struct stack{
        Strategy *data;
        struct stack* next;
    }stack;
    stack *s=NULL;
    FILE *fp;
    if((fp=fopen(Strategy_filename,"w"))==NULL)
    {
        printf("无法打开%s文件!\n",Strategy_filename);
        return ;
    }
    else{
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
               fprintf(fp,"%.2lf\n",s->data->origin);
               fprintf(fp,"%.2lf\n",s->data->discont); 
               p=s->data->right;
               stack *new=s;
               s=s->next;
               free(new);
            }
        }       
        printf("消费优惠策略数据库已更新！\n");
    }
    fclose(fp);
}

void  push_res(Data *p)
{
    FILE *fp;
    if((fp=fopen(Resturant_filename,"w"))==NULL)
    {
        printf("无法打开%s文件!\n",Resturant_filename);
        return ;
    }
    else{
        fprintf(fp,"%s\n",p->res->res_name);
        fprintf(fp,"%s\n",p->res->res_contactnum);
        fprintf(fp,"%s\n",p->res->res_address);
        fprintf(fp,"%s\n",p->res->res_owner);
        fprintf(fp,"%s\n",p->res->manager_code);
        fprintf(fp,"%.2f\n",p->res->res_turnover);
        printf("餐厅信息已更新！\n");
    }
    fclose(fp);
}
void putout(Data *p)
{
    push_Igd(p->Igd);
    push_Menu(p->menu);
    push_user(p->users);
    push_strategy(p->strategy);
    push_res(p);
}    
