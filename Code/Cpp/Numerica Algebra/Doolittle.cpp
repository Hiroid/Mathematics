#include <bits/stdc++.h>
///#define debug

using namespace std;

const int nmax = 1e3 + 5;

int n, m;
double A[nmax][nmax]= {},
       B[nmax][nmax] = {},
       L[nmax][nmax]={},
       U[nmax][nmax] = {};

void init() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%lf", &A[i][j]);
            B[i][j] = A[i][j];
        }
        L[i][i] = 1;
    }
    #ifdef debug
    printf("\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            std::cout << A[i][j] << "\t";
        }printf("\n");
    }
    #endif // debug
}

void LU() {
    for (int i = 1; i <= n; i++) {
        if (i == 1) {
            for (int j = i; j <= n; j++) {
                U[1][j] = A[1][j];
            }
            for (int j = i + 1; j <= n; j++) {
                L[j][1] = A[j][1] / U[1][1];
            }
        }
        else {
            #ifdef debug
            printf("Calculating line U\n");
            #endif // debug
            for (int j = i; j <= n; j++) {
                double temp = 0;
                for (int k = 1; k < i; k++) {
                    temp += L[i][k] * U[k][j];
                }
                #ifdef debug
                printf("i = %d j = %d temp = %.10f\n", i, j, temp);
                #endif // debug
                U[i][j] = A[i][j] - temp;
            }
            #ifdef debug
            printf("\nCalculating Role L\n");
            #endif // debug
            for (int j = i + 1; j <= n; j++) {
                double temp = 0;
                for (int k = 1; k < i; k++) {
                    temp += L[j][k] * U[k][i]; /// U[k][i] it's easy to write in the opposite way
                }
                #ifdef debug
                printf("i = %d j = %d temp = %.10f\n", i, j, temp);
                #endif // debug
                L[j][i] = (A[j][i] - temp) / U[i][i];/// U[i][i] is easy to write to A[i][i]
            }
        }
    }
    #ifdef debug
    printf("Matrix L\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%.6f\t", L[i][j]);
        }printf("\n\n");
    }

    printf("Matrix U\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%.6f\t", U[i][j]);
        }printf("\n\n");
    }
    #endif // debug
}

void LU_solve() {
    printf("Doolittle\n");
    for (int i = 1; i <= n; i++) L[i][n + 1] = A[i][n + 1];
    for (int i = 1; i <= n; i++) {
        if (i == 1) continue;
        else {
            double temp = 0;
            for (int j = 1; j < i; j++) {
                temp += L[i][j] * L[j][m];
            }
            L[i][m] = (L[i][m] - temp) / L[i][i];
        }
    }
    #ifdef debug
    for (int i = 1; i <= n; i++) {
        printf("y[%d] = %.10f\n", i, L[i][m]);
    }
    #endif // debug

    for (int i = 1; i <= n; i++) U[i][n + 1] = L[i][n + 1];
    for (int i = n; i >= 1; i--) {
        if (i == n) U[n][m] /= U[n][n];
        else {
            double temp = 0;
            for (int j = n; j > i; j--) {
                temp += U[i][j] * U[j][m];
            }
            U[i][m] = (U[i][m] - temp) / U[i][i];
        }
    }
    for (int i = 1; i <= n; i++) {
        printf("x[%d] = %.10f\n", i, U[i][m]);
    }
}

int main() {
    init();
    LU();
    LU_solve();
    return 0;
}
/*
4 5
6 2 1 -1 6
2 4 1 0 -1
1 1 4 -1 5
-1 0 -1 3 -5
*/
