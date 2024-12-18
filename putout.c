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
            fprintf(fp,"%d ",s->price);
            fprintf(fp,"%d\n",s->NUM_source);
            for(int i=0;i<s->NUM_source;i++)
            {
                fprintf(fp,"%d %d\n",s->source[i].source_Id,s->source[i].source_amount);
            }
           p=p->next;
        }
        printf("菜单数据库已更新完毕!\n");

    }

    fclose(fp);
} 
//更新用户数据库
