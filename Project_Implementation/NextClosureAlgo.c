#include<stdio.h>
#include<stdlib.h>
int G,M,k=1,stop=2;
void derivative(int *A,int g_derivative[],int Context[G][M]) 
{
    for(int i=0;i<M;i++)
    {
        if(*(A+i)==0)
        continue;
        for(int j=0;j<G;j++)
        {
            if(Context[j][i]==0)
            g_derivative[j]=0;
        }
    }
}
void initialize(int A[],int n,int value)
{
    for(int i=0;i<n;i++)
    A[i]=value;
    return;
}
void initialize_closure(int *A,int n,int value)
{
    for(int i=0;i<n;i++)
    *(A+i)=value;
    return;
}
int* Closure(int Context[G][M],int* A)
{
    int* B = (int*)malloc(M);
    initialize(B,M,1);
    for(int i=0;i<G;i++)
    {
        int flag=0;
        for(int j=0;j<M;j++)
        {
            if(*(A+j)==1 && Context[i][j]!=1)
            {
                flag=1;
                break;
            }
        }
        if(flag==0)
        {
            for(int j=0;j<M;j++)
            {
                if(B[j]==1 && Context[i][j]==1)
                continue;
                else
                B[j]=0;
            }
        }
    }
    return B;
}
void Print(int *a,int n,int Context[G][M])
{
    printf("Concept %d:",k);
    k++;
    for(int i=0;i<n;i++)
    {
        if(*(a+i)==1)
        printf(" A%d",i+1);
    }
    printf(" -> ");
    int g_derivative[G];
    initialize(g_derivative,G,1);
    derivative(a,g_derivative,Context);
    for(int i=0;i<G;i++)
    {
        if(g_derivative[i]==1)
        printf("T%d ",i+1);
    }
    printf("\n");
}
int* NextClosure(int *A,int Context[G][M])
{
    for(int m=M-1;m>=0;m--)
    {
        if(*(A+m)==1)
        *(A+m)=0;
        else
        {
            int temp[M];
            for(int i=0;i<M;i++)
            {
                if(*(A+i)==0)
                temp[i]=0;
                else 
                temp[i]=1;
            }
            temp[m]=1;
            int* B=temp;
            B=Closure(Context,B);
            int flag=0;
            for(int i=m-1;i>=0;i--)
            {
                if(*(B+i)==1 && *(A+i)==0)
                {
                    flag=1;
                    break;
                }
            }
            if(flag==0)
            return B;
        }
    }
    *A=stop;
    return A;
    
}
void Concepts(int Context[G][M])
{
    int A[M];
    initialize(A,M,0);
    int *A_Closure=A;
    A_Closure=Closure(Context,A_Closure);
    do
    {
        Print(A_Closure,M,Context);
        A_Closure=NextClosure(A_Closure,Context);
    }while(*A_Closure!=stop);
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
	printf("A - Attribute\n");
	printf("T - Object\n");
	Concepts(Context);
}



