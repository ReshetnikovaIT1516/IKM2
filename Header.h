
#include <iostream>
#include <stdexcept>
#include <string>
#include <cctype>
#include <sstream>
#include <climits>
#include <windows.h> 

using namespace std;

class InputException : public exception {
public:
    InputException(const string& msg);
    const char* what() const noexcept override;
private:
    string message;
};

class checkingForInput {
public:
    static int getInteger(const string& prompt, int min, int max);
    static int getBallColor(int ballNumber);
};

struct Node {
    int value;
    Node* next;
    Node(int val) : value(val), next(nullptr) {}
};

class LinkedList {
public:
    LinkedList();
    ~LinkedList();
    void push_back(int value);
    bool empty() const;
    Node* begin() const;
    Node* end() const;
    Node* erase(Node* first, Node* last);
private:
    Node* head;
    Node* tail;
};

class BallRow {
public:
    BallRow(const LinkedList& input);
    int findAndRemoveRow();
private:
    LinkedList balls;
};