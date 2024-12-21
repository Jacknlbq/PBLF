#include "head.h"
int current_Igd;
//初始化
//初始化原料表，返回指向第一原料的地址，原料表是用类似数组的结构存的。文件创建失败返回空指针
Ingredient* init_Igd()
{
   Ingredient *p=(Ingredient*)malloc(sizeof(Ingredient)*Max_Igd);
   current_Igd=0;
   FILE *fp;

   if((fp=fopen(Igd_filename,"r"))==NULL)
   {
      if((fp=fopen(Igd_filename,"w"))==NULL)
      {
        printf("无法创建%s文件!\n",Igd_filename);
        free(p);
        return NULL;
      }
      else printf("文件创建完成！\n");
   }
   else {
       int i=0;
       fgetc(fp);
       while(!feof(fp))
       {
           fseek(fp,-1,SEEK_CUR);
           fscanf(fp,"%s\n",p[i].Igd_name);
           fscanf(fp,"%d\n",&p[i].Igd_amount);
           fgetc(fp);
           i++;
       }
       fclose(fp);
       printf("原料表已经初始化，现已有%d个元素。\n",i);
       current_Igd=i;
   }
   return p;
}
//初始化菜单,返回指向第一道菜的指针,如果文件创建失败，返回NULL
Menu *init_menu()
{

    //指向第一道菜
     Menu *p=(Menu *)malloc(sizeof(Menu));
     p->next=NULL;
    //指向最后一道菜
    Menu *tail=p;
    Menu *new;


     FILE *fp;
     if((fp=fopen(Foods_filename,"r"))==NULL)
   {
      if((fp=fopen(Foods_filename,"w"))==NULL)
      {
        printf("无法创建%s文件!\n",Foods_filename);
        free(p);
        return NULL;
      }
        else printf("%s文件创建完成!\n",Foods_filename);
   }
   else{
      fgetc(fp);

      while(!feof(fp))
      {
          new=(Menu*)malloc(sizeof(Menu));
          new->next=NULL;
          tail->next=new;
          tail=new;

        fseek(fp,-1,1);
        info_foods *s=(info_foods*)malloc(sizeof(info_foods));
        fscanf(fp,"%s",s->food_name);
        fscanf(fp,"%d",&s->food_id);
        fscanf(fp,"%lf",&s->price);
        fscanf(fp,"%d",&s->NUM_source);
        
        Source *q=(Source*)malloc(sizeof(Source)*s->NUM_source);
        for(int i=0;i<s->NUM_source;i++)
        {
            fscanf(fp,"%d",&q[i].source_Id);
            fscanf(fp,"%d\n",&q[i].source_amount);
        }

        fscanf(fp,"%s\n",s->food_description);
         s->source=q;
         tail->foodsinfo=s;
         fgetc(fp);
      }
              fclose(fp);
   }
   return p;
}
//初始化用户表,返回指向第一个用户的指针（没有数据）,如果文件创建失败，返回NULL，
User* init_user()
{
    User *p=(User*)malloc(sizeof(User));
    p->next=NULL;
    User *s=p;
    User *new;
    FILE *fp;
    if((fp=fopen(User_filename,"r"))==NULL)
    {
        if((fp=fopen(User_filename,"w"))==NULL)
        {
            printf("无法创建%s文件!\n",User_filename);
            free(p);
            return NULL;
        }
        else printf("%s文件创建完成!\n",User_filename);
    }
    else{
        int i=0;
        fgetc(fp);
        while(!feof(fp))
        {

            //节点交替
            new=(User*)malloc(sizeof(User));
            new->next=NULL;
            s->next=new;
            s=new;

            fseek(fp,-1,1);
            fscanf(fp,"%s\n",s->ID);
            fscanf(fp,"%s\n",s->code);
            fscanf(fp,"%c\n",&s->grade);
            fscanf(fp,"%lf\n",&s->surplus);
            fscanf(fp,"%lf\n",&s->consumption);
            fgetc(fp);
        }
        fclose(fp);
    }
    return p;
}
void search_insert(Strategy *root,Strategy *p)
{
    double n=p->origin;
     while(1)
     {
         if(n>root->origin)
         {
            if(!root->left)
            {
                root->left=p;
                return;
            }
             root=root->left;        
         }
         else
         {
            if(!root->right)
            {
                root->right=p;
                return;
            }
            root=root->right;
         }
     }
}
//非递归创建排序二叉树--消费政策,如果文件未创建则返回NULL;否则返回根节点（有值）
Strategy *init_strategy()
{
     Strategy *root=(Strategy*)malloc(sizeof(Strategy));
     root->left=root->right=NULL;
     Strategy *p=root;

     FILE *fp;
     if((fp=fopen(Strategy_filename,"r"))==NULL) 
     {
         if((fp=fopen(Strategy_filename,"w"))==NULL)
           {
            printf("%s文件创建失败!\n",Strategy_filename);
           }
           else printf("%s文件创建完成!\n",Strategy_filename);
           free(fp);
           return NULL;
     }
     else {
        fgetc(fp);
         while(!feof(fp))
         {
            fseek(fp,-1,1);
            fscanf(fp,"%lf",&p->origin);
            fscanf(fp,"%lf\n",&p->discont);
            if(p!=root)
            {
                search_insert(root,p);
            }
            p=(Strategy*)malloc(sizeof(Strategy));
            p->left=p->right=NULL;
            fgetc(fp);
         }
         free(p); 
         fclose(fp);
     }
    
    return root;
}
//初始化食物ID
void init_ID(Menu *p){
    ID=0;
    p=p->next;
    while(p)
    {
       ID = p->foodsinfo->food_id>ID ?p->foodsinfo->food_id :ID;
       p=p->next;
    }
}
//初始化Data,
Data * init_Data()
{
    Data *p=(Data*)malloc(sizeof(Data));
    p->Igd=init_Igd();
    p->menu=init_menu();
    p->users=init_user();
    p->strategy=init_strategy();
    init_queue(p);
    init_ID(p->menu);
    return p;
}

