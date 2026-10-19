#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <limits.h>

#define MAXV 100

typedef struct {
    int u, v;
    int w;
} Edge;

int parent[MAXV];
int rnk[MAXV];

void dsu_init(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rnk[i] = 0;
    }
}

int find(int v) {
    if (parent[v] == v) return v;
    return parent[v] = find(parent[v]);
}

void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) {
        if (rnk[a] < rnk[b]) parent[a] = b;
        else if (rnk[b] < rnk[a]) parent[b] = a;
        else {
            parent[b] = a;
            rnk[a]++;
        }
    }
}

void swap(Edge* a, Edge* b) {
    Edge t = *a;
    *a = *b;
    *b = t;
}

void sort_edges(Edge edges[], int m) {
    for (int i = 0; i < m - 1; i++)
        for (int j = 0; j < m - i - 1; j++)
            if (edges[j].w > edges[j + 1].w)
                swap(&edges[j], &edges[j + 1]);
}

int main() {

    int choice;
    int n;
    int matrix[MAXV][MAXV];

    // ------------------ MENU INPUT ---------------------
    printf("Enter 0 for ready matrix or 1 to enter matrix: ");
    scanf("%d", &choice);

    if (choice == 0) {
        // готова матриця 5x5
        n = 5;
        int ready[5][5] = {
            {0,4,2,10,6},
            {4,0,3,0,4},
            {2,3,0,1,5},
            {10,0,1,0,3},
            {6,4,5,3,0}
        };

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                matrix[i][j] = ready[i][j];

        printf("Using ready 5x5 matrix.\n");
    }
    else if (choice == 1) {
        printf("Enter number of vertices: ");
        scanf("%d", &n);

        if (n < 1 || n > MAXV) {
            printf("Error! Wrong number of vertices.\n");
            return 1;
        }

        printf("Enter matrix (%d x %d):\n", n, n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &matrix[i][j]);
                if (matrix[i][j] < 0) {
                    printf("Error, wrong matrix value.\n");
                    return 1;
                }
                if (i == j && matrix[i][j] != 0) {
                    printf("Diagonal must be 0!\n");
                    return 1;
                }
            }
        }
    }
    else {
        printf("Wrong input!\n");
        return 1;
    }

    // ------------------ EDGE LIST ----------------------
    Edge edges[MAXV * MAXV];
    int m = 0;

    printf("\nStep 1: Edge list\n");
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (matrix[i][j] > 0) {
                edges[m].u = i;
                edges[m].v = j;
                edges[m].w = matrix[i][j];
                printf("  Edge (%d-%d) weight = %d\n", i, j, matrix[i][j]);
                m++;
            }

    if (m == 0) {
        printf("No edges in graph.\n");
        return 1;
    }

  
    printf("\nStep 2: Sort edges\n");
    sort_edges(edges, m);
    for (int i = 0; i < m; i++)
        printf("  (%d-%d) weight = %d\n", edges[i].u, edges[i].v, edges[i].w);

    
    printf("\nStep 3: Kruskal algorithm\n");
    dsu_init(n);

    Edge mst[MAXV];
    int mst_size = 0;
    int total_weight = 0;

    for (int i = 0; i < m; i++) {
        int u = edges[i].u;
        int v = edges[i].v;

        if (find(u) != find(v)) {
            unite(u, v);
            mst[mst_size++] = edges[i];
            total_weight += edges[i].w;
        }
    }

    
    if (mst_size != n - 1) {
        printf("\nGraph is not connected. MST does not exist.\n");
        return 1;
    }

    printf("\nMST edges:\n");
    for (int i = 0; i < mst_size; i++)
        printf("  (%d-%d) weight = %d\n", mst[i].u, mst[i].v, mst[i].w);

    printf("Total weight = %d\n", total_weight);

    return 0;
}
