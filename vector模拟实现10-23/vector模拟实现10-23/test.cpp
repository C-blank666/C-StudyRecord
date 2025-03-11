#include"vector.h"
void test01() {
	wz::vector<int> v1 = { 1,2,3,4,5 };
	v1.push_back(1);
	v1.push_back(1);
	v1.push_back(1);
	v1.push_back(1);
	v1.push_back(1);
	v1.push_back(1);
	for (auto& e : v1) {
		cout << e << ' ';
	}
	cout << endl;
}
void test02() {
	wz::vector<int> v1 = { 1,2,3,4,5 };
	wz::vector<int> v2(v1);
	for (auto& e : v2) {
		cout << e << ' ';
	}
	cout << endl;
}
void test03() {
	wz::vector<int> v1 = { 1,2,3,4,5 };
	wz::vector<int> v2 = { 1,2,3 };
	v2 = v1;
	for (auto& e : v2) {
		cout << e << ' ';
	}
	cout << endl;
}
void test04() {
	wz::vector<int> v1 = { 1,2,3,4,5 };
	v1.erase(v1.begin());
	for (auto& e : v1) {
		cout << e << ' ';
	}
	cout << endl;
}
int main() {
	//test01();
	//test02();
	//test03();
	test04();
	return 0;
}