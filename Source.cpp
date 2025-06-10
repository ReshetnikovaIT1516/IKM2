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

InputException::InputException(const string& msg) : message(msg) {} // �����������, ����������� ��������� �� ������

const char* InputException::what() const noexcept // ��������������� ������ what() 
// noexcept �����������, ��� ����� what() �� �������� ����������
// override  ��������� ����������� ���������, ��� �� ������������� ��������������  �����
{
    return message.c_str();// ������ ����� ��������� �� ������
}

// ����������� ����� ��� ��������� ������ ����� � ������ ��� ���������
int checkingForInput::getInteger(const string& prompt, int min, int max)
{
    while (true)
    {
        cout << prompt; //Prompt ������ - �����������, ������� ������������ ��� ������� ����� �� ������������.
        string input;
        getline(cin, input);

        try {
            if (input.empty())
            {
                throw InputException("������: ������ ����. ����������, ������� �����.");
            }
            // �������� �� ������� ���������� �������� (����� ������ � ������)
            bool hasMinus = (input[0] == '-');
            for (size_t i = hasMinus ? 1 : 0; i < input.size(); ++i)
            {
                if (!isdigit(input[i]))
                {
                    throw InputException("������: ������� ������������ �������. ����������, ������� ����� �����.");
                }
            }

            if (input.length() > 10 || (hasMinus && input.length() > 11)) // �������� �� ������� ������� �����
            {
                throw InputException("������: ������� ������� ������� �����. ����������, ������� ����� ��������.");
            }

            long long value; // �������������� � ��������� ������������
            try
            {
                value = stoll(input);
            }
            catch (...) // ��� ��������� ������
            {
                throw InputException("������: ������������ �������� ������.");
            }

            if (value < min || value > max)
            {
                throw out_of_range("������: ����� ������ ���� �� " + to_string(min) + " �� " + to_string(max));
            }

            if (value < INT_MIN || value > INT_MAX)
            {
                throw InputException("������: ������� ����� �� ��������� ����������� ���������.");
            }

            return static_cast<int>(value);
        }
        catch (const exception& e)
        {
            cerr << e.what() << endl;
        }
    }
}

int checkingForInput::getBallColor(int ballNumber)  // ����������� ����� ��� ��������� ����� ������ (0-9)
{
    while (true)
    {
        cout << "����� " << ballNumber << ": ";
        string input;
        getline(cin, input);

        try
        {
            if (input.empty())
            {
                throw InputException("������: ������ ����. ����������, ������� ���� ������.");
            }

            for (char c : input)
            {
                if (!isdigit(c))
                {
                    throw InputException("������: ���� ������ ������ ���� ������ �� 0 �� 9.");
                }
            }

            int color = stoi(input); // ����������� ������ � �����

            if (color < 0 || color > 9)
            {
                throw out_of_range("������: ���� ������ ������ ���� �� 0 �� 9.");
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

int BallRow::findAndRemoveRow() // ���� ��� �� 3 � ����� ����� � �������
{
    int totalRemoved = 0; // ������� 
    bool changed; // ����, ���� �� ���������

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

            // ������������ ���������� ������ ������ ���������� �������
            while (next != balls.end() && *next == currentValue)
            {
                ++next;
                ++count;
            }

            if (count >= 3)
            {
                // ������� ������������������ ����� ���������
                i = balls.erase(current, next);
                totalRemoved += count;
                changed = true;
                // ����� �������� ����� ��������� ����� � ������
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