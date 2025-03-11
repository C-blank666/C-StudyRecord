#include<assert.h>
#include<iostream>
using namespace std;
namespace wz {
	template<class T>
	struct list_node {
		T _data;
		list_node<T>* _next;
		list_node<T>* _prev;
		list_node(const T& x = T()) 
			:_data(x)
			,_next(nullptr)
			,_prev(nullptr)
		{}
	};
	template<class T,class Ref,class Ptr>
	struct list_iterator {
		typedef list_node<T> Node;
		typedef list_iterator<T, Ref, Ptr> Self;
		Node* _node;
		list_iterator(Node* node)
			:_node(node)
		{}
		Ref operator*() {
			return _node->_data;
		}
		Ptr operator->() {
			return &_node->_data;
		}
		Self& operator++() {
			_node = _node->_next;
			return *this;
		}
		Self& operator--() {
			_node = _node->_prev;
			return *this;
		}
		Self operator++(int) {
			Self tmp(*this);
			_node = _node->_next;
			return tmp;
		}
		Self operator--(int) {
			Self tmp(*this);
			_node = _node->_prev;
			return tmp;
		}
		bool operator==(const Self& s) {
			return _node == s._node;
		}
		bool operator!=(const Self& s) {
			return _node != s._node;
		}
	};
	template<class T> 
	class list {
		typedef list_node<T> Node;
	public:
		typedef list_iterator<T, T&, T*> iterator;
		typedef list_iterator<T, const T&, const T*> const_iterator;
		iterator begin() {
			return iterator(_head->_next);
		}
		iterator end() {
			return iterator(_head);
		}
		const_iterator begin()const {
			return iterator(_head->_next);
		}
		const_iterator end()const {
			return iterator(_head);
		}
		void init_empty() {
			_head = new Node();
			_head->_next = _head;
			_head->_prev = _head;
		}
		list() {
			init_empty();
		}
		list(const list<T>& lt) {
			init_empty();
			for (auto& e : lt){
				push_back(e);
			}
		}
		~list() {
			clear();
			delete _head;
			_head(nullptr);
		}
		list<T>& operator=(list<T> lt) {
			swap(lt);
			return *this;
		}
		void swap(list<T>& lt) {
			std::swap(_head, lt._head);
			std::swap(_size, lt._size);
		}
		void clear() {
			iterator it = begin();
			while (it != end()) {
				it = erase(it);
			}
		}
		void push_back(const T& x) {
			insert(end(), x);
		}
		iterator insert(iterator pos, const T& x) {
			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* newnode = new Node(x);

			newnode->_next = cur;
			newnode->_prev = prev;

			prev->_next = newnode;
			cur->_prev = newnode;

			++_size;
			return iterator(newnode);
		}
		iterator erase(iterator pos) {
			Node* del = pos._node;
			Node* next = del->_next;
			Node* prev = del->_prev;

			next->_prev = prev;
			prev->_next = next;

			delete del;
			del(nullptr);

			--_size;

			return iterator(next);
		}
	private:
		Node* _head;
		size_t _size;
	};
	template<class T>
	void swap(list<T> l1, list<T> l2) {
		l1.swap(l2);
	}
}
