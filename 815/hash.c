#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAXSIZE 100
#define HASHSIZE 12
#define NULLKEY -32768

typedef struct 
{
    int *elem;  //动态分配数组
    int count;
}HashTable;

int m = 0; //散列表表长，全局变量
 
int init_HashTable(HashTable *H)
{
    int i;

    m = HASHSIZE;
    H->count = m;
    H->elem =(int *)malloc(m*sizeof(int));

    for (int i = 0; i < m; i++)
    {
        H->elem[i] = NULLKEY;
    }
    
    return 1;
}

int Hash(int key)
{
    return key % m;
}
void insertHash(HashTable *H,int key)
{
    int addr = Hash(key);
    while (H->elem[addr] != NULLKEY)
    {
        addr = (addr+1) % m;
    }
    H->elem[addr] = key;
}
int searchHash(HashTable H,int key,int *result_addr)
{
    *result_addr = Hash(key);

    while (H.elem[*result_addr] != key)
    {
        *result_addr = (*result_addr+1) % m; 
        if (H.elem[*result_addr] == NULLKEY || *result_addr == Hash(key))
        {
            return -1;
        }
    }
    return 1;
}
int main()
{
	int arr[HASHSIZE] = {12, 67, 56, 16, 25, 37, 22, 29, 15, 47, 48, 34};
	int i, p, key, result;
	HashTable H;

	key = 39;

	init_HashTable(&H);
	for(i = 0; i < m; i++)
	{
		 insertHash(&H, arr[i]);
	}
	
	result = searchHash(H, key, &p);
	if (result)
	{
		printf("查找 %d 的地址为：%d \n", key, p);
	}
	else
	{
		printf("查找 %d 失败。\n", key);
	}

	for(i = 0; i < m; i++)
	{
		key = arr[i];
		searchHash(H, key, &p);
		printf("查找 %d 的地址为：%d \n", key, p);
	}

	return 0;
}