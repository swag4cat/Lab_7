#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

const double PI = acos(-1); // Определение числа PI через арккосинус

// Рекурсивная функция для построения кривой Коха
void koch_draw(sf::VertexArray& lines, double x1, double y1, double x2, double y2, int depth) {
    if (depth == 0) { // Базовый случай рекурсии - рисуем прямую линию
        lines.append(sf::Vertex(sf::Vector2f(x1, y1), sf::Color::White));
        lines.append(sf::Vertex(sf::Vector2f(x2, y2), sf::Color::White));
        return;
    }

    double dx = x2 - x1;
    double dy = y2 - y1;

    // Вычисляем точки, делящие отрезок на 3 равные части
    double xA = x1 + dx / 3.0;
    double yA = y1 + dy / 3.0;

    double xB = x1 + 2.0 * dx / 3.0;
    double yB = y1 + 2.0 * dy / 3.0;

    // Вычисляем координаты вершины равностороннего треугольника (центральной части)
    double angle = atan2(dy, dx) - PI / 3.0; // Угол поворота на 60 градусов
    double length = sqrt(dx * dx + dy * dy) / 3.0; // Длина стороны
    double xC = xA + length * cos(angle);
    double yC = yA + length * sin(angle);

    // Рекурсивно вызываем функцию для всех 4 новых отрезков
    koch_draw(lines, x1, y1, xA, yA, depth - 1);
    koch_draw(lines, xA, yA, xC, yC, depth - 1);
    koch_draw(lines, xC, yC, xB, yB, depth - 1);
    koch_draw(lines, xB, yB, x2, y2, depth - 1);
}

int main() {
    int depth;
    std::cout << "Введите глубину рекурсии (например, 1): ";
    std::cin >> depth; // Получаем глубину рекурсии от пользователя

    // Создаем окно SFML
    sf::RenderWindow window(sf::VideoMode(1000, 400), "Кривая Коха — Правильная");
    window.setFramerateLimit(60);

    sf::VertexArray lines(sf::Lines); // Массив вершин для отрисовки линий

    // Начальные точки горизонтального отрезка (основа кривой Коха)
    double x1 = 100, y1 = 300;
    double x2 = 900, y2 = 300;

    // Запускаем построение кривой Коха
    koch_draw(lines, x1, y1, x2, y2, depth);

    // Основной цикл отрисовки
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black); // Очищаем экран
        window.draw(lines); // Рисуем кривую Коха
        window.display(); // Отображаем на экране
    }

    return 0;
}
