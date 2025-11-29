#include <stdio.h>
#include <math.h>

int main() {
    int S;
    scanf("%d", &S);

    int n = S - 1;      // número de passos
    int k = n / 2;      // posição central

    long double prob = 1.0;

    // calcula C(n, k)
    for (int i = 1; i <= k; i++) {
        prob *= (long double)(n - k + i) / i;
    }

    // multiplica por 2^{-n}
    prob *= powl(0.5L, n);

    printf("%.2Lf\n", prob * 100.0L);

    return 0;
}
