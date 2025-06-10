#include <iostream>
#include <list>
#include <stdexcept>
#include <string>
#include <cctype>
#include <sstream>
#include <climits>
#include <windows.h> 

using namespace std;

class InputException : public exception // Для создания пользовательских исключений, связанных с обработкой ввода данных

{
public:
    InputException(const string& msg); // Конструктор, принимающий сообщение об ошибке
    const char* what() const noexcept override;
private:
    string message;
};
class checkingForInput // Класс для проверки и обработки пользовательского ввода
{
public:
    static int getInteger(const string& prompt, int min, int max); // Статический метод для получения целого числа в нужном нам диапазоне
    static int getBallColor(int ballNumber);  // Статический метод для получения цвета шарика (0-9)
};
class BallRow  // Класс для работы с рядом шариков
{
public:
    BallRow(const list<int>& input);
    int findAndRemoveRow(); // Ищем ряд из 3 и более шаров и удаляем
private:
    list<int> balls;
};