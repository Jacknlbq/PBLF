#include "head.h"
//创建节点
User* create_user() 
{
    
    User* newUser = (User*)malloc(sizeof(User));
    printf("输入该账户的id: ");
    scanf("%s",newUser->ID);
    printf("输入该账户的密码: ");
    scanf("%s",newUser->code);
    newUser->grade='C';
    printf("当前用户等级：%c\n",newUser->grade);
    newUser->consumption=newUser->surplus=0;
    printf("用户创建完成！\n");

    newUser->next=NULL;
    return newUser;
}

//检查id是否存在,存在返回对应节点的前驱节点，不存在返回NULL
User* isUserExist(User*head, char id[])
{
        while(head->next)
    {
        if((strcmp(head->next->ID,id)==0))
        {
             return head;
        }
        head=head->next;
    }
    return NULL;
}
//添加新用户
void add_user(User *head)
{
    User *newUser=create_user();
    while(isUserExist(head,newUser->ID))
    {
        printf("该id已存在,请重新输入!\n");
        printf("输入该账户的id: ");
        scanf("%s",newUser->ID);
    }
    //头插法
    newUser->next=head->next;
    head->next=newUser;
    printf("添加成功！\n");
}
//删除用户
void delete_user(User *head)
{
    char id[Maxsize];
    printf("输入要删除的用户的id: ");
    scanf("%s",id);
    User *temp;
    while(!(temp=isUserExist(head,id)))
    {
        printf("用户不存在,请重新输入!\n");
        printf("输入要删除的用户的id: ");
        scanf("%s",id);
    }
    char code[Maxsize];
    printf("输入该用户密码: ");
    scanf("%s",code);
    int i=0;
    while(strcmp(temp->next->code,code)!=0)
    {
        i++;
        printf("密码错误,请重新输入!\n");
        printf("输入密码: ");
        scanf("%s",code);
        if(i==3)
        {
            printf("密码错误次数过多,请稍后再试！\n");
            return;
        }
    }
    User *del=temp->next;
    temp->next=del->next;
    free(del);
    printf("删除成功！\n");
    return;
}

//更改密码
void changeCode(User *temp)
{   
    printf("输入新密码: ");
    scanf("%s",temp->code);
    printf("修改成功！\n");
}
//充钱系统。
void recharge(User* temp)
{
    printf("删除用户，充值金额概不退还\n");

    printf("充值金额: ");
    double money;
    scanf("%lf",&money);
    temp->surplus+=money;
    temp->consumption+=money;
    printf("充值成功！\n");
    printf("当前余额为%.2lf\n",temp->surplus);
    if(temp->consumption>=upgrademoney&&temp->grade!='A')
    {
        printf("恭喜亲爱的大冤种！您单笔消费%d元,您的等级将升级！\n",upgrademoney);
        temp->grade-=1;
        printf("当前用户等级：%c\n",temp->grade);
    }
}

//登录，返回用户节点,失败返回空指针
User* logIn(User* head)
{
    char id[Maxsize];
    char code[Maxsize];
    printf("输入用户id: ");
    scanf("%s",id);
    User*temp;
    int i=0;
    while(!(temp=isUserExist(head,id)))
    {
        i++;
        printf("用户不存在,请重新输入!\n");
        printf("输入用户id: ");
        scanf("%s",id);
        if(i==4)
        {
            printf("次数过多,请稍后再试！\n");
            return NULL;
        }
    }
    printf("输入该用户密码: ");
    scanf("%s",code);
    i=0;
    while(strcmp(temp->next->code,code)!=0)
    {
        i++;
        printf("密码错误,请重新输入!\n");
        printf("输入密码: ");
        scanf("%s",code);
        if(i==4)
        {
            printf("密码错误次数过多,请稍后再试！\n");
            return NULL;
        }
    }
    return temp->next;
}
//打印用户信息
void printInfo(User* temp)
{
    printf("**************************************\n");
    printf("用户信息：\n");
    printf("用户id: %s\n",temp->ID);
    printf("用户等级: %c\n",temp->grade);
    printf("用户余额: %.2lf\n",temp->surplus);
    printf("用户消费总额: %.2lf\n",temp->consumption);
}
//用户内部
void local_user(User *local)
{
     printf("**************************************\n");
     printf("欢迎用户%s\n",local->ID);

     while(1)
        {
            printf("**************************************\n");
            printf("指令菜单：\n");
            printf("1.修改密码；\n");
            printf("2.充值；\n");
            printf("3.查看用户信息；\n");
            printf("4.退出。\n");
            printf("输入指令(使用数字): ");
            int operation;
            scanf("%d",&operation);
            switch (operation)
            {
            case 1:
                changeCode(local);
                break;
            case 2:
                recharge(local);
                break;
            case 3:
                printInfo(local);
                break;
            case 4:
                return;
                break;    
            default:
                printf("不存在的指令,请重新输入\n");
                break;
            }
        }
}
