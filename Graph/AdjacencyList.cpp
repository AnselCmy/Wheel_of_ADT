#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#define MAXVERNUM 100 
#define INF 9999

#define ElementType string //string is not a type which can use typedef
typedef int CostType;
/***
+ UDG: undirected graph
+ UDN: undirected net
+ DG:  direcred graph
+ DN:  direcred net
***/
using namespace std;

/***
##SideNode:
+ use alloc number to represent the data
+ next is the link to chain the next point
***/
typedef struct SideNode_
{
    int allocNum; 
    CostType cost; 
    SideNode_* next; 
} SideNode;

/***
##HeadNode:
+ all real vertexs are stored in the head
+ the first of sideList is `vacant`
***/
typedef struct HeadNode_
{
    ElementType data; 
    SideNode* sideList; 
    int sideListLen;
} HeadNode;

/***
##AdjaList:
+ headList is a vector to store the pointer of HeadNode
+ verNum is the number of vertex
***/
typedef struct AdjaList
{
    vector<HeadNode*> headList; 
    int verNum;
    string graphKind; 
} Graph;


/***
get the allocated number of this vertex in graph
***/
int GetTheNum(string vertex, Graph* graph)
{
    for(int i=0; i<graph->verNum; i++)
    {
        if(graph->headList[i]->data == vertex)
        {
            return i;
        }
    }
    return -1;   
}

// void
int* Dijkstra(Graph* graph, /*int dist[], int path[],*/ string first)
{
/**/int* dist = new int[graph->verNum];
    int* path = new int[graph->verNum];

    int *solved = new int [graph->verNum];
    CostType minDist;
    SideNode* p;
    // initial
    for(int i=0; i<graph->verNum; i++)
    {
        solved[i] = 0; // '0' means not solved 
        dist[i] = INF;
        path[i] = -1;
    }
    // solve the first vertex
    solved[GetTheNum(first, graph)] = 1;
    dist[GetTheNum(first, graph)] = 0;
    path[GetTheNum(first, graph)] = -1;
    p = graph->headList[GetTheNum(first, graph)]->sideList->next; // the first is vacant

    while(p)
    {
        dist[p->allocNum] = p->cost; // the distance to the first
        path[p->allocNum] = GetTheNum(first, graph); // the immediate predecessor of p
        p = p->next;
    }

    int nearestVertex;
    
    // solve the vertexs except the first
    
    // 'for(int i=0; i<graph->verNum; i++)' is available
    // <--attention-->
    // never code it as 'for(int i=0; i<graph->verNum-1; i++)'
    // cause one less loop in this 'for loop' can't meet the condition of
    // jumping out of the function which is 'minDist == INF'
    // using while(1) is the most secure
    while(1)
    {
        minDist = INF;
        // find the vertex has the nearest dis to first
        for(int j=0; j<graph->verNum; j++)
        {
            if(solved[j] == 0 && dist[j] < minDist)
            {
                nearestVertex = j;
                minDist = dist[j];
            }
        }
        if(minDist == INF)
            // return;
/**/        return dist;
        solved[nearestVertex] = 1;

        // reflush the dis from node adjacent to nearestVertex to the first
        p = graph->headList[nearestVertex]->sideList->next;
        while(p)
        {
            if(solved[p->allocNum] == 0 && minDist + p->cost < dist[p->allocNum])
            {
                dist[p->allocNum] = minDist + p->cost;
                path[p->allocNum] = nearestVertex;
            }
            p = p->next;
        }
    }
}

int CreatGraphFromFile(char* fileName, Graph *graph)
{
    ifstream f;
    f.open(fileName); //the parameter of open can only be char*,not string
    // used for get kind in first line
    string kind;
    // used for get all vertex in second line 
    string vertex;
    string vertexName;
    stringstream ssVertex; //transform string into stringstream for getline
    // used for transform string into int 
    string weight;
    stringstream ssWeight;
    
    graph->verNum = 0;
    
    //1 get the kind of the graph
    getline(f, kind);
    graph->graphKind = kind;

    //2 get all vertexs and alloc them a number 
    getline(f, vertex); //put all vertexs into string vertex
    ssVertex << vertex;

    while(getline(ssVertex, vertexName, ' '))
    {
        // creat a new headnode and use push_back to push it into vector
        HeadNode* tempHeadNode = new HeadNode;
        tempHeadNode->data = vertexName;
        tempHeadNode->sideListLen = 0;
        //tempHeadNode->sideList = NULL;
        tempHeadNode->sideList = new SideNode; //also allocate the space for sideList of the head
        tempHeadNode->sideList->next = NULL;
        
        graph->headList.push_back(tempHeadNode);
        graph->verNum++;
    }

    while(1)
    {
        if(f.peek() == EOF) //avoid that reading teice at the last line
            break;

        //3 get the contain of the graph by line
        getline(f, vertex); 
        ssVertex.clear();
        ssVertex << vertex;
        int parseData[3];

        for(int j=0; j<2; j++) //only two vertex in one line
        {
            getline(ssVertex, vertexName, ' ');
            for(int i=0; i<graph->verNum; i++)
            {   
                if(graph->headList[i]->data == vertexName)
                {
                    parseData[j] = i;
                    break;
                }
            }
        }
        if(graph->graphKind == "UDN" || graph->graphKind == "DN")
        {
            getline(ssVertex, weight, ' ');
            ssWeight << weight;
            ssWeight >> parseData[2];
            ssWeight.clear();
        }

        //4 put the data into graph
        int row = parseData[0];
        int col = parseData[1];
        SideNode* tempSideNode = new SideNode;
        tempSideNode->allocNum = col;
        tempSideNode->next = NULL;
        tempSideNode->cost = 1; //if graph, use 1
        if(graph->graphKind == "UDN" || graph->graphKind == "DN") //graph has no cost
        {
            tempSideNode->cost = parseData[2];
        }

        SideNode* temp = graph->headList[row]->sideList; //get the first of sideList
        while( temp->next!=NULL )
        {
            temp = temp->next;
        }
        temp->next = tempSideNode;
        graph->headList[row]->sideListLen++;
    }
}
          
void PrintAdjaList(Graph* graph)
{
    int number;
    cout << "GraphKind:" << graph->graphKind << endl;
    for(int i=0; i<graph->verNum; i++)
    {

        cout << graph->headList[i]->data << "--"; //print the head
        SideNode* tempSideNode = graph->headList[i]->sideList->next; //first of sideList is vacant
        for(int j=0; j<graph->headList[i]->sideListLen; j++)
        {
            number = tempSideNode->allocNum;
            cout << graph->headList[number]->data;
            if(graph->graphKind == "UDN" || graph->graphKind == "DN")
            {
                cout <<'('<< tempSideNode->cost <<')';
            }
            cout << "--";
            tempSideNode = tempSideNode->next;
        }
        cout << endl << "|" << endl;
    }
}

int main(int argc, char const *argv[])
{
    Graph *graph = new Graph;
    char fileName[] = "graph2.txt";
    CreatGraphFromFile(fileName, graph);
    //PrintAdjaList(graph);
    
    // int* dist = new int[graph->verNum];
    // int* path = new int[graph->verNum];
    // Dijkstra(graph, dist, path, "1");
    int* dist = Dijkstra(graph, "1");

    //cout << GetTheNum("2", graph);

    for(int i=0; i<graph->verNum; i++)
    {
        cout << dist[i] << " ";
    }
    
    // cout << endl;
    // for(int i=0; i<graph->verNum; i++)
    // {
    //     cout << path[i] << " ";
    // }
    return 0;
}