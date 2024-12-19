#include "head.h"
int ID;

//获取原料列表,n为原料种类数
Source *get_source(int n)
{
    int i = 0;
    Source *source = (Source*)malloc(sizeof(Source)*n);
     for(int i=0;i<n;i++)
        {
            printf("请输入原料Id:");
            scanf("%d",&source[i].source_Id);
            printf("请输入原料消耗量:");
            scanf("%d\n",&source[i].source_amount);
        }
    return source;
}

info_foods *get_info()
{
    info_foods *info = (info_foods*)malloc(sizeof(info_foods));
    if (info == NULL){
        return NULL;
    }
    
    printf("请输入菜品名称：");
    scanf("%s",info->food_name);
    

    printf("请输入菜品价格：");
    scanf("%d",&info->price);
    
    info->food_id = ID++;

    printf("请输入菜品所需原料种类数：");
    scanf("%d",&info->NUM_source);

    info->source = get_source(info->NUM_source);

    printf("请输入菜品描述：");
    scanf("%s",info->food_description);
    return info;
}//获取菜品信息
//新加菜品
void menu_insert(Menu *L)
{
        Menu *node = (Menu*)malloc(sizeof(Menu));
        node->foodsinfo = get_info();//调用获取食物信息函数
        //头插法插入
        node->next = L->next;
        L->next = node;
        printf("菜品添加成功！\n");
}
//删除菜品
void menu_delete(Menu *L)
{
        int i;
        printf("请输入您要删除的菜品的ID:");
        scanf("%d",&i);
        while (L->next){
            if (L->next->foodsinfo->food_id == i){
                Menu *node = L->next;
                L->next = node->next;
                free(node->foodsinfo->source);
                free(node);
                printf("删除成功！\n");
                return ;
            }
            L=L->next;
         }
        printf("没有找到该菜品！\n");
}
//修改菜品信息
void menu_update(Menu *L)
{
   int i;
        printf("请输入您要更改的菜品ID:");
        scanf("%d",&i);
        while (L->next){
            if (L->next->foodsinfo->food_id == i){
                printf("请输入新的菜品信息：\n");

                Menu *node = L->next->next;
                free(L->next->foodsinfo->source);
                free(L->next);
                Menu *new_node = (Menu*)malloc(sizeof(Menu));
                new_node->foodsinfo = get_info();
                new_node->next = node;
                L->next = new_node;
                printf("修改成功！\n");
                return ;
            }
            L=L->next;
         }
        printf("没有找到该菜品！\n");
}
//仅修改单个菜品描述
void menu_comment(Menu *L)
{
        
        int i;
        printf("请输入您要描述的菜品的ID:");
        scanf("%d",&i);
        while (L->next){
            if (L->next->foodsinfo->food_id == i){
                printf("请输入新的菜品描述：\n");
                scanf("%s",L->next->foodsinfo->food_description);
                printf("修改成功！\n");
                return ;
            }
            L=L->next;
         }
        printf("没有找到该菜品！\n");
    
}
void menu_print(Menu *L)
{
    if (L->next == NULL){
        printf("菜单为空!\n");
        return;
    }
    else{
        Menu *node = L->next;
        while (node != NULL){
            printf("菜名:%s\n", node->foodsinfo->food_name);
            printf("价格:%d\n", node->foodsinfo->price);
            printf("描述:%s\n", node->foodsinfo->food_description);
            //这里的输出效果还需要完善
            node = node->next;
        }
    }
}//打印菜单
