#pragma once
#include<iostream>
#include<assert.h>
using namespace std;
namespace wz {
	template<class T>
	struct list_node {
		T _data;
		list_node<T>* next;
		list_node<T>* prev;
		list_node(const T& data = T())
			:_data(data)
			,next(nullptr)
			,prev(nullptr)
		{}
	};
	template<class T, class Ref, class Ptr>
	struct list_iterator {
		typedef list_node<T> Node;
		typedef list_iterator<T, Ref, Ptr> self;
		Node* _node;
		list_iterator(Node* node)
			:_node(node)
		{}
		Ref operator*() {
			return _node->_data;
		}
		Ptr operator->() {
			return &(_node->_data);
		}
		self& operator++() {
			_node = _node->next;
			return *this;
		}
		self& operator--() {
			_node = _node->prev;
			return *this;
		}
		self operator--(int) {
			self tmp = *this;
			_node = _node->prev;
			return tmp;
		}
		self operator++(int) {
			self tmp = *this;
			_node = _node->next;
			return tmp;
		}
		bool operator!=(const self& s) {
			return !(_node == s._node);
		}
		bool operator==(const self& s) {
			return _node == s._node;
		}
	};
	template<class T>
	class list {
		typedef list_node<T> Node;
	public:
		typedef list_iterator<T,T&,T*> iterator;
		typedef list_iterator<T,const T&,const T*> const_iterator;
		void init_empty() {
			_head = new Node();
			_head->next = _head;
			_head->prev = _head;
		}
		list(){
			init_empty();
		}
		list(size_t n,const T& data) {
			init_empty();
			for (size_t i = 0; i < n; i++)
			{
				push_back(data);
			}
		}
		list(const list<T>& lt) {
			init_empty();
			for (auto& e : lt) {
				push_back(e);
			}
		}
		~list() {
			clear();
			delete _head;
			_head = nullptr;
		}
		void swap(list<T>& lt) {
			std::swap(lt._head, _head);
			std::swap(lt._size, _size);
		}
		void clear() {
			auto it = begin();
			while (it != end()) {
				it = erase(it);
			}
		}
		list<T>& operator=(list<T> lt) {
			swap(lt);
			return *this;
		}
		iterator begin() {
			return iterator(_head->next);
		}
		iterator end() {
			return iterator(_head);
		}
		const_iterator begin()const {
			return iterator(_head->next);
		}
		const_iterator end() const {
			return iterator(_head);
		}
		void push_back(const T& x) {
			Node* tail = _head->prev;
			Node* newnode = new Node(x);
			newnode->prev = tail;
			newnode->next = _head;
			_head->prev = newnode;
			tail->next = newnode;
		}
		void push_front(const T& x) {
			insert(begin(), x);
		}
		void pop_back() {
			erase(--end());
		}
		void pop_front() {
			erase(begin());
		}
		iterator insert(iterator pos, const T& x) {
			Node* cur = pos._node;
			Node* newnode = new Node(x);
			Node* prev = cur->prev;

			prev->next = newnode;
			newnode->prev = prev;

			newnode->next = cur;
			cur->prev = newnode;
			_size++;

			return iterator(newnode);
		}
		iterator erase(iterator pos) {
			assert(pos != end());
			Node* del = pos._node;
			Node* next = del->next;
			Node* prev = del->prev;

			next->prev = prev;
			prev->next = next;
			delete del;

			_size--;
			return iterator(next);
		}
	private:
		Node* _head;
		size_t _size;
	};
	template<class T>
	void swap(list<T>& lt1, list<T>& lt2) {
		lt1.swap(lt2);
	}
}
