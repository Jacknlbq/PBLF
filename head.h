#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Maxsize 30//名字长度上限
#define Max_Igd 20//原料上限
#define Max_table 50 //桌位


#define Igd_filename "Igd.txt"
#define User_filename "User.txt"
#define Foods_filename "Foods.txt"
#define Strategy_filename "Strategy.txt"



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
    struct user* next;
}User;

//用料信息
typedef struct source{
    int source_Id;//用于直接访问原料表Id-1即为顺序表下标。
    int source_amount;//原料数量
}Source;

//食物信息，名字，价格，用料指针，用料类数,唯一标识Id。
typedef struct info_foods{
    char food_name[Maxsize];
    int price;
    int food_id;
    int sale;
     Source *source;//顺序表存用料
     int NUM_source;//用料种类数
}info_foods;

//菜单信息，链表存储，数据单元为食物信息。
typedef struct menu{
   info_foods *foodsinfo;
   struct menu* next;
}Menu;

//点餐顺序，采用顺序表，队列
typedef struct queue{
    char  ID[Maxsize];
    int NUM_foods;
    int *foos_id;
}Queue;

//优惠策略,排序二叉树存储
typedef struct pstrategy{
    int origin;//原价
    double discont;
    struct pstrategy *left,*right;
}Strategy;


//用于访问各种数据
typedef struct Data{
    Ingredient *Igd;
    User *users;
    Menu *menu;
    Strategy *strategy;
    int head,tail,status;
    Queue* list;//指向队列头尾
}Data;
#ifndef WUYU_H
#define WUYU_H

extern int current_Igd;

Ingredient* init_Igd();
Menu *init_menu();
User* init_user();
Strategy *init_strategy();
void search_insert(Strategy *root,Strategy *p);

void push_Igd(Ingredient *p);
void push_Menu(Menu* p);
void push_user(User *p);
void push_strategy(Strategy* p);

#endif
