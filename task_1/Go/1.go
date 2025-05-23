package main

import (
	"fmt"
	"image/color"
	"math"

	"github.com/fogleman/gg"
)

const (
	width  = 1000
	height = 400
)

func kochDraw(dc *gg.Context, x1, y1, x2, y2 float64, depth int) {
	if depth == 0 {
		dc.DrawLine(x1, y1, x2, y2)
		dc.Stroke()
		return
	}

	dx := x2 - x1
	dy := y2 - y1

	// Точки, делящие отрезок на 3 части
	xA := x1 + dx/3
	yA := y1 + dy/3

	xB := x1 + 2*dx/3
	yB := y1 + 2*dy/3

	// Вершина равностороннего треугольника
	angle := math.Atan2(dy, dx) - math.Pi/3
	length := math.Hypot(dx, dy) / 3
	xC := xA + length*math.Cos(angle)
	yC := yA + length*math.Sin(angle)

	// Рекурсивно строим
	kochDraw(dc, x1, y1, xA, yA, depth-1)
	kochDraw(dc, xA, yA, xC, yC, depth-1)
	kochDraw(dc, xC, yC, xB, yB, depth-1)
	kochDraw(dc, xB, yB, x2, y2, depth-1)
}

func main() {
	var depth int
	fmt.Print("Введите глубину рекурсии (например, 1): ")
	fmt.Scan(&depth)

	dc := gg.NewContext(width, height)
	dc.SetColor(color.Black)
	dc.Clear()

	dc.SetColor(color.White)
	kochDraw(dc, 100, 300, 900, 300, depth)

	// Сохраняем результат
	err := dc.SavePNG("koch_curve.png")
	if err != nil {
		fmt.Println("Ошибка при сохранении изображения:", err)
		return
	}
	fmt.Println("Кривая Коха сохранена как koch_curve.png")
}
