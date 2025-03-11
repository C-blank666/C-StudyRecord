#include"Date.h"
bool Date::operator==(const Date& d)const {
	return (_year == d._year && _month == d._month && _day == d._day);
}
bool Date::operator!=(const Date& d)const {
	return !(_year == d._year && _month == d._month && _day == d._day);
}
bool Date::operator<(const Date& d)const {
	if (_year < d._year)return true;
	else if (_year == d._year && _month < d._month) return true;
	else if (_year == d._year && _month == d._month && _day < d._day) return true;
	return false;
}
bool Date::operator<=(const Date& d)const {
	return *this < d || *this == d;
}
bool Date::operator>(const Date& d)const {
	return !(*this <= d);
}
bool Date::operator>=(const Date& d)const {
	return !(*this < d);
}
Date& Date::operator+=(const int& day) {
	_day += day;
	while (_day > GetMonthDay(_year,_month)) {
		_day -= GetMonthDay(_year, _month);
		++_month;
		if (_month == 13) ++_year, _month = 1;
	}
	return *this;
}
Date& Date::operator-=(const int& day) {
	_day -= day;
	while (_day <= 0) {
		--_month;
		if (_month == 0) --_year, _month = 12;
		_day += GetMonthDay(_year, _month);
	}
	return *this;
}
int Date::operator-(const Date& d)const {
	int n = 0;
	Date MaxD = *this;
	Date MinD = d;
	int flag = 1;
	if (*this < d) {
		MaxD = d;
		MinD = *this;
		flag = -1;
	}
	while (MinD != MaxD) {
		MinD++;
		n++;
	}
	return n*flag;
}
ostream& operator<<(ostream& out, const Date& d) {
	cout << d._year << "年" << d._month << "月" << d._day << "日" << endl;
	return out;
}
istream& operator>>(istream& in, Date& d) {
	cout << "请输入年月日>:" << endl;
	while (1) {
		cin >> d._year >> d._month >> d._day;
		if (!d.chackDate())
			cout << "日期错误重新输入" << endl;
		else
			break;
	}
	return in;
}

void test01() {
	Date d1;
	Date d2(2033, 1, 1);
	cout << (d1 == d2) << endl;
	cout << (d1 < d2) << endl;
	cout << (d1 <= d2) << endl;
	cout << (d1 > d2) << endl;
	cout << (d1 >= d2) << endl;
}
void test02() {
	Date d1;
	//d1 += 2000;
	Date d2(d1 + 2000);
	//d1.print();
	d2.print();
}
void test03() {
	Date d1;
	d1 -= 2000;
	d1.print();
	Date d2;
	cout << (d2 - d1) << endl;
	cout << (d1 - d2) << endl;
	cout << d1 << d2 << endl;
}
void test04() {
	Date d(22, 2222, 2);
	cin >> d;
	cout << d;
}



int main() {
	//test01();
	//test02();
	//test03();
	test04();
	return 0;
}