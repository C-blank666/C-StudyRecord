#include<iostream>
#include<vector>
#include<string>
#include<map>
#include <algorithm>  
#include<unordered_map>
using namespace std;
class solution {
public:
    int totalfruit(vector<int>& fruits) {
        unordered_map<int, int> m;
        int len = 0;
        for (int left = 0, right = 0; right < fruits.size(); right++) {
            m[fruits[right]]++;
            while (m.size() > 2) {
                m[fruits[left]]--;
                if (m[fruits[left]] == 0) {
                    m.erase(fruits[left]);
                }
                left++;
            }
            len = max(len, right - left + 1);
        }
        return len;
    }
};
//oj复习（滑动窗口）



 //definition for a node.

class node {
public:
    int val;
    node* next;
    node* random;

    node(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};


class solution {
public:
    node* copyrandomlist(node* head) {
        map<node*, node*> m;
        node* cur = head;
        node* copyhead = nullptr, * copytail = nullptr;
        while (cur) {
            if (copyhead == nullptr) {
                copytail = copyhead = new node(cur->val);
                m[cur] = copytail;
            }
            else {
                node* prev = copytail;
                copytail = new node(cur->val);
                prev->next = copytail;
                m[cur] = copytail;
            }
            cur = cur->next;
        }
        cur = head;
        while (cur) {
            if (cur->random == nullptr) {
                m[cur]->random = nullptr;
            }
            else {
                m[cur]->random = m[cur->random];
            }
            cur = cur->next;
        }
        return copyhead;
    }
};
//oj在线（用c++map解决随即链表的复制问题）

class solution {
public:
    struct comp {
        bool operator()(const pair<string, int>& x, const pair<string, int>& y) {
            return x.second > y.second;
        }
    };

    vector<string> topkfrequent(vector<string>& words, int k) {
        map<string, int> m;
        for (auto e : words) {
            m[e]++;
        }
        vector<pair<string, int>> v = { m.begin(),m.end() };
        stable_sort(v.begin(), v.end(), comp());
        vector<string> ret;
        for (int i = 0; i < k; i++) {
            ret.push_back(v[i].first);
        }
        return ret;
    }
};
//oj在线（求前k个高频单词—map应用）




class Solution {
public:
	bool samemap(const map<char, int>& m, const map<char, int>& n) {
		auto itm = m.begin();
		auto itn = n.begin();
		while (itm != m.end()) {
			if (itm->first != itn->first || itm->second != itn->second)
				return false;
			itm++;
			itn++;
		}
		return true;
	}
	vector<int> findAnagrams(string s, string p) {
		vector<int> ret;
		map<char, int> m;
		map<char, int> n;
		for (auto e : p) {
			m[e]++;
		}
		for (int left = 0, right = 0; right < s.size(); right++) {
			n[s[right]]++;
			if (right - left + 1 == p.size()) {
				if (samemap(m, n))
					ret.push_back(left);
				n[s[left]]--;
				if (n[s[left]] == 0)
					n.erase(s[left]);
				left++;
			}
		}
		return ret;
	}
};
int main() {
	Solution so;
	string s = "baa";
	string p = "aa";
	vector<int> ret = so.findAnagrams(s, p);
	for (auto e : ret) {
		cout << e << ' ';
	}
	return 0;
}