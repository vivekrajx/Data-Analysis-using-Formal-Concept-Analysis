#include<stdio.h>
#include<math.h>
#include<stdlib.h>
int G,M;
void initialize(int A[],int n,int value)
{
    for(int i=0;i<n;i++)
    A[i]=value;
    return;
}
void derivative(int g_derivative[],int context[G][M],int i) 
{
    for(int j=0;j<M;j++)
    {
        if(context[i][j]==1)
        g_derivative[j]=1;
        else 
        g_derivative[j]=0;
    }
       
}
void Closure(int a[],int context[G][M],int B[])
{
    for(int i=0;i<G;i++)
    {
        int flag=0;
        int g_derivative[M];
        derivative(g_derivative,context,i);
        for(int j=0;j<M;j++)
        {
            if(a[j]==1 && g_derivative[j]!=1)
            {
                flag=1;
                break;
            }
        }
        if(flag==0)
        {
            for(int j=0;j<M;j++)
            {
                if(B[j]==1 && g_derivative[j]==1)
                continue;
                else
                B[j]=0;
            }
        }
    }
}
int main()
{
    printf("Enter number of objects and attributes: ");
	scanf("%d %d", &G, &M);
	int Context[G][M];
	printf("Enter the context: \n");
	for (int i = 0;i < G;i++)
	{
		for (int j = 0;j < M;j++)
		{
			scanf("%d",&Context[i][j]);
		}
	}
    int A[M],B[M];
    printf("\nEnter the attribute set: ");
    for(int i=0;i<M;i++)
    scanf("%d",&A[i]);
    initialize(B,M,1);
    Closure(A,Context,B);
    for(int i=0;i<M;i++)
    {
        printf("%d ",B[i]);
    }
}

