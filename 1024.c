#include <stdio.h>
#include <string.h>

int main() {
    int N;
    scanf("%d\n", &N);

    while (N--) {
        char s[1005];
        fgets(s, 1005, stdin);

        int len = strlen(s);

        // Remover \n se existir
        if (len > 0 && s[len-1] == '\n') {
            s[len-1] = '\0';
            len--;
        }

        // 1ª passada: +3 em letras
        for (int i = 0; i < len; i++) {
            if ((s[i] >= 'a' && s[i] <= 'z') ||
                (s[i] >= 'A' && s[i] <= 'Z')) {
                s[i] += 3;
            }
        }

        // 2ª passada: inverter string
        for (int i = 0, j = len-1; i < j; i++, j--) {
            char temp = s[i];
            s[i] = s[j];
            s[j] = temp;
        }

        // 3ª passada: da metade em diante, -1 em qualquer caractere
        for (int i = len/2; i < len; i++) {
            s[i]--;
        }

        printf("%s\n", s);
    }

    return 0;
}
