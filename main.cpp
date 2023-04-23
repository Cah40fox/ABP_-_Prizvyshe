#include <iostream>
#include <climits>
using namespace std;

// Задаємо кількість вершин графа
#define V 6

// Функція для виводу матриці дистанцій
void printSolution(int dist[][V])
{
    cout << "Shortest distances between every pair of vertices:\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INT_MAX) {
                cout << "INF"
                     << "\t";
            } else {
                cout << dist[i][j] << "\t";
            }
        }
        cout << endl;
    }
}

// Функція для знаходження найкоротших відстаней між кожною парою вершин графа
void floydWarshall(int graph[][V])
{
    int dist[V][V], i, j, k;

    // Ініціалізуємо відстані як ваги ребер графа
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] = graph[i][j];

    // Застосовуємо алгоритм Флойда-Уоршелла для знаходження найкоротших відстаней між кожною парою вершин графа
    for (k = 0; k < V; k++) {
        for (i = 0; i < V; i++) {
            for (j = 0; j < V; j++) {
                if (dist[i][k] == INT_MAX || dist[k][j] == INT_MAX)
                    continue;
                else if (dist[i][j] > dist[i][k] + dist[k][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
    // Виводимо знайдені найкоротші відстані
    printSolution(dist);
}
// Функція для знаходження найкоротших шляхів до всіх вершин від заданої вершини
void dijkstra(int graph[V][V], int src)
{
    int dist[V]; // масив для зберігання найкоротших відстаней
    bool sptSet[V]; // масив для зберігання флагів відвіданих вершин

    // Ініціалізуємо відстані як нескінченні, а флаги - як невідвідані
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    // Відстань від заданої вершини до неї самої - завжди 0
    dist[src] = 0;

    // Знаходимо найкоротші шляхи до всіх вершин від заданої вершини
    for (int count = 0; count < V - 1; count++) {
        // Знаходимо вершину з найменшою відстанню, яка ще не була відвідана
        int u, minDist = INT_MAX;
        for (int v = 0; v < V; v++)
            if (!sptSet[v] && dist[v] <= minDist)
                minDist = dist[v], u = v;

        // Позначаємо знайдену вершину як відвідану
        sptSet[u] = true;

        // Оновлюємо відстані до всіх сусідніх вершин, що ще не відвідали
        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    // Виводимо знайдені найкоротші шляхи
    cout << "Shortest distances from vertex " << src << ":\n";
    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX)
            cout << i << ": INF" << endl;
        else
            cout << i << ": " << dist[i] << endl;
    }
}

int main() {
    // Граф у вигляді матриці суміжності
    int graph[V][V] = {
            {1,       INT_MAX,       1, 1, INT_MAX, INT_MAX},
            {INT_MAX,       1,       1, 1, INT_MAX, INT_MAX},
            {1, 1,       1,       INT_MAX, 1, 1},
            {1,       1, INT_MAX,       1, 1,       1},
            {INT_MAX, INT_MAX, 1, 1, 1,       INT_MAX},
            {INT_MAX, INT_MAX,       1,       1, INT_MAX,       1}
    };

    floydWarshall(graph);
    cout << endl;

    dijkstra(graph, 0);

    return 0;
}
