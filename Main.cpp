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

    if(head = nullptr)
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

    //Value of the starting vertex
    int startVal;     
    // Array to store the shortest distances from the startVal vertex to all other vertices
    int dist[numOfVertices];

    // Array to keep track of visited vertices
    bool visited[numOfVertices] = {false};

    // Initialize distances to all vertices as infinity and startVal vertex as 0
    for (int i = 0; i < numOfVertices; i++)
    {
        dist[i] = INF;
    }
    dist[startVal - 1] = 0;

    // Loop through all vertices
    for (int count = 0; count < numOfVertices - 1; count++)
    {
        // Find the vertex with the minimum distance value from the set of vertices not yet processed
        int minDist = INF;
        int minIndex = -1;
        for (int v = 0; v < numOfVertices; v++)
        {
            if (!visited[v] && dist[v] < minDist)
            {
                minDist = dist[v];
                minIndex = v;
            }
        }

        // Mark the picked vertex as visited
        visited[minIndex] = true;

        // Update dist value of the adjacent vertices of the picked vertex
        for (int v = 0; v < numOfVertices; v++)
        {
            if (!visited[v] && matrix[minIndex * numOfVertices + v] && dist[minIndex] != INF 
            && dist[minIndex] + matrix[minIndex * numOfVertices + v] < dist[v])
            {
                dist[v] = dist[minIndex] + matrix[minIndex * numOfVertices + v];
            }
        }


    for(int i = 0; i < numOfVertices; i++)
    {
        if(vDegrees[i] % 2 == 1)
        {
            // Input Dijkstra algorithm here for vDegrees[i], but print out for i + 1
            // Print the shortest distances from startVal vertex to all other vertices
            cout << "Single source shortest path lengths from node " << startVal << end;
            cout << i + 1 << ": ";
            if (dist[i] == INF)
                cout << INF;
            else
                cout << dist[i];
            cout << end;
        }
    } 
    cout << "\n";
    
    return 0;
}