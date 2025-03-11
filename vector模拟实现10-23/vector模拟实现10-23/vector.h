#pragma once
#include<iostream>
#include<assert.h>
using namespace std;
namespace wz {
	template<class T>
	class vector {
	public:
		using iterator = T*;
		using const_iterator = const T*;
		iterator begin() {
			return _start;
		}
		iterator end() {
			return _finish;
		}
		const_iterator begin()const {
			return _start;
		}
		const_iterator end()const {
			return _finish;
		}
		size_t size()const {
			return _finish - _start;
		}
		size_t capacity()const {
			return _endofstorage - _start;
		}
		vector() {}
		vector(initializer_list<T> li) {
			reserve(li.size());
			for (auto& e : li) {
				push_back(e);
			}
		}
		template<class InputIterator>
		vector(InputIterator first, InputIterator last) {
			while (first != last) {
				push_back(*first);
				++first;
			}
		}
		vector(size_t n, const T& val = T()) {
			reserve(n);
			for (size_t i = 0; i < n; i++)
			{
				push_back(val);
			}
		}
		vector(int n, const T& val = T()) {
			reserve(n);
			for (int i = 0; i < n; i++)
			{
				push_back(val);
			}
		}
		vector(const vector<T>& v) {
			reserve(v.size());
			for (auto& e : v) {
				push_back(e);
			}
		}
		~vector() {
			if (_start) {
				delete[] _start;
				_start = _finish = _endofstorage = nullptr;
			}
		}
		void clear() {
			_finish = _start;
		}
		vector& operator=(const vector<T>& v) {
			clear();
			reserve(v.size());
			for (auto& e : v) {
				push_back(e);
			}
			return *this;
		}
		T& operator[](size_t i) {
			return _start[i];
		}
		const T& operator[](size_t i)const {
			return _start[i];
		}
		void swap(vector<T>& v) {
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_endofstorage, v._endofstorage);
		}
		void push_back(const T& x) {
			if (_finish == _endofstorage) {
				reserve(capacity() == 0 ? 4 : capacity() * 2);
			}
			*_finish = x;
			++_finish;
		}
		void reserve(size_t n) {
			if (n > capacity()) {
				T* tmp = new T[n];
				size_t oldSize = size();
				if (_start) {
					int i = 0;
					for (size_t i = 0; i < oldSize; i++)
					{
						tmp[i] = _start[i];
					}
					delete[] _start;
				}
				_start = tmp;
				_finish = _start + oldSize;
				_endofstorage = _start + n;
			}
		}
		void rsize(size_t n, const T& val = T()) {
			if (n < size()) {
				_finish = _start + n;
			}
			if (n > size()) {
				reserve(n);
				while (_finish < n) {
					*_finish = val;
					_finish++;
				}
			}
		}
		bool empty()
		{
			return _start == _finish;
		}

		void pop_back()
		{
			assert(!empty());

			--_finish;
		}

		iterator insert(iterator pos, const T& val) {
			assert(pos >= _start && pos <= _finish);
			if (_finish == _endofstorage) {
				size_t len = pos - _start;
				reserve(capacity() == 0 ? 4 : capacity() * 2);
				pos = _start + len;
			}
			iterator tmp = _finish - 1;
			while (tmp >= pos) {
				*(tmp + 1) = *tmp;
				tmp--;
			}
			*pos = val;
			_finish++;
			return pos;
		}
		iterator erase(iterator pos) {
			assert(pos >= _start && pos < _finish);
			iterator tmp = pos;
			while (tmp < _finish) {
				*tmp = *(tmp + 1);
				tmp++;
			}
			_finish--;
			return pos;
		}
	private:
		iterator _start = nullptr;
		iterator _finish = nullptr;
		iterator _endofstorage = nullptr;
	};

}#pragma once
