#include<iostream>
#include<vector>
#include<map>
#include<unordered_map>
using namespace std;
//只出现一次的数字（位运算复习）
class Solution1 {
public:
	vector<int> singleNumber(vector<int>& nums) {
		int t = 0;
		for (auto x : nums) {
			t ^= x;
		}
		int tmp = (t == INT_MIN ? t : t & (-t));
		int type1 = 0, type2 = 0;
		for (auto x : nums) {
			if (x & tmp) {
				type1 ^= x;
			}
			else {
				type2 ^= x;
			}
		}
		return { type1,type2 };
	}
};
//汉明距离（位运算复习）
class Solution2 {
public:
	int hammingDistance(int x, int y) {
		int tmp = x ^ y;
		int Distance = 0;
		while (tmp) {
			if ((tmp & 1) == 1)
				Distance++;
			tmp >>= 1;
		}
		return Distance;
	}
};
//判断字符是否唯一（位运算）
class Solution3 {
public:
	bool isUnique(string astr) {
		if (astr.size() > 26) return false;
		int hash = 0;
		for (auto& x : astr) {
			if (((hash >> (x - 'a')) & 1) == 1)// target>>x & 1 这里判断的是第x位是否为1
				return false;
			hash |= (1 << (x - 'a')); // target |= (1 << x) 将第x位的数字修改为1
		}
		return true;
	}
};
//丢失的数字（位运算）
class Solution4 {
public:
	int missingNumber(vector<int>& nums) {
		int ret = 0;
		for (auto x : nums) {
			ret ^= x;
		}
		for (int i = 0; i <= nums.size(); i++) {
			ret ^= i;
		}//运用了^（异或）的运算律
		return ret;
	}
};
//两个整数相加（不利用+-符号）
class Solution5 {
public:
	int getSum(int a, int b) {
		while (1) {
			int result = a ^ b;
			unsigned int next = (unsigned int)(a & b) << 1;
			if (next == 0)
				return result;
			a = result;
			b = next;
		}
	}
};
//只出现一次的数字II
//这次的数组中除了答案数字外，其余数字均出现3次
/*
* 由于数组中的元素都在 int（即 32 位整数）范围内，因此我们可以依次计算答
案的每一个二进制位是 0 还是 1。
具体地，考虑答案的第 i 个二进制位（i 从 0 开始编号），它可能为 0 或 1。对
于数组中非答案的元素，每一个元素都出现了 3 次，对应着第 i 个二进制位的 3
个 0 或 3 个 1，无论是哪一种情况，它们的和都是 3 的倍数（即和为 0 或 3）。
因此：
答案的第 i 个二进制位就是数组中所有元素的第 i 个二进制位之和除以 3 的余数。
这样一来，对于数组中的每一个元素 x，我们使用位运算 (x >> i) & 1 得到 x 的
第 i 个二进制位，并将它们相加再对 3 取余，得到的结果一定为 0 或 1，即为答
案的第 i 个二进制位。
*/
class Solution6 {
public:
	int singleNumber(vector<int>& nums) {
		int ret = 0;
		for (int i = 0; i < 32; i++) {
			int sum = 0;
			for (auto& num : nums) {
				sum += (num & 1);
				num >>= 1;
			}
			ret |= ((sum % 3) << i);
		}
		return ret;
	}
};
//丢失的两个数字（时间复杂度o(n)空间复杂度o(1)）
class Solution7 {
public:
	vector<int> missingTwo(vector<int>& nums) {
		int des = 0;
		int n = nums.size();
		for (auto& x : nums) {
			des ^= x;
		}
		for (int i = 1; i <= n + 2; i++) {
			des ^= i;
		}
		int tmp = (des == INT_MIN ? des : (des & (-des)));
		int type1 = 0, type2 = 0;
		for (auto& x : nums) {
			if (x & tmp)
				type1 ^= x;

			else
				type2 ^= x;
		}
		for (int i = 1; i <= n + 2; i++) {
			if (i & tmp)
				type1 ^= i;

			else
				type2 ^= i;
		}
		return { type1,type2 };
	}
};
//连续数组（前缀和复习）
class Solution8 {
public:
	int findMaxLength(vector<int>& nums) {
		for (auto& x : nums) {
			if (x == 0)
				x = -1;
		}
		unordered_map<int, int> hash;
		int sum = 0, len = 0;
		hash[0] = -1;
		for (int i = 0; i < nums.size(); i++) {
			sum += nums[i];
			if (hash.count(sum))
				len = max(len, i - hash[sum]);
			else
				hash[sum] = i;
		}
		return len;
	}
};

//替换所有的问号（模拟）
class Solution9 {
public:
	string modifyString(string s) {
		int n = s.size();
		for (int i = 0; i < n; i++) {
			if (s[i] == '?') {
				for (char ch = 'a'; ch <= 'z'; ch++) {
					if ((i == 0 || ch != s[i - 1]) && (i == n - 1 || ch != s[i + 1])) {
						s[i] = ch;
						break;
					}
				}
			}
		}
		return s;
	}
};




class Solution {
public:
	struct ListNode {
		int val;
		ListNode* next;
		ListNode() : val(0), next(nullptr) {}
		ListNode(int x) : val(x), next(nullptr) {}
		ListNode(int x, ListNode* next) : val(x), next(next) {}
	};
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode* cur1 = l1;
		ListNode* cur2 = l2;
		ListNode* haedPrev = new ListNode;
		ListNode* cur3 = haedPrev;
		int next = 0;
		while (cur1 || cur2) {
			int val = (cur1->val) + (cur2->val);
			next = val / 10;
			val %= 10;
			ListNode* Node = new ListNode(val + next);
			cur3->next = Node;
			cur3 = Node;
			cur1 = cur1->next;
			cur2 = cur2->next;
		}
		return haedPrev->next;
	}
};
void test01() {

}
int main() {

	return 0;
}