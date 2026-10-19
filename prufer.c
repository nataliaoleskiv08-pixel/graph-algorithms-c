#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int choise;
    int code_pruf[20];
    int m = 0;
    printf("Enter 0 for ready code or 1 for enter code: ");
    scanf("%d", &choise);
    if (choise == 0) {
        int ready_code[] = { 3,4,5,4,3,4,4,5,2,3 };
        m = 10;
        for (int i = 0; i < m; i++) {
            code_pruf[i] = ready_code[i];
        }
    }
    else if (choise == 1) {
        printf("Enter size of code: ");
        scanf("%d", &m);
        if (m < 1) {
            printf("Wrong input!");
            return 1;
        }
        printf("Enter element: ");
        for (int i = 0; i < m; i++) {
            scanf("%d", &code_pruf[i]);
        }
    }
    else {
        printf("Wrong input!");
        return 1;
    }
    int n = m + 2;


    int* degree = (int*)calloc(n + 1, sizeof(int));
    if (!degree) {
        perror("calloc");
        return 1;
    }

    for (int i = 1; i <= n; ++i) degree[i] = 1;
    for (int i = 0; i < m; ++i) {
        int v = code_pruf[i];
        if (v < 1 || v > n) {
            fprintf(stderr, "Error1\n");
            free(degree);
            return 1;
        }
        degree[v] += 1;
    }

    int (*edges)[2] = malloc((n - 1) * sizeof * edges);
    if (!edges) {
        perror("malloc");
        free(degree);
        return 1;
    }
    int edge_count = 0;

    printf("Code Pruf: size %d. %d versh:\n", m, n);
    for (int i = 0; i < m; ++i) printf("%d ", code_pruf[i]);
    printf("\n\n");

    for (int k = 0; k < m; ++k) {

        printf("%d)\n", k + 1);
        printf("  Code remain: ");
        for (int j = k; j < m; ++j) printf("%d ", code_pruf[j]);
        printf("\n");

        int leaf = -1;
        for (int i = 1; i <= n; ++i) {
            if (degree[i] == 1) { leaf = i; break; }
        }
        if (leaf == -1) {
            fprintf(stderr, "Nothing was found. %d\n", k + 1);
            free(degree); free(edges);
            return 1;
        }

        int connect_to = code_pruf[k];
        edges[edge_count][0] = leaf;
        edges[edge_count][1] = connect_to;
        edge_count++;

        printf("  Adding rebro: (%d - %d)\n\n", leaf, connect_to);

        degree[leaf] -= 1;
        degree[connect_to] -= 1;
    }


    int a = -1, b = -1;
    for (int i = 1; i <= n; ++i) {
        if (degree[i] == 1) {
            if (a == -1) a = i;
            else if (b == -1) b = i;
        }
    }
    if (a == -1 || b == -1) {
        fprintf(stderr, "Error, no remain vershins were found\n");
        free(degree); free(edges);
        return 1;
    }

    edges[edge_count][0] = a;
    edges[edge_count][1] = b;
    edge_count++;

    printf("Final step: remain vershini %d and %d\n\n", a, b);

    printf("Tree (rebra %d):\n", edge_count);
    for (int i = 0; i < edge_count; ++i) {
        printf("  %d - %d\n", edges[i][0], edges[i][1]);
    }
    free(edges); free(degree);

    return 0;
}
