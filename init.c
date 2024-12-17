#include "head.h"

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
           fscanf(fp,"%d\n",p[i].Igd_amount);
           fgetc(fp);
           i++;
       }
       fclose(fp);
       printf("原料表已经初始化，现已有%d个元素。",i);
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
        else printf("文件创建完成！\n");
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
        fscanf(fp,"%d",&s->price);
        fscanf(fp,"%d",s->NUM_source);
        
        Source *q=(Source*)malloc(sizeof(Source)*s->NUM_source);
        for(int i=0;i<s->NUM_source;i++)
        {
            fscanf(fp,"%d",&q[i].source_Id);
            fscanf(fp,"%d\n",&q[i].source_amount);
        }
         s->source=q;
         tail->foodsinfo=s;

         fgetc(fp);
      }
              fclose(fp);
   }
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

            new=(User*)malloc(sizeof(User));
            new->next=NULL;
            //节点交替
            s->next=new;
            s=new;

            fseek(fp,-1,1);
            fscanf(fp,"%s\n",s->ID);
            fscanf(fp,"%s\n",s->code);
            fscanf(fp,"%c\n",s->grade);
            fgetc(fp);
        }
        
    }
    return p;
}

//初始化Data,
void init_Data(Data* p)
{
    p=(Data*)malloc(sizeof(Data));
    p->head=p->tail=NULL;
    p->Igd=init_Igd();
    p->menu=init_menu();
    p->users=init_user();
}

