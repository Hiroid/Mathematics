///"" find the header in the present folder
#include <bits/stdc++.h>
///#define debug
///#define maj

const int nmax = 1e3 + 5;

int n, m;
double A[nmax][nmax] = {}, B[nmax][nmax] = {};

void init() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%lf", &A[i][j]);
            B[i][j] = A[i][j];
        }
    }
    #ifdef debug
    printf("\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            std::cout << B[i][j] << "\t";
        }printf("\n");
    }
    #endif // debug
}

void swp(int step) {
    int maxr = step;
    double maxv = std::abs(B[step][step]);
    for (int i = step + 1; i <= n; i++) {
        if (std::abs(B[i][step]) > maxv) {
            maxr = i;
            maxv = std::abs(B[i][step]);
        }
    }
    if (maxr != step) {
        double temp = 0;
        for (int j = 1; j <= m; j++) {
            temp = B[maxr][j];
            B[maxr][j] = B[step][j];
            B[step][j] = temp;
        }
    }
}

void Gauss() {
    printf("Gauss");
    #ifdef maj
    printf(" line major");
    #endif // maj
    printf("\n");
    for (int i = 1; i < n; i++) {
        #ifdef maj
        swp(i);
        #endif // maj
        for (int j = i + 1; j <= n; j++) {
            for (int k = i + 1; k <= m; k++) {
                #ifdef debug
                printf("i = %d  j = %d  k = %d  B[%d][%d] = %.6f\n", i, j, k, j, k, B[j][k]);
                printf("B[%d][%d] = %.6f  "
                       "B[%d][%d] = %.6f  "
                       "B[%d][%d] = %.6f\n", i, k, B[i][k], j, i, B[j][i], i, i, B[i][i]);
                #endif // debug

                B[j][k] -= B[i][k] * B[j][i] / B[i][i];

                #ifdef debug
                printf("B[%d][%d] = %.6f\n\n", j, k, B[j][k]);
                #endif // debug
            }
            B[j][i] = 0;
        }
    }
    #ifdef debug
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            std::cout << B[i][j] << "\t";
        }printf("\n\n");
    }
    #endif // debug
}

void Guass_solve() {
    for (int i = n; i >= 1; i--) {
        if (i == n) B[n][m] /= B[n][n];
        else {
            double temp = 0;
            for (int j = n; j > i; j--) {
                temp += B[i][j] * B[j][m];
            }
            B[i][m] = (B[i][m] - temp) / B[i][i];
        }
    }
    for (int i = 1; i <= n; i++) {
        printf("ans[%d] = %.10f\n", i, B[i][m]);
    }
}

int main() {
    init();
    Gauss();
    Guass_solve();
    return 0;
}
/*
3 4
1e-7 0.3654 2.5542 1
-1.2546 1e-7 1.2563 2
-2.2213 0.2362 1e-4 3
*/
