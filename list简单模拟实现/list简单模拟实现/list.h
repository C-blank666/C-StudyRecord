#pragma once
#include<iostream>
using namespace std;
namespace wz {
	template<class T>
	struct list_node {
		T data;
		list_node<T>* _next;
		list_node<T>* _prev;
		list_node(const T& x = T())
			:data(x)
			, _next(nullptr)
			, _prev(nullptr)
		{}
	};
	template<class T>
	struct list_iterator 
	{
		typedef list_node<T> Node;
		typedef list_iterator<T> Self;
		Node* _node;

		list_iterator(Node* node)
			:_node(node)
		{}
		T& operator*() {
			return _node->data;
		}
		T* operator->() {
			return &_node->data;
		}
		Self& operator++() {
			_node = _node->next;
			return *this;
		}
		Self& operator--() {
			_node = _node->prev;
			return *this;
		}
		Self operator++(int) {
			Self tmp = *this;
			_node = _node->next;
			return tmp;
		}
		Self operator--(int) {
			Self tmp = *this;
			_node = _node->prev;
			return tmp;
		}
		bool operator!=(const Self& s) {
			return !(_node == s._node);
		}
	};
	template<class T>
	class list {
		typedef list_node<T> Node;
	public:
		typedef list_iterator<T> iterator;
		void init_empty() {
			_head = new Node();
			_head->_next = _head;
			_head->_prev = _head;
		}
		list() {
			init_empty();
		}
		iterator begin() {
			return iterator(_head->_next);
		}
		iterator end() {
			return iterator(_head);
		}
		void push_back(const T& val) {
			Node* newnode = new Node(val);
			Node* tail = _head->_prev;
			newnode->_prev = tail;
			newnode->_next = _head;
			_head->_prev = newnode;
			tail->_next = newnode;
		}
	private:
		Node* _head;
	};
}