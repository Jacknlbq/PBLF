#include"head.h"

//插入Igd
void insert_Igd(Ingredient *p)
{
    printf("输入原料名:");
    scanf("%s",p[current_Igd].Igd_name);
    printf("输入原料数量:");
    scanf("%d",&p[current_Igd].Igd_amount);
    current_Igd++;
    printf("插入成功！\n");
}
//删除Igd
void delete_Igd(Ingredient *p)
{
    int n;
    printf("输入要删除的原料编号:");
    scanf("%d",&n);
    if(n>current_Igd||n<=0)
    {
        printf("没有该原料！\n");
        return;
    }
    for(int i=n-1;i<current_Igd-1;i++)
    {
        p[i]=p[i+1];
    }
    current_Igd--;
    printf("删除成功！\n");
}
//展示Igd
void show_Igd(Ingredient *p)
{
    for(int i=0;i<current_Igd;i++)
    {
        printf("**************************************\n");
        printf("原料编号:%d\n",i+1);
        printf("原料名:%s\n",p[i].Igd_name);
        printf("原料数量:%d\n",p[i].Igd_amount);
    }
}
//原料库更新
void update_Igd(Ingredient *p)
{
    printf("**************************************\n");
    printf("输入要更新的原料编号:");
    int n;
    scanf("%d",&n);
    if(n>current_Igd||n<=0)
    {
        printf("没有该原料！\n");
        return;
    }
    printf("输入添加量:");
    int m;
    scanf("%d",&m);
    p[n-1].Igd_amount+=m;
}
//餐厅信息修改
void modify_res(Res_info *p)
{
    printf("**************************************\n");
    printf("输入新的餐厅名:");
    scanf("%s",p->res_name);
    printf("输入新的联系方式:");
    scanf("%s",p->res_contactnum);
    printf("输入新的地址:");
    scanf("%s",p->res_address);
    printf("输入新的店主:");
    scanf("%s",p->res_owner);
    printf("输入新的管理员密码:");
    scanf("%s",p->manager_code);
    printf("修改成功！\n");
}
