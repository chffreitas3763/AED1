#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char num[64], cutoff[16];

    // Leitura até EOF. Cada caso tem duas strings (num e cutoff)
    while (scanf("%s %s", num, cutoff) == 2) {
        // separar parte inteira e fracionária de num
        char integer[64] = {0};
        char frac_all[1024] = {0}; // armazena toda a parte fracionária de num

        char *dot = strchr(num, '.');

        if (!dot) {
            // não há ponto
            strcpy(integer, num);
            frac_all[0] = '\0';
        } else {
            // tem ponto
            int len_int = dot - num;
            if (len_int > 0) {
                strncpy(integer, num, len_int);
                integer[len_int] = '\0';
            } else {
                // caso ".xxx"
                strcpy(integer, "0");
            }
            // copia tudo depois do ponto (pode ser vazio)
            strcpy(frac_all, dot + 1);
        }

        // remover zeros à esquerda da parte inteira (deixar "0" se ficar vazia)
        int i = 0;
        while (integer[i] == '0' && integer[i+1] != '\0') i++;
        if (i > 0) memmove(integer, integer + i, strlen(integer + i) + 1);

        // obter os 4 dígitos de cutoff (sempre "0.####")
        char cut4[5];
        strncpy(cut4, cutoff + 2, 4);
        cut4[4] = '\0';

        // comparar frac_all com cut4:
        // compare dígito a dígito (até 4). Se igual nos 4 primeiros, então
        // se houver dígitos adicionais em frac_all diferentes de '0' -> num > cutoff
        int cmp = 0; // cmp >0 => frac(num) > cutoff ; cmp <0 => frac(num) < cutoff
        int lf = strlen(frac_all);

        for (int k = 0; k < 4; k++) {
            char d_num = (k < lf) ? frac_all[k] : '0';
            char d_cut = cut4[k];
            if (d_num > d_cut) { cmp = 1; break; }
            if (d_num < d_cut) { cmp = -1; break; }
        }
        if (cmp == 0) {
            // primeiros 4 dígitos iguais; verificar se há dígitos extras não-zero em num
            if (lf > 4) {
                // se algum dos dígitos extras != '0' => num > cutoff
                int any = 0;
                for (int k = 4; k < lf; k++) if (frac_all[k] != '0') { any = 1; break; }
                if (any) cmp = 1;
                else cmp = 0; // exatamente igual (segundo enunciado não ocorre)
            } else {
                cmp = 0; // igual ou não tem mais dígitos
            }
        }

        // se frac(num) > cutoff => arredonda para cima; caso contrário arredonda para baixo
        long long val = atoll(integer);
        if (cmp > 0) val++;

        printf("%lld\n", val);
    }

    return 0;
}
