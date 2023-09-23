#pragma once

template <typename T>
class List
{
public:
	struct Node
	{
		T _data;
		Node* _prev;
		Node* _next;
	};

	class iterator
	{
		friend List;
	private:
		Node* _node;
	public:
		iterator(Node* node = nullptr)
		{
			_node = node;
		}

		iterator operator ++(int)
		{
			iterator tmp(this);

			_node = _node->_next;

			return tmp;
		}

		iterator& operator++()
		{
			_node = _node->_next;

			return *this;
		}

		iterator operator --(int)
		{
			iterator tmp(this);

			_node = _node->_prev;

			return tmp;
		}

		iterator& operator--()
		{
			_node = _node->_prev;

			return *this;
		}

		T& operator *()
		{
			return _node->_data;
		}
		bool operator ==(const iterator& other)
		{
			return _node == other._node;
		}
		bool operator !=(const iterator& other)
		{
			return _node != other._node;
		}
	};

public:
	List()
	{
		_head._prev = nullptr;
		_head._next = &_tail;
		_tail._prev = &_head;
		_tail._next = nullptr;
	};
	~List()
	{
		while (_size != 0)
		{
			pop_back();
		}
	};

	iterator begin()
	{
		return iterator(_head._next);
	}
	iterator end()
	{
		//Tail ��带 ����Ű��(�����Ͱ� ���� ��¥ ���� �� ���) ���ͷ����͸� ����
			//�Ǵ� ������ ������ �� �ִ� ���ͷ����͸� ����

		return iterator(&_tail);
	}

	void push_front(T data)
	{
		AddNode(&_head, data);
	}
	void push_back(T data)
	{
		AddNode(_tail._prev, data);
	}
	void pop_front()
	{
		RemoveNode(_head._next);
	}
	void pop_back()
	{
		RemoveNode(_tail._prev);
	}
	void clear()
	{
		while (_size != 0)
		{
			pop_back();
		}
	}
	int	size() { return _size; };
	bool empty() { return _size == 0; };



	iterator erase(iterator iter)
	{
		return iterator(RemoveNode(iter._node));
	}
	//- ���ͷ������� �� ��带 ����.
	//- �׸��� ���� ����� ���� ��带 ī��Ű�� ���ͷ����� ����

	void remove(T Data)
	{
		List<int>::iterator iter;
		for (iter = begin(); iter != end(); ++iter)
		{
			if (*iter == Data)
			{
				erase(iter);
				return;
			}
		}
	}

private:
	void AddNode(Node* node, T data)
	{
		Node* newNode = new Node;
		newNode->_data = data;

		Node* prevNode = node;
		Node* nextNode = node->_next;

		prevNode->_next = newNode;
		newNode->_prev = prevNode;

		nextNode->_prev = newNode;
		newNode->_next = nextNode;

		_size++;
	}

	Node* RemoveNode(Node* node)
	{
		if (_size == 0)
			return nullptr;

		Node* prevNode = node->_prev;
		Node* nextNode = node->_next;

		prevNode->_next = nextNode;
		nextNode->_prev = prevNode;

		delete node;

		_size--;
		return nextNode;
	}

private:
	int _size = 0;
	Node _head;
	Node _tail;
};
