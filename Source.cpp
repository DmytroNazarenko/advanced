#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <fstream>
#include <queue>
#include <vector>
#include <cstring>
#include <iomanip>
typedef long long ll;
typedef long long ull;
typedef long double ld;



int main()
{
    std::vector<int> L;
    int ***mas = new int **[110];
    for (int i = 0;i < 110; ++i) {
        mas[i] = new int *[310];
        for (int j = 0;j < 310; ++j) {
            mas[i][j] = new int[310];
        }
    }
    int N, M, D;
    std::cin >> M >> D;
    std::cin >> N;
    for (int i = 0; i < N; ++i) {
        int k;
        std::cin >> k;
        L.push_back(k);
    }
    mas[0][0][0] = 0;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j <= N; ++j) {
            if (i != 0) mas[i][j][0] = mas[i - 1][j][D];
            else
                mas[i][j][0] = 0;
            for (int k = 1; k <= D; ++k) {
                mas[i][j][k] = mas[i][j][k - 1];
                if (j > 0) mas[i][j][k] = std::max(mas[i][j][k], mas[i][j - 1][k]);
                if (j > 0 && k >= L[j - 1]) mas[i][j][k] =
                    std::max(mas[i][j][k], mas[i][j - 1][k - L[j - 1]] + 1);
            }
        }
    }
    std::cout << mas[M - 1][N][D];
}
