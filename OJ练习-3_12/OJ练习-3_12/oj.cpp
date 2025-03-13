#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
//复习-找到字符串中所有的异位词
using namespace std;
class Solution1 {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> ret;
        int hash1[26] = { 0 };
        int hash2[26] = { 0 };
        int count = 0;
        for (auto e : p) {
            hash1[e - 'a']++;
        }
        for (int left = 0, right = 0; right < s.size(); right++) {
            int out = s[right] - 'a';
            if (++hash2[out] <= hash1[out])
                count++;
            if (right - left + 1 > p.size()) {
                int in = s[left++] - 'a';
                if (hash2[in]-- <= hash1[in])
                    count--;
            }
            if (count == p.size())
                ret.push_back(left);
        }
        return ret;
    }
};
//复习—串联所有单词的子串
class Solution2 {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> ret;
        int sigLen = words[0].size();
        int sumlen = words.size();
        unordered_map<string, int> hash1;
        for (auto& e : words) {
            hash1[e]++;
        }
        for (int i = 0; i < sigLen; i++) {
            unordered_map<string, int> hash2;
            int count = 0;
            for (int left = i, right = i; right + sigLen <= s.size();
                right += sigLen) {
                string out = s.substr(right, sigLen);
                hash2[out]++;
                if (hash1[out] && hash2[out] <= hash1[out])
                    count++;
                if (right - left + 1 > sigLen * sumlen) {
                    string in = s.substr(left, sigLen);
                    if (hash1[in] && hash2[in] <= hash1[in])
                        count--;
                    hash2[in]--;
                    left += sigLen;
                }
                if (count == sumlen)
                    ret.push_back(left);
            }
        }
        return ret;
    }
};
//覆盖最小字串
class Solution3 {
public:
    string minWindow(string s, string t) {
        int hash1[126] = { 0 };
        int hash2[126] = { 0 };
        for (auto& e : t) {
            hash1[e - 'A']++;
        }
        int len = s.size() + 1;
        string ret;
        string tmp;
        int count = 0;
        for (int left = 0, right = 0; right < s.size(); right++) {
            int out = s[right] - 'A';
            hash2[out]++;
            if (hash2[out] <= hash1[out])
                count++;
            tmp.push_back(s[right]);
            while (count == t.size()) {
                if (len > right - left + 1) {
                    len = right - left + 1;
                    ret = tmp;
                }
                int in = s[left] - 'A';
                if (hash2[in] <= hash1[in])
                    count--;
                hash2[in]--;
                tmp.erase(0,1);
                left++;
            }
        }
        return ret;
    }
};
int main() {
    Solution3 s3;
    string s = "dabc";
    string t = "abc";
    s3.minWindow(s, t);
    return 0;
}