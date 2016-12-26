#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
#define ElementType int

struct Node
{
    ElementType data;
    Node* next;
    Node* prior;
};

struct DCircList
{
    Node* head;
    Node* tail;
};

/***
this function only allocates a new head of a list
***/
DCircList* InitialList()
{
    DCircList* list = new DCircList;
    list->head = new Node;
    list->head->next  = list->head; // point it to itself
    list->head->prior = list->head;
    list->tail = list->head;
    return list;
}

/***
the head pointer is vacant 
without data
***/
void CreatListFromFile(char* fileName, DCircList* list)
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
        temp->prior = list->tail;
        list->tail = temp; // move the tail pointer
    }
    list->tail->next  = list->head; // the only difference from simple List                                
    list->head->prior = list->tail;
}

void PrintList(DCircList* list)
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

bool IsSymmetrical(DCircList* list)
{
    Node* temp1 = list->head->next;
    Node* temp2 = list->head->prior;
    while(temp1 != temp2 && temp1->next != temp2) //odd or even
    {
        if(temp1->data != temp2->data) 
        {
            return false;
        }
        else
        {
            temp1 = temp1->next;
            temp2 = temp2->prior;
        }
    }
    return true;
}

void Reverse(DCircList* list)
{
    Node* temp1 = list->head->prior; // point to tail
    Node* temp2 = temp1->prior; //the seconde element from back
    list->tail = list->head;

    while(temp1 != list->head)
    {
        temp1->prior = list->tail;
        list->tail->next = temp1; // tail inter
        
        list->tail = temp1; // move the tail, for the using of next loop
        temp1 = temp2;
        temp2 = temp2->prior;
    }
    // finish the last work to circule the list
    list->tail->next = list->head; 
    list->head->prior = list->tail;
}

int main(int argc, char const *argv[])
{
    DCircList* list = InitialList();
    CreatListFromFile("ListFile.txt", list);
    PrintList(list);
    cout << IsSymmetrical(list) << endl;

    Reverse(list);
    PrintList(list);
    return 0;
}