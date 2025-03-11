#include"list.h"
void test01() {
	wz::list<int> l1;
	l1.push_back(1);
	l1.push_back(1);
	l1.push_back(1);
	l1.push_back(1);
	l1.push_back(1);
	l1.push_back(1);
	for (auto e : l1) {
		cout << e << ' ';
	}
	cout << endl;
}


int main() {
	test01();
	return 0;
}