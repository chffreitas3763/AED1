#include <stdio.h>
#include <string.h>

int main() {
    int N;
    if (scanf("%d", &N) != 1) return 0;
    getchar(); // consome apenas o '\n' após o inteiro

    while (N--) {
        char s[150];
        if (!fgets(s, sizeof(s), stdin)) break;

        int len = strlen(s);
        if (len > 0 && s[len-1] == '\n') {
            s[len-1] = '\0';
            len--;
        }

        int mid = len / 2;

        // imprimir reverse da primeira metade
        for (int i = mid - 1; i >= 0; i--) putchar(s[i]);

        // imprimir reverse da segunda metade
        for (int i = len - 1; i >= mid; i--) putchar(s[i]);

        putchar('\n');
    }
    return 0;
}
