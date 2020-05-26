#pragma once

#include<iostream>
#include<algorithm>
#include<vector>


//using namespace std;
namespace datastructure {
namespace linklist {

template<class DataType>
class SingleNode
{
public:
	SingleNode() {};
	SingleNode(DataType x) : val_(x), next_(nullptr) {};
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
public:
	SingleLinkList();	
	SingleLinkList(DataType x, int n);	
	DataType GetElem(int n);	
	int FindElem(DataType value);	
	void TopInsert(DataType value);
	void BackInsert(DataType value);	
	DataType GetNthFromEnd(int n) const;	
	void RemoveNthFromEnd(int n);	
	void RemoveNthFromStart(int n);	
	void SortLink1();	
	void SortLink2();	
	SingleNode<DataType> * MergeSort(SingleNode<DataType> *SingleNode1);
	SingleNode<DataType> * Merge(SingleNode<DataType>* l1, SingleNode<DataType>* l2);
	void ReverseList();	
	bool GudgeEqual(SingleLinkList &a);
	int GetLen() const {
		return len_;
	}
	/*friend ostream &operator<<(ostream &output, const SingleLinkList &D) {
		if (D.len_ == 0)
		{
			std::cout << "SingleLinkList is empty" << std::endl;
			exit(1);
		}
		SingleNode<DataType> *p = D.head_->next_;
		for (int i = 1; i <= D.len_; i++)
		{
			output << p->val_ << ' ';
			p = p->next_;
		}
		std::cout << std::endl;
		return output;
	}*/
	~SingleLinkList();
};


template<class DataType>
SingleLinkList<DataType>::SingleLinkList()
{
	head_ = new SingleNode<DataType>;
	len_ = 0;
	head_->next_ = NULL;
}

template<class DataType>
SingleLinkList<DataType>::SingleLinkList(DataType x, int n)
{
	head_ = new SingleNode<DataType>;
	len_ = n;
	head_->next_ = NULL;
	SingleNode<DataType> *p = head_;
	for (int i = 0; i < n; i++)
	{
		p->next_ = new SingleNode<DataType>(x);
		p = p->next_;
	}
}

template<class DataType>
SingleLinkList<DataType>::~SingleLinkList()
{
	SingleNode<DataType> *p1 = head_, *p2;
	while (p1 != NULL)
	{
		p2 = p1->next_;
		delete p1;
		p1 = p2;
	}
}

template<class DataType>
DataType SingleLinkList<DataType>::GetElem(int n)
{
	if (n > len_ || n < 1)
	{
		std::cerr << "错误?"<<std::endl;
		return -1;
	}
	else
	{
		SingleNode<DataType> *p = head_;
		for (int i = 0; i < n; i++)
		{
			p = p->next_;
		}
		DataType value = p->val;
		return value;
	}
}

template<class DataType>
int SingleLinkList<DataType>::FindElem(DataType value)
{
	SingleNode<DataType> *p = head_->next_;
	int pos = 1;
	while (p)
	{
		if (p->val == value)
			return pos;
		else
		{
			p = p->next_;
			pos++;
		}
	}
	return -1;
}

template<class DataType>
void  SingleLinkList<DataType>::TopInsert(DataType value)
{
	SingleNode<DataType> *p = new SingleNode<DataType>(value);
	SingleNode<DataType> *k = head_->next_;
	head_->next_ = p;
	p->next_ = k;
	len_++;
}

template<class DataType>
void SingleLinkList<DataType>::BackInsert(DataType value)
{
	SingleNode<DataType> *p = head_;
	for (int i = 0; i < len_; i++)
	{
		p = p->next_;
	}
	p->next_ = new SingleNode<DataType>(value);
	len_++;
}

template<class DataType>
DataType SingleLinkList<DataType>::GetNthFromEnd(int n) const
{
	if (n > len_ || n < 0)
	{
		std::cerr << "错误?" << std::endl;
		return -1;
	}
	else if (n == len_)
		return head_->next_->val;
	else
	{
		SingleNode<DataType> *p = head_->next_;
		for (int i = 0; i < len_ - n; i++)
		{
			p = p->next_;
		}
		return p->val;
	}
}

template<class DataType>
void SingleLinkList<DataType>::RemoveNthFromEnd(int n)
{
	if (n > len_ || n < 0)
	{
		std::cerr << "错误?" << std::endl;
	}
	else
	{
		if (n == len_)
		{
			SingleNode<DataType> *p = head_->next_;
			head_->next_ = head_->next_->next_;
			delete p;
		}
		else if (n == 1)
		{
			SingleNode<DataType> *p = head_->next_;
			for (int i = 1; i < len_ - 1; i++)
			{
				p = p->next_;
			}
			SingleNode<DataType> *k = p->next_;
			p->next_ = NULL;
			delete k;
		}
		else
		{
			SingleNode<DataType> *p = head_;
			for (int i = 0; i < len_ - n; i++)
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
void SingleLinkList<DataType>::RemoveNthFromStart(int n)
{
	if (n<0 || n>len_)
		std::cerr << "错误?" << std::endl;
	else
	{
		if (n == 1)
		{
			SingleNode<DataType> *p = head_->next_;
			head_->next_ = head_->next_->next_;
			delete p;
		}
		else if (n == len_)
		{
			SingleNode<DataType> *p = head_->next_;
			for (int i = 1; i < len_ - 1; i++)
			{
				p = p->next_;
			}
			SingleNode<DataType> *k = p->next_;
			p->next_ = NULL;
			delete k;
		}
		else
		{
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
void SingleLinkList<DataType>::ReverseList()
{
	if (!(head_ == NULL || head_->next_ == NULL))
	{
		SingleNode<DataType> *p = head_->next_;
		SingleNode<DataType> *k = p->next_;
		head_->next_->next_ = NULL;
		head_->next_ = NULL;
		while (k)
		{
			SingleNode<DataType> *temp = k->next_;
			k->next_ = p;
			p = k;
			k = temp;
		}
		head_->next_ = p;
	}
}

template<class DataType>
void SingleLinkList<DataType>::SortLink1()
{
	std::vector<DataType> temp;
	SingleNode<DataType> *p = head_->next_;
	for (int i = 0; i < len_; i++)
	{
		temp.push_back(p->val);
		p = p->next_;
	}
	sort(temp.begin(), temp.end());
	p = head_->next_;
	for (int i = 0; i < len_; i++)
	{
		p->val = temp[i];
		p = p->next_;
	}
}

template<class DataType>
void SingleLinkList<DataType>::SortLink2()
{
	head_->next_ = mergesort(head_->next_);
}

template<class DataType>
SingleNode<DataType> * SingleLinkList<DataType>::MergeSort(SingleNode<DataType>*SingleNode1)
{
	if (!SingleNode1 || !SingleNode1->next_) return SingleNode1;
	SingleNode<DataType> *fast = SingleNode1;
	SingleNode<DataType> *slow = SingleNode1;
	SingleNode<DataType> *brek = SingleNode1;
	while (fast && fast->next_)
	{
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
SingleNode<DataType> * SingleLinkList<DataType>::Merge(SingleNode<DataType>* l1, SingleNode<DataType>* l2)
{
	if (l1 == NULL)
	{
		return l2;
	}
	if (l2 == NULL)
	{
		return l1;
	}
	if (l1->val < l2->val)
	{
		l1->next_ = merge(l1->next_, l2);
		return l1;
	}
	else
	{
		l2->next_ = merge(l2->next_, l1);
		return l2;
	}
}

template<class DataType>
bool SingleLinkList<DataType>::GudgeEqual(SingleLinkList &a)
{
	if (a.getlen() != len_)
		return false;
	else
	{
		SingleNode<DataType> *q = a.head_->next_;
		SingleNode<DataType> *k = head_->next_;
		for (int i = 0; i < len_; i++)
		{
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
