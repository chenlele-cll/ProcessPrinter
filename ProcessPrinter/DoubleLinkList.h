#pragma once

#include<iostream>
#include "ProcessInfo.h"

/*————————————————
版权声明：本文为CSDN博主「陈乐乐happy」的原创文章，遵循 CC 4.0 BY - SA 版权协议，转载请附上原文出处链接及本声明。
原文链接：https ://blog.csdn.net/weixin_39139505/article/details/90295704*/

namespace datastructure {
namespace linklist{

template<class DataType>
class DoubleNode {
public:
	DoubleNode() {}
	DoubleNode(DataType & val) :val_(val), next_(nullptr), prev_(nullptr) {}
	DoubleNode(DataType & val, DoubleNode<DataType> * next, DoubleNode<DataType> * prev) :val_(val), next_(next), prev_(prev) {}

public:
	DataType val_;
	DoubleNode<DataType> *next_;
	DoubleNode<DataType> *prev_;
};

template<class DataType>
class DoubleLinkList {
public:
	DoubleLinkList();
	DoubleLinkList(const DoubleLinkList<DataType> &list);
	DoubleLinkList<DataType>& operator=(const DoubleLinkList<DataType>& list);
	~DoubleLinkList();
	int GetLength() const;
	DataType GetValue(int index);
	DoubleNode<DataType>* Front() const;
	DoubleNode<DataType>* Back() const;
	DoubleNode<DataType>* GetHead() const;
	void HeadInsert(DataType val);
	void LastInsert(DataType val);
	void SelectInsert(DataType data);
	void Insert(DoubleNode<DataType>* pos, DataType data);
	bool Delete(int index);
	void PopBack();
	void PopFront();
	bool IsEmpty();
	void ForwardPrint();
	void ReversePrint();
	void ForwardChangeHead();
	void ReverseChangeHead();
	void Clear();

private:
	DoubleNode<DataType>* GetDoubleNode(int index) const;
	bool IndexIsValid(int index) const;
	void Swap(DataType& val1, DataType& val2);
private:
	int len_;
	DoubleNode<DataType> *head_;
};

template<class DataType>
DoubleLinkList<DataType>::DoubleLinkList() :len_(0) {
	head_ = new DoubleNode<DataType>();
	head_->next_ = head_;
	head_->prev_ = head_;
}

template<class DataType>
DoubleLinkList<DataType>::DoubleLinkList(const DoubleLinkList<DataType>& list) :DoubleLinkList() {
	DoubleNode<DataType>* it = list.GetHead()->next_;
	int len = list.GetLength();
	while (len) {
		this->LastInsert(it->val_);
		it = it->next_;
		len--;
	}
}

template<class DataType>
DoubleLinkList<DataType>& DoubleLinkList<DataType>::operator=(const DoubleLinkList<DataType>& list) {
	if (this != &list) {
		this->Clear();
		const DoubleNode<DataType> * it = list.GetHead()->next_;
		int len = list.GetLength();
		while (len) {
			this->HeadInsert(it->val_);
			it = it->next_;
			len--;
		}
	}
	return *this;
}

template<class DataType>
void DoubleLinkList<DataType>::Clear() {
	DoubleNode<DataType>* tmp;
	DoubleNode<DataType>* it = head_->next_;
	while (it != head_) {
		tmp = it;
		it = it->next_;
		delete tmp;
	}
	len_ = 0;
	head_->next_ = head_;
	head_->prev_ = head_;
	tmp = it = nullptr;
}

template<class DataType>
DoubleLinkList<DataType>::~DoubleLinkList() {
	this->Clear();
	delete head_;
	head_ = nullptr;
}

template<class DataType>
DoubleNode<DataType>* DoubleLinkList<DataType>::GetDoubleNode(int index) const{
	if (!IndexIsValid(index)) return nullptr;

	if (index <= len_ / 2) {
		auto it = head_->next_;
		while (index) {
			it = it->next_;
			index--;
		}
		return it;
	}
	else {
		auto it = head_->prev_;
		index = len_ - index - 1;
		while (index) {
			it = it->prev_;
			index--;
		}
		return it;
	}
}

template<class DataType>
int DoubleLinkList<DataType>::GetLength() const {
	return len_;
}

template<class DataType>
bool DoubleLinkList<DataType>::IsEmpty() {
	return len_ == 0;
}

template<class DataType>
void DoubleLinkList<DataType>::HeadInsert(DataType val) {
	DoubleNode<DataType>* node = new DoubleNode<DataType>(val, head_->next_, head_);
	head_->next_->prev_ = node;
	head_->next_ = node;
	len_++;
}

template<class DataType>
void DoubleLinkList<DataType>::LastInsert(DataType val) {
	DoubleNode<DataType> * node = new DoubleNode<DataType>(val, head_, head_->prev_);
	head_->prev_->next_ = node;
	head_->prev_ = node;
	len_++;
}

template<class DataType>
void DoubleLinkList<DataType>::SelectInsert(DataType val) {
	if (val <= head_->next_->val_) this->HeadInsert(val);
	else if (val >= head_->prev_->val_) this->LastInsert(val);
	else {
		DoubleNode<DataType>* it = head_->next_;
		while (val > it->val_) it = it->next_;
		Insert(it, val);
	}
}

template<class DataType>
void DoubleLinkList<DataType>::Insert(DoubleNode<DataType>* pos,DataType data) {
	DoubleNode<DataType> *node = new DoubleNode<DataType>(data,pos,pos->prev_);
	pos->prev_->next_ = node;
	pos->prev_ = node;
	len_++;
}

template<class DataType>
bool DoubleLinkList<DataType>::Delete(int index) {
	auto node = GetDoubleNode(index);
	if (node == nullptr) return false;
	node->next_->prev_ = node->prev_;
	node->prev_->next_ = node->next_;
	len_--;
	return true;
}

template<class DataType>
void DoubleLinkList<DataType>::ForwardPrint() {
	DoubleNode<DataType>* it = head_->next_;
	int len = len_;
	while (len) {
		std::cout << it->val_ << " ";
		it = it->next_;
		len--;
	}
	std::cout << std::endl;
}

template<class DataType>
void DoubleLinkList<DataType>::ReversePrint() {
	DoubleNode<DataType>* it = head_->prev_;
	int len = len_;
	while (len) {
		std::cout << it->val_ << " ";
		it = it->prev_;
		len--;
	}
	std::cout << std::endl;
}

template<class DataType>
void DoubleLinkList<DataType>::PopBack() {
	Delete(len_ - 1);
}

template<class DataType>
void DoubleLinkList<DataType>::PopFront() {
	Delete(0);
}

template<class DataType>
DoubleNode<DataType>* DoubleLinkList<DataType>::Front() const{
	return GetDoubleNode(0);
}

template<class DataType>
DoubleNode<DataType>* DoubleLinkList<DataType>::Back() const{
	return GetDoubleNode(len_ - 1);
}

template<class DataType>
DoubleNode<DataType>* DoubleLinkList<DataType>::GetHead() const{
	return head_;
}

template<class DataType>
bool DoubleLinkList<DataType>::IndexIsValid(int index) const{
	return index >= 0 && index < len_;
}

template<class DataType>
DataType DoubleLinkList<DataType>::GetValue(int index) {
	if (IndexIsValid(index)) {
		return GetDoubleNode(index)->val_;
	}
	return {};
}

template<class DataType>
void DoubleLinkList<DataType>::Swap(DataType& val1, DataType& val2) {
	DataType tmp = val1;
	val1 = val2;
	val2 = val1;
}

template<class DataType>
void DoubleLinkList<DataType>::ForwardChangeHead() {
	Swap(head_->val_, head_->next_->val_);
	head_ = head_->next_;
}

template<class DataType>
void DoubleLinkList<DataType>::ReverseChangeHead() {
	Swap(head_->val_, head_->prev_->val_);
	head_ = head_->prev_;
}

}	// namespace linklist
}	// namespace datastructure
