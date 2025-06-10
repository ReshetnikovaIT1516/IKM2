#include <iostream>
#include <list>
#include <stdexcept>
#include <string>
#include <cctype>
#include <sstream>
#include <climits>
#include <windows.h> 
#include "Header.h"

using namespace std;

InputException::InputException(const string& msg) : message(msg) {} // Конструктор, принимающий сообщение об ошибке

const char* InputException::what() const noexcept // Переопределение метода what() 
// noexcept гарантирует, что метод what() не выбросит исключение
// override  позволяет компилятору проверить, что мы действительно переопределяем  метод
{
    return message.c_str();// Хранит текст сообщения об ошибке
}

// Статический метод для получения целого числа в нужном нам диапазоне
int checkingForInput::getInteger(const string& prompt, int min, int max)
{
    while (true)
    {
        cout << prompt; //Prompt строка - приглашение, которая используется для запроса ввода от пользователя.
        string input;
        getline(cin, input);

        try {
            if (input.empty())
            {
                throw InputException("Ошибка: Пустой ввод. Пожалуйста, введите число.");
            }
            // Проверка на наличие нечисловых символов (кроме минуса в начале)
            bool hasMinus = (input[0] == '-');
            for (size_t i = hasMinus ? 1 : 0; i < input.size(); ++i)
            {
                if (!isdigit(input[i]))
                {
                    throw InputException("Ошибка: Введены недопустимые символы. Пожалуйста, введите целое число.");
                }
            }

            if (input.length() > 10 || (hasMinus && input.length() > 11)) // Проверка на слишком длинное число
            {
                throw InputException("Ошибка: Введено слишком большое число. Пожалуйста, введите число поменьше.");
            }

            long long value; // Преобразование с проверкой переполнения
            try
            {
                value = stoll(input);
            }
            catch (...) // Все остальные ошибки
            {
                throw InputException("Ошибка: Недопустимый числовой формат.");
            }

            if (value < min || value > max)
            {
                throw out_of_range("Ошибка: Число должно быть от " + to_string(min) + " до " + to_string(max));
            }

            if (value < INT_MIN || value > INT_MAX)
            {
                throw InputException("Ошибка: Введено число за пределами допустимого диапазона.");
            }

            return static_cast<int>(value);
        }
        catch (const exception& e)
        {
            cerr << e.what() << endl;
        }
    }
}

int checkingForInput::getBallColor(int ballNumber)  // Статический метод для получения цвета шарика (0-9)
{
    while (true)
    {
        cout << "Шарик " << ballNumber << ": ";
        string input;
        getline(cin, input);

        try
        {
            if (input.empty())
            {
                throw InputException("Ошибка: Пустой ввод. Пожалуйста, введите цвет шарика.");
            }

            for (char c : input)
            {
                if (!isdigit(c))
                {
                    throw InputException("Ошибка: Цвет шарика должен быть числом от 0 до 9.");
                }
            }

            int color = stoi(input); // Преобразуем строку в число

            if (color < 0 || color > 9)
            {
                throw out_of_range("Ошибка: Цвет шарика должен быть от 0 до 9.");
            }

            return color;
        }
        catch (const exception& e)
        {
            cerr << e.what() << endl;
        }
    }
}

BallRow::BallRow(const list<int>& input) : balls(input) {}

int BallRow::findAndRemoveRow() // Ищем ряд из 3 и более шаров и удаляем
{
    int totalRemoved = 0; // Счетчик 
    bool changed; // Флаг, были ли изменения

    do
    {
        changed = false;
        auto i = balls.begin();

        while (i != balls.end())
        {
            auto current = i;
            int currentValue = *current;
            auto next = current;
            ++next;
            int count = 1;

            // Подсчитываем количество подряд идущих одинаковых шариков
            while (next != balls.end() && *next == currentValue)
            {
                ++next;
                ++count;
            }

            if (count >= 3)
            {
                // Удаляем последовательность через итераторы
                i = balls.erase(current, next);
                totalRemoved += count;
                changed = true;
                // После удаления нужно проверить снова с начала
                break;
            }
            else
            {
                i = next;
            }
        }
    } while (changed);

    return totalRemoved;
}