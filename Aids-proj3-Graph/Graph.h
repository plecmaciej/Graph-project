#include <iostream>

#define UN_VISITED 'u'
#define RED 'r'
#define GREEN 'g'
#define INF 1000000
#define SMALLEST_VALUE -1

using namespace std;

class Graph {
private:
    int n; 
    int** neigboursList;
    int* neighbourNumbers; 

public:

    Graph(int vertices) : n(vertices) {
        neigboursList = new int* [n + 1];
        neighbourNumbers = new int[n + 1];
        for (int i = 0; i <= n; ++i) {
            neigboursList[i] = nullptr;
            neighbourNumbers[i] = 0;
        }
    }

    ~Graph() {
        for (int i = 0; i <= n; ++i) {
            delete[] neigboursList[i];
        }
        delete[] neigboursList;
        delete[] neighbourNumbers;
    }

    void addEdges(int u, int s, int* neighbors) {
        neighbourNumbers[u] = s;
        neigboursList[u] = new int[s];
        for (int i = 0; i < s; ++i) {
            neigboursList[u][i] = neighbors[i];
        }
    }

    void printGraph() {
        for (int i = 1; i <= n; ++i) {
            cout << i << " : ";
            for (int j = 0; j < neighbourNumbers[i]; ++j) {
                cout << neigboursList[i][j] << " ";
            }
            cout << endl;
        }
    }

    void merge(int arr[], int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        int* leftArr = new int[n1];
        int* rightArr = new int[n2];

        for (int i = 0; i < n1; i++) {
            leftArr[i] = arr[left + i];
        }
        for (int i = 0; i < n2; i++) {
            rightArr[i] = arr[mid + 1 + i];
        }

        int i = 0;
        int j = 0;
        int k = left;

        while (i < n1 && j < n2) {
            if (leftArr[i] >= rightArr[j]) {
                arr[k] = leftArr[i];
                i++;
            }
            else {
                arr[k] = rightArr[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr[k] = leftArr[i];
            i++;
            k++;
        }

        while (j < n2) {
            arr[k] = rightArr[j];
            j++;
            k++;
        }

        delete[] leftArr;
        delete[] rightArr;
    }

    void mergeSort(int arr[], int left, int right) {
        if (left >= right) return; 
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }

    void DFS(int v, bool* visited) {
        visited[v] = true;
        for (int i = 0; i < neighbourNumbers[v]; ++i) {

            int neighbor = neigboursList[v][i];
            if (!visited[neighbor]) {
                DFS(neighbor, visited);
            }
        }
    }

    bool DFSColored(int v, char* visited, char lastColor) {
        char color = getOppositeColor(lastColor);
        visited[v] = color;

        for (int i = 0; i < neighbourNumbers[v]; ++i) {

            int neighbor = neigboursList[v][i];
            if (visited[neighbor] == UN_VISITED) {
                if (!DFSColored(neighbor, visited, color)) return false;
            }
            else if (visited[neighbor] == color) { 
                //cout << " tak nie mozna " << neighbor;
                return false; 
            }
        }
        return true;
    }

    char getOppositeColor(char color) {
        if (color == RED) return GREEN;
        else return RED;
    }

    void printGradualSequence() {
        int* degrees = new int[n + 1];

        for (int i = 1; i <= n; ++i) {
            degrees[i] = neighbourNumbers[i];
        }

        mergeSort(degrees, 1, n);

        for (int i = 1; i <= n; ++i) {
            cout << degrees[i] << " ";
        }
        cout << endl;

        delete[] degrees;
    }

    int getNumberOfCohesion() {
        int numberOfCohesion = 0;
        bool* visited = new bool[n + 1];

        for (int i = 1; i <= n; i++) {
            visited[i] = false;
        }

        for (int i = 1; i <= n; i++) {
            if (!visited[i]) {
                DFS(i, visited);
                numberOfCohesion++;
            }
        }

        delete[] visited;
        return numberOfCohesion;
    }

    char bipartiteness() {
        char isBipartiness = '?';
        char* visited = new char[n + 1];

        for (int i = 1; i <= n; i++) {
            visited[i] = UN_VISITED;
        }
     
        if (!DFSColored(1, visited, RED)) {
            isBipartiness = 'F';
        }
        else {
            isBipartiness = 'T';
        }

        delete[] visited;
        return isBipartiness;
    }

    int bfs(int vertice) {
        int* distances = new int[n + 1];
        int* queue = new int[n + 1];
        int front = 0, end = 0 ,highestValue = 0;

        for (int i = 1; i <= n; i++) {
            distances[i] = INF;
        }

        distances[vertice] = 0;
        queue[end] = vertice;
        end++;

        while (front < end) {

            int tempVertice = queue[front];
            front++;

            for (int i = 0; i < neighbourNumbers[tempVertice]; i++) {

                int neighbour = neigboursList[tempVertice][i];

                if (distances[neighbour] == INF) {

                    queue[end] = neighbour;
                    end++;
                    distances[neighbour] = distances[tempVertice] + 1;

                    if (distances[neighbour] > highestValue) {
                        highestValue = distances[neighbour];
                    }
                }
            }
        }

        delete[] queue;
        delete[] distances;

        return highestValue;
    }



    void printEccentricities() {

        for (int i = 1; i <= n; ++i) {

            cout << bfs(i) << " ";
        }

        cout << "\n";
    }

    void printColoring() {
        int* colors = new int[n + 1];
        bool* possibleValues = new bool[n + 1];
        int highestColor = 0;
        bool wasUsed = false;
        //int vertice = 0;

        for (int i = 0; i <= n; i++) {
            colors[i] = 0;
            possibleValues[i] = true;
        }

        for (int vertice = 1; vertice <= n; vertice++) {

            //for (int i = 1; i <= n; i++) {
            //    possibleValues[i] = true;
            //}

            for (int i = 0; i < neighbourNumbers[vertice]; i++) {
                int neighbour = neigboursList[vertice][i];
                if (colors[neighbour] != 0) {
                    possibleValues[colors[neighbour]] = false;
                    if (highestColor < colors[neighbour]) highestColor = colors[neighbour];
                    
                }
            }

            for (int i = 1; i <= highestColor + 1; i++) {
                if (possibleValues[i] && !wasUsed) {
                    colors[vertice] = i;
                    cout << i << " ";
                    wasUsed = true;
                    //break;
                }
                possibleValues[i] = true;
            }
            highestColor = 0;
            wasUsed = false;
        }

        delete[] possibleValues;
        delete[] colors;
        cout << "\n";

        return;
    }

    void printLF() {
        int* colors = new int[n + 1];
        bool* possibleValues = new bool[n + 1];
        int value = SMALLEST_VALUE;
        int vertice = 0;
        int highestColor = 0;
        bool wasUsed = false;

        for (int i = 0; i < n + 1; i++) {
            colors[i] = 0;
            possibleValues[i] = true;
        }

        for (int counter = n; counter>0; counter--){

            for (int i = 1; i < n + 1; i++) {
                if (neighbourNumbers[i] > value && colors[i] == 0) {
                    vertice = i;
                    value = neighbourNumbers[i];
                }

            }
            for (int i = 0; i < neighbourNumbers[vertice]; i++) {
                int neighbour = neigboursList[vertice][i];
                if (possibleValues[colors[neighbour]]) {
                    possibleValues[colors[neighbour]] = false;
                    if (highestColor < colors[neighbour]) highestColor = colors[neighbour];
                }
            }

            for (int i = 1; i <= highestColor + 1; i++) {
                if (possibleValues[i] && !wasUsed) {
                    colors[vertice] = i;
                    //cout << i << " ";
                    wasUsed = true;
                    //break;
                }
                possibleValues[i] = true;
            }

            highestColor = 0;
            wasUsed = false;
            value = SMALLEST_VALUE;
        }

        for (int i = 1; i < n + 1; i++) {
            cout << colors[i] << " ";
        }

        delete[] possibleValues;
        delete[] colors;
        cout << "\n";
        return;
    }

    void printSLF() {
        int* colors = new int[n + 1];
        bool* possibleValues = new bool[n + 1];

        for (int i = 0; i <= n; i++) {
            colors[i] = 0;
            possibleValues[i] = true;
        }

        for (int counter = n; counter > 0; counter--) {
            int vertice = 0;
            int highestSaturation = SMALLEST_VALUE;
            int highestDegree = SMALLEST_VALUE;

            for (int i = 1; i <= n; i++) {
                if (colors[i] == 0) {
                    int saturationNumber = 0;
                    int degree = neighbourNumbers[i];

                    for (int j = 0; j < degree; j++) {
                        int neighbour = neigboursList[i][j];
                        if (colors[neighbour] > 0) {
                            possibleValues[colors[neighbour]] = false;
                        }
                    }

                    for (int j = 1; j <= n; j++) {
                        if (!possibleValues[j]) {
                            saturationNumber++;
                            possibleValues[j] = true; 
                        }
                    }

                    if (saturationNumber > highestSaturation ||
                        (saturationNumber == highestSaturation && degree > highestDegree)) {
                        highestSaturation = saturationNumber;
                        highestDegree = degree;
                        vertice = i;
                    }
                }
            }

            for (int i = 0; i < neighbourNumbers[vertice]; i++) {
                int neighbour = neigboursList[vertice][i];
                if (colors[neighbour] > 0) {
                    possibleValues[colors[neighbour]] = false;
                }
            }

            for (int i = 1; i <= n; i++) {
                if (possibleValues[i]) {
                    colors[vertice] = i;
                    break;
                }
            }

            for (int i = 0; i <= n; i++) {
                possibleValues[i] = true;
            }
        }

        for (int i = 1; i <= n; i++) {
            cout << colors[i] << " ";
        }

        delete[] colors;
        delete[] possibleValues;
        cout << "\n";

        return;
    }

    int getNumComplementEdges() {
        int totalEdges = (n - 1) * n;
        for (int i = 1; i <= n; i++) {
            totalEdges -= neighbourNumbers[i];
        }
        return totalEdges / 2;
    }
};
