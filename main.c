#include "head.h"

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
        case 4:
           putout(p);
            return 0;    
        default:
            break;
        }
    }
    
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
//菜单界面
void menu_system(Data *p)
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
//原料库管理
void ingredient_system(Data *p)
{
    int operation=0;
    while (1)
    {
        printf("**************************************\n");
        printf("指令菜单：\n");
        printf("1.添加原料；\n");
        printf("2.删除原料；\n");
        printf("3.查看原料；\n");
        printf("4.更新原料；\n");
        printf("5.退出。\n");
        printf("输入指令(使用数字): ");
        scanf("%d",&operation);
        switch (operation)
    {
    case 1:
        insert_Igd(p->Igd);
        break;

    case 2:
        delete_Igd(p->Igd);
        break;

    case 3:
        show_Igd(p->Igd);
        break;

    case 4:
        update_Igd(p->Igd);
        break;

    case 5:
        return;
    default:
        printf("不存在的指令,请重新输入\n");
        break;
    }
    }
}
//管理员界面
void manager_main(Data *p)
{
    int operation=0;
    while (1)
    {
        printf("**************************************\n");
        printf("指令菜单：\n");
        printf("1.菜单管理；\n");
        printf("2.出餐。\n");
        printf("3.原料库管理；\n");
        printf("4.查看餐厅信息。\n");
        printf("5.修改餐厅信息。\n");
        printf("6.优惠策略管理。\n");
        printf("7.退出。\n");
        printf("输入指令(使用数字): ");
        scanf("%d",&operation);
        switch (operation)
      {
        case 1:
            menu_system(p);
             break;
        case 2:
            pop_queue(p);
            break;
        case 3:
            ingredient_system(p);
            break;
        case 4: 
            printf("**************************************\n");
            printf("餐厅信息如下：\n");
            printf("餐厅名：%s\n",p->res->res_name);
            printf("联系方式：%s\n",p->res->res_contactnum);
            printf("地址：%s\n",p->res->res_address);
            printf("店主：%s\n",p->res->res_owner);
            break;
        case 5:
            modify_res(p->res);
            break;
        case 6:
            strategy_system(p->strategy);
            break;
        case 7:
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
//优惠策略管理
void strategy_system(Strategy *p)
{
    int operation=0;
    while (1)
    {
        printf("**************************************\n");
        printf("指令菜单：\n");
        printf("1.添加策略；\n");
        printf("2.删除策略；\n");
        printf("3.修改策略；\n");
        printf("4.查看策略；\n");
        printf("5.退出。\n");
        printf("输入指令(使用数字): ");
        scanf("%d",&operation);
        switch (operation)
    {
    case 1:
        insert_strategy(&p);
        break;

    case 2:
        delete_strategy(&p);
        break;

    case 3:
        modify_strategy(p);
        break;

    case 4:
        print_strategy(p);
        break;

    case 5:
        return;
    default:
        printf("不存在的指令,请重新输入\n");
        break;
    }
    }
}
