#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

class Solution {
public:
    // Основная функция для определения победителя
    bool PredictTheWinner(vector<int>& nums) {
        int n = nums.size();
        // Создаем таблицу для мемоизации (кеширования результатов)
        vector<vector<int>> memo(n, vector<int>(n, INT32_MIN));
        // Игрок 1 побеждает, если его счёт >= 0 (включая ничью)
        return score(nums, 0, n - 1, memo) >= 0;
    }

private:
    // Рекурсивная функция с мемоизацией для вычисления максимального счёта
    int score(vector<int>& nums, int i, int j, vector<vector<int>>& memo) {
        // Базовый случай: если остался один элемент
        if (i == j) return nums[i];
        // Если результат уже вычислен, возвращаем его
        if (memo[i][j] != INT32_MIN) return memo[i][j];

        // Рекурсивно вычисляем счёт при выборе левого или правого элемента:
        int pickLeft = nums[i] - score(nums, i + 1, j, memo);
        int pickRight = nums[j] - score(nums, i, j - 1, memo);

        // Сохраняем максимальный результат в таблицу
        memo[i][j] = max(pickLeft, pickRight);
        return memo[i][j];
    }
};

int main() {
    vector<int> nums;
    int n;
    cout << "Введите количество чисел: ";
    cin >> n;

    cout << "Введите " << n << " чисел: ";
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        nums.push_back(x);
    }

    Solution solver;
    // Проверяем, может ли первый игрок победить
    bool result = solver.PredictTheWinner(nums);

    if (result)
        cout << "Игрок 1 может победить (или сыграть вничью)." << endl;
    else
        cout << "Игрок 1 не может победить." << endl;

    return 0;
}
