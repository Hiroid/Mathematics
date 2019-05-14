#include <bits/stdc++.h>
///#define debug

using namespace std;

const int nmax = 1e3 + 5;

double A[nmax][nmax] = {};
double x[nmax][nmax] = {};

int n, m;
double w = 1.22;
double e = 1e-5;

void init() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n + 1; j++) {
            cin >> A[i][j];
        }
    }
    for (int i = 1; i <= n; i++) cin >> x[i][0];
}

void Jacobi() {
    printf("Jacobi Method ");
    double fan;
    int k = 1;
    do {
        fan = 1e9;
        for (int i = 1; i <= n; i++) {
            double temp = 0;
            for (int j = 1; j <= n; j++) {
                if (j == i) continue;
                temp += A[i][j] * x[j][k - 1];
            }
            x[i][k] = 1 / A[i][i] * (A[i][n + 1] - temp);
            fan = min(fan, abs(x[i][k] - x[i][k - 1]));
            #ifdef debug
            printf("k = %d\ti = %d\tx[%d][%d] = %.8lf\n", k, i, k, i, x[i][k]);
            #endif // debug
        }
        k++;
        if (k >= 10000) {
            printf("Non convergence\n");
            return;
        }
    } while(fan > e);
    printf("Iteration times = %d\n", --k);
    for (int i = 1; i <= n; i++) {
        cout << x[i][k] << endl;
    }
}

void Guass_Sediel() {
    printf("Guass-Sediel Method ");
    double fan;
    int k = 1;
    do {
        fan = 1e9;
        for (int i = 1; i <= n; i++) {
            double temp = 0;
            for (int j = 1; j <= n; j++) {
                if (j == i) continue;
                if (j <= i - 1) temp += A[i][j] * x[j][k];
                else temp += A[i][j] * x[j][k - 1];
            }
            x[i][k] = 1 / A[i][i] * (A[i][n + 1] - temp);
            fan = min(fan, abs(x[i][k] - x[i][k - 1]));
            #ifdef debug
            printf("k = %d\ti = %d\tx[%d][%d] = %.8lf\n", k, i, k, i, x[i][k]);
            #endif // debug
        }
        k++;
        if (k >= 10000) {
            printf("Non convergence\n");
            return;
        }
    } while(fan > e);
    printf("Iteration times = %d\n", --k);
    for (int i = 1; i <= n; i++) {
        cout << x[i][k] << endl;
    }
}

void SOR() {
    printf("SOR Method ");
    double fan;
    int k = 1;
    do {
        fan = 1e9;
        for (int i = 1; i <= n; i++) {
            double temp = 0;
            for (int j = 1; j <= n; j++) {
                if (j == i) continue;
                if (j <= i - 1) temp += A[i][j] * x[j][k];
                else temp += A[i][j] * x[j][k - 1];
            }
            x[i][k] = (1 - w) * x[i][k - 1] + w / A[i][i] * (A[i][n + 1] - temp);
            fan = min(fan, abs(x[i][k] - x[i][k - 1]));
            #ifdef debug
            printf("k = %d\ti = %d\tx[%d][%d] = %.8lf\n", k, i, k, i, x[i][k]);
            #endif // debug
        }
        k++;
        if (k >= 10000) {
            printf("Non convergence\n");
            return;
        }
    } while(fan > e);
    printf("Iteration times = %d\n", --k);
    for (int i = 1; i <= n; i++) {
        cout << x[i][k] << endl;
    }
}

int main(){
    init();
    ///Jacobi();
    ///Guass_Sediel();
    SOR();
    return 0;
}
/*
3 4
4 3 0 24
3 4 -1 30
0 -1 4 -24
1 1 1
*/
