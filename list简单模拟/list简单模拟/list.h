#pragma once
#include<iostream>
using namespace std;
namespace wz {
	template<class T>
	struct list_node {
		T _data;
		list_node<T>* _next;
		list_node<T>* _prev;
		list_node(const T& data = T())
			:_data(data)
			, _next(nullptr)
			, _prev(nullptr)
		{}
	};
	template<class T>
	class list_iterator {
		typedef list_node<T> Node;
		typedef list_iterator<T> self;
		Node* _node;
		list_iterator(Node* node)
			:_node(node)
		{}
		T& operator*() {
			return _node->_data;
		}
		T* operator->() {
			return &_node->_data;
		}
		self& operator++() {
			_node = _node->_next;
			return *this;
		}
		self& operator--() {
			_node = _node->_prev;
			return *this;
		}
		self operator++(int) {
			self tmp(*this);
			_node = _node->_next;
			return tmp;
		}
		self operator--(int) {
			self tmp(*this);
			_node = _node->_prev;
			return tmp;
		}
		bool operator!=(const self& s) {
			return _node != s.node;
		}
	};
	template<class T>
	class list {
		typedef list_node<T> Node;
	public:
		typedef list_iterator<T> iterator;
		void empty_init() {
			_head = new Node();
			_head->_next = _head;
			_head->_prev = _head;
		}
		list() {
			empty_init();
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