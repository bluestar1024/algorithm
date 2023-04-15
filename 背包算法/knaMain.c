#include<stdio.h>
#define MAX(A,B) ((A)>(B)?(A):(B))
unsigned int a=10,b=34;
float w[100]={2,8,4,4,8,7,8,5,16,16},p[100]={15,25,9,9,15,12,12,6,14,9},sum;

int funct(unsigned int i,unsigned int j)
{
	//printf("递归判断：%d,%d\n",i,j);
	if((i>0)&&(j>=w[i-1]))
	{
		printf("递归中1：%d,%d,%f,%f\n",i,j,w[i-1],p[i-1]);
		return MAX(funct(i-1,j),funct(i-1,j-w[i-1])+p[i-1]);
	}
	else if((i>0)&&((j<w[i-1])&&(j>0)))
	{
        printf("递归中2：%d,%d,%f,%f\n",i,j,w[i-1],p[i-1]);
	    return funct(i-1,j);
	}
	else //if((i=0)||(j=0))
	{
		printf("返回0：%d,%d\n",i,j);
		return 0;
	}
	/*else
	{
		printf("计算出错：%d,%d\n",i,j);
		return -0.01;
	}*/
}

int main()
{
    printf("开始递归：%d,%d\n",a,b);
	sum=funct(a,b);
	printf("装入背包物品的最大价值：%f\n",sum);
	while(1);
}
