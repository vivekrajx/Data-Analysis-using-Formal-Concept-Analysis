#include<stdio.h>
#include<stdlib.h>

int G,M,k=1,stop=2;
typedef struct node {
    int Concept_no;
	int index;
    int val;
    struct node * next;
} node_C;//LIST TO STORE CONCEPTS OBJECTS AND ATTRIBUTES.
node_C* Obj_list = NULL;
node_C* Attr_list =  NULL;
node_C* Obj_head_ref = NULL;
node_C* Attr_head_ref = NULL;
int IND_A=0;
int IND_O=0;

typedef struct node1 {
	int obj_first;
    int obj_last;
    int attr_first;
    int attr_last;
    struct node1 * next;
} FL_INDEX;  //LIST TO STORE CONCEPTS FTRST AND LAST INDEX.
FL_INDEX* Index = NULL;
FL_INDEX* Index_head = NULL;

//FUNCTIONS FOR QUICK SORT*********************
void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 
int partition (int arr[], int low, int high) 
{ 
    int pivot = arr[high];  
    int i = (low - 1); 
    for (int j = low; j <= high- 1; j++) 
    { 
        if (arr[j] < pivot) 
        { 
            i++; 
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 
void quickSort(int arr[], int low, int high) 
{ 
    if (low < high) 
    { 
        int pi = partition(arr, low, high); 
        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
    } 
} 
//********************************************

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
    Index->attr_first=IND_A;    //first index of concept attribute.
    int checkFiObjSet=0;
    for(int i=0;i<n;i++)
    {
        if(*(a+i)==1)
        {   Attr_list->Concept_no=k;
            Attr_list->index=IND_A; //attribute index
            Attr_list->val=i+1;
        	node_C* newAttrNode = (node_C*)malloc(sizeof(node_C));
        	Attr_list->next=newAttrNode;
        	Attr_list=newAttrNode;
        	Attr_list->next=NULL;
			printf(" A%d",i+1);
            IND_A++;
		}
		else
		checkFiObjSet++;
        
    }
    if(checkFiObjSet==n)
    {
        Attr_list->Concept_no=k;
        Attr_list->index=IND_A;
        Attr_list->val=0;
        node_C* newAttrNode = (node_C*)malloc(sizeof(node_C));
        Attr_list->next=newAttrNode;
        Attr_list=newAttrNode;
        Attr_list->next=NULL;
        IND_A++;
    
    }
    Index->attr_last=IND_A-1;//last index of concept attribute.
    
    printf(" } -> { ");
    int g_derivative[G];
    initialize(g_derivative,G,1);
    derivative(a,g_derivative,Context);
    Index->obj_first=IND_O;//first index of concept objects.
    int checkFieObjSet=0;
    for(int i=0;i<G;i++)
    {
        
        if(g_derivative[i]==1)
        {   Obj_list->Concept_no=k;
            Obj_list->index=IND_O;//Object index
            Obj_list->val=i+1;
        	node_C* newObjNode = (node_C*)malloc(sizeof(node_C));
        	Obj_list->next=newObjNode;
        	Obj_list=newObjNode;
        	Obj_list->next=NULL;
			printf("T%d ",i+1);
            IND_O++;
		}  
		else
		checkFieObjSet++;
    }
    if(checkFieObjSet==G)
    {
      Obj_list->Concept_no=k;
      Obj_list->index=IND_O;
      Obj_list->val=0;
      node_C* newObjNode = (node_C*)malloc(sizeof(node_C));
      Obj_list->next=newObjNode;
      Obj_list=newObjNode;
      Obj_list->next=NULL;
      IND_O++;  
    }
    Index->obj_last=IND_O-1;//last index of concept objects.
    FL_INDEX* newIndexNode = (FL_INDEX*)malloc(sizeof(FL_INDEX));
    Index->next=newIndexNode;
    Index=Index->next;
    Index->next=NULL;
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

    Index = (FL_INDEX*)malloc(sizeof(FL_INDEX));
    Index_head = Index; //first node of concept object_index and attribute_index.
    
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
    node_C* RR = Obj_head_ref;
    printf("OBJECT LIST :  ");
	while(RR->next!=NULL)
	{
		printf("T%d(%d)  ",RR->val,RR->index);
		RR=RR->next;
	}
    printf("\n");
	
	node_C* RRR = Attr_head_ref;
	printf("ATTRIBUTE LIST :  ");
	while(RRR->next!=NULL)
	{
		printf("A%d(%d)  ",RRR->val,RRR->index);
		RRR=RRR->next;
	}
    printf("\n");
    //printf("\n%d\n%d",IND_A,IND_O);

//WORKING OF OBJECT AND ARRAY INDEX LIST.
    printf("OBJECT_____INDEX        ATTRIBUTE_____INDEX \n");
    FL_INDEX* oo = Index_head;
    while(oo->next!=NULL)
	{
		printf("ObjF%d      ObjL%d         AttrF%d      AttrL%d\n",oo->obj_first,oo->obj_last,oo->attr_first,oo->attr_last);
		oo=oo->next;
	}
    printf("\n");
 
//SEARCHING IMPLEMENTATION **************************************************************************    
    int N;
    printf("Enter number of Objects: ");
    scanf("%d",&N);
    int SearchObjSet[N];
    printf("\nEnter Object Set to be searched : ");
    for(int i=0;i<N;i++)
    scanf("%d",&SearchObjSet[i]);
    if(N==1&&SearchObjSet[0]==0)
    {
        printf("\nCorresponding Attribute set to the given Object Set are : ");
        for(int i=1;i<=M;i++)
            printf("%d ",i);
    }
    else
    {
    quickSort(SearchObjSet, 0, N-1); 
    //check if given object set is present.
    node_C* Traverse_Obj_list = Obj_head_ref;
    int c=0,F,z,a=0;
    z=Traverse_Obj_list->Concept_no;//stores index of previous object
    while(Traverse_Obj_list!=NULL)
	{
		node_C* T =Traverse_Obj_list;
		F=T->index;
		int i,x,y;
		for(i=0;i<N;i++)
		{
		    if(T->val!=SearchObjSet[i])
		    break;
		    x=T->Concept_no;//stores index of current object.
		    T=T->next;
		    y=T->Concept_no;//stores index of next object.
		}
		if(i==N&&x!=y&&(x!=z||a==0))
		{
		    c++;
		    break;
		}
		a=1;
		z=Traverse_Obj_list->Concept_no;//stores index of previous object
		Traverse_Obj_list = Traverse_Obj_list->next;
	}
	if(c==0)
	printf("NOT FOUND ");
    else
    {
        int FirstAttrInd,LastAttrInd;
        FL_INDEX* TraverseIndexList = Index_head;
        while(TraverseIndexList!=NULL)
        {
            if(TraverseIndexList->obj_first==F)
            {
                FirstAttrInd=TraverseIndexList->attr_first;
                LastAttrInd=TraverseIndexList->attr_last;
                break;
            }
            TraverseIndexList = TraverseIndexList->next;
        }
        printf("\nCorresponding Attribute set to the given Object Set are : ");
        node_C* Traverse_Attr_list = Attr_head_ref;
        while(Traverse_Attr_list!=NULL)
        {
            if(Traverse_Attr_list->index>=FirstAttrInd&&Traverse_Attr_list->index<=LastAttrInd)
            printf(" A%d",Traverse_Attr_list->val);
            
            Traverse_Attr_list = Traverse_Attr_list->next;
            
            if(Traverse_Attr_list->index>LastAttrInd)
            break;
        }
    }
    }
// END OF SEARCHING IMPLEMENTATION ***************************************************************************************************************

}   
