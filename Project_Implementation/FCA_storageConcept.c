#include<stdio.h>
#include<stdlib.h>
int G,M,k=1,stop=2;

typedef struct node {
	int x;
    int val;
    struct node * next;
} node_C;//LIST TO STORE CONCEPTS OBJECTS AND ATTRIBUTES.
node_C* Obj_list = NULL;
node_C* Attr_list =  NULL;
node_C* Obj_head_ref = NULL;
node_C* Attr_head_ref = NULL;

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
    printf("Concept %d: {",k);
    int checkFiAttrSet=0;
    for(int i=0;i<n;i++)
    {
        if(*(a+i)==1)
        {
            Attr_list->x=k;
            Attr_list->val=i+1;
        	node_C* newAttrNode = (node_C*)malloc(sizeof(node_C));
        	Attr_list->next=newAttrNode;
        	Attr_list=newAttrNode;
        	Attr_list->next=NULL;
            printf(" A%d",i+1);
        }
        else
        checkFiAttrSet++;
        
    }
    if(checkFiAttrSet==n)
    {
        Attr_list->x=k;
        Attr_list->val=0;
        node_C* newAttrNode = (node_C*)malloc(sizeof(node_C));
        Attr_list->next=newAttrNode;
        Attr_list=newAttrNode;
        Attr_list->next=NULL;
        
    } 
    printf(" } -> { ");
    int g_derivative[G];
    initialize(g_derivative,G,1);
    derivative(a,g_derivative,Context);
    int checkFieObjSet=0;
    for(int i=0;i<G;i++)
    {
        if(g_derivative[i]==1)
        {   Obj_list->x=k;
            Obj_list->val=i+1;
        	node_C* newObjNode = (node_C*)malloc(sizeof(node_C));
        	Obj_list->next=newObjNode;
        	Obj_list=newObjNode;
        	Obj_list->next=NULL;
            printf("T%d ",i+1);
        }
        else
        checkFieObjSet++;
    }
    if(checkFieObjSet==G)
    {   Obj_list->x=k;
        Obj_list->val=0;
        node_C* newObjNode = (node_C*)malloc(sizeof(node_C));
        Obj_list->next=newObjNode;
        Obj_list=newObjNode;
        Obj_list->next=NULL;    
    }
    k++;
    printf(" }\n");
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
    Obj_list = (node_C *)malloc(sizeof(node_C));
    Attr_list = (node_C *)malloc(sizeof(node_C));
    Obj_head_ref = Obj_list;
    Attr_head_ref = Attr_list;

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


//WORKING OF OBJECT AND ATTRIBUTE LIST.
    node_C* Obj_list_ref = Obj_head_ref;
	while(Obj_list_ref->next!=NULL)
	{
		printf("T%d(%d)  ", Obj_list_ref->val, Obj_list_ref->x);
		Obj_list_ref = Obj_list_ref->next;
	}
    printf("\n");
	
	node_C* Attr_list_ref = Attr_head_ref;
	while(Attr_list_ref->next!=NULL)
	{
		printf("A%d(%d)  ", Attr_list_ref->val, Attr_list_ref->x);
		Attr_list_ref = Attr_list_ref->next;
	}
    printf("\n");

}

