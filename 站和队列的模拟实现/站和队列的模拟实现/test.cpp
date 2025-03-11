#include"stack.h"
#include"queue.h"
using namespace std;
void test01() {
	wz::stack<int, vector<int>> s1;
	s1.push(1);
	s1.push(2);
	s1.push(3);
	s1.push(4);
	for (size_t i = 0; i < 4; i++)
	{
		cout << s1.top() << endl;
		s1.pop();
	}

}
void test02() {
	wz::stack<int, list<int>> s1;
	s1.push(1);
	s1.push(2);
	s1.push(3);
	s1.push(4);
	for (size_t i = 0; i < 4; i++)
	{
		cout << s1.top() << endl;
		s1.pop();
	}
}
void test03() {
	wz::queue<int> q1;
	q1.push(1);
	q1.push(2);
	q1.push(3);
	q1.push(4);
	for (size_t i = 0; i < 4; i++)
	{
		cout << q1.top() << endl;
		q1.pop();
	}
}
int main() {
	test01();
	test02();
	test03();
	return 0;
}