#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#define INF 9999
using namespace std;

typedef struct sideNode_
{
    int crossingNum;
    int cost;
} sideNode;

typedef struct headNode_
{
    int data;
    vector<sideNode*> sideList;
} headNode;


vector<headNode*> CreatGraphFromTerminal(vector<int>& loc)
{
    // input the info 
    int info[3];
    /*info[0] friends
      info[1] crossing
      info[2] road*/ 
    for(int i=0; i<3; i++)
    {
        cin >> info[i];
    }

    // input their location
    //vector<int> loc;
    int temp;
    for(int i=0; i<info[0]; i++)
    {
        cin >> temp;
        loc.push_back(temp);
    }

    // initial the garph
    vector<headNode*> graph;
    for(int i=1; i<=info[1]; i++)
    {
        headNode* tempHeadNode = new headNode;
        tempHeadNode->data = i;
        graph.push_back(tempHeadNode);
    }

    int row, col, cost;
    for(int i=1; i<=info[2]; i++)
    {
       cin >> row;
       cin >> col;
       cin >> cost;
       // this is a undirection graph
       sideNode* tempSideNode1 = new sideNode;
       tempSideNode1->cost = cost;
       tempSideNode1->crossingNum = col;
       sideNode* tempSideNode2 = new sideNode;
       tempSideNode2->cost = cost;
       tempSideNode2->crossingNum = row;
       graph[row-1]->sideList.push_back(tempSideNode1);
       graph[col-1]->sideList.push_back(tempSideNode2);
    }
    return graph;
}

void PrintGraph(vector<headNode*> graph)
{
    vector<headNode*>::iterator iter1 = graph.begin();
    vector<sideNode*>::iterator iter2;
    for(iter1; iter1 != graph.end(); iter1++)
    {
        cout << (*iter1)->data; // iter point the headNode*, so * is needed
        for(iter2 = (*iter1)->sideList.begin(); iter2 != (*iter1)->sideList.end(); iter2++)
        {
            cout << "--" << (*iter2)->crossingNum;
        }
        cout << endl;
    }    
}

int* Dis(vector<headNode*> graph, int* solved, int* dist, int firstLoc)
{
    // int* solved = new int[graph.size()+1]; // the 0 is vacant position
    // int* dist = new int[graph.size()+1];
    // initial
    for(int i=1; i<=graph.size(); i++)
    {
        solved[i] = 0;
        dist[i] = INF;
    }

    // solve the firstLoc
    solved[firstLoc] = 1;
    dist[firstLoc] = -1;

    vector<sideNode*>::iterator iter = graph[firstLoc-1]->sideList.begin();
    for(iter; iter != graph[firstLoc-1]->sideList.end(); iter++)
    {
        dist[(*iter)->crossingNum] = (*iter)->cost;
    }

    // solve other vertexs
    int nearestLoc;
    int minDist;
    for(int i=0; i<graph.size(); i++)
    {
        // find the nearest vertex to the first
        minDist = INF;
        for(int j=1; j<=graph.size(); j++)
        {
            if(solved[j] == 0 && dist[j] < minDist)
            {
                nearestLoc = j;
                minDist = dist[j];
            }
        }

        if(minDist == INF)
            return dist;
        solved[nearestLoc] = 1;

        // reflush the dist[]
        iter = graph[nearestLoc-1]->sideList.begin();
        for(iter; iter != graph[nearestLoc-1]->sideList.end(); iter++)
        {
            if(solved[(*iter)->crossingNum] == 0 && minDist + (*iter)->cost < dist[(*iter)->crossingNum])
            {
                dist[(*iter)->crossingNum] = minDist + (*iter)->cost;
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    vector<int> loc;
    vector<headNode*> graph = CreatGraphFromTerminal(loc);
    PrintGraph(graph);

    //int* d =  Dis(graph, loc[0]);

    int* solved = new int[graph.size()+1]; // the 0 is vacant position
    int* dist = new int[graph.size()+1];

    vector<int> total;
    int cnt;
    int flag;
    for(int i=0; i<loc.size(); i++)
    {
        cnt = 0;
        //flag = false;
        Dis(graph, solved, dist, loc[i]);
        for(int j=0; j<loc.size(); j++)
        {
            if(loc[j] != loc[i]) //except itself
            {
                cout << dist[loc[j]] << endl;
                cnt += dist[loc[j]];
            }
        }
        total.push_back(cnt); 
    }

    // cout << "min:" << *(min_element(total.begin(), total.end()));
    for(int i=0; i<total.size(); i++)
    {
        cout << total[i] << " ";
    }
    return 0;
}