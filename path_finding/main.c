#include<stdio.h>
#include<math.h>
float D(int u,int v,float matrix[][6])
{
    return matrix[u][v];
}
void short_path(int* nodes,float* cost,float matrix[][6])
{
    for(int n=0;n<6;n++)//n is the number of elements in N'
    {
        int pivot_node=n;
        //first choose the pivot node
        for(int i=n+1;i<6;i++)
        {
            if(cost[i]<cost[pivot_node])
            {
                pivot_node=i;
            }
        }
        //you have your pivot node now.
        //now bring all the pivots to the left by swapping the appropriate indices.
        float temp=cost[pivot_node];
        cost[pivot_node]=cost[n];
        cost[n]=temp;
        int tem=nodes[pivot_node];
        nodes[pivot_node]=nodes[n];
        nodes[n]=tem;
        //after swapping, there are n+1 nodes in N' ie the nodes from 0 till n in the nodes array belong to N'(and so do the corresponding cost values).
        //update the values of cost using the present pivot.
        for(int i=n+1;i<6;i++)
        {
            float temp=cost[n]+D(nodes[n],nodes[i],matrix);
            if(cost[i]>temp)
            {
                cost[i]=temp;
            }
        }
        //cost has been updated.
        
    }
}
int main()
{
    float k=INFINITY;
    //following is the adjacency matrix that captures the graph information.
    float matrix[6][6]={{0,3,k,1,k,k},
        {3,0,3,6,15,2},
        {k,3,0,k,k,9},
        {1,6,k,0,12,k},
        {k,15,k,12,0,6},
        {k,2,9,k,6,0}};
    float matrix2[6][6]={ {0,1.5,k,k,k,0.7},
        {k,0,1.1,k,k,k},
        {k,k,0,k,3,k},
        {k,2.3,4.5,0,k,k},
        {k,k,k,k,0,k},
        {k,k,k,k,6.5,0}};
            
    
    //float cost[6]={0,3,k,1,k,k};//node 1 is the source node.
    float cost[6]={k,2.3,4.5,0,k,k};
    int nodes[6]={0,1,2,3,4,5};//maintains the order of the nodes.
    short_path(nodes,cost,matrix2);
    for(int i=0;i<6;i++)
    {
        printf("the length of the shortest path between the source node and node %d is %f\n",1+nodes[i],cost[i]);
    }
    
}

