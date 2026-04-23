#include <stdio.h>

/* Função auxiliar para trocar dois elementos no vetor */
void troca(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * CONSTRÓI HEAP (Sobe na árvore)
 * Transforma um vetor v[1..m] em um heap.
 * A ideia é que, enquanto o valor de um filho for maior que o de seu pai,
 * os valores são trocados e subimos em direção à raiz [3].
 */
static void constroiHeap(int m, int v[]) {
    for (int k = 1; k < m; ++k) {
        int f = k + 1; // f é o filho
        // Enquanto o filho não for a raiz e for maior que o pai (f/2)
        while (f > 1 && v[f/2] < v[f]) {
            troca(&v[f/2], &v[f]);
            f /= 2; // Sobe um passo em direção à raiz [3]
        }
    }
}

/**
 * FUNÇÃO PENEIRA (Desce na árvore)
 * Recebe um vetor v[1..m] e faz o elemento v[4] descer até sua posição correta.
 * É o coração do algoritmo, pulando de uma camada para a seguinte [5, 6].
 */
static void peneira(int m, int v[]) {
    int p = 1;      // p é o pai (começa na raiz)
    int f = 2;      // f é o filho esquerdo de p
    int x = v[4];   // x guarda o valor que está "peneirando" para baixo

    while (f <= m) {
        // Escolhe o filho f de p que tem o maior valor [6]
        if (f < m && v[f] < v[f+1]) {
            ++f; // f passa a ser o filho direito
        }
        // Se o valor x for maior ou igual ao maior dos filhos, paramos [6]
        if (x >= v[f]) {
            break;
        }
        // Caso contrário, o filho sobe para a posição do pai
        v[p] = v[f];
        p = f;      // O "buraco" desce para a posição do filho
        f = 2 * p;  // Novo filho esquerdo
    }
    v[p] = x; // Coloca o valor original na sua posição correta [6]
}

/**
 * ALGORITMO HEAPSORT
 * Rearranja o vetor v[1..n] em ordem crescente em duas fases [7].
 */
void heapsort(int n, int v[]) {
    // Fase 1: Transforma o vetor original em um heap [7]
    constroiHeap(n, v);

    // Fase 2: Retira elementos do heap em ordem decrescente
    for (int m = n; m > 1; --m) {
        // O maior elemento está sempre em v[4]. 
        // Trocamos ele com o último elemento (v[m]) [7]
        troca(&v[4], &v[m]);

        // "Peneiramos" o novo v[4] para restaurar a propriedade de heap 
        // no vetor reduzido v[1..m-1] [7]
        peneira(m - 1, v);
    }
}

int main() {
    // Exemplo de uso: vetor com índices 1..10 (tamanho 11 para ignorar o índice 0)
    // Conforme as fontes, v[1..n] é a convenção [1, 2]
    int n = 10;
    int v[] = {0, 161, 41, 101, 141, 71, 91, 31, 21, 81, 17}; 

    printf("Vetor original:\n");
    for (int i = 1; i <= n; i++) printf("%d ", v[i]);
    
    heapsort(n, v);

    printf("\n\nVetor ordenado:\n");
    for (int i = 1; i <= n; i++) printf("%d ", v[i]);
    printf("\n");

    return 0;
}