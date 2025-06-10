#include <iostream>
#include <list>
#include <stdexcept>
#include <string>
#include <cctype>
#include <sstream>
#include <climits>
#include <windows.h> 

using namespace std;

class InputException : public exception // ��� �������� ���������������� ����������, ��������� � ���������� ����� ������

{
public:
    InputException(const string& msg); // �����������, ����������� ��������� �� ������
    const char* what() const noexcept override;
private:
    string message;
};
class checkingForInput // ����� ��� �������� � ��������� ����������������� �����
{
public:
    static int getInteger(const string& prompt, int min, int max); // ����������� ����� ��� ��������� ������ ����� � ������ ��� ���������
    static int getBallColor(int ballNumber);  // ����������� ����� ��� ��������� ����� ������ (0-9)
};
class BallRow  // ����� ��� ������ � ����� �������
{
public:
    BallRow(const list<int>& input);
    int findAndRemoveRow(); // ���� ��� �� 3 � ����� ����� � �������
private:
    list<int> balls;
};