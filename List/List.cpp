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


/***
head is vacant pointer,
and the first node is 1 but not 0, 
***/
struct List
{
    Node* head;
    Node* tail;
};


/***
this function only allocates a new head of a list
***/
List* InitialList()
{
    List* list = new List;
    list->head = new Node;
    list->head->next = NULL;
    list->tail = list->head;
    return list;
}


/***
attention that
the head pointer doesn't have a data,
but the tail have the data.
***/
void CreatListFromFile(char* fileName, List* list)
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
        ssNodeData << nodeData; // for type transforing
        ssNodeData >> etNodeData;
        
        Node* temp = new Node;
        temp->data = etNodeData;
        list->tail->next = temp;
        list->tail = temp; // move the tail pointer
    }
    list->tail->next = NULL;
}


void CreatListFromTerminal(List* list)
{
    ElementType nodeData;
    cout << "+input the data with the end of 2333:" << endl;
    cin >> nodeData;
    while(nodeData != 2333)
    {
        Node* temp = new Node;
        temp->data = nodeData;
        list->tail->next = temp;
        list->tail = temp;
        cin >> nodeData;
    }
    list->tail->next = NULL;
}


/***
attention that
in this function,
we can't move the pointer of head,
or the head of this the list will be moved in main.
***/
void PrintList(List* list)
{
    Node* temp = list->head->next;
    if(temp == NULL)
    {
        cout << "a vacant list";
    }
    while(temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}


/***
if a list only have a head,
this function can return 0. 
***/
int GetLength(List* list)
{
    Node* temp = list->head; 
    int cnt=0;
    while(temp->next)
    {
        temp = temp->next;
        cnt++;
    }  
    return cnt;  
}


/***
the first data is 1,
0 is the head.
***/
void DeleteByLoc(int loc, List* list)
{
    if(loc < 1 || loc > GetLength(list))
    {
        cout << "wrong loction!" << endl;
        return;
    }

    Node* temp = list->head;
    for(int i=1; i<=loc-1; i++)
    {
        temp = temp->next;
    }
    Node* deleteNode = temp->next;
    temp->next = temp->next->next;
    delete deleteNode;
}

void DeleteByNum(ElementType num, List* list)
{
    // must use a pointer to store the head pointer
    // but not move the head directely
    Node* temp = list->head;
    for(int i=0; i<GetLength(list)-1; i++)
    {
        temp = temp->next;
        if(temp->next->data == num) //cause we need to get the forehead of the deletedata
        {
            Node* deleteNode = temp->next;
            temp->next = temp->next->next;
            delete deleteNode;
            break;
        }
    }
    return;
}

void Insert(ElementType data, int loc, List* list)
{
    if(loc < 1 || loc > GetLength(list)+1)
    {
        cout << "wrong loction!" << endl;
        return;
    }

    Node* temp1 = list->head;
    for(int i=1; i<=loc-1; i++)
    {
        temp1 = temp1->next;
    }
    Node* temp2 = temp1->next; //store temp1->next

    Node* insertNode = new Node;
    insertNode->data = data;
    
    temp1->next = insertNode;
    insertNode->next = temp2;
}


void DestroyList(List* list)
{
    int len = GetLength(list);
    for(int i=1; i<=len; i++)
    {
        DeleteByLoc(1, list);
    }
    delete list->head;
    delete list;
}

void UnionTwoOrderList(List* l1, List* l2)
{
    Node* temp1 = l1->head;
    Node* temp2 = l2->head;
    while(temp1->next && temp2->next)
    {
        if(temp1->next->data < temp2->next->data)
        {
            Node* deleteNode = temp1->next;
            temp1->next = temp1->next->next;
            delete deleteNode; 
        }
        else if(temp1->next->data > temp2->next->data)
        {
            temp2 = temp2->next;
        }
        else
        {
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }
}

/***
get the reverse of the list
using original node
***/
void Reverse(List* list)
{
    Node* r = list->head->next; // store the head and the first data
    list->tail = r; // point the tail into the first data
    Node* temp1 = r->next; // put a pointer into the next of the first data
    r->next = NULL; // cause the pointer r is the tail now
    Node* temp2; // cause we need to change the temp1->next, so we need to use temp2 to store the next
    while(temp1) // head interpoation
    {
        temp2 = temp1->next;
        temp1->next = list->head->next;
        list->head->next = temp1;
        temp1 = temp2;
    }
}

/***
used in ConnectTwoDescend2Ascend()
***/
void HeadInter(List* dst, Node*& temp/*, Node*& reseve*/)
{
    Node* reseve;
    reseve = temp->next;
    temp->next = dst->head->next;
    dst->head->next = temp;
    temp = reseve;
}

/***
connect two descending list 
into one ascending list
***/
List* ConnectTwoDescend2Ascend(List* l1, List* l2)
{
    List* l3 = InitialList();
    Node* temp1 = l1->head->next;
    Node* temp2 = l2->head->next;
    // Node* reseve1;
    // Node* reseve2;
    while(temp1 && temp2)
    {
        if(temp1->data < temp2->data)
        {
            HeadInter(l3, temp1);
        }
        else if(temp1->data > temp2->data)
        {
            HeadInter(l3, temp2);
        }
        else
        {
            HeadInter(l3, temp1);
            HeadInter(l3, temp2);
        }
    }
    if(temp1 == NULL)
    {
        while(temp2)
        {
            HeadInter(l3, temp2);   
        }        
    }
    else
    {
        while(temp1)
        {
            HeadInter(l3, temp1);
        }
    }
    return l3;
}

int main(int argc, char const *argv[])
{
    List* list = InitialList();
    CreatListFromFile("ListFile.txt", list);
    // CreatListFromTerminal(list);
    PrintList(list);

    cout << "after DeleteByLoc:" << endl;
    DeleteByLoc(2, list);
    PrintList(list);

    cout << "after insert:" << endl;
    Insert(100, GetLength(list)+1, list);
    PrintList(list);

    cout << "after DeleteByNum:" << endl;
    DeleteByNum(100, list);
    PrintList(list);
    
    cout << "union test:" << endl;
    List* A = InitialList();
    List* B = InitialList();
    CreatListFromFile("ListFile1.txt", A);
    CreatListFromFile("ListFile2.txt", B);
    cout << "A:";
    PrintList(A);
    cout << "B:";
    PrintList(B);
    UnionTwoOrderList(A, B);
    cout << "A U B:";
    PrintList(A);

    cout << "after reverse:" << endl;
    Reverse(list);
    cout << "reversed list:";
    PrintList(list);

    cout << "descend 2 ascend:" <<endl;
    List* l1 = InitialList();
    List* l2 = InitialList();
    List* l3 = InitialList();
    CreatListFromFile("ListFile1.txt", l1);
    CreatListFromFile("ListFile2.txt", l2);
    cout << "l1:";
    PrintList(l1);
    cout << "l2:";
    PrintList(l2);
    l3 = ConnectTwoDescend2Ascend(l1, l2);
    PrintList(l3);

    DestroyList(list);
    return 0;
}