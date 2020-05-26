#pragma once

#include<iostream>
#include<algorithm>
#include<vector>

/*————————————————
版权声明：本文为CSDN博主「陈乐乐happy」的原创文章，遵循 CC 4.0 BY - SA 版权协议，转载请附上原文出处链接及本声明。
原文链接：https ://blog.csdn.net/weixin_39139505/article/details/90295704*/

namespace datastructure {
namespace linklist {

template<class DataType>
class SingleNode
{
public:
	SingleNode() :next_(nullptr) {};
	SingleNode(DataType& x) : val_(x), next_(nullptr) {};
	SingleNode(DataType& x, SingleNode<DataType> * next) :val_(x), next_(next) {};
public:
	DataType val_;
	SingleNode<DataType> * next_;
};

template<class DataType>
class SingleLinkList
{
private:
	int len_;
	SingleNode<DataType> *head_;
	SingleNode<DataType> *tail_;
public:
	SingleLinkList();
	SingleLinkList(DataType x, int n);
	SingleLinkList(const SingleLinkList<DataType>& list);
	SingleLinkList<DataType>& operator=(const SingleLinkList<DataType>& list);
	DataType GetElem(int n) const;
	SingleNode<DataType>* Front() const;
	SingleNode<DataType>* Back() const;
	DataType FrontValue() const;
	DataType BackValue() const;
	int FindElem(DataType value);
	void TopInsert(DataType value);
	void BackInsert(DataType value);
	void SelectInsert(DataType value);
	void Insert(SingleNode<DataType>* node, DataType value);
	void Clear();
	DataType GetNthFromEnd(int n) const;
	void RemoveNthFromEnd(int n);
	void RemoveNthFromStart(int n);
	SingleNode<DataType>* Delete(SingleNode<DataType>* node);
	void SortLink1();
	void SortLink2();
	SingleNode<DataType> * MergeSort(SingleNode<DataType> *SingleNode1);
	SingleNode<DataType> * Merge(SingleNode<DataType>* l1, SingleNode<DataType>* l2);
	void ReverseList();
	bool GudgeEqual(const SingleLinkList<DataType> &a);
	int GetLength() const;
	void Print() const;
	~SingleLinkList();

private:
	bool IndexIsValid(int index) const;
};

template<class DataType>
bool SingleLinkList<DataType>::IndexIsValid(int index) const {
	return index >= 0 && index < len_;
}

template<class DataType>
SingleLinkList<DataType>::SingleLinkList()
{
	head_ = new SingleNode<DataType>();
	tail_ = head_;
	len_ = 0;
}

template<class DataType>
SingleLinkList<DataType>::SingleLinkList(const SingleLinkList<DataType>& list) :SingleLinkList() {
	SingleNode<DataType>*  it = list.Front();
	while (it) {
		this->BackInsert(it->val_);
		it = it->next_;
	}
}

template<class DataType>
void SingleLinkList<DataType>::Clear() {
	SingleNode<DataType> *p1 = head_->next_, *p2;
	while (p1 != NULL) {
		p2 = p1->next_;
		delete p1;
		p1 = p2;
	}
}

template<class DataType>
SingleLinkList<DataType>& SingleLinkList<DataType>::operator=(const SingleLinkList<DataType>& list) {
	if (this != &list) {
		this->Clear();
		const SingleNode<DataType>* it = list.Front();
		while (it) {
			this->BackInsert(it->val_);
			it = it->next_;
		}
	}
	return *this;
}

template<class DataType>
int SingleLinkList<DataType>::GetLength() const {
	return len_;
}

template<class DataType>
void SingleLinkList<DataType>::Print() const {
	SingleNode<DataType> * it = this->head_->next_;
	while (it) {
		std::cout << it->val_ << " ";
		it = it->next_;
	}
	std::cout << std::endl;
}

template<class DataType>
SingleNode<DataType>* SingleLinkList<DataType>::Front() const {
	return head_->next_;
}

template<class DataType>
SingleNode<DataType>* SingleLinkList<DataType>::Back() const {
	return tail_;
}

template<class DataType>
DataType SingleLinkList<DataType>::FrontValue() const {
	return head_->next_->val_;
}

template<class DataType>
DataType SingleLinkList<DataType>::BackValue() const {
	return tail_->val_;
}
template<class DataType>
void SingleLinkList<DataType>::SelectInsert(DataType value) {
	SingleNode<DataType>* pre = head_;
	SingleNode<DataType>* cur = head_->next_;
	if (len_ == 0 || value <= head_->next_->val_) this->TopInsert(value);
	else if (value >= tail_->val_) this->BackInsert(value);
	else {
		while (cur->val_ < value) {
			pre = cur;
			cur = cur->next_;
		}
		this->Insert(pre, value);
	}
}

template<class DataType>
void SingleLinkList<DataType>::Insert(SingleNode<DataType>* node, DataType value) {
	SingleNode<DataType>* next = node->next_;
	node->next_ = new SingleNode<DataType>(value, next);
	len_++;
}

template<class DataType>
SingleLinkList<DataType>::SingleLinkList(DataType x, int n)
{
	head_ = new SingleNode<DataType>;
	len_ = n;
	head_->next_ = NULL;
	SingleNode<DataType> *p = head_;
	for (int i = 0; i < n; i++) {
		p->next_ = new SingleNode<DataType>(x);
		p = p->next_;
	}
}

template<class DataType>
SingleLinkList<DataType>::~SingleLinkList() {
	this->Clear();
	delete head_;
}

template<class DataType>
DataType SingleLinkList<DataType>::GetElem(int n)  const {
	if (!IndexIsValid(n)) {
		std::cerr << "索引值错误" << std::endl;
		return INT_MIN;
	}
	else {
		SingleNode<DataType> *p = head_;
		for (int i = 0; i < n; i++) {
			p = p->next_;
		}
		DataType value = p->val;
		return value;
	}
}

template<class DataType>
int SingleLinkList<DataType>::FindElem(DataType value) {
	SingleNode<DataType> *p = head_->next_;
	int pos = 1;
	while (p) {
		if (p->val == value)
			return pos;
		else {
			p = p->next_;
			pos++;
		}
	}
	return -1;
}

template<class DataType>
void  SingleLinkList<DataType>::TopInsert(DataType value) {
	SingleNode<DataType> *p = new SingleNode<DataType>(value);
	SingleNode<DataType> *k = head_->next_;
	head_->next_ = p;
	p->next_ = k;
	len_++;
	if (len_ == 1) tail_ = head_->next_;
}

template<class DataType>
void SingleLinkList<DataType>::BackInsert(DataType value) {
	tail_->next_ = new SingleNode<DataType>(value);
	tail_ = tail_->next_;
	len_++;
}

template<class DataType>
DataType SingleLinkList<DataType>::GetNthFromEnd(int n) const {
	if (!IndexIsValid(n)) {
		std::cerr << "索引值错误" << std::endl;
		return INT_MIN;
	}
	else if (n == len_)
		return head_->next_->val;
	else {
		SingleNode<DataType> *p = head_->next_;
		for (int i = 0; i < len_ - n; i++) {
			p = p->next_;
		}
		return p->val;
	}
}

template<class DataType>
void SingleLinkList<DataType>::RemoveNthFromEnd(int n) {
	if (!IndexIsValid(n)) {
		std::cerr << "索引值错误" << std::endl;
	}
	else {
		if (n == len_) {
			SingleNode<DataType> *p = head_->next_;
			head_->next_ = head_->next_->next_;
			delete p;
		}
		else if (n == 1) {
			SingleNode<DataType> *p = head_->next_;
			for (int i = 1; i < len_ - 1; i++) {
				p = p->next_;
			}
			SingleNode<DataType> *k = p->next_;
			p->next_ = NULL;
			delete k;
		}
		else {
			SingleNode<DataType> *p = head_;
			for (int i = 0; i < len_ - n; i++) {
				p = p->next_;
			}
			SingleNode<DataType> *k = p->next_;
			p->next_ = p->next_->next_;
			delete k;
		}
		len_--;
	}
}

template<class DataType>
void SingleLinkList<DataType>::RemoveNthFromStart(int n)
{
	if (!IndexIsValid(n))
		std::cerr << "索引值错误" << std::endl;
	else {
		if (n == 1) {
			SingleNode<DataType> *p = head_->next_;
			head_->next_ = head_->next_->next_;
			delete p;
		}
		else if (n == len_) {
			SingleNode<DataType> *p = head_->next_;
			for (int i = 1; i < len_ - 1; i++)
			{
				p = p->next_;
			}
			SingleNode<DataType> *k = p->next_;
			p->next_ = NULL;
			delete k;
		}
		else {
			SingleNode<DataType> *p = head_;
			for (int i = 0; i < n - 1; i++)
			{
				p = p->next_;
			}
			SingleNode<DataType> *k = p->next_;
			p->next_ = p->next_->next_;
			delete k;
		}
		len_--;
	}
}

template<class DataType>
SingleNode<DataType>* SingleLinkList<DataType>::Delete(SingleNode<DataType>* node) {
	SingleNode<DataType>* it = head_;
	while (it!=nullptr&&it->next_ != node) {
		it = it->next_;
	}
	it->next_ = node->next_;
	SingleNode<DataType>* next = node->next_;
	delete node;
	node = nullptr;
	return next;
}

template<class DataType>
void SingleLinkList<DataType>::ReverseList() {
	if (!(head_ == NULL || head_->next_ == NULL)) {
		SingleNode<DataType> *p = head_->next_;
		SingleNode<DataType> *k = p->next_;
		head_->next_->next_ = NULL;
		head_->next_ = NULL;
		while (k) {
			SingleNode<DataType> *temp = k->next_;
			k->next_ = p;
			p = k;
			k = temp;
		}
		head_->next_ = p;
	}
}

template<class DataType>
void SingleLinkList<DataType>::SortLink1() {
	std::vector<DataType> temp;
	SingleNode<DataType> *p = head_->next_;
	for (int i = 0; i < len_; i++) {
		temp.push_back(p->val);
		p = p->next_;
	}
	sort(temp.begin(), temp.end());
	p = head_->next_;
	for (int i = 0; i < len_; i++) {
		p->val = temp[i];
		p = p->next_;
	}
}

template<class DataType>
void SingleLinkList<DataType>::SortLink2() {
	head_->next_ = mergesort(head_->next_);
}

template<class DataType>
SingleNode<DataType> * SingleLinkList<DataType>::MergeSort(SingleNode<DataType>*SingleNode1) {
	if (!SingleNode1 || !SingleNode1->next_) return SingleNode1;
	SingleNode<DataType> *fast = SingleNode1;
	SingleNode<DataType> *slow = SingleNode1;
	SingleNode<DataType> *brek = SingleNode1;
	while (fast && fast->next_) {
		fast = fast->next_->next_;
		brek = slow;
		slow = slow->next_;
	}
	brek->next_ = nullptr;
	SingleNode<DataType> *l1 = mergesort(SingleNode1);
	SingleNode<DataType> *l2 = mergesort(slow);
	return merge(l1, l2);
}

template<class DataType>
SingleNode<DataType> * SingleLinkList<DataType>::Merge(SingleNode<DataType>* l1, SingleNode<DataType>* l2) {
	if (l1 == NULL) {
		return l2;
	}
	if (l2 == NULL) {
		return l1;
	}
	if (l1->val < l2->val) {
		l1->next_ = merge(l1->next_, l2);
		return l1;
	}
	else {
		l2->next_ = merge(l2->next_, l1);
		return l2;
	}
}

template<class DataType>
bool SingleLinkList<DataType>::GudgeEqual(const SingleLinkList<DataType> &a) {
	if (a.GetLength() != len_)
		return false;
	else {
		SingleNode<DataType> *q = a.head_->next_;
		SingleNode<DataType> *k = head_->next_;
		for (int i = 0; i < len_; i++) {
			if (q->val != k->val)
				return false;
			q = q->next_;
			k = k->next_;
		}
		return true;
	}
}

}	// namespace linklist
}	// namespace datastructure
