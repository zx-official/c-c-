#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct good_info
{
    double price;      //物品效益
    double sum_price;  //物品总价值
    double get_rate;   //获得此物品占总数的比例
    int get_weight;    //获得此物品的物品数量
    int sum_weight;    //物品总重量
} good_info;

 void print_array(good_info *goods, int n);

/*********按物品效益，重量比值做序排列***************/
void insert_sort_by_price(good_info *goods, int n)
{
    int i, j;
    good_info tmp;

    for(i = 1; i < n; i++)
    {

        tmp = goods[i];
        j = i - 1;
        while ((j >= 0) && (tmp.price > goods[j].price))
        {
            goods[j + 1] = goods[j];
            j--;
        }

        goods[j + 1] = tmp;
    }
}

 void bag(good_info *goods, int capacity, int n)
 {
 	int left;
    int i;

    for(i = 0; i < n; i++)
    {
    	goods[i].get_weight = 0;
    }

    left = capacity;                     //背包剩余容量

    for(i = 0; i < n; i++)
    {
        if(left <= goods[i].sum_weight )   //当该物品重量大与剩余容量跳出
        {
            break;
       	}

        goods[i].get_weight = goods[i].sum_weight;
        goods[i].get_rate  = 1.0;

        left -= goods[i].sum_weight;                        //确定背包新的剩余容量
    }

    if(i < n)
    {
    	goods[i].get_weight = left;                          //该物品所要放的量
    	goods[i].get_rate = left * 1.0 / goods[i].sum_weight;//该物品所要放的量
    }

 }

 void print_array(good_info *goods, int n)
 {
 	int i;

 	for(i = 0; i < n; i++)
	{
		printf("%d\t%lf\t%lf\t%d\t%lf\n",
				goods[i].sum_weight,
				goods[i].sum_price,  goods[i].price,
				goods[i].get_weight, goods[i].get_rate);
	}
    printf("\n");
}

//贪心法解决背包问题
int main(int argc, char const *argv[])
{
	int n = 10;
    int i;
    int  capacity;

    good_info *goods;//定义一个指针
    goods = (good_info *)malloc(sizeof(good_info) * n);
	if (goods == NULL)
	{
		printf("malloc failed\n");
		exit(1);
	}

    srand(time(NULL));
   	for(i = 0; i < n; i++)
	{
		goods[i].sum_weight = rand() % 50 +1;
		goods[i].sum_price = rand() % 100 + 1;
		goods[i].price = goods[i].sum_price/goods[i].sum_weight;//得出物品的重量比
	}
    printf("original states: \n");
    print_array(goods, n);

	printf("背包的最大容量：");
    scanf("%d", &capacity);
    printf("directly Greed result \n");
    bag(goods, capacity, n);
   	print_array(goods, n);

    insert_sort_by_price(goods, n);
	bag(goods, capacity, n);
   	print_array(goods, n);

	free(goods);

	return 0;
}
