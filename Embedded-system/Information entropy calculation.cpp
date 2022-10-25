#include<stdio.h>
#include<math.h>

 
int main()//计算信息熵 H(X) 
{
	while(1)
	{
		
		int n=0;
 
		double result=0;
		printf("请输入H(X)包含的元素个数：");	
		scanf("%d",&n);
		double A[n];
		double B[n];
		for(int i=0;i<n;i++)
		{
			printf("H(X)中第%d个元素为：",i+1);
	
			scanf("%lf",&A[i]);	
		}
		for(int m=0;m<n;m++)
		{
			B[m]=-((A[m])*log2(A[m]));
			result += B[m];
		}
		printf("The result is %lf\n\n",result);
	}
} 


