package main

import (
	"fmt"
	"math"
)

var (
	minEdges  = math.MaxInt
	bestMask  int
	adjMatrix [][]int
)

func countCrossEdges(mask, n int) int {
	count := 0
	for i := 0; i < n; i++ {
		for j := i + 1; j < n; j++ {
			if adjMatrix[i][j] == 1 {
				inDiffGroups := ((mask>>i)&1) != ((mask>>j)&1)
				if inDiffGroups {
					count++
				}
			}
		}
	}
	return count
}

func search(bit, mask, n int) {
	if bit == n {
		if mask == 0 || mask == (1<<n)-1 {
			return // Пропускаем пустую или полную группу
		}
		edges := countCrossEdges(mask, n)
		if edges < minEdges {
			minEdges = edges
			bestMask = mask
		}
		return
	}

	// Рекурсивно пробуем: страна `bit` в группе 0 и в группе 1
	search(bit+1, mask, n) // В группе 0
	search(bit+1, mask|(1<<bit), n) // В группе 1
}

func main() {
	var n int
	fmt.Print("Введите количество стран: ")
	fmt.Scan(&n)

	adjMatrix = make([][]int, n)
	fmt.Printf("Введите матрицу смежности (%dx%d):\n", n, n)
	for i := range adjMatrix {
		adjMatrix[i] = make([]int, n)
		for j := range adjMatrix[i] {
			fmt.Scan(&adjMatrix[i][j])
		}
	}

	search(0, 0, n)

	fmt.Println("Минимальное количество связей между группами:", minEdges)

	fmt.Print("Группа 1: ")
	for i := 0; i < n; i++ {
		if (bestMask>>i)&1 == 1 {
			fmt.Print(i+1, " ")
		}
	}
	fmt.Println()

	fmt.Print("Группа 2: ")
	for i := 0; i < n; i++ {
		if (bestMask>>i)&1 == 0 {
			fmt.Print(i+1, " ")
		}
	}
	fmt.Println()
}
