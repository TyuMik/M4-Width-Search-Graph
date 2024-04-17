#include <iostream>
#include <fstream>
#include <Windows.h>

int** create_arr(int rows) {
    int** arr = new int* [rows];
    for (int i = 0; i < rows; i++) {
        arr[i] = new int[rows];
    }
    return arr;
}

void delete_arr(int** arr, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] arr[i];
    }
    delete[] arr;
    arr = nullptr;
}

void BFS(int** arr, const int num_vertex, int vertex) {

    int* visited = new int[num_vertex] {0};
    int* queue = new int[num_vertex] {0};

    int start = 0, end = 0;

    queue[end++] = vertex;

    for (int i = 0; i < num_vertex; i++) {

        if ((visited[i] == 0) && (queue[start] != vertex)) {
            queue[end++] = i + 1;
        }

        while (start != end) {

            int node = queue[start] - 1;
            visited[node] = 1;
            start++;

            for (int j = 0; j < num_vertex; j++) {
                if ((arr[node][j] == 1) && (visited[j] == 0)) {
                    queue[end++] = j + 1;
                    visited[j] = 1;
                }
            }

            std::cout << node + 1 << " ";
        }

    }

    delete[] visited;
    delete[] queue;
}


int main(int argc, char** argv)
{
    setlocale(LC_ALL, "Russian");

    std::ifstream input_data("in.txt");

    if (input_data.is_open()) {

        int num_vertex, start_vertex;
        input_data >> num_vertex;
        int** adj_matrix = create_arr(num_vertex);

        for (int i = 0; i < num_vertex; i++) {
            for (int j = 0; j < num_vertex; j++) {
                input_data >> adj_matrix[i][j];
            }
        }

        do {
            std::system("cls");
            std::cout << "В графе " << num_vertex << " вершин. ";
            std::cout << "Введите номер вершины, с которой начнётся обход: ";
            std::cin >> start_vertex;
        } while ((start_vertex > num_vertex) || (start_vertex <= 0));


        std::cout << "Порядок обхода вершин: ";

        BFS(adj_matrix, num_vertex, start_vertex);

        std::cout << std::endl;

        delete_arr(adj_matrix, num_vertex);

        input_data.close();
    }
    else {
        std::cout << "Ошибка! Не удалось открыть файл";
        std::cout << std::endl;
    }

    return 0;
}