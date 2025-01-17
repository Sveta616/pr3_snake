// Snake.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <windows.h>   
struct Apple
{
    int x;
    int y;
};
struct Node
{
    int x;
    int y;
    Node* next;
};

class Snake
{
private:
    Node* head = nullptr;
    Node* tail = nullptr;
    Apple apple;
    char pole[20][20];
    int score = 0;
public:
    void Tail()
    {
        Node* current = head;// начинаем с головы змейки
        while (current->next != nullptr)  // до конца змейки
        {
            current = current->next;// на след элемент
        }
        tail = current;// устанавливаем хвост
    }
    void Add(int x, int y)
    {
        if (head == nullptr) // змейка пустая
        {
            head = new Node{ x,y,nullptr };// новая часть
            return;
        }
        Tail(); // находим хвост
        Node* current = tail; // указатель на хвост
        current->next = new Node{ x,y,nullptr }; // добавляем еще часть новую
        score++; 
    }
    void DoApple()
    {
        do
        {
            int x = rand() % 20; // выбираем позицию яблока рандомно
            int y = rand() % 20;
            if (pole[x][y] == '.' || pole[x][y] == NULL) // проверка есть ли место
            {
                apple.x = x; 
                apple.y = y;
                break;

            }
        } while (true);
    }
    bool Refresh(int temp)
    {
        system("cls"); //очистка коносоли 
        Node* next= head; // на след поз
        int pervx = 0;// пред координата х и у
        int pervy = 0;
        bool game = true;
        if (score >= 99)
        {
            game = false;
        }
        if (next != nullptr)
        {
            switch (temp)
            {
            case 0:pervx = next->x;
                pervy = next->y;
                if (next->x <= 0)//вркзалась в поле
                {
                    game = false;
                }
                else
                {
                    next->x -= 1;//вверх
                }
                break;

            case 1: pervx = next->x;
                pervy = next->y;
                if (next->x >= 19)
                {
                    game = false;
                }
                else
                {
                    next->x += 1;//вниз
                }
                break;
            case 2: pervx = next->x;
                pervy = next->y;
                if (next->y <= 0)
                {
                    game = false;
                }
                else
                {
                    next->y -= 1;//влево
                }
                break;
            case 3: pervx = next->x;
                pervy = next->y;
                if (next->y >= 19)
                {
                    game = false;
                }
                else
                {
                    next->y += 1;// вправо
                }
                break;
            }
        }
        for (int i = 0;i < 20;i++)
        {
            for (int j = 0; j < 20; j++)
            {
                pole[i][j] = '.';
            }
        }
        pole[apple.x][apple.y] = 'X';
        Node* current = head;
        if (current != nullptr) 
        {
            int x = current->x;
            int y = current->y;
            Node* proverka = head;
            while (proverka->next != nullptr) // проходим по каждой части змейки
            {
                if (proverka->next->x == x && proverka->next->y == y) // проверка на то врезалась ли голова змейки в тело
                {
                    game = false;
                }
                proverka = proverka->next;// переход на след часть
            }
            pole[x][y] = 'O';
            while (current->next != nullptr) // перемещение
            {

                x = current->next->x; //сохраняем след часть
                y = current->next->y;
                current->next->x = pervx; //перемещаем след часть
                current->next->y = pervy;
                pervx = x;//обновление координат
                pervy = y;

                pole[current->next->x][current->next->y] = 'o'; // устанавливаем тело змейки на поле
                current = current->next;
            }
            Node* check = head;

            if (check->x == apple.x && check->y == apple.y) // проверка на то съела ли голова змейки яблоко
            {
                Add(pervx, pervy); // добавляем часть змейки 
                DoApple(); // генерируем новое яблоко
            }

        }

        for (int i = 0; i < 20; i++) //вывод новго пооя
        {
            for (int j = 0; j < 20; j++)
            {
                std::cout << pole[i][j] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "score : " << score << "\n";
        return game;
    }
   };
    int main()
    {
        Snake game;
        srand(time(NULL));
        game.Add(10,9); // начальная змейка
        game.DoApple(); // начальное яблоко
        bool isGaming = true;
        int temp = 0;

        while (isGaming)
        {
           isGaming = game.Refresh(temp); // обновление поля 
            Sleep(105);

            if (_kbhit()) // когда нажимается клавиша выполняется условие
            {
                switch (_getch()) // определяем какую клавишу нажали
                {
                case'w'://вверх
                    if (temp != 0 && temp != 1)
                    {
                        temp = 0;
                    }
                    break;
                case's'://вниз
                    if (temp != 0 && temp != 1)
                    {
                        temp = 1;
                    }
                    break;
                case'a'://влево
                    if (temp != 2 && temp != 3)
                    {
                        temp = 2;
                    }
                    break;
                case'd'://вправо
                    if (temp != 2 && temp != 3)
                    {
                        temp = 3;
                    }
                    break;
                }

            }

        }

        std::cout << "game over";
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
