// Snake_game.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <windows.h>  
struct Node {
    int x, y;
    Node* next;
};

class Snake {
public:
    Node* head;
    Node* tail;
    int length;
    int navigate; // 0-вверх, 1-вправо 2-вниз, 3-влево
    int score;

    Snake(int startX, int startY) {
        head = new Node{ startX, startY, nullptr };
        tail = head;
        length = 0;
        navigate = 1;// реализуем вправо
    }

    void grow() {
        Node* newNode = new Node{ tail->x, tail->y, nullptr };
        tail->next = newNode;
        tail = newNode;
        length++;
    }

    void move(bool hasEaten) {
        Node* newHead = new Node;
        newHead->x = head->x;
        newHead->y = head->y;

        switch (navigate) {
        case 0: newHead->y--; break; // up
        case 1: newHead->x++; break; // right
        case 2: newHead->y++; break; // down
        case 3: newHead->x--; break; // left
        }

        newHead->next = head;
        head = newHead;

        // Remove the last segment only if the snake hasn't grown
        if (!hasEaten) {
            Node* temp = head;
            for (int i = 0; i < length; i++) { // Loop through the correct length
                temp = temp->next;
            }
            temp->next = nullptr; // remove the last element
        }
        else {
            score++; // Increment score when the snake eats an apple
        }

    }
    void changeDirection(int newDirection) {
        // Определяем текущее направление
        int currentDirection = navigate;

        if ((currentDirection == 0 && newDirection == 2) ||  // Up vs Down
            (currentDirection == 1 && newDirection == 3) ||  // Right vs Left
            (currentDirection == 2 && newDirection == 0) ||  // Down vs Up
            (currentDirection == 3 && newDirection == 1)) {  // Left vs Right
            return;
        }

        // Если новое направление не противоположное, меняем направление
        navigate = newDirection;
    }
    bool checkCollision(int width, int height) {
        if (head->x < 1 || head->x >= width - 1 || head->y < 1  ||head->y >= height - 1) {
            return true;
        }

        Node* current = head->next;
        while (current != nullptr) {
            if (current->x == head->x && current->y == head->y) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

struct Apple {
    int x, y;
};

void draw(Snake& snake, Apple& apple, int width, int height) {
    system("cls");
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (x == 0  ||x == width - 1  ||y == 0 || y == height - 1) {
                std::cout << "#"; // boundaries
            }
            else if (x == snake.head->x && y == snake.head->y) {
                std::cout << "O"; // snake head
            }
            else if (x == apple.x && y == apple.y) {
                std::cout << "X"; // apple
            }
            else {
                bool isBody = false;
                Node* current = snake.head->next;
                while (current != nullptr) {
                    if (current->x == x && current->y == y) {
                        std::cout << "o"; // snake body
                        isBody = true;
                        break;
                    }
                    current = current->next;
                }
                if (!isBody) {
                    std::cout << " "; // empty space
                }
            }
        }
        std::cout << std::endl;
    }
    std::cout << "Score: " << snake.score << std::endl; // Display the score
}
void placeApple(Apple& apple, int width, int height, Snake& snake) {
    bool onSnake;
    do {
        onSnake = false;
        apple.x = rand() % 20; // random x within bounds
        apple.y = rand() % 20; // random y within bounds

        // Check if the apple is placed on the snake
        Node* current = snake.head;
        while (current != nullptr) {
            if (current->x == apple.x && current->y == apple.y) {
                onSnake = true;
                break;
            }
            current = current->next;
        }
    } while (onSnake);
}

int main()
{
    const int width = 20;
    const int height = 20;
    Snake snake(width, height);
    Apple apple;
    placeApple(apple, width, height, snake);

    while (true) {
        if (_kbhit()) {
            switch (_getch()) {
            case 'w': snake.changeDirection(0); break; // up
            case 'd': snake.changeDirection(1); break; // right
            case 's': snake.changeDirection(2); break; // down
            case 'a': snake.changeDirection(3); break; // left
            }
        }
        bool hasEaten = (snake.head->x == apple.x && snake.head->y == apple.y);
        snake.move(hasEaten); // Pass whether the snake has eaten an apple

        if (snake.checkCollision(width, height)) {
            std::cout << "Game Over!" << std::endl;
            break;
        }

        if (hasEaten) {
            snake.grow(); // Add a new segment to the snake
            placeApple(apple, width, height, snake); // Place a new apple
        }

        draw(snake, apple, width, height);
        Sleep(100); // delay for game speed
    }
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
