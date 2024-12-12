#include <iostream>
using namespace std;
int findd(int arr[], int u, int v) {
    if (arr[u] == arr[v])
        return 1;
    else
        return 0;
}
void unionn(int arr[], int n, int u, int v) {
    int temp = arr[u];
    for (int i = 0; i < n; i++) {
        if (arr[i] == temp)
            arr[i] = arr[v];
    }
}
int Partition(int A[], int B[], int C[], int l, int r) {
    int pivot = A[l];
    int pivotB = B[l];
    int pivotC = C[l];
    int i = l;
    int j = r + 1;
    while (true) {
        do {
            i++;
        } while (i <= r && A[i] <= pivot);
        do {
            j--;
        } while (A[j] > pivot);

        if (i >= j)
            break;
        swap(A[i], A[j]);
        swap(B[i], B[j]);
        swap(C[i], C[j]);
    }
    swap(A[l], A[j]);
    swap(B[l], B[j]);
    swap(C[l], C[j]);
    return j;
}
void QuickSort(int A[], int B[], int C[], int l, int r) {
    if (l < r) {
        int s = Partition(A, B, C, l, r);
        QuickSort(A, B, C, l, s - 1);
        QuickSort(A, B, C, s + 1, r);
    }
}
void Kruskal(int n, int e, int u[], int v[], int w[]) {
    int arr[n];
    for (int i = 0; i < n; i++)
        arr[i] = i;
    int mst_cost = 0;
    QuickSort(w, u, v, 0, e - 1);
    cout << "\nEdges in the MST:\n";
    for (int i = 0; i < e; i++) {
        if (!findd(arr, u[i], v[i])) {
            unionn(arr, n, u[i], v[i]);
            mst_cost += w[i];
            cout << u[i] << " - " << v[i] << " (Weight: " << w[i] << ")\n";
        }
    }
    cout << "Total cost of MST: " << mst_cost << endl;
}
int main() {
    int n, e;
    cout << "Enter number of vertices and edges: ";
    cin >> n >> e;
    int u[e], v[e], w[e];
    cout << "Enter edges (u, v, weight):\n";
    for (int i = 0; i < e; i++) {
        cin >> u[i] >> v[i] >> w[i];
    }
    cout << "\nEntered edges are:\n";
    for (int i = 0; i < e; i++) {
        cout << u[i] << " - " << v[i] << " (Weight: " << w[i] << ")\n";
    }
    Kruskal(n, e, u, v, w);
    return 0;
}