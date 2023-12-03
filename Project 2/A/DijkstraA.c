//
//  main.c
//  Dijkstras
//
//  Created by Mythili Mulani on 02/10/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>

//The vertices start from 1 and go up to V, but the matrix indexes start from 0 and go up to V-1
typedef struct _graphmatrix{
    int V;
    int E;
    int **matrix;
}Graph;

//Array is used as a priority queue
typedef struct _priorityqueue{
    int PQsize;
    int* PQ;
} PriorityQueue;

//Data stores the arrays d (shortest distance from the source vertex), pi (the previous vertex in the shortest path), S (1 if the vertex has been selected, 0 if not)
//for vertex v, all the relevent data is at index v-1
typedef struct _data{
    int* d;
    int* pi;
    int* S;
}Data;

int comparisons = 0;
int fixingcomparisons = 0;
//Graph methods
void printGraphMatrix(Graph g);
void fillGraphMatrix(void);

//Priority Queue methods
void createPQ(Graph g,Data info, PriorityQueue* p);
void insert(int vertex, Data info, PriorityQueue* p);
void delete(int vertex, Data info, PriorityQueue* p);
void fix(Data info, PriorityQueue* p, int index);
bool emptyPQ(PriorityQueue p);


//Algorithm methods
void initialiseAlgo(Data* info, Graph g);
double dijkstra_matrix_array(Graph g);
void printData(Data info, int size);
void printShortestPath(Data info, int source, int target);

                       
void printShortestPath(Data info, int source, int target) {
    if (source == target) {
        return;
       // printf("%d ", info.pi[source-1]);
    } else if (info.pi[target-1] == 0) {
        printf("No path exists from %d to %d\n", source, target);
    } else {
        printShortestPath(info, source, info.pi[target-1]);
        printf("-> %d ", info.pi[target-1]);
    }
}



double dijkstra_matrix_array(Graph g){
    
    clock_t start_time = clock();
    
    Data info;
    initialiseAlgo(&info, g);
    PriorityQueue p;
    createPQ(g, info, &p);
    
    int sourceVertex = 1;
    //starting with source
    info.d[sourceVertex-1] = 0;
    fix(info, &p, sourceVertex-1);
    
    int curvertex, weight;
    
    while(!emptyPQ(p)){
        curvertex = p.PQ[0];
        info.S[curvertex-1] = 1;
        
        delete(curvertex, info, &p);
        
        for(int v=1; v<=g.V; v++){
            //checks for adjacent vertices
            weight = g.matrix[curvertex-1][v-1];
            if(weight!=0){
                comparisons++;
                //checking if vertex is still in the V-S set, since all the ones in S already have their shortest distance sorted
                if(info.S[v-1]==0){
                    
                    comparisons++;
                    //checking for if the distance needs to be updated
                    if(info.d[v-1]> info.d[curvertex-1]+weight){

                        delete(v, info, &p);
                        info.d[v-1] = info.d[curvertex-1]+weight;
                        info.pi[v-1] = curvertex;
                        insert(v, info, &p);
                    }
                }
            }

        }

    }
    
    clock_t end_time = clock();
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        return elapsed_time;
}

//prints Data
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
    printf("\n");
}

//initialises all the arrays in Data
void initialiseAlgo(Data* info, Graph g){
    info->d =  malloc(sizeof(int)*g.V);
    info->pi =  malloc(sizeof(int)*g.V);
    info->S =  malloc(sizeof(int)*g.V);
    
    //initialise d[v] to infinity for all v
    for(int i = 0; i < g.V; i++)
        info->d[i] = INT_MAX;
    
    //initialise S[v] to 0 for all v
    for(int i = 0; i < g.V; i++)
        info->S[i] = 0;
    
    //initialise pi[v] to 0 for all v, since values of V start from 1, this is okay to do
    for(int i = 0; i < g.V; i++)
        info->pi[i] = 0;
    
    
    //printData(*info, g.V);
}



void createPQ(Graph g, Data info, PriorityQueue* p){
    p->PQsize = g.V;
    p->PQ = malloc(sizeof(int)*g.V);
    for(int i = 0; i < g.V; i++)
        p->PQ[i] = i+1;

    //fix(info, p, 0);
}


//insert of a vertex is only done directly after the same vertex is deleted
//that vertex is stored at index PQsize (last index of priortiy queue is stored at index PQsize-1
//so we just have to increase the size by one (to include the vertex to be inserted), and call fix
void insert(int vertex, Data info, PriorityQueue* p){
    p->PQsize++;
    fix(info, p, (p->PQsize-1));
}


//swap the vertex to be deleted with the last element of the priority queue
// then reduce the size of the queue by one to exclude it
//call fix
void delete(int vertex, Data info, PriorityQueue* p){
    int vlast = p->PQ[p->PQsize-1];
    int index=0;
    while(p->PQ[index]!=vertex)
        index++;
    p->PQ[p->PQsize-1] = p->PQ[index];
    p->PQ[index] = vlast;
    p->PQsize--;
    fix(info, p, index);
}


//using insertion sort because at every point that fix is called, there is at most one element that is  out of place in the priority queue
//starting at index since that is the first element that is out of place, all the ones before it are sorted
//when coming from delete, index = index of deleted vertex since that is where we have added the last vertex after the swap
//when coming from insert, index = PQsize since that is where the element to be added is, everything before that is sorted.
void fix(Data info, PriorityQueue* p, int index){
    int temp, firstD, nextD, firstV, nextV;
    if(index==0) index++;
    

    for(int i=index; i<p->PQsize; i++){
        for(int j=i; j>0; j--){
            
            //comparing d[v]
            firstV = p->PQ[j-1];
            nextV = p->PQ[j];
            firstD = info.d[firstV-1];
            nextD = info.d[nextV-1];
            fixingcomparisons++;
            //if d[v] of the first is greater than next, swap
            if(firstD > nextD){
                temp = p->PQ[j-1];
                p->PQ[j-1] = p->PQ[j];
                p->PQ[j] = temp;
            }
            else
                break;
        }
    }
}

bool emptyPQ(PriorityQueue p){
    if(p.PQsize==0)
        return true;
    return false;
}

void fillGraphMatrix(void){
    
    clock_t start_time,end_time;
    double elapsed_time,algotime;
    
    // Get graph values from graphs.txt (generated by Input Generator,py
    FILE*input = fopen("/Users/mythilimulani/Documents/Sem3/SC2001/proj2/input2.txt", "r");

    // Create the output csv file
    FILE*output = fopen("/Users/mythilimulani/Documents/Sem3/SC2001/proj2/output.csv", "a");
    fprintf(output, "%s" ,"Number of edges, Number of vertices, Number of algocomparisons, Number of fixingcomparisons, graph creating time, algorithm time\n"); // Column headers
    //fclose(output);

    // If files not found
    if (input == NULL){
        printf("Error opening file");
        return;
    }

    else if (output == NULL){
        printf("Error opening file");
        return;
    }

    else{
        int n=0;
        fscanf(input, "%d", &n);
        
        while (n != -3){ // While not end of file
            
            // Number of edges and number of vertices
            int edge_no=0, vertice_no=0;
            fscanf(input,"%d",&edge_no);
            fscanf(input,"%d",&vertice_no);
            
            start_time = clock();
            
            Graph g;
            int i,j;
            
            g.V = vertice_no;
            g.E = edge_no;
            g.matrix = (int **)malloc(g.V*sizeof(int *));
            for(i=0;i<g.V;i++)
                g.matrix[i] = (int *)malloc(g.V*sizeof(int));
            
            for(i=0;i<g.V;i++)
                for(j=0;j<g.V;j++)
                    g.matrix[i][j] = 0;
            
            //filled such that row->column
            int V1, V2, weight;
            // printf("Enter two vertices a, b which are conected as such a-> b, also add the weight of the edge:\n");
            fscanf(input,"%d",&V1);
            while(V1!=-1)
            {
                fscanf(input,"%d",&V2);
                fscanf(input,"%d",&weight);
                if(V1>0 && V1<=g.V && V2>0 && V2<=g.V && weight>=0)
                {
                    
                    g.matrix[V1-1][V2-1] = weight;
                }
                else
                    break;
                //printf("Enter two vertices a, b which are conected as such a-> b, also add the weight of the edge:\n");
                fscanf(input,"%d",&V1);
            }
            end_time = clock();
            elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
            
            // Print graph
            printf("\ng.V = %d",g.V);
            
            // Implement Dijkstra's algorithm
            algotime = dijkstra_matrix_array(g);
            
            // Output results to output.csv
            fprintf(output, "%d, %d, %d, %d, %f, %f\n", vertice_no, edge_no, comparisons, fixingcomparisons, elapsed_time, algotime);
            
            for(int p = 0; p < g.V; p++){
                free(g.matrix[p]);
            }
            free(g.matrix);
            
            // Update n
            fscanf(input, "%d", &n); //(n=-2)
        }
    }

}

void printGraphMatrix(Graph g)
{
    int i,j;
    printf("\nNo of vertices: %d\n",g.V);
    printf("No of edges: %d\n",g.E);
    for(i=0;i<g.V;i++){
        for(j=0;j<g.V;j++)
            printf("%d\t",g.matrix[i][j]);
        printf("\n\n");
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");

    fillGraphMatrix();
    return 0;
}
