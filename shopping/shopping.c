/*
ID: lic92031
LANG: C
TASK: shopping
*/
#include <stdio.h>
int s;
int so_n[99] = {0}, so_c[99][5] = {0}, so_k[99][5] = {0}, so_p[99] = {0};
int b;
int b_c[5] = {0}, b_k[5] = {0}, b_p[5] = {0};
int rb[1000] = {0};

void KTcom(int n, int *a) {
    int i = 0;
    while (n > 0) {
        a[i] = n % 10;
        n /= 10;
        i++;
    }
}
int KText(int *a) {
    int i = 0;
    int n = 0;
    for (i = b - 1; i >= 0; i--) {
        n *= 10;
        n += a[i];
    }
    return n;
}
int KTnext(int n) {
    n++;
    int a[5] = {0};
    KTcom(n, a);
    int i = 0;
    for (i = 0; i < b; i++) {
        if (a[i] > b_k[i]) {
            a[i] = a[i] % (b_k[i] + 1);
            a[i + 1]++;
        }
    }
    return KText(a);
}
int main() {
    FILE *fin = fopen("shopping.in", "r");
    FILE *fout = fopen("shopping.out", "w");
    fscanf(fin, "%d", &s);
    int i = 0, j = 0;
    for (i = 0; i < s; i++) {
        fscanf(fin, "%d", &so_n[i]);
        for (j = 0; j < so_n[i]; j++)
            fscanf(fin, "%d%d", &so_c[i][j], &so_k[i][j]);
        fscanf(fin, "%d", &so_p[i]);
    }
    fscanf(fin, "%d", &b);
    for (i = 0; i < b; i++) {
        fscanf(fin, "%d%d%d", &b_c[i], &b_k[i], &b_p[i]);
        rb[b_c[i]] = i;
    }
    int f[100000] = {0};
    int g[100000] = {0};
    int goal = KText(b_k);
    int p = 0;
    g[p] = 1;
    f[p] = 0;
    while (p != goal) {
        int a[5] = {0};
        p = KTnext(p);
        KTcom(p, a);
        for (i = 0; i < b; i++) {
            int bb[5] = {0};
            for (j = 0; j < b; j++)
                bb[j] = a[j];
            if (bb[i] > 0) {
                bb[i] -= 1;
                if (f[KText(bb)] + b_p[i] < f[p] || !g[p]) {
                    g[p] = 1;
                    f[p] = f[KText(bb)] + b_p[i];
                }
            }
        }
        for (i = 0; i < s; i++) {
            int bb[5] = {0};
            for (j = 0; j < b; j++)
                bb[j] = a[j];
            int flag = 1;
            for (j = 0; j < so_n[i]; j++) {
                if (so_k[i][j] > bb[rb[so_c[i][j]]]) {
                    flag = 0;
                    break;
                }
                bb[rb[so_c[i][j]]] -= so_k[i][j];
            }
            if (flag) {
                if (f[KText(bb)] + so_p[i] < f[p]) f[p] = f[KText(bb)] + so_p[i];
            }
        }
    }
    fprintf(fout, "%d\n", f[goal]);
    fclose(fout);
    fclose(fin);
    return 0;
}
