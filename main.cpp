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
void dijkstra(int graph[][6], int size, int start_vertex, int* distances) {

    bool* visited = new bool[size];
    for (int i = 0; i < size; i++) {
        distances[i] = INT_MIN; // Ініціалізація найкоротших відстаней
        visited[i] = false; // Відвідуваність вершин
    }

    distances[start_vertex] = 0; // Нульова відстань для початкової вершини

    for (int i = 0; i < size - 1; i++) {
        // Знаходимо вершину з мінімальною відстанню до поточної вершини
        int min_vertex = -1;
        for (int j = 0; j < size; j++) {
            if (!visited[j] && (min_vertex == -1 || distances[j] > distances[min_vertex])) {
                min_vertex = j;
            }
        }

        visited[min_vertex] = true; // Позначаємо вершину як відвідану

        // Оновлюємо найкоротші відстані для сусідніх вершин, які ще не відвідані
        for (int j = 0; j < size; j++) {
            int edge_weight = graph[min_vertex][j];
            if (edge_weight != 0 && !visited[j]) {
                int distance_through_min_vertex = distances[min_vertex] + edge_weight;
                if (distance_through_min_vertex > distances[j]) {
                    distances[j] = distance_through_min_vertex;
                }
            }
        }
    }

    delete[] visited;
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

    int graph[6][6] = {{0, 5, 1, 0, 0, 0},
                       {5, 0, 2, 1, 0, 0},
                       {1, 2, 0, 1, 1, 0},
                       {0, 1, 1, 0, 2, 1},
                       {0, 0, 1, 2, 0, 0},
                       {0, 0, 0, 1, 0, 0}};
    int distances[6];
    dijkstra(graph, 6, 0, distances);

    return 0;
}
