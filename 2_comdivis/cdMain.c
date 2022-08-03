#include <stdio.h>

int main(void)
{
    unsigned int d[100],i;
    printf(">:");
    scanf("%u%u",d,d+1);
    for(i = 0;d[i+1] != 0;i++)
    {
	   d[i+2] = d[i] % d[i+1];
    }
    printf("%u\n",d[i]);
    return 0;
}
