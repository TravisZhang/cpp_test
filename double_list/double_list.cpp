#include <assert.h>
#include <vector>
#include <memory.h>
#include <iostream>

// Define class List
template<typename T>
struct Node
{
    Node(Node *pre, Node *next, const T& value) {
        value_ = value;
        pre_ = pre;
        next_ = next;
    }
    ~Node() {
        pre_ = nullptr;
        next_ = nullptr;
        ~value_();
    }
    
    Node *pre_ = nullptr;
    Node *next_ = nullptr;
    T value_ = new T;
    
};

template<typename T>
class List
{
public:
    List() {}
    ~List() {
        if(head != nullptr) {
            while((*head).next != nullptr) {
                Node *tmp_ptr = head;
                head = (*head).next;
                ~(*tmp_ptr)();
            }
            ~(*head)();
        }
    }
    void PushFront(const T& value) {
        if(head == nullptr) {
            head = new Node<T>(nullptr, nullptr, value);
        }
        else {
            
        }
    }
    PushBack();
    PopFront();
    PopBack();
    Size();
private:
    Node<T> *head = nullptr;
};
// Define class List private members and declare private Node

// Declare List::~List

// Declare List::PushFront()

// Declare List::PushBack()

// Declare List::PopFront()

// Declare List::PopBack()

// Declare List::Size()

// Design a doubly linked list to pass these tests
int main() {
  // Sanity test
  List<int> list1;
  list1.PushBack(9);
  assert(list1.Size() == 1);

  // Deeper test
  List<int> list2;
  list2.PushFront(9);
  list2.PushBack(10);
  assert(list2.Size() == 2);
  assert(list2.PopBack() == 10);
  assert(list2.PopFront() == 9);
  assert(list2.Size() == 0);
}