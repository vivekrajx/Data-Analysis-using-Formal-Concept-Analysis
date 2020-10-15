#include<stdio.h>
#include<stdlib.h>
int G,M,k=1,stop=2;
int power(int a,int b)
{
    int temp=1;
    for(int i=0;i<b;i++)
    temp*=a;
    return temp;
}
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
void binary(int n,int binary_array[],int number_of_attributes)
{
    int i = 0; 
    for(int i=0;i<number_of_attributes;i++) 
    { 
        binary_array[i] = n % 2; 
        n = n / 2; 
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
double stability(int *A,int B[],int Context[G][M]) 
{
    double num=0,dem=0;
    int number_of_attributes=0;
    for(int i=0;i<M;i++)
    {
        if(*(A+i)==1)
        number_of_attributes++;
    }
    if(number_of_attributes==0)
    return 1;
    int temp[number_of_attributes],subset[M],p=0;
    for(int i=0;i<M;i++)
    {
        if(*(A+i)==1)
        {
            temp[p]=i;
            p++;
        }
    }
    for(int i=0;i<number_of_attributes;i++)
    dem=power(2,number_of_attributes);
    for(int i=0;i<dem;i++)
    {
        initialize(subset,M,0);
        int binary_array[number_of_attributes];
        binary(i,binary_array,number_of_attributes);
        for(int j=0;j<number_of_attributes;j++)
        {
            if(binary_array[j]==1)
            subset[temp[j]]=1;
        }
        int* array_pointer=subset;
        int subset_derivative[G];
        initialize(subset_derivative,G,1);
        derivative(array_pointer,subset_derivative,Context);
        int flag=0;
        for(int j=0;j<G;j++)
        {
            if(subset_derivative[j]!=B[j])
            {
                flag=1;
                break;
            }
        }
        if(flag==0)
        num++;
    }
    return num/dem;
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
    printf("%0.4f\n",stability(a,g_derivative,Context));
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



