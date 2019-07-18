#include <vector>
#include <iostream>
#include <memory.h>
using namespace std;

template<typename T>
class TNode
{
public:
		TNode() {}
		~TNode() {}

		void SetParent(const TNode<T> * const pin) { parent_ = pin; }
    void SetLeft(const TNode<T> * const pin) { left_ = pin; }
    void SetRight(const TNode<T> * const pin) { right_ = pin; }

    TNode<T>* GetParent() const { return parent_; }
    TNode<T>* GetLeft() const { return left_; }
    TNode<T>* GetRight() const { return right_; }

    T GetData() const { return data_; }

protected:
		T data_;
    TNode<T>* parent_ = NULL;
    TNode<T>* left_ = NULL;
    TNode<T>* right_ = NULL;
};

template<typename T>
class BiTree : protected TNode<T>
{
public:
  BiTree() {}
  ~BiTree() {}

  TNode<T>* TreeSearch(TNode<T>* x, T data_in);
  
};

template<typename T>
TNode<T>* BiTree<T>::TreeSearch(TNode<T>* x, T data_in) {
  if( x == NULL || data_in == x.GetData()) {
    return x;
  }
  if( data_in < x.GetData()) {
    return TreeSearch(x.GetLeft(), data_in);
  }
  else {
    return TreeSearch(x.GetRight(), data_in);
  }
}


int main(int argc, char* argv[])
{


		return 0;
}