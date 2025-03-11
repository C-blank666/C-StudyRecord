#include<iostream>
#include<vector>
#include<deque>
#include<list>
namespace wz {
	template<class T, class Continer = deque<T>>
	class queue {
	public:
		void push(const T& val) {
			con.push_back(val);
		}
		void pop() {
			con.pop_front();
		}
		T& top() {
			return con.front();
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