/**
 * # 5、实验设备管理系统设计

实验设备信息包括：设备编号，设备种类(如：微机、打印机、扫描仪等等)，设备名称，设备价格，设备购入日期，是否报废，报废日期等。

实现功能包括：

（1）能够完成对设备的录入和修改

（2）对设备进行分类统计

（3）设备的破损耗费和遗损处理

（4）设备的查询

要求：系统以菜单方式工作。
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Date
{
    int year;
    int month;
    int day;
}Date;

typedef struct equipment
{
    int No;
    char type[100];
    char name[100];
    double price;
    Date date;
    int is_scrapped;
    Date scrapped_date;
}equipment;
typedef struct node
{
   equipment info;
   struct node* next; 
}node;
// 定义全局变量head
node *head = NULL;
void insert_node(node **listHead, node *target)
{
    if (*listHead == NULL) 
    {
        *listHead = target;
    } else 
    {
        target->next = *listHead;
        *listHead = target;
    }
}
void show(node **linkhead)
{
node *current = *linkhead;

    printf("%-10s %-15s %-20s %-10s %-15s %-10s %-15s\n", 
           "No", "Type", "Name", "Price", "Purchase Date", "is_Scrapped", "Scrapped Date");
    printf("=============================================================================================================\n");

    while (current != NULL) {
        printf("%-10d %-15s %-20s %-10.2lf %04d/%02d/%02d      %-12s ", 
               current->info.No, current->info.type, current->info.name, current->info.price,
               current->info.date.year, current->info.date.month, current->info.date.day,
               current->info.is_scrapped ? "Yes" : "No");

        if (current->info.is_scrapped) {
            printf("%04d/%02d/%02d", 
                   current->info.scrapped_date.year, current->info.scrapped_date.month, current->info.scrapped_date.day);
        }

        printf("\n");

        current = current->next;
    }
    int totalEquipment = 0;
    double totalPrice = 0.0;
    int scrappedCount = 0;

    current = *linkhead; 
    while (current != NULL)
    {
        totalEquipment++;
        totalPrice += current->info.price;
        if (current->info.is_scrapped)
        {
            scrappedCount++;
        }
        current = current->next;
    }

    printf("汇总:");
    printf("\t总件数: %-30d 总价: %-25.2lf\t 报废数: %-20d \n", totalEquipment,totalPrice,scrappedCount);

}
void release_link(node **linkhead)
{
    while (*linkhead != NULL)
    {
        node *temp = *linkhead;
        *linkhead = (*linkhead)->next;
        free(temp);
    }
}

//（1）能够完成对设备的录入和修改
void analyze_data()
{
    //将文件中的内容写入链表中
    FILE* fp = fopen("equipment.dat","rb");
    if ( fp == NULL)
    {
        printf("文件打开失败\n");
        return ;
    }
    if (head != NULL)
    {
        release_link(&head);
    }
    
    equipment information;
    //node *temp = (node*)malloc(sizeof(node));
    while(fread(&information,sizeof(equipment),1,fp) == 1)
    {
        node *temp = (node*)malloc(sizeof(node));
        temp->info = information;
        temp->next = NULL;
        insert_node(&head,temp);
    }
    show(&head);
    fclose(fp);
}

void insert_eqp()
{
    if (head == NULL)
    {
        printf("还未解析文件，逻辑错误！\n");
        return ;
    }
    
    node *new_node = (node *)malloc(sizeof(node)); // 分配内存给新节点

    printf("请输入新的设备的编号、设备类型、设备名称，设备价格，设备购入日期，是否报废(0/1)，报废日期: ");
    scanf("%d %s %s %lf %d %d %d %d",
          &new_node->info.No, new_node->info.type, new_node->info.name, &new_node->info.price,
          &new_node->info.date.year, &new_node->info.date.month, &new_node->info.date.day,
          &new_node->info.is_scrapped);
    if (new_node->info.is_scrapped == 1)
    {
        printf("请输入报废日期\n");
        scanf("%d %d %d", &new_node->info.scrapped_date.year,&new_node->info.scrapped_date.month,&new_node->info.scrapped_date.day);
    }
    

    insert_node(&head,new_node);
}
void write_file()
{
    FILE *fp = fopen("equipment.dat","wb");
    if (fp == NULL)
    {
        printf("文件打开失败\n");
        return ;
    }
    node * temp = head;
    for (*temp; temp != NULL; temp = temp->next)
    {
        if(fwrite(&temp->info,sizeof(equipment),1,fp) != 1)
        {
            printf("文件写入错误");
        }
    }
    printf("文件写入成功\n");
    fclose(fp);
}
int search_type(const char* search_type)
{
    node *temp = head;
    while (temp != NULL)
    {
        if (strcmp(temp->info.type,search_type) == 0 )
        {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}
void statistics()
{
    printf("请输入要统计的设备种类\n");
    char eqp_type[100];
    scanf("%s",eqp_type);
    if (search_type(eqp_type) == 0)
    {
        printf("没有该类设备\n");
        return ;
    }else
    {
        // 并不修改，故创建临时链表存储统计数据
        node *statistics_head = NULL;
       node *temp = head;
       while (temp != NULL)
       {
            if (strcmp(temp->info.type, eqp_type) == 0)
            {
                node * new_node =(node *)malloc(sizeof(node));
                new_node->info = temp->info;
                new_node->next = NULL;
                insert_node(&statistics_head,new_node);
            }
            temp = temp->next;
       }
       show(&statistics_head);
    }
}
// 考虑到其他字段可能又重复，从设计角度考虑No是唯一的唯一字段，故使用No作为基准搜索节点
node *search_node(int No)
{
    node *temp = head;
    while (temp != NULL)
    {
        if (temp->info.No == No)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
void del_node(node *target_node)
{
    if(target_node == head)
    {
        head =target_node->next;
        free(target_node);
    }else
    {
        node *pre = head;
        while (pre != NULL)
        {
            if (pre->next == target_node)
            {
                pre->next = target_node->next;
                target_node->next = NULL;
                free(target_node);
                printf("删除成功!\n");
                return ;
            }
            pre = pre->next;
        }
        printf("没找到该序号，查找失败！\n");
           
    }

}
void del_scrapped()
{
    node *temp = head;
    while (temp != NULL)
    {
        if (temp->info.is_scrapped == 1)
        {
            printf("%s 被删除",temp->info.name);
            del_node(temp);
            
        }
        
        temp = temp->next;
    }
    
}
int main(int argc, char const *argv[])
{
    int choice;

    while (1)
    {
        printf("1. 录入设备\n2. 显示设备信息\n3. 加载文件\n4. 写入文件\n5. 统计选定种类\n6. 查看当前链表内容\n"
       "7. 删除设备信息(按编号)\n8. 处理报废设备(删除信息)\n9. 退出\n");

        printf("请选择操作：");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            insert_eqp();
            break;
        case 2:
            show(&head);
            break;
        case 3:
            analyze_data();
            break;
        case 4:
            write_file();
            break;
        case 5:
            statistics();
            break;
        case 6:
            show(&head);
            break;
        case 7:
            printf("请输入设备的编号\n");
            int No;
            scanf("%d",&No);
            del_node(search_node(No));
            show(&head);
            break;
        case 8:
            del_scrapped();
            show(&head);
            break;
        case 9:
            // 释放链表内存
            release_link(&head);
            exit(0); // 退出程序
        default:
            printf("无效的选择。\n");
        }
    }

    return 0;
}

