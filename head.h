#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Maxsize 30//名字长度上限
#define Max_Igd 20//原料上限
#define Max_table 50 //桌位

#define Igd_filename "Igd.txt"
#define User_filename "User.txt"
#define Foods_filename "foods.txt"
#define Menu_filename "menu/txt"


//原料信息
typedef struct ingredient{
    char Igd_name[Maxsize];//原料名
    int Igd_amount;//原料数量
}Ingredient;

//用户信息
 typedef struct  user{
    char ID[Maxsize];
    char code[Maxsize];
    char grade;//"区分用户等级，享受不同折扣,"A","B"...
}User;

//用料信息
typedef struct source{
    int source_Id;//用于直接访问原料表Id-1即为顺序表下标。
    int source_amount;//原料数量
}Source;

//食物信息，名字，价格，用料头指针，用料总类数。
typedef struct info_foods{
    char food_name[Maxsize];
    int price;
     Source *source;//顺序表存用料
     int NUM_source;//用料种类数
}info_foods;

//菜单信息，链表存储，数据单元为食物信息。
typedef struct menu{
   info_foods *foodsinfo;
   struct menu* next;
}Menu;

//点餐顺序，采用顺序表，队列
typedef struct list{
    char  ID[Maxsize];
}List;

//用于访问各种数据
typedef struct Data{
    Ingredient *Igd;
    User *users;
    Menu *menu;
    List* head,*tail;//指向队列头尾
}Data;
