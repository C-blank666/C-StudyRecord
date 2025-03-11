#include<iostream>
#include<string>
#include<map>
#include<unordered_map>
#include<vector>
#include<set>

//找到字符串中所有字母异位词(复习，两种方法)
using namespace std;
class Solution1 {
public:
    bool isSame(const int* h1, const int* h2) {
        for (int i = 0; i < 26; i++) {
            if (h1[i] != h2[i])
                return false;
        }
        return true;
    }

    vector<int> findAnagrams(string s, string p) {
        int hash1[26] = { 0 };
        int hash2[26] = { 0 };
        vector<int> ret;
        for (auto e : p) {
            hash1[e - 'a']++;
        }
        for (int left = 0, right = 0; right < s.size(); right++) {
            hash2[s[right] - 'a']++;
            if (right - left + 1 == p.size()) {
                if (isSame(hash1, hash2))
                    ret.push_back(left);
                hash2[s[left++] - 'a']--;
            }
        }
        return ret;
    }
};
class Solution2 {
public:
    vector<int> findAnagrams(string s, string p) {
        int count = 0;
        int hash1[26] = { 0 };
        int hash2[26] = { 0 };
        vector<int> ret;
        for (auto e : p) {
            hash1[e - 'a']++;
        }
        for (int left = 0, right = 0; right < s.size(); right++) {
            hash2[s[right] - 'a']++;
            if (hash2[s[right] - 'a'] <= hash1[s[right] - 'a'])
                count++;
            if (right - left + 1 > p.size()) {
                if (hash2[s[left] - 'a'] <= hash1[s[left] - 'a'])
                    count--;
                hash2[s[left] - 'a']--;
                left++;
            }
            if (count == p.size())
                ret.push_back(left);
        }
        return ret;
    }
};

//串联所有单词的子串
class Solution3 {
public:
    void window(const string& s, int left, int right, vector<int>& ret,
        unordered_map<string, int> hash1, const vector<string>& words) {
        unordered_map<string, int> hash2;
        int count = 0;
        int len = words[0].size();
        for (int _left = left, _right = right; _right + len <= s.size();
            _right += len) {
            string in = s.substr(_right, len);
            hash2[in]++;
            if (hash1.count(in) && hash2[in] <= hash1[in])
                count++;
            if (_right - _left + len > words.size() * len) {
                string out = s.substr(_left, len);
                if (hash1.count(out) && hash2[out] <= hash1[out])
                    count--;
                hash2[out]--;
                _left += len;
            }
            if (count == words.size()) {
                ret.push_back(_left);
            }
        }
    }

    vector<int> findSubstring(string s, vector<string>& words) {

        vector<int> ret;
        unordered_map<string, int> hash1;
        for (auto e : words) {
            hash1[e]++;
        }
        for (int left = 0, right = 0; right < words[0].size();
            right++, left++) {
            window(s, left, right, ret, hash1, words);
        }
        return ret;
    }
};
int main() {
    Solution3 s3;
    string s = "dddddddddddd";
    vector<string> words = { "dddd","dddd" };
    vector<int> ret = s3.findSubstring(s, words);
    for (auto e : ret) {
        cout << e << " ";
    }
    return 0;
}