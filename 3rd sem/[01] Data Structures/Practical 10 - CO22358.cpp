#include <iostream>
#include <cstdlib>
using namespace std;

struct linkedNode {
    char vertex;
    int weight;
    struct linkedNode* next;
};

struct Edge {
    char source;
    char dest;
    int weight;
};

struct graphraph {
    int vertices;
    int edges;
    struct linkedNode** adjList;
};

struct Edge newEdge(char a, char b, int weight) {
    struct Edge E;
    E.source = a;
    E.dest = b;
    E.weight = weight;
    return E;
}

struct graphraph* createGraph(int noOfVertices) {
    if (noOfVertices < 0) {
        cout << "Number of vertices cannot be negative." << endl;
        exit(EXIT_FAILURE);
    }

    struct graphraph* graph = (struct graphraph*)malloc(sizeof(struct graphraph));
    if (graph == NULL) {
        cout << "Memory allocation error." << endl;
        exit(EXIT_FAILURE);
    }

    graph->vertices = noOfVertices;
    graph->edges = 0;

    graph->adjList = (struct linkedNode**)malloc(noOfVertices * sizeof(struct linkedNode*));
    if (graph->adjList == NULL) {
        cout << "Memory allocation error." << endl;
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < noOfVertices; i++) {
        graph->adjList[i] = NULL;
    }

    return graph;
}

int insertEdge(struct graphraph* graph, char source, char dest, int weight) {
    int noOfVertices = graph->vertices;
    int sourceIndex = -1;

    for (int m = 0; m < noOfVertices; m++) {
        if (graph->adjList[m] == NULL) {
            graph->adjList[m] = (struct linkedNode*)malloc(sizeof(struct linkedNode));
            if (graph->adjList[m] == NULL) {
                cout << "Memory allocation error." << endl;
                exit(EXIT_FAILURE);
            }
            graph->adjList[m]->vertex = source;
            graph->adjList[m]->weight = 0;
            graph->adjList[m]->next = NULL;
            sourceIndex = m;
            break;
        }
        else if (graph->adjList[m]->vertex == source) {
            sourceIndex = m;
            break;
        }
    }

    if (sourceIndex == -1) {
        cout << "Invalid source vertex." << endl;
        return 0;
    }

    struct linkedNode* ptr = graph->adjList[sourceIndex];
    struct linkedNode* prev = NULL;

    while (ptr != NULL) {
        if (ptr->vertex == dest) {
            cout << "Edge already exists." << endl;
            return 0;
        }
        else {
            prev = ptr;
            ptr = ptr->next;
        }
    }

    struct linkedNode* newNode = (struct linkedNode*)malloc(sizeof(struct linkedNode));
    if (newNode == NULL) {
        cout << "Memory allocation error." << endl;
        exit(EXIT_FAILURE);
    }
    newNode->vertex = dest;
    newNode->weight = weight;
    newNode->next = NULL;

    if (prev == NULL) {
        graph->adjList[sourceIndex] = newNode;
    }
    else {
        prev->next = newNode;
    }

    graph->edges++;
    return 1;
}

void DFSUtil(struct graphraph* graph, int index, bool visited[]) {
    visited[index] = true;
    cout << graph->adjList[index]->vertex << " ";

    for (struct linkedNode* ptr = graph->adjList[index]->next; ptr != NULL; ptr = ptr->next) {
        int neighborIndex = -1;
        for (int i = 0; i < graph->vertices; i++) {
            if (graph->adjList[i] != NULL && graph->adjList[i]->vertex == ptr->vertex) {
                neighborIndex = i;
                break;
            }
        }

        if (neighborIndex != -1 && !visited[neighborIndex]) {
            DFSUtil(graph, neighborIndex, visited);
        }
    }
}

void DFS(struct graphraph* graph, char s) {
    int noOfVertices = graph->vertices;
    bool visited[noOfVertices];
    for (int i = 0; i < noOfVertices; i++) {
        visited[i] = false;
    }

    int startIndex = -1;
    for (int i = 0; i < noOfVertices; i++) {
        if (graph->adjList[i] != NULL && graph->adjList[i]->vertex == s) {
            startIndex = i;
            break;
        }
    }
    DFSUtil(graph, startIndex, visited);
    cout << endl;
}
struct Queue {
    int front, rear, capacity;
    char* array;
    Queue(int size) {
        front = rear = -1;
        capacity = size;
        array = new char[size];
        if (array == NULL) {
            cout << "Memory allocation error." << endl;
            exit(EXIT_FAILURE);
        }
    }
    bool isEmpty() {
        return front == -1;
    }

    void enqueue(char item) {
        if (rear == capacity - 1) {
            cout << "Queue is full" << endl;
            return;
        }
        if (front == -1) {
            front = 0;
        }
        rear++;
        array[rear] = item;
    }

    char dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return '\0';
        }
        char item = array[front];
        front++;
        if (front > rear) {
            front = rear = -1;
        }
        return item;
    }
};

void BFS(struct graphraph* graph, char s) {
    int noOfVertices = graph->vertices;
    bool visited[noOfVertices];
    for (int i = 0; i < noOfVertices; i++) {
        visited[i] = false;
    }

    int startIndex = -1;
    for (int i = 0; i < noOfVertices; i++) {
        if (graph->adjList[i] != NULL && graph->adjList[i]->vertex == s) {
            startIndex = i;
            break;
        }
    }

    if (startIndex == -1) {
        cout << "Invalid starting vertex" << endl;
        return;
    }

    Queue q(noOfVertices);
    q.enqueue(s);
    visited[startIndex] = true;

    while (!q.isEmpty()) {
        char c = q.dequeue();
        cout << c << " ";

        int currentIndex = -1;
        for (int i = 0; i < noOfVertices; i++) {
            if (graph->adjList[i] != NULL && graph->adjList[i]->vertex == c) {
                currentIndex = i;
                break;
            }
        }
        if (currentIndex != -1) {
            for (struct linkedNode* ptr = graph->adjList[currentIndex]->next; ptr != NULL; ptr = ptr->next) {
                int neighborIndex = -1;
                for (int i = 0; i < noOfVertices; i++) {
                    if (graph->adjList[i] != NULL && graph->adjList[i]->vertex == ptr->vertex) {
                        neighborIndex = i;
                        break;
                    }
                }
                if (neighborIndex != -1 && !visited[neighborIndex]) {
                    q.enqueue(ptr->vertex);
                    visited[neighborIndex] = true;
                }
            }
        }
    }
    cout << endl;
}
int main() {
    int numVertices;
    cout << "Enter the number of vertices: ";
    cin >> numVertices;
    struct graphraph* G = createGraph(numVertices);
    int numEdges;
    cout << "Enter the number of edges: ";
    cin >> numEdges;
    for (int i = 0; i < numEdges; i++) {
        char source, dest;
        int weight;
        cout << "Enter edge " << i + 1 << " (source destination weight): ";
        cin >> source >> dest >> weight;
        insertEdge(G, source, dest, weight);
    }
    for (int i = 0; i < G->vertices; i++) {
        cout << "Vertex " << i << " edges: ";
        struct linkedNode* ptr = G->adjList[i];
        while (ptr != NULL) {
            cout << "(" << ptr->vertex << ", " << ptr->weight << ") ";
            ptr = ptr->next;
        }
        cout << endl;
    }
    char startVertex;
    cout << "Enter the starting vertex for BFS and DFS: ";
    cin >> startVertex;

    cout << "BFS Traversal: ";
    BFS(G, startVertex);

    cout << "DFS Traversal: ";
    DFS(G, startVertex);

    return 0;
}