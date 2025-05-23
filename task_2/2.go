package main

import (
	"fmt"
	"math"
)

func PredictTheWinner(nums []int) bool {
	n := len(nums)
	// Создаем таблицу memo размером n x n, заполняем минимальными значениями
	memo := make([][]int, n)
	for i := range memo {
		memo[i] = make([]int, n)
		for j := range memo[i] {
			memo[i][j] = math.MinInt32
		}
	}
	return score(nums, 0, n-1, memo) >= 0
}

func score(nums []int, i, j int, memo [][]int) int {
	if i == j {
		return nums[i]
	}
	if memo[i][j] != math.MinInt32 {
		return memo[i][j]
	}

	pickLeft := nums[i] - score(nums, i+1, j, memo)
	pickRight := nums[j] - score(nums, i, j-1, memo)

	memo[i][j] = max(pickLeft, pickRight)
	return memo[i][j]
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func main() {
	var n int
	fmt.Print("Введите количество чисел: ")
	fmt.Scan(&n)

	nums := make([]int, n)
	fmt.Printf("Введите %d чисел: ", n)
	for i := 0; i < n; i++ {
		fmt.Scan(&nums[i])
	}

	if PredictTheWinner(nums) {
		fmt.Println("Игрок 1 может победить (или сыграть вничью).")
	} else {
		fmt.Println("Игрок 1 не может победить.")
	}
}
