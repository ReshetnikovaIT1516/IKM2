#include "Header.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <cctype>
#include <sstream>
#include <climits>
#include <windows.h> 

InputException::InputException(const string& msg) : message(msg) {} // �����������, ����������� ��������� �� ������

const char* InputException::what() const noexcept // ��������������� ������ what() 
// noexcept �����������, ��� ����� what() �� �������� ����������
// override ��������� ����������� ���������, ��� �� ������������� �������������� �����
{
    return message.c_str(); // ���������� ��������� �� ������
}

// ���������� checkingForInput
int checkingForInput::getInteger(const string& prompt, int min, int max)
{
    while (true)
    {
        cout << prompt; // ������� �����������
        string input;
        getline(cin, input); // ������ ����

        try
        {
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

            if (input.size() > 1 && input[0] == '0')
            {
                throw InputException("������: ����� �� ����� ���������� � ����.");
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

int checkingForInput::getBallColor(int ballNumber)
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
            if (input.size() > 1 && input[0] == '0')
            {
                throw InputException("������: ����� �� ����� ���������� � ����.");
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

// ���������� LinkedList
LinkedList::LinkedList() : head(nullptr), tail(nullptr) {} // �����������

LinkedList::~LinkedList() // ����������
{
    Node* current = head;
    while (current) // ������� ��� ����
    {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

void LinkedList::push_back(int value) // ���������� � �����
{
    Node* newNode = new Node(value);
    if (!head) // ���� ������ ����
    {
        head = tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }
}

bool LinkedList::empty() const // �������� �� �������
{
    return head == nullptr;
}

Node* LinkedList::begin() const // ��������� ������ ������
{
    return head;
}

Node* LinkedList::end() const // ��������� ����� ������
{
    return nullptr; // ����� ������ - nullptr
}

Node* LinkedList::erase(Node* first, Node* last) // �������� ���������
{
    if (!first || first == last) return last; // ���� ������ �������

    // ������� ���� ����� first
    Node* prev = nullptr;
    Node* current = head;
    while (current && current != first)
    {
        prev = current;
        current = current->next;
    }

    // ������� ���� �� first �� last
    Node* temp = first;
    while (temp != last)
    {
        Node* next = temp->next;
        delete temp;
        temp = next;
    }

    // ��������� �����
    if (prev)
    {
        prev->next = last;
    }
    else
    {
        head = last; // ������� � ������
    }

    if (!last)
    {
        tail = prev; // ���� ������� �� �����
    }

    return last;
}

// ���������� BallRow
BallRow::BallRow(const LinkedList& input) // �����������
{
    Node* current = input.begin();
    while (current) // �������� ��� ��������
    {
        balls.push_back(current->value);
        current = current->next;
    }
}

int BallRow::findAndRemoveRow() // ����� � �������� �������������������
{
    int totalRemoved = 0; // ������� ��������� �������
    bool changed; // ���� ���������

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

            // ������� ������ ������ ������
            while (next && next->value == currentValue)
            {
                next = next->next;
                count++;
            }

            if (count >= 3) // ���� ����� ������������������
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