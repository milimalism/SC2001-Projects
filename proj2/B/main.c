//
//  main.c
//  dijkstras_2
//
//  Created by Mythili Mulani on 02/10/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct _listnode
{
    int vertex;
    int weight;
    struct _listnode *next;
} ListNode;

//list[i] stores list of vertexes adjacent to vertex (i+1)
typedef struct _graph{
    int V;
    int E;
    ListNode **list;
}Graph;

//heap is used as a priority queue. stores vertex with minimum distance at its root
typedef struct _heap{
    int PQsize;
    int * PQ ;
} Heap;

//Data stores the arrays d (shortest distance from the source vertex), pi (the previous vertex in the shortest path), S (1 if the vertex has been selected, 0 if not)
//for vertex v, all the relevent data is at index v-1
//array indexes stores the index of the vertex in the the heap
typedef struct _data{
    int* d;
    int* pi;
    int* S;
    int* indexes;
}Data;

//Graph methods
void printGraphList(Graph g);
void creategraph(void);

//Priority Queue methods
void constructPriorityQueue(Graph g, Heap* h, Data info);
void deleteMin(Heap* h, Data info);
void reaarangeHeap(Heap p, int vertex, Data info);
void fix_Heap(Heap h, int k, int root, Data info);
void printHeap (Heap p);
bool emptyPQ(Heap p);

//Algorithm methods
void dijkstra_list_heap(Graph g);
void initialiseAlgo(Data* info, Graph g);
void printData(Data info, int size);


void dijkstra_list_heap(Graph g){
    
    Data info;
    initialiseAlgo(&info, g);
    
    Heap p;
    constructPriorityQueue(g, &p, info);
    
    printf("\nEnter source vertex");
    int sourceVertex = 0;
    scanf("%d", &sourceVertex);
    
    //starting with source
    info.d[sourceVertex-1] = 0;
    reaarangeHeap(p, sourceVertex, info);
    
    
    ListNode* neighbour;
    int curVertex;
    while(!emptyPQ(p)){
        curVertex = p.PQ[1];
        deleteMin(&p, info);
        info.S[curVertex-1] = 1;
        
        neighbour = g.list[curVertex-1];
        while(neighbour!=NULL){
            
            //check if still in V-S
            if(info.S[neighbour->vertex-1]==0){
                
                //compare distances to minimise it
                if(info.d[neighbour->vertex-1] > ((info.d[curVertex-1])+ neighbour->weight)){
                    
                    //change the distance of neighbour->vertex
                    info.d[neighbour->vertex-1] = ((info.d[curVertex-1])+ neighbour->weight);
                    info.pi[neighbour->vertex-1] = curVertex;
                    
                    //rearrange the heap
                    reaarangeHeap(p, neighbour->vertex, info);
                }
            }
            
            //continue to next neighbour
            neighbour = neighbour->next;
        }
        //to see the arrays after each vertex is chosen
        printf("\nCurrent Vertex: %d\n", curVertex);
        printData(info, g.V);
        printHeap(p);
    }
    
}



void initialiseAlgo(Data* info, Graph g){
    info->d =  malloc(sizeof(int)*g.V);
    info->pi =  malloc(sizeof(int)*g.V);
    info->S =  malloc(sizeof(int)*g.V);
    info->indexes =  malloc(sizeof(int)*g.V);
    
    //initialise d[v] to infinity for all v
    for(int i = 0; i < g.V; i++)
        info->d[i] = INT_MAX;
    
    //initialise S[v] to 0 for all v
    for(int i = 0; i < g.V; i++)
        info->S[i] = 0;
    
    //initialise pi[v] to 0 for all v, since values of V start from 1, this is okay to do
    for(int i = 0; i < g.V; i++)
        info->pi[i] = 0;
    
    //initialise indexes[v] to 0 for all v, since heap indexes start from 1, this is okay to do
    for(int i = 0; i < g.V; i++)
        info->indexes[i] = i+1;
    
    
    printData(*info, g.V);
}


void printData(Data info, int size){
    int j = size;
    printf("\n   ");
    for(j=0;j<size;j++)
        printf("%d\t",j+1);
    printf("\n");printf("\nd  ");
    
    for(j=0;j<size;j++)
        printf("%d\t",info.d[j]);
    printf("\n");printf("\nS  ");
    
    for(j=0;j<size;j++)
        printf("%d\t",info.S[j]);
    printf("\n");printf("\npi ");
    
    for(j=0;j<size;j++)
        printf("%d\t",info.pi[j]);
    printf("\n");printf("\nid ");
    
    for(j=0;j<size;j++)
        printf("%d\t",info.indexes[j]);
    printf("\n");
}


void reaarangeHeap(Heap p, int vertex, Data info){
    //get index of vertex whose distance has been changed
    int vertexIndex = info.indexes[vertex-1];
    int parentIndex = vertexIndex/2;
    int vertexDistance = info.d[p.PQ[vertexIndex]-1];
    int parentDistance = info.d[p.PQ[vertexIndex/2]-1];
    
    //reaarange heap by checking vertex distance with parent and moving it up since the value can only be smaller than it was
    while(parentIndex>0 && parentDistance>vertexDistance){ //swap
        
        //swap heap elements
        p.PQ[vertexIndex] = p.PQ[parentIndex];
        p.PQ[parentIndex] = vertex;
        
        //update indexes
        info.indexes[vertex-1] = parentIndex;
        info.indexes[p.PQ[vertexIndex]-1] = vertexIndex;
        
        //continue loop
        vertexIndex = parentIndex;
        parentIndex = vertexIndex/2;
        vertexDistance = info.d[p.PQ[vertexIndex]-1];
        parentDistance = info.d[p.PQ[parentIndex]-1];
    }
}

void constructPriorityQueue(Graph g, Heap* p, Data info){
    p->PQsize = g.V;
    p->PQ = malloc((p->PQsize + 1) * sizeof(int));
    p->PQ[0] = 0;
    
    //initially all distances are same so it doesnt matter how you fill in the heap
    for(int i = 1; i <= g.V; i++)
        p->PQ[i] = i;
    
}


void fix_Heap(Heap p, int k, int root, Data info){
    //iterative approach
    int j = root, cj;
    while(j*2<=p.PQsize){
        cj = (j*2<p.PQsize && info.d[p.PQ[j*2]-1]>info.d[p.PQ[j*2+1]-1])? j*2+1 : j*2;
        if(info.d[p.PQ[cj]-1] >= info.d[k-1]){
            p.PQ[cj/2] = k;
            break;
        }
        info.indexes[p.PQ[cj]-1] = cj/2;
        p.PQ[cj/2] = p.PQ[cj];
        j = cj;
    }
    p.PQ[j] = k;
    info.indexes[k-1] = j;
    
}

void deleteMin(Heap* h, Data info){
    int k = h->PQ[h->PQsize];
    h->PQsize=h->PQsize-1;
    fix_Heap(*h, k, 1, info);
}


bool emptyPQ(Heap p){
    if(p.PQsize==0)
        return true;
    return false;
    
}

void printHeap(Heap p){
    printf("\n\n");
    for(int i = 0; i<= p.PQsize; i++)
        printf("%d ", p.PQ[i]);
    printf("\n\n");
}



void creategraph(void){
    
    printf("Enter number of vertices\n");
    int N;
    scanf("%d", &N);
    
    //create graph
    Graph g;
    g.V = N;
    g.E = 0;
    g.list = (ListNode **) malloc(g.V*sizeof(ListNode *));
    
    int i,j;
    for(i=0;i<g.V;i++)
        g.list[i] = NULL;
    
    int V1, V2, weight;
    ListNode* temp;
    //printf("Enter two vertices a, b which are conected as such a-> b, also add the weight of the edge:\n");
    scanf("%d",&V1);
    while(V1!=-1)
    {
        scanf("%d",&V2);
        scanf("%d",&weight);
        if(V1>0 && V1<=g.V && V2>0 && V2<=g.V && weight>=0)
        {
            
            if(g.list[V1-1]==NULL){
                g.list[V1-1] = (ListNode *)malloc(sizeof(ListNode));
                g.list[V1-1]->vertex = V2;
                g.list[V1-1]->weight = weight;
                g.list[V1-1]->next = NULL;
            }
            else{
                temp = (ListNode *)malloc(sizeof(ListNode));
                temp->next = g.list[V1-1];
                temp->vertex = V2;
                temp->weight = weight;
                g.list[V1-1] = temp;
            }
            g.E++;
        }
        else
            break;
       // printf("Enter two vertices a, b which are conected as such a-> b, also add the weight of the edge:\n");
        scanf("%d",&V1);
    }
    printGraphList(g);
    
    dijkstra_list_heap(g);
}


void printGraphList(Graph g){
    int i;
    ListNode* temp;

    for(i=0;i<g.V;i++)
    {
        printf("%d:\t",i+1);
        temp = g.list[i];
        while(temp!=NULL){
            printf("%d(%d) -> ",temp->vertex, temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    creategraph();
    return 0;
}
