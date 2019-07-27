#include <assert.h>
#include <vector>
#include <memory.h>
#include <iostream>

// Define class List
template<typename T>
class Node
{
public:
    Node(Node *pre, Node *next, const T& value) {
        value_ = value;
        pre_ = pre;
        next_ = next;
    }
    ~Node() {
        pre_ = nullptr;
        if(next_ != nullptr) {
	        next_->~Node<T>(); 
	        next_ = nullptr;
	    }
	    value_.~T();
    }
    Node<T> *GetPrePtr() { return pre_; }
    Node<T> *GetNextPtr() { return next_; }
    T GetValue() const { return value_; }
    void SetPrePtr(Node<T> * const ptr) { pre_ = ptr; }
    void SetNextPtr(Node<T> * const ptr) { next_ = ptr; }
    void SetValue(const T& value) { value_ = value; }
private:
    Node<T> *pre_ = nullptr;
    Node<T> *next_ = nullptr;
    T value_;
    
};

template<typename T>
class List
{
public:
    List() {}
    // ~List() {
    //     if(head_ != nullptr) {
    //         while((*head_).next_ != nullptr) {
    //             Node<T> *tmp_ptr = head_;
    //             head_ = (*head_).next_;
    //             ~(*tmp_ptr)();
    //         }
    //         ~(*head_)();
    //     }
    // }
    ~List() {
    	if(head_ != nullptr) {
    		head_->~Node<T>();
    	}
    }
    void PushFront(const T& value) {
	    Node<T> *tmp_ptr = new Node<T>(nullptr, head_, value);
	    if(head_ != nullptr) {
	    	head_->SetPrePtr(tmp_ptr);
	    }
	    head_ = tmp_ptr;
    }
    void PushBack(const T& value) {
    	if(head_ == nullptr) {
            head_ = new Node<T>(nullptr, nullptr, value);
        }
        else {
        	Node<T> *tmp_ptr = head_;
        	while(tmp_ptr->GetNextPtr() != nullptr) {
        		tmp_ptr = tmp_ptr->GetNextPtr();
        	}
        	Node<T> *new_node_ptr = new Node<T>(tmp_ptr, nullptr, value);
        	tmp_ptr->SetNextPtr(new_node_ptr);
        }
    }
    T PopFront() {
    	if(head_ == nullptr) {
    		std::cout << "head null" << std::endl;
    		exit(0);
    	}
    	else {
    		Node<T> *tmp_ptr = head_;
	    	head_ = head_->GetNextPtr();
	    	tmp_ptr->SetNextPtr(nullptr);
	    	const T value = tmp_ptr->GetValue();
	    	tmp_ptr->~Node<T>();
	    	return value;
	    }
    }
    T PopBack() const {
    	if(head_ == nullptr) {
    		std::cout << "head null" << std::endl;
    		exit(0);
    	}
    	else {
    		Node<T> *tmp_ptr = head_;
        	while(tmp_ptr->GetNextPtr() != nullptr) {
        		tmp_ptr = tmp_ptr->GetNextPtr();
        	}
        	(tmp_ptr->GetPrePtr())->SetNextPtr(nullptr);
        	const T value = tmp_ptr->GetValue();
        	tmp_ptr->~Node<T>();
        	return value;
    	}
    }
    int Size() {
    	int size = 0;
    	if(head_ != nullptr) {
    		++size;
    		Node<T> *tmp_ptr = head_;
	    	while(tmp_ptr->GetNextPtr() != nullptr) {
	    		tmp_ptr = tmp_ptr->GetNextPtr();
	    		++size;
	    	}
	    }
	    return size;
    }
    void Show() {
    	Node<T> *tmp_ptr = head_;
  		std::cout << "value: ";
    	while(tmp_ptr != nullptr) {
    		std::cout << tmp_ptr->GetValue() << ' '; 
    		tmp_ptr = tmp_ptr->GetNextPtr();
    	}
    	std::cout << std::endl;
    }
private:
    Node<T> *head_ = nullptr;
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
  std::cout << "list1.Size(): " << list1.Size() << std::endl;
  list1.Show();

  // Deeper test
  List<int> list2;
  list2.PushFront(9);
  std::cout << "list2.Size(): " << list2.Size() << std::endl;
  list2.PushBack(10);
  std::cout << "list2.Size(): " << list2.Size() << std::endl;
  assert(list2.Size() == 2);
  std::cout << "list2.Size() after Size(): " << list2.Size() << std::endl;
  list2.Show();
  assert(list2.PopBack() == 10);
  std::cout << "list2.Size() after PopBack(): " << list2.Size() << std::endl;
  list2.Show();
  assert(list2.PopFront() == 9);
  std::cout << "list2.Size() after PopFront(): " << list2.Size() << std::endl;
  list2.Show();
  assert(list2.Size() == 0);
}