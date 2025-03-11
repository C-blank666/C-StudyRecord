#pragma once
#include<iostream>
#include<vector>
#include<list>
#include<deque>
namespace wz {
	template<class T, class Continer = deque<T>>
	class stack {
	public:
		void push(const T& val) {
			con.push_back(val);
		}
		void pop() {
			con.pop_back();
		}
		T& top() {
			return con.back();
		}
		size_t size()const {
			return con.size();
		}
		size_t capacity() const {
			return con.capacity();
		}
		bool empty()const {
			return con.empty();
		}
	private:
		Continer con;
	};
}