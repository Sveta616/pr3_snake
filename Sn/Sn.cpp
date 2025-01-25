// Sn.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <windows.h>   
int height = 20;
int width = 20;
char headS = 'O';
char body = 'o';
char apple = '@';
char pole[20][20];

struct Snake {
    int x, y;
    Snake* next;
};

Snake* head = nullptr;
int ap1, ap2;
bool finish = false;
char go = 'w';

void Game() {

    head = new Snake();
    head->x = height / 2;
    head->y = width / 2;
    head->next = nullptr;


    do {
        ap1 = 1 + rand() % (height - 2);
        ap2 = 1 + rand() % (height - 2);
    } while (ap1 == head->x && ap2 == head->y);
}

void Draw() {
    system("cls");
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || j == 0 || i == height - 1 || j == width - 1) {
                pole[i][j] = '#';
            }
            else {
                pole[i][j] = ' ';
            }
        }
    }

  
    pole[ap1][ap2] = apple;

   
    Snake* current = head;
    while (current != nullptr) {
        pole[current->x][current->y] = body;
        current = current->next;
    }
    pole[head->x][head->y] = headS;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            std::cout << pole[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void SnakeGo(char go) {
    int newX = head->x;
    int newY = head->y;

    switch (go) {
    case 'w': newX--; break; 
    case 's': newX++; break; 
    case 'a': newY--; break; 
    case 'd': newY++; break; 
    }

    
    if (newX <= 0 || newX >= height - 1 || newY <= 0 || newY >= width - 1) {
        finish = true;
        return;
    }

    
    Snake* current = head->next;
    while (current != nullptr) {
        if (current->x == newX && current->y == newY) {
            finish = true;
            return;
        }
        current = current->next;
    }

    
    if (newX == ap1 && newY == ap2) {
       
        Snake* news = new Snake();
        news->x = head->x;
        news->y = head->y;
        news->next = head;
        head = news;

      
        do {
            ap1 = 1 + rand() % (height - 2);
            ap2 = 1 + rand() % (width - 2);
        } while (pole[ap1][ap2] != ' ');
    }
    else {
       
        Snake* current = head;
        int predX = current->x;
        int predY = current->y;
        int pX, pY;

        while (current->next != nullptr) {
            pX = current->next->x;
            pY = current->next->y;
            current->next->x = predX;
            current->next->y = predY;
            predX = pX;
            predY = pY;
            current = current->next;
        }
        head->x = newX; 
        head->y = newY;
    }
}



int main()
{
    srand(time(NULL));
    Game();

    while (!finish) {
        Draw();

       
        if (_kbhit()) {
            char mego = _getch();
          
            if ((mego == 'w' && go != 's') ||
                (mego == 's' && go != 'w') ||
                (mego == 'a' && go != 'd') ||
                (mego == 'd' && go != 'a')) {
              go = mego;
            }
        }  
        SnakeGo(go);

        Sleep(100);
    }

    if (finish) {
        system("cls");
        std::cout << "game over, bye!" << std::endl;
    }
};

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
