#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Maxsize 30//名字长度上限
#define Max_Igd 20//原料上限
#define Max_table 50 //桌位
#define upgrademoney 1000//升级金额

#define Igd_filename "Igd.txt"
#define User_filename "User.txt"
#define Foods_filename "Foods.txt"
#define Strategy_filename "Strategy.txt"
#define Resturant_filename "Resturant.txt"


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
    double surplus;//余额
    double consumption;//消费总额
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
    double price;
    int food_id;
    char food_description[100];//菜品描述
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
    int status;//是否是会员
    int NUM_foods;
    int *foos_id;
}Queue;

//优惠策略,排序二叉树存储
typedef struct pstrategy{
    double origin;//原价
    double discont;
    struct pstrategy *left,*right;
}Strategy;

typedef struct res_info{
    char res_name[Maxsize];//餐厅名
    char res_owner[Maxsize];//餐厅所有者
    char res_contactnum[18];//联系电话
    char res_address[Maxsize];//餐厅地址
    float res_turnover;//= 0.00 餐厅营业额
    float res_profit;//= res_turnover*5 餐厅利润
    char manager_code[Maxsize];//管理员密码
}Res_info;

//用于访问各种数据
typedef struct Data{
    Ingredient *Igd;
    User *users;
    Menu *menu;
    Strategy *strategy;

    int head,tail;
    Queue* list;//点餐队列

    Res_info *res;

}Data;
#ifndef WUYU_H
#define WUYU_H

extern int current_Igd;
extern int ID;

Ingredient* init_Igd();
Menu *init_menu();
User* init_user();
Strategy *init_strategy();
Data * init_Data();
void init_ID(Menu *p);
void search_insert(Strategy *root,Strategy *p);
Res_info* init_res();


void push_Igd(Ingredient *p);
void push_Menu(Menu* p);
void push_user(User *p);
void push_strategy(Strategy* p);
void push_res(Data *p);
void putout(Data *p);


void insert_queue(Data *q);
Queue *init_queue(Data *q);
Menu *search_foods(int ID,Menu *p);
void pop_queue(Data* q);
Strategy *search_strategy(double origin,Strategy *p);
int search_ingredient(Ingredient *p,Menu *q);
void modify_ingredient(Ingredient *p,Menu *q);


Source *get_source(int n);
info_foods *get_info();
void menu_insert(Menu *L);
void menu_delete(Menu *L);
void menu_update(Menu *L);
void menu_comment(Menu *L);
void menu_print(Menu *L);

User* logIn(User*head);
void local_user(User *local);
void printInfo(User* temp);
void recharge(User* temp);
void changeCode(User *temp);
void delete_user(User *head);
void add_user(User *head);
User* isUserExist(User*head, char id[]);
User* create_user() ;

void User_main(User *head);
void order_system(Data *p);
void manager_main(Data *p);
void strategy_system(Strategy *p);
void ingredient_system(Data *p);
int manager_logIn(Res_info *res);

void insert_Igd(Ingredient *p);
void delete_Igd(Ingredient *p);
void show_Igd(Ingredient *p);
void update_Igd(Ingredient *p);
void modify_res(Res_info *p);

void print_strategy(Strategy *p);
void insert_strategy(Strategy **p);
void delete_strategy(Strategy **p);
void modify_strategy(Strategy *p);
Strategy*  search_equvial(Strategy *root,Strategy *p);


#endif
