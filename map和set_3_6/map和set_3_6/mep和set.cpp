#include<iostream>
#include<set>
#include<map>
using namespace std;
//set的使用

void test01() {
	set<int> s;
	s.insert(3);
	s.insert(2);
	s.insert(1);
	s.insert(4);
	s.insert(2);//不允许冗余
	auto it = s.begin();//支持迭代器
	while (it != s.end()) {
		cout << *it << " ";
		it++;
	}//默认是中序遍历，打印出的顺序由小到大，若想改变可以自己写仿函数传入
	cout << endl;
	s.erase(1);
	s.erase(2);
	s.erase(3);
	s.erase(4);
	s = { 1,2,3,4 };
	auto it1 = s.begin();
	while (it1 != s.end()) {
		cout << *it1 << " ";
		it1++;
	}
	cout << endl;
	s.insert({ 5,6,7,8 });
	for (const auto& e : s) {
		cout << e << ' ';
	}
}

void test02() {
	set<int> s;
	s = { 1,2,3,4,5,6,7,8,9,10 };
	for (const auto& e : s) {
		cout << e << ' ';
	}
	cout << endl;
	cout << s.erase(1) << endl;
	cout << s.erase(2) << endl;
	cout << s.erase(3) << endl;
	cout << s.erase(11) << endl;//erase如果删除成功，则返回删除元素的个数，删除失败返回0

	auto it = s.find(5);
	if (it == s.end()) cout << "find返回end()" << endl;//find()找到元素后返回该元素的迭代器，未找到则返回end()
	it++;
	cout << "*it:" << *it << endl;

}
void test03() {
	set<int> s;
	s = { 1,2,3,4,5,6,7,8,9,10 };
	auto first = s.lower_bound(3);
	auto last = s.upper_bound(6);
	s.erase(first, last);
	/*
	* 我们平时在向容器的函数传入迭代器区间时，由于左闭右开的规则，函数的作用区间都是左闭右开的
	* 所以要求我们在传入迭代器区间时也要按照左闭右开的规则传入，而lower_bound和upper_bound这两个函数
	* 则能帮助我们更加遍历的完成左闭右开的传入规则，
	* 即lower_bound返回一个不小于目标值的迭代器，upper_bound返回目标值的下一个值的一个迭代器
	*/
	for (const auto& e : s) {
		cout << e << ' ';
	}
	cout << endl;
}

void test04() {
	//multiset
	multiset<int> s;
	s.insert(1);
	s.insert(1);
	s.insert(1);
	s.insert(2);
	s.insert(2);
	s.insert(3);
	s.insert(4);
	s.insert(5);
	for (const auto& e : s) {
		cout << e << ' ';
	}//multiset允许多个相同的数据存在
	cout << endl;
	auto it = s.find(1);
	while (it != s.end() && *it == 1) {
		cout << *it << ' ';
		it++;
	}//multiset的find函数查找的是按中序遍历顺序的第一个，所以这里按照顺序去递增的找会找到所有的1
	cout << endl;
	cout << s.erase(1) << endl;;//multiset的erase会删除所有的值，并返回删除的个数
	for (const auto& e : s) {
		cout << e << ' ';
	}
	cout << endl;
}

//map的使用
void test05() {
	pair<string, string> p1 = { "你好","hello" };
	pair<string, string> p2 = { "再见","bye" };
	pair<string, string> p3 = { "飞","fly" };
	pair<string, string> p4 = { "国家","country" };
	map<string, string> m = { p1,p2,p3,p4 };//map的初始化，传入的第一个模板参数是键类型，传入后被const修饰
	//不能被改变，第二个传入的叫值类型，可以改变
	//两个值被写入pair类型，以此作为map类型的元素
	m.insert(make_pair("手", "hand"));//用make_pair插入,不需要模板参数，make_pair会自动识别
	m.insert(pair<string, string>("父母", "parent"));//用pair匿名对象插入，需要显式写出模板参数
	m.insert({ "儿子","son" });//直接隐式类型转换插入
	m.insert({ "儿子","son" });//insert的返回值是一个pair<iterator,bool>的类型，如果插入失败，
	//返回{已经存在pair对象的迭代器,false}成功{插入的pair对象的迭代器，true},不会报错。

	for (const auto& e : m) {//map支持迭代器
		cout << e.first << ":" << e.second << endl;
	}
	auto it = m.find("儿子");
	it->second = "Son";//值类可以被改，键类不行
	//it->first = "父亲";报错
	//find函数返回的是迭代器，如果找不到返回end()
	for (const auto& e : m) {
		cout << e.first << ":" << e.second << endl;
	}
	cout << m.erase("儿子") << endl;//如果传入键类，同样返回删除的个数，成功返回1，失败返回0
	map<string, string>::iterator ret = m.erase(m.begin());
	cout << ret->first << "翻译为" << ret->second << endl;//传入迭代器，则返回被删除迭代器的下一个迭代器
	for (const auto& e : m) {
		cout << e.first << ":" << e.second << endl;
	}
	//operator[]
	//这里的[]重载比较不一样，该重载函数有三个作用，找，改，插入
	cout << m["父母"] << endl;//它的返回值是pair对象的第二个成员second
	cout << m["儿子"] << endl;//这里什么也不会打印，因为儿子已经被删了，但“儿子”这一键类还是被初始化了
	cout << (m["儿子"] = "son") << endl;//修改
	cout << (m["女孩"] = "girl") << endl;//插入加修改
	//之所以能实现这种多样的功能，是因为operator[]复用了insert函数，具体等学到源码分析
}

int main() {
	/*test01();
	test02();
	test03();
	test04();*/
	test05();
	return 0;
}