#include <vector>
#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
using namespace std;
// FIFO
template<typename T>
class MyQueue
{
public:
	MyQueue(int _n) { 
		size_t n = std::max(1, _n);
		q_.resize(n);
		head_ = q_.begin();
		tail_ = head_;
		length_ = 0;
		flag_ = 0;
	}
	~MyQueue() {}

	vector<T>& GetQueue() const { return q_; }
	size_t GetHead() const { return (head_-q_.begin()); }
	size_t GetTail() const { return (tail_-q_.begin()); }
	size_t GetLength() const { return length_; }

	T operator[] (auto&& in) // rvalue reference
  {
      in = in < 0 ? 0 : in;
      in = in > q_.size() ? q_.size() : in;
      size_t n = static_cast<size_t>(in);
      return *(q_.begin()+n);
  }

	void EnQueue(const T x);
	T DeQueue();

private:
	vector<T> q_;
	typename vector<T>::iterator head_;
	typename vector<T>::iterator tail_;
	size_t length_ = 0;
	bool flag_ = 0;
};

template<typename T>
void MyQueue<T>::EnQueue(const T x) {
	if(head_ == tail_ && flag_ == 1) {
		cout << "ERROR, no more spaces!!!" << endl;
	}
	else {
		if(head_ == tail_) {
			flag_ = 1;
		}
		*tail_ = x;
		if(tail_ == q_.end()-1) {
			tail_ = q_.begin();
		}
		else {
			++tail_;
		}
		++length_;
	}
}

template<typename T>
T MyQueue<T>::DeQueue() {
	if(length_ == 0) {
		cout << "ERROR, no element inside!!!" << endl;
	}
	else {
		T x = *head_;
		if(head_ == q_.end()-1) {
			head_ = q_.begin();
		}
		else {
			++head_;
		}
		--length_;
		return x;
	}
}

int main(int argc, char* argv[])
{

	int n = 10;
	MyQueue<int> my_queue(n);
	for(int i = 0; i < n+1; ++i) {
		my_queue.EnQueue(i+2);
	}
	cout << "dequeue: " << my_queue.DeQueue() << endl;
	cout << "queue length: " << my_queue.GetLength() << endl;
	cout << "queue head: " << my_queue.GetHead() << " value: " << my_queue[my_queue.GetHead()] << endl;
	cout << "queue tail: " << my_queue.GetTail() << " value: " << my_queue[my_queue.GetTail()] << endl;

  return 0;
}