#include <vector>
#include <iostream>
#include <memory>
using namespace std;

// the property of binary tree:
// if x is a node in binary tree and y is a child in x's left sub tree, then y.key <= x.key;
// if y is a child in x's right sub tree, then y.key >= x.key

template<typename T>
class TNode
{
public:
	TNode() {}
	~TNode() { data_ptr_->~T(); data_ptr_ = NULL; }

	void SetParent(const TNode<T> * const pin) { parent_ = pin; }
	void SetLeft(const TNode<T> * const pin) { left_ = pin; }
	void SetRight(const TNode<T> * const pin) { right_ = pin; }

	TNode<T>* GetParent() const { return parent_; }
	TNode<T>* GetLeft() const { return left_; }
	TNode<T>* GetRight() const { return right_; }

	T SetData(const T& data_in) { *data_ptr_ = data_in; }
	T GetData() const { return *data_ptr_; }

protected:
	T* data_ptr_;
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

	TNode<T>* TreeSearchRecur(TNode<T>* x, T data_in);
	TNode<T>* TreeSearchIter(TNode<T>* x, T data_in);
	void InorderTreeWalk(TNode<T>* x, std::vector<T>& result); // display all values in ascending order of a tree(sub tree)
	TNode<T>* GetTreeMin();
	TNode<T>* GetTreeMin(TNode<T>* x);
	TNode<T>* GetTreeMax();
	TNode<T>* GetTreeMax(TNode<T>* x);
	TNode<T>* GetSuccessor(TNode<T>* x); // get the node whose value is just bigger than x's
	TNode<T>* GetPredecessor(TNode<T>* x); // get the node whose value is just smaller than x's
	void TreeInsert(TNode<T>* x);
	void Transplant(TNode<T>* u, TNode<T>* v); // use sub tree v to replace sub tree u
	void TreeDelete(TNode<T>* x);

private:
	TNode<T>* root_;

};

template<typename T>
TNode<T>* BiTree<T>::TreeSearchRecur(TNode<T>* x, T data_in) {
	if (x == NULL || data_in == x->GetData()) {
		return x;
	}
	if (data_in < x->GetData()) {
		return TreeSearchRecur(x->GetLeft(), data_in);
	}
	else {
		return TreeSearchRecur(x->GetRight(), data_in);
	}
}

template<typename T>
TNode<T>* BiTree<T>::TreeSearchIter(TNode<T>* x, T data_in) { // x is usually a root node of a tree(or sub tree)
	while (x != NULL && x->GetData() != data_in) {
		if (data_in < x->GetData()) {
			x = x->GetLeft();
		}
		else {
			x = x->GetRight();
		}
	}
	return x;
}

template<typename T>
void BiTree<T>::InorderTreeWalk(TNode<T>* x, std::vector<T>& result) { // x is usually a root node of a tree(or sub tree)
	if (x != NULL) {
		InorderTreeWalk(x->GetLeft());
		result.push_back(x->GetData());
		InorderTreeWalk(x->GetRight());
	}
}

template<typename T>
TNode<T>* BiTree<T>::GetTreeMin() { // find min in whole tree
	TNode<T>* x = root_;
	while (x->GetLeft() != NULL) {
		x = x->GetLeft();
	}
	return x;
}

template<typename T>
TNode<T>* BiTree<T>::GetTreeMin(TNode<T>* x) { // find min in tree x
	while (x->GetLeft() != NULL) {
		x = x->GetLeft();
	}
	return x;
}


template<typename T>
TNode<T>* BiTree<T>::GetTreeMax() { // find max in whole tree
	TNode<T>* x = root_;
	while (x->GetRight() != NULL) {
		x = x->GetRight();
	}
	return x;
}

template<typename T>
TNode<T>* BiTree<T>::GetTreeMax(TNode<T>* x) { // find max in tree x
	while (x->GetRight() != NULL) {
		x = x->GetRight();
	}
	return x;
}

template<typename T>
TNode<T>* BiTree<T>::GetSuccessor(TNode<T>* x) { // find the node just bigger than x(in the whole tree)
	if (x->GetRight() != NULL) {
		return GetTreeMin(x->GetRight()); // if x has right sub tree, then result is the smallest node in it
	}
	else {
		TNode<T>* p = x->GetParent();
		while (p != NULL && x = p->GetRight()) {
			x = p;
			p = p->GetParent();
		}
		return p; // the first node with x(input) as its biggest node in its left tree
		// note: if p is input's suc, then input is p's pre
	}
}

template<typename T>
TNode<T>* BiTree<T>::GetPredecessor(TNode<T>* x) { // find node just smaller than x(in the whole tree)
	if (x->GetLeft() != NULL) {
		return GetTreeMax(x->GetLeft()); // if x has left sub tree, the result is the biggest one in it
	}
	else {
		TNode<T>* p = x->GetParent();
		while (p != NULL && x = p->GetLeft()) {
			x = p;
			p = p->GetParent();
		}
		return p; // the first node with x(input) as its smallest node in its right tree
		// note: if p is input's pre, then input is p's suc
	}
}

template<typename T>
void BiTree<T>::TreeInsert(TNode<T>* x) {
	TNode<T>* y = root_;
	if (y == NULL) {
		root_ = x; // empty tree
	}
	else {
		TNode<T>* z = y;
		while (z != NULL) {
			y = z; // we must keep track of the parent
			if (z->GetData() < x->GetData()) {
				z = z->GetRight();
			}
			else {
				z = z->GetLeft();
			}
		}
		if (x->GetData() < y->GetData()) {
			y->SetLeft() = x;
		}
		else {
			y->SetRight() = x;
		}
		x->SetParent(y);
	}
}

template<typename T>
void BiTree<T>::Transplant(TNode<T>* u, TNode<T>* v) {
	if (u->GetParent() == NULL) {
		root_ = v;
	}
	else {
		TNode<T>* p = u->GetParent();
		if (u == p->GetLeft()) {
			p->SetLeft(v);
		}
		else {
			p->SetRight(v);
		}
	}
	if (v != NULL) {
		v->SetParent(u->GetParent());
	}
}

template<typename T>
void BiTree<T>::TreeDelete(TNode<T>* x) {
	if (x->GetLeft() == NULL) {
		Transplant(x, x->GetRight());
	}
	else if (x->GetRight() == NULL) {
		Transplant(x, x->GetLeft());
	}
	else {
		// if there are two children of x, we must choose from the bigger side
		// the reason is we must make sure we can replace the new one's right sub tree with old right sub tree
		// and if choose from left side, it's not possible 
		// and y(the replace one) must has no left child (so that it's the smallest on right side)
		TNode<T>* y = GetSuccessor(x);
		if (y == x->GetRight()) {
			// y has no left child i.e. all y's child bigger than y
			Transplant(x, y);
			y->SetLeft(x->GetLeft());
			(y->GetLeft())->SetParent(y);
		}
		else {
			Transplant(y, y->GetRight()); // because y has no left child
			y->SetRight(x->GetRight());
			(y->GetRight())->SetParent(y);
			// below is the same as above
			Transplant(x, y);
			y->SetLeft(x->GetLeft());
			(y->GetLeft())->SetParent(y);
		}
	}
	x->~TNode();
}

int main(int argc, char* argv[])
{


	return 0;
}