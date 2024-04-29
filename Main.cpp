#include "Edge.h"
#include <iostream>
using namespace std;

struct Node
{
    Edge* data;
    struct Node* next;

    Node()
    {
        next = nullptr;
    }

    Node(Edge* data)
    {
        this->data = data;
        this->next = nullptr;
    }
};

class LinkedList
{   
    public:
    Node* head;

    LinkedList()
    {
        head = nullptr;
    }

    void insertNode(Edge*);

    void printList();
};

void LinkedList::insertNode(Edge* data)
{
    Node* newNode = new Node(data);

    if(head == nullptr)
    {
        head = newNode;
        head->next = nullptr;
        if(head->next == nullptr)
        return;
    }

    Node* temp = head;
    while(temp != nullptr && temp->next != nullptr)
    {
        temp = temp->next;
    }

    temp->next = newNode;
};

void LinkedList::printList()
{
    Node* temp = head;

    if(head == nullptr)
    {
        cout << " ";
        return;
    }

    while(temp != nullptr)
    {
        cout << temp->data->startVert << " " << temp->data->endVert;
        temp = temp->next;
    }
}

int main(){

    // start of the initial pipeline that loads the test case file stream from std::cin
    
    // Added by me
    LinkedList Graph;

    int numOfVertices;
    int numOfEdges;

    if(!std::cin.eof()){
        std::cin >> numOfVertices;
        std::cin >> numOfEdges;
    }
    else{
        std::cout<<"Input not found!"<<std::endl;
        return NULL;
    }

    while(!std::cin.eof()){
        int startVertice;
        int endVertice;
        std::cin >> startVertice;
        std::cin >> endVertice;
        Edge* newEdge = new Edge(startVertice, endVertice);
        // Here is where you load up the Graph object
        Graph.insertNode(newEdge);
    }

    // And here is where you start working on the three tasks

    // Part 1 ------------------------------------------------------------------------------------------

    //Graph.printList();
    int matrix[numOfVertices][numOfVertices];

    // Filling the adjacency matrix (Initiate with 0 then fill up with 1s when necessary)
    for(int i = 0; i < numOfVertices; i++)
    {
        for(int j = 0; j < numOfVertices; j++)
        {
            matrix[i][j] = 0;
        }
    }

    Node* temp0 = Graph.head;
    while(temp0 != nullptr)
    {
        matrix[temp0->data->startVert - 1][temp0->data->endVert - 1] = 1;
        matrix[temp0->data->endVert - 1][temp0->data->startVert - 1] = 1;

        temp0 = temp0->next;
    }


    // Print out the matrix
    cout << "The adjacency matrix of G:" << "\n";
    for(int i = 0; i < numOfVertices; i++)
    {
        for(int j = 0; j < numOfVertices; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";

    // Part 2 ------------------------------------------------------------------------------------------

    int vDegrees[numOfVertices] = {0};
    
    // Make an array of each vertices' degrees
    Node* temp1 = Graph.head;
    while(temp1 != nullptr)
    {
        vDegrees[temp1->data->startVert - 1] += 1;
        vDegrees[temp1->data->endVert   - 1] += 1;

        temp1 = temp1->next;
    }
    
    // Print out only the odd ones
    cout << "The odd degree vertices in G:" << "\n";
    cout << "O = { ";
    for(int i = 0; i < numOfVertices; i++)
    {
        if(vDegrees[i] % 2 == 1)
        {
            cout << i + 1 << " ";
        }
    } 
    cout << "}\n"; 

    // Part 3 ------------------------------------------------------------------------------------------
    int max = 0x7FFFFFFF;

    for(int i = 0; i < 1 /* CHANGE to numOfVertices */; i++)
    {
        if(vDegrees[i] % 2 == 1)
        {
            // Dijkstra algorithm for all odd degrees

            int dist[numOfVertices];

            int matrixCopy[numOfVertices][numOfVertices];

            for(int a = 0; a < numOfVertices; a++)
            {
                for(int b = 0; b < numOfVertices; b++)
                {
                    matrixCopy[a][b] = matrix[a][b];
                }
            }

            for(int j = 0; j < numOfVertices; j++)
            {
                dist[j] = max;
            }

            // Array for visited/unvisited nodes
            bool visited[numOfVertices] = {false};

            // Set starting node distance to 0 and mark as visited
            dist[i] = 0;
            visited[i] = true;

            // First dijkstra iteration
            for(int k = 0; k < numOfVertices; k++)
            {
                if(matrixCopy[i][k] == 1)
                {
                    matrixCopy[i][k] = 0;
                    matrixCopy[k][i] = 0;
                    dist[k] = 1;
                    visited[k] = true;
                }
                
            }

            // Rest of dijkstra iterations
            for(int m = 0; m < numOfVertices; m++)
            {
                if(visited[m] == true)
                {
                    for(int n = 0; n < numOfVertices; n++)
                    {
                        if(visited[n] == false && matrixCopy[m][n] == 1)
                        {
                            matrixCopy[n][m] = 0;
                            matrixCopy[m][n] = 0;
                            dist[n] = dist[m] += 1;
                            visited[n] = true;
                        }
                    }
                }
            }

            // Print info
            cout << "Single source shortest path lengths from node " << i + 1 << "\n";
            for(int i = 0; i < numOfVertices; i++)
            {
                cout << i + 1 << ": " << dist[i] << "\n";
            }
            
        }

    } 

    cout << "\n"; 

    return 0;
}