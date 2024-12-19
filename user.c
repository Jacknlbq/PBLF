#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Maxsize 30//名字长度上限
#define Max_Igd 20//原料上限
#define Max_table 50 //桌位
#define Max_user 1000//用户上限

#define Igd_filename "Igd.txt"
#define User_filename "User.txt"
#define Foods_filename "foods.txt"
#define Menu_filename "menu/txt"


//原料信息
typedef struct ingredient
{
    char Igd_name[Maxsize];//原料名
    int Igd_amount;//原料数量
}Ingredient;

//用户信息
 typedef struct  user{
    char ID[Maxsize];
    char code[Maxsize];
    char grade;//"区分用户等级，享受不同折扣,"A","B"...
    struct user *next;
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


//************************************************************************************************************************ */

User* create_user(char id[],char code[],char grade) 
{
    User* newUser = (User*)malloc(sizeof(User));
    strcpy(newUser->ID,id);
    newUser->ID[sizeof(newUser->ID)-1]='\0';

    strcpy(newUser->code,code);
    newUser->code[sizeof(newUser->code)-1]='\0';

    newUser->grade=grade;

    newUser->next=NULL;
    return newUser;
}

int isUserExist(User*head, char id[])
{
    User*temp=head;
    while(temp!= NULL )
    {
        if((strcmp(temp->ID,id)==0))
        {
        return 1;
        }
        temp=temp->next;
    }
    return 0;
}

void add_user(User **head,char id[],char code[],char grade)
{
    
    if(isUserExist(*head,id))
    {
        printf("用户名已经存在");
        return;
    }
    User *newUser =create_user(id,code,grade);
    if(*head==NULL)
    {
        *head=newUser;
    }
    else
    {
        User*temp =*head;
        while(temp->next!=NULL)
        {
            temp = temp->next;
        }
        temp->next = newUser;
    }
}//添加新用户

void delete_user(User **head,char id[])
{
    User*temp =*head;
    User*prev=NULL;
    if(temp != NULL && (strcmp(temp->ID,id)==0))
    {
        *head=temp->next;
        free(temp);
        return;
    }
    //检测第一个
    while(temp!= NULL && (strcmp(temp->ID,id)!=0))
    {
        prev=temp;
        temp=temp->next;
        free(temp);
    }
    //遍历
    if(temp=NULL)
    return;
    //不存在时返回
    prev->next=temp->next;
    free(temp);
}//删除用户

void changeCode(User *head,char id[],char newCode[])
{
    User*temp=head;
    while(temp!=NULL)
    {
        if((strcmp(temp->ID,id))==0)
        {
            strcpy(temp->code,newCode);
            return;
        }
        temp=temp->next;
    }
    printf("用户不存在");
}//更改密码

void changeGrade(User*head,char id[],char newgrade)
{
    User*temp=head;
    while(temp!=NULL)
    {
        if(strcmp(temp->ID,id)==0)
        {
            temp->grade = newgrade;
            return;
        }
        temp=temp->next;
    }
    printf("用户不存在");
}//更改等级

char* logIn(User*head,char id[],char code[])
{
    User*temp=head;
    while(temp!=NULL)
    {
        if((strcmp(temp->ID,id)==0) && (strcmp(temp->code,code)==0))
        {
            
            return temp->ID;
        }
        temp=temp->next;
    }
    
    return NULL;
}//登录，返回登录者id,失败返回空指针

void printInfo(User*head)
{
    User*temp=head;
        while (temp!=NULL)
        {
            printf("%s\t%s\t%c\n",temp->ID,temp->code,temp->grade);
            temp=temp->next;
        }
}

void main()
{
    char id_scan[Maxsize];
    char code_scan[Maxsize];
    char grade_scan;
    char current_user_id[Maxsize];
    int operation=0;
    User *head = NULL;
    
    while (1)
    {
        printf("指令菜单：\n");
        printf("1.注册用户；\n");
        printf("2.注销用户；\n");
        printf("3.更改密码；\n");
        printf("4.更改用户等级；\n");
        printf("5.登录；\n");
        printf("6.退出。\n");
        printf("7.打印。\n");
        printf("输入指令(使用数字): ");
        scanf("%d",&operation);
        switch (operation)
    {
    case 1:
        printf("输入id: ");
        scanf("%s",id_scan);
        printf("输入密码: ");
        scanf("%s",code_scan);
        printf("输入等级: ");
        scanf(" %c",&grade_scan);
        add_user(&head,id_scan,code_scan,grade_scan);
        break;

    case 2:
        printf("输入id: ");
        scanf("%s",id_scan);
        delete_user(&head,id_scan);
        break;
        
    case 3:
        printf("输入id: ");
        scanf("%s",id_scan);
        printf("输入新密码: ");
        scanf("%s",code_scan);
        changeCode(head,id_scan,code_scan);
        break;

    case 4:
        printf("输入id: ");
        scanf("%s",id_scan);
        printf("输入新等级: ");
        scanf(" %c",&grade_scan);
        changeGrade(head,id_scan,grade_scan);
        break;

    case 5:
        printf("输入id: ");
        scanf("%s",id_scan);
        printf("输入密码: ");
        scanf("%s",code_scan);
        if ((logIn(head,id_scan,code_scan))!=NULL)
        {
            printf("登录成功");
        }
        else
        {
            printf("登录失败");
        }
        
        strcpy(current_user_id,logIn(head,id_scan,code_scan));

    case 6:
        return;

    case 7:
        printInfo(head);
        break;
    
    default:
        printf("不存在的指令,请重新输入\n");
        break;
    }
    }    
}