#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int min_edges = INT_MAX;
int best_mask = 0;

int count_cross_edges(const vector<vector<int>>& A, int mask, int n) {
    int count = 0;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (A[i][j]) {
                bool in_diff_groups = ((mask >> i) & 1) != ((mask >> j) & 1);
                if (in_diff_groups) count++;
            }
            return count;
}

// Рекурсивная функция перебора масок
void search(int bit, int mask, const vector<vector<int>>& A, int n) {
    if (bit == n) {
        // Пропускаем полные группы (все 0 или все 1)
        if (mask == 0 || mask == (1 << n) - 1) return;

        int edges = count_cross_edges(A, mask, n);
        if (edges < min_edges) {
            min_edges = edges;
            best_mask = mask;
        }
        return;
    }

    // Рекурсивно пробуем: страна `bit` в группе 0 и в группе 1
    search(bit + 1, mask, A, n); // Страна в группе 0
    search(bit + 1, mask | (1 << bit), A, n); // Страна в группе 1
}

int main() {
    int n;
    cout << "Введите количество стран: ";
    cin >> n;

    vector<vector<int>> A(n, vector<int>(n));
    cout << "Введите матрицу смежности (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> A[i][j];

    search(0, 0, A, n); // Запуск перебора с пустой маской

    cout << "Минимальное количество связей между группами: " << min_edges << endl;

    cout << "Группа 1: ";
    for (int i = 0; i < n; ++i)
        if ((best_mask >> i) & 1)
            cout << i + 1 << " ";
    cout << endl;

    cout << "Группа 2: ";
    for (int i = 0; i < n; ++i)
        if (!((best_mask >> i) & 1))
            cout << i + 1 << " ";
    cout << endl;

    return 0;
}
