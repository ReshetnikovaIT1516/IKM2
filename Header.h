#include <iostream>
#include <stdexcept>
#include <string>
#include <cctype>
#include <sstream>
#include <climits>
#include <windows.h> 

using namespace std;

// Класс для пользовательских исключений ввода
class InputException : public exception
{
public:
    InputException(const string& msg); // Конструктор с сообщением об ошибке
    const char* what() const noexcept override; // Переопределение what()
private:
    string message; // Сообщение об ошибке
};

// Класс для проверки ввода
class checkingForInput
{
public:
    static int getInteger(const string& prompt, int min, int max); // Получение целого числа в диапазоне
    static int getBallColor(int ballNumber); // Получение цвета шарика (0-9)
};

// Узел для односвязного списка
struct Node 
{
    int value;    // Значение узла
    Node* next;   // Указатель на следующий узел
    Node(int val) : value(val), next(nullptr) {} // Конструктор
};

// Самописный односвязный список
class LinkedList
{
public:
    LinkedList();  // Конструктор
    ~LinkedList(); // Деструктор
    void push_back(int value); // Добавление в конец
    bool empty() const; // Проверка на пустоту
    Node* begin() const; // Получение начала списка
    Node* end() const;   // Получение конца списка
    Node* erase(Node* first, Node* last); // Удаление диапазона
private:
    Node* head; // Указатель на начало
    Node* tail; // Указатель на конец
};

// Класс для работы с цепочкой шариков
class BallRow 
{
public:
    BallRow(const LinkedList& input); // Конструктор с цепочкой шариков
    int findAndRemoveRow(); // Поиск и удаление последовательностей
private:
    LinkedList balls; // Цепочка шариков
};