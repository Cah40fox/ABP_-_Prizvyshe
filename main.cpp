#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

  a b c d e f
a 1 0 1 1 0 0
b 0 1 1 1 0 0
c 1 1 1 0 1 1
d 1 1 0 1 1 1
e 0 0 1 1 1 0
f 0 0 1 1 0 1
void dijkstra(int graph[V][V], int src) {
    int dist[V];
    bool sptSet[V];
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
    dist[src] = 0;
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;
        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
    printSolution(dist);
}
#define V 6
int minDistance(const int dist[], const bool sptSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (!sptSet[v] && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}
void printSolution(int dist[]) {
    cout << "Vertex \t Distance from Source\n";
    for (int i = 0; i < V; i++)
        cout << abc[i] << "\t\t" << dist[i] << endl;
}
char abc[V] = {'a', 'b', 'c', 'd', 'e', 'f'};
int lab_9_1() {
    int k = -1;
    int graph[V][V] = {
            {1, 0, 1, 1, 0, 0},
            {0, 1, 1, 1, 0, 0},
            {1, 1, 1, 0, 1, 1},
            {1, 1, 0, 1, 1, 1},
            {0, 0, 1, 1, 1, 0},
            {0, 0, 1, 1, 0, 1}
    };
    while (k == -1) {
        cout << "Choose vertex: ";
        char choice;
        cin >> choice;
        for (int i = 0; i < 6; i++) {
            if (choice == abc[i]) {
                k = i;
                break;
            }
        }
        if (k == -1) {
            cout << "Only a,b,c,d,e,f!" << endl;
        }
    }
    dijkstra(graph, k);
    return 0;
}
void floydWarshall(int graph[V][V]) {
    int dist[V][V];
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            dist[i][j] = graph[i][j];
    for (int k = 0; k < V; k++)
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX
                    && dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
    printSolution(dist);
}
void printSolution(int dist[][V]) {
    cout << "Shortest distances between every pair of
    vertices:\n";
    cout << "\t";
    for (char i : abc) cout << i << "\t";
    cout << endl;
    for (int i = 0; i < V; i++) {
        cout << abc[i] << "\t";
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INT_MAX)
                cout << "INF" << "\t";
            else
                cout << dist[i][j] << "\t";
        }
        cout << endl;
    }
}
int lab_9_2() {
    int graph[V][V] = {
            {1 , INF, 1 , 1 , INF, INF},
            {INF, 1 , 1 , 1 , INF, INF},
            {1 , 1 , 1 , INF, 1 , 1 },
            {1 , 1 , INF, 1 , 1 , 1 },
            {INF, INF, 1 , 1 , 1 , INF},
            {INF, INF, 1 , 1 , INF, 1 }
    };
    floydWarshall(graph);
    return 0;
}
#define INF INT_MAX
int main() {
    char choice;
    while (true) {
        cout << "Dijkstra (1) or floydWarshall (2)?" << endl;
        cin >> choice;
        if (choice == '1' || choice == '2') break;
        else cout << "Only 1 or 2" << endl;
    }
    switch (choice){
        default:
            break;
        case '1':
            lab_9_1();
            break;
        case '2':
            lab_9_2();
            break;
    }
}