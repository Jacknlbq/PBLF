#include <stdio.h>
#include <stdlib.h>
#include "head.h"
int ID = 0;

Source *get_source(){
    int i = 0;
    Source source[Max_Igd];
    for (;i++;i<Max_Igd){
        source[i].source_Id = i+1;
        printf("请输入所需原料数量：");
        scanf("%d",&(source[i].source_amount));
    }
    return source;
}//获取原料列表

info_foods *get_info(){
    info_foods *info = (info_foods*)malloc(sizeof(info_foods));
    if (info == NULL){
        return NULL;
    }
    char food_name[Maxsize];
    char ch = '0';
    int i = 0;
    printf("请输入菜品名称：");
    while (ch = getchar() != "\n"){
    food_name[i++] = ch;
    }
    food_name[i] = '\0';
    
    int price = 0;
    printf("请输入菜品价格：");
    scanf("%.2f",&price);
    
    char food_description[100];
    char ch = '0';
    int j = 0;
    printf("请输入菜品名称：");
    while (ch = getchar() != "\n"){
    food_description[j++] = ch;
    }
    food_description[j] = '\0';
    
    Source *source = get_source();

    int NUM_source = 0;
    printf("请输入用料总数");
    scanf("%d",&NUM_source);
    strcpy(info->food_name, food_name);
    info->price = price;
    strcpy(info->food_description, food_description);
    info->source = source;
    info->NUM_source = NUM_source;
    return info;
}//获取菜品信息

void menu_insert(Menu *L){
    if (L->next == NULL){
        Menu *node = (Menu*)malloc(sizeof(Menu));
        if (node == NULL){
            return 0;
        }//检测申请内存是否成功
        info_foods *info = get_info();//调用获取食物信息函数
        node->foodsinfo = info;
        node->foodsinfo->food_id = ID;
        ID++;
        node->next = NULL;
        L->next = node;
        return 1;
    }//若链表为空，则创建一个新节点，并插入到链表头
    else{
        Menu *node = L->next;
        while (node->next!= NULL){
            node = node->next;
        }
        node->next = (Menu*)malloc(sizeof(Menu));
        if (node->next == NULL){
            return 0;
        }//检测申请内存是否成功
        info_foods *info = get_info();//调用获取食物信息函数
        node->next->foodsinfo = info;
        node->foodsinfo->food_id = ID;
        ID++;
        node->next->next = NULL;
        return 1;
    }//若链表不为空，则遍历到最后一个节点，并插入一个新节点
}
/*用例:
    menu_insert(menu1);
*/

void menu_delete(Menu *L){//food_name字符数组这里可能会出现有无空字符的问题，所以改用food_id
    if (L->next == NULL){
        return 0;
    }
    else{
        int i;
        printf("请输入您要删除的菜品ID:");
        scanf("%d",&i);
        Menu *node = L->next;
        Menu *pre = L;
        while (node->next!= NULL){
            if (node->foodsinfo->food_id == i){
                pre->next = node->next;
                free(node);
                return 1;
            }//循环遍历链表找到要删除的节点，并删除
            pre = node;
            node = node->next;
        }
        if (node->foodsinfo->food_id == i){
            pre->next = NULL;
            free(node);
            return 1;
        }//若要删除的节点是最后一个节点，则直接删除
    }
    return 0;
}
/*用例:
    menu_delete(Menu1);
*/

void menu_update(Menu *L){
    if (L->next == NULL){
        return 0;
    }//若链表为空，则返回
    else{
        Menu *node = L->next;
        int i = 0;
        printf("请输入您要修改的菜品ID:");
        scanf("%d",&i);
        while (node->next != NULL){
            if (node->foodsinfo->food_id == i){
                info_foods *info = get_info();//调用获取食物信息函数
                node-> foodsinfo = info;
                return 1;
            }
            node = node->next;
        }//循环遍历链表根据菜品名找到要修改的菜品，并修改菜品信息
        if (node->foodsinfo->food_id == i){
            info_foods *info = get_info();//调用获取食物信息函数
            node->foodsinfo = info;
            return 1;
        }
    }
    return 0;
}//修改单个菜品信息
/*用例：
    menu_update(Menu1);
*/

void menu_comment(Menu *L){
    if (L->next == NULL){
        return 0;
    }//若链表为空，则返回
    else{
        char *new_description;
        char ch;
        int i = 0;
        while((ch = getchar()) != '\n'){
            new_description[i++] = ch;
        }
        Menu *node = L->next;
        while (node->next != NULL){
            if (node->foodsinfo->food_id == i){
                strcpy(node->foodsinfo->food_description,new_description);
                return 1;
            }
            node = node->next;
        }//循环遍历链表根据菜品名找到要修改的菜品，并修改菜品信息
        if (node->foodsinfo->food_id == i){
            strcpy(node->foodsinfo->food_description,new_description);
            return 1;
        }
    }
    return 0;
}//仅修改单个菜品描述

void menu_print(Menu *L){
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
    return 0;
}//向用户打印菜单