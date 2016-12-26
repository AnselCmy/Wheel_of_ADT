#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
#define ElementType int

struct Node
{
    ElementType data;
    Node* next;
};

struct CircList
{
    Node* head;
    Node* tail;
};

/***
this function only allocates a new head of a list
***/
CircList* InitialList()
{
    CircList* list = new CircList;
    list->head = new Node;
    list->head->next = list->head; // point it to itself
    list->tail = list->head;
    return list;
}

/***
the head pointer is vacant 
without data
***/
void CreatListFromFile(char* fileName, CircList* list)
{
    ifstream f;
    f.open(fileName);
    string nodeData;
    string allData;
    stringstream ssNodeData;
    stringstream ssAllData;
    ElementType etNodeData;

    getline(f, allData); // get all the node data as string
    ssAllData << allData; // put them into sstream for getline

    while(getline(ssAllData, nodeData, ' '))
    {
        ssNodeData.clear(); // essential 
        ssNodeData << nodeData; // for type transforming
        ssNodeData >> etNodeData;
        
        Node* temp = new Node;
        temp->data = etNodeData;
        list->tail->next = temp;
        list->tail = temp; // move the tail pointer
    }
    list->tail->next = list->head; // the only difference from simple List                                
}

void PrintList(CircList* list)
{
    Node* temp = list->head->next;
    if(temp == NULL)
    {
        cout << "a vacant list";
    }
    while(temp != list->head)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

/***
connect B at the end of A
***/
void ConnectCircList(CircList* c1, CircList* c2)
{
    c1->tail->next = c2->head->next;
    c2->tail->next = c1->head;
    c1->tail = c2->tail;
    delete c2->head;
}

int main(int argc, char const *argv[])
{
    CircList* circList = InitialList();
    CreatListFromFile("ListFile.txt", circList);
    PrintList(circList);

    CircList* A = InitialList();
    CircList* B = InitialList();
    CreatListFromFile("ListFile1.txt", A);
    CreatListFromFile("ListFile2.txt", B);
    ConnectCircList(A, B);
    PrintList(A);
    return 0;
}