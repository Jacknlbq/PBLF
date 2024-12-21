#include "head.h"
extern int current_Igd;

int main()
{
    Data *p=init_Data();//初始化数据
    int operation=0;
    printf("**************************************\n");
    printf("欢迎来到餐厅管理系统！\n");


    while(1)
    {
        printf("**************************************\n");
        printf("指令菜单：\n");
        printf("1.用户系统；\n");
        printf("2.管理员系统；\n");
        printf("3.点餐；\n");
        printf("4.退出。\n");
        printf("输入指令(使用数字): ");
        printf("**************************************\n");
        scanf("%d",&operation);
        switch (operation)
        {
        case 1:
            User_main(p->users);
            break;
        case 2:
            if(manager_logIn(p->res))
            {
                manager_main(p);
            }
            break;
        case 3:
            order_system(p);
            break;    
        default:
            break;
        }
    }

    push_Igd(p->Igd);
    push_Menu(p->menu);
    push_user(p->users);
    push_strategy(p->strategy);


    return 0;
}
//用户主函数,传入用户链表头指针
void User_main(User *head)
{
    int operation=0;  
    printf("**************************************\n");
    printf("欢迎来到用户系统！\n");  
    while (1)
    {
        printf("**************************************\n");
        printf("指令菜单：\n");
        printf("1.注册用户；\n");
        printf("2.注销用户；\n");
        printf("3.登录；\n");
        printf("4.退出。\n");
        printf("输入指令(使用数字): ");
        scanf("%d",&operation);
        switch (operation)
    {
    case 1:
        add_user(head);
        break;

    case 2:
        delete_user(head);
        break;

    case 3:
        User *temp;
        if (temp=logIn(head))
        {
            printf("登录成功\n");
            local_user(temp);
        }
        else
        {
            printf("登录失败\n");
        }
                break;
    case 4:
        return;
    default:
        printf("不存在的指令,请重新输入\n");
        break;
    }
    }    
}
//管理员登录
int manager_logIn(Res_info *res)
{
    char code[Maxsize];
    printf("**************************************\n");
    printf("正在进行管理员登录！\n");
    printf("请输入管理员密码: ");
    scanf("%s",code);
    int i=0;
    while(strcmp(code,res->manager_code)!=0)
    {
        if(i==4)
        {
            printf("密码错误次数过多,请稍后再试！\n");
            return 0;
        }
        i++;
        printf("密码错误,请重新输入!\n");
        printf("输入密码: ");
        scanf("%s",code);
    }
    printf("登录成功！\n");
    return 1;
    
}
//管理员界面
void manager_main(Data *p)
{
    int operation=0;
    while (1)
    {
        printf("**************************************\n");
        printf("指令菜单：\n");
        printf("1.添加菜品；\n");
        printf("2.删除菜品；\n");
        printf("3.修改菜品信息；\n");
        printf("4.查看菜品信息；\n");
        printf("5.退出。\n");
        printf("输入指令(使用数字): ");
        scanf("%d",&operation);
        switch (operation)
    {
    case 1:
        menu_insert(p->menu);
        break;

    case 2:
        menu_delete(p->menu);
        break;

    case 3:
        menu_update(p->menu);
        break;

    case 4:
        menu_print(p->menu);
        break;

    case 5:
        return;
    default:
        printf("不存在的指令,请重新输入\n");
        break;
    }
    }
}
//点餐系统
void order_system(Data *p)
{
    int operation=0;
    printf("**************************************\n");
    printf("欢迎来到点餐系统！\n");
    while (1)
    {
        printf("**************************************\n");
        printf("指令菜单：\n");
        printf("1.点餐；\n");
        printf("2.查看菜单；\n");
        printf("3.退出。\n");
        printf("输入指令(使用数字): ");
        scanf("%d",&operation);
        switch (operation)
        {
            case 1:
                insert_queue(p);
                break;
            case 2:
                menu_print(p->menu);
                break;
            case 3:
                return;
            default:
                printf("不存在的指令,请重新输入\n");
                break;
        }
    }
}