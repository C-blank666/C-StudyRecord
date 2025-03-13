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
//法一
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
                tmp.erase(0, 1);
                left++;
            }
        }
        return ret;
    }
};
//法二
class Solution4 {
public:
    string minWindow(string s, string t) {
        int hash1[128] = { 0 };
        int hash2[128] = { 0 };
        int kinds = 0;
        for (auto ch : t)
            if (hash1[ch]++ == 0)
                kinds++;
        int minlen = s.size() + 1, begin = -1;
        for (int left = 0, right = 0, count = 0; right < s.size(); right++) {
            char in = s[right];
            if (++hash2[in] == hash1[in])
                count++;
            while (count == kinds) {
                if (right - left + 1 < minlen) {
                    minlen = right - left + 1;
                    begin = left;
                }
                char out = s[left++];
                if (hash2[out]-- == hash1[out]) count--;
            }
        }
        if (begin == -1) return "";
        else {
            return s.substr(begin, minlen);
        }
    }
};


//二分查找
class Solution5 {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        int mid = (left + right) / 2;
        while (left <= right) {
            if (target > nums[mid])
                left = mid + 1;
            else if (target < nums[mid])
                right = mid - 1;
            else
                return mid;
            mid = (left + right) / 2;
        }
        return -1;
    }
};


//在排序数组中查找元素的第一个和最后一个位置（二分查找）
class Solution6 {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        if (nums.size() == 0)
            return { -1, -1 };
        int left = 0;
        int right = nums.size() - 1;
        vector<int> ret;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (target > nums[mid]) {
                left = mid + 1;
            }
            else if (target <= nums[mid]) {
                right = mid;
            }
        }
        if (nums[left] == target)
            ret.push_back(left);
        else
            return { -1, -1 };
        left = 0;
        right = nums.size() - 1;
        while (left < right) {
            int mid = left + (right - left + 1) / 2;
            if (target >= nums[mid]) {
                left = mid;
            }
            else if (target < nums[mid]) {
                right = mid - 1;
            }
        }
        if (nums[left] == target)
            ret.push_back(left);
        else
            return { -1, -1 };
        return ret;
    }
};

//求x的平方根
class Solution7 {
public:
    int mySqrt(int x) {
        if (x < 1)
            return 0;
        int left = 1, right = x;
        while (left < right) {
            long long mid = left + (right - left + 1) / 2;
            if (mid * mid <= x) {
                left = mid;
            }
            else if (mid * mid > x) {
                right = mid - 1;
            }
        }
        return left;
    }
};
//搜索插入位置（二分查找）
class Solution8 {
public:
    int searchInsert(vector<int>& nums, int target) {
        if (target == 0) return 0;
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] >= target) {
                right = mid;
            }
            else if (nums[mid] < target) {
                left = mid + 1;
            }
        }
        return target > nums[nums.size() - 1] ? left + 1 : left;
    }
};
int main() {
    int x;
    int y = 16;

    cout << x << endl;
    return 0;
}