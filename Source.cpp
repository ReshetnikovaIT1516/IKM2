#include "Header.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <cctype>
#include <sstream>
#include <climits>
#include <windows.h> 

InputException::InputException(const string& msg) : message(msg) {} // Конструктор, принимающий сообщение об ошибке

const char* InputException::what() const noexcept // Переопределение метода what() 
// noexcept гарантирует, что метод what() не выбросит исключение
// override позволяет компилятору проверить, что мы действительно переопределяем метод
{
    return message.c_str(); // Возвращаем сообщение об ошибке
}

// Реализация checkingForInput
int checkingForInput::getInteger(const string& prompt, int min, int max)
{
    while (true)
    {
        cout << prompt; // Выводим приглашение
        string input;
        getline(cin, input); // Читаем ввод

        try
        {
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

            if (input.size() > 1 && input[0] == '0')
            {
                throw InputException("Ошибка: Число не может начинаться с нуля.");
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

int checkingForInput::getBallColor(int ballNumber)
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
            if (input.size() > 1 && input[0] == '0')
            {
                throw InputException("Ошибка: Число не может начинаться с нуля.");
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

// Реализация LinkedList
LinkedList::LinkedList() : head(nullptr), tail(nullptr) {} // Конструктор

LinkedList::~LinkedList() // Деструктор
{
    Node* current = head;
    while (current) // Удаляем все узлы
    {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

void LinkedList::push_back(int value) // Добавление в конец
{
    Node* newNode = new Node(value);
    if (!head) // Если список пуст
    {
        head = tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }
}

bool LinkedList::empty() const // Проверка на пустоту
{
    return head == nullptr;
}

Node* LinkedList::begin() const // Получение начала списка
{
    return head;
}

Node* LinkedList::end() const // Получение конца списка
{
    return nullptr; // Конец списка - nullptr
}

Node* LinkedList::erase(Node* first, Node* last) // Удаление диапазона
{
    if (!first || first == last) return last; // Если нечего удалять

    // Находим узел перед first
    Node* prev = nullptr;
    Node* current = head;
    while (current && current != first)
    {
        prev = current;
        current = current->next;
    }

    // Удаляем узлы от first до last
    Node* temp = first;
    while (temp != last)
    {
        Node* next = temp->next;
        delete temp;
        temp = next;
    }

    // Обновляем связи
    if (prev)
    {
        prev->next = last;
    }
    else
    {
        head = last; // Удаляем с начала
    }

    if (!last)
    {
        tail = prev; // Если удалили до конца
    }

    return last;
}

// Реализация BallRow
BallRow::BallRow(const LinkedList& input) // Конструктор
{
    Node* current = input.begin();
    while (current) // Копируем все элементы
    {
        balls.push_back(current->value);
        current = current->next;
    }
}

int BallRow::findAndRemoveRow() // Поиск и удаление последовательностей
{
    int totalRemoved = 0; // Счетчик удаленных шариков
    bool changed; // Флаг изменений

    do
    {
        changed = false;
        Node* i = balls.begin();

        while (i != balls.end())
        {
            Node* current = i;
            int currentValue = current->value;
            Node* next = current->next;
            int count = 1;

            // Считаем подряд идущие шарики
            while (next && next->value == currentValue)
            {
                next = next->next;
                count++;
            }

            if (count >= 3) // Если нашли последовательность
            {
                i = balls.erase(current, next);
                totalRemoved += count;
                changed = true;
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