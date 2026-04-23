#include <stdio.h>
#include <stdlib.h>

/* Função auxiliar para trocar dois elementos no vetor */
void troca(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * CONSTRÓI HEAP (Sobe na árvore)
*/
static void constroiHeap(int m, int v[]) {
    for (int k = 1; k < m; ++k) {
        int f = k + 1; 
        while (f > 1 && v[f/2] < v[f]) {
            troca(&v[f/2], &v[f]);
            f /= 2; 
        }
    }
}

/**
 * FUNÇÃO PENEIRA (Desce na árvore)
 */
static void peneira(int m, int v[]) {
    int p = 1;      // p é o pai (raiz)
    int f = 2;      // f é o filho esquerdo
    int x = v[1];   // x guarda o valor da raiz que vai descer

    while (f <= m) {
        if (f < m && v[f] < v[f+1]) {
            ++f; 
        }
        if (x >= v[f]) {
            break;
        }
        v[p] = v[f];
        p = f;      
        f = 2 * p;  
    }
    v[p] = x; 
}

/**
 * ALGORITMO HEAPSORT
 */
void heapsort(int n, int v[]) {
    constroiHeap(n, v);

    for (int m = n; m > 1; --m) {
        // O maior elemento está sempre em v[1]
        troca(&v[1], &v[m]);
        peneira(m - 1, v);
    }
}

int main() {
    int n = 10000; // Definindo para 10.000 elementos
    
    // Alocação dinâmica para evitar estouro de pilha
    // Alocamos n + 1 para manter a lógica de índices 1..n
    int *v = (int *)malloc((n + 1) * sizeof(int));

    if (v == NULL) {
        printf("Erro de memória!\n");
        return 1;
    }

    // Preenchendo o vetor com valores decrescentes para testar o pior caso
    for (int i = 1; i <= n; i++) {
        v[i] = n - i;
    }

    printf("Ordenando %d elementos...\n", n);
    
    heapsort(n, v);

    printf("Ordenacao concluida.\n");
    
    // Mostrando apenas os primeiros e últimos 10
    printf("Primeiros 10 elementos: ");
    for (int i = 1; i <= 10; i++) printf("%d ", v[i]);
    
    printf("\nUltimos 10 elementos:   ");
    for (int i = n - 9; i <= n; i++) printf("%d ", v[i]);
    printf("\n");

    free(v);
    return 0;
}