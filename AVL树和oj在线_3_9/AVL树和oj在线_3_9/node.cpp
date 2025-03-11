#include<iostream>
#include<vector>
#include<map>
using namespace std;
class Solution1 {
public:
    bool issame(int* h1, int* h2) {
        for (int i = 0; i < 26; i++) {
            if (h1[i] != h2[i])
                return false;
        }
        return true;
    }

    vector<int> findAnagrams(string s, string p) {
        int hash1[26] = { 0 };
        int hash2[26] = { 0 };
        for (auto e : p) {
            hash1[e - 'a']++;
        }
        vector<int> ret;
        for (int left = 0, right = 0; right < s.size(); right++) {
            hash2[s[right] - 'a']++;
            if (right - left + 1 == p.size()) {
                if (issame(hash1, hash2))
                    ret.push_back(left);
                hash2[s[left] - 'a']--;
                left++;
            }
        }
        return ret;
    }
};//用哈希表解决问题
class Solution2 {
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
};//用map解决问题
class Solution3 {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> ret;
        int hash1[26] = { 0 };
        int hash2[26] = { 0 };
        for (auto e : p) {
            hash1[e - 'a']++;
        }
        int count = 0;
        for (int left = 0, right = 0; right < s.size(); right++) {
            if (++hash2[s[right] - 'a'] <= hash1[s[right] - 'a'])
                count++;
            if (right - left + 1 > p.size()) {
                char out = s[left++];
                if (hash2[out - 'a']-- <= hash1[out - 'a'])
                    count--;
            }
            if (count == p.size())
                ret.push_back(left);
        }
        return ret;
    }
};//用有效字母数来解决问题
//总的来说，都用了滑动窗口的思想