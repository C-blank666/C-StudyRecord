#include<iostream>
#include<map>
#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std;
//连续数组
class Solution1 {
public:
	int findMaxLength(vector<int>& nums) {
		for (auto& x : nums) {
			if (x == 0) x = -1;
		}
		int sum = 0, len = 0;
		unordered_map<int, int> hash;
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
//二维数组的前缀和（映射错位）
namespace solution2 {

	void test01() {
		int m, n;
		cout << "请输入行和列>:";
		cin >> m >> n;
		vector<vector<int>> towDimnArr(m, vector<int>(n));

		for (int i = 0; i < m; i++) {
			cout << "请输入第" << i << "行共" << n << "个元素>:";
			for (int j = 0; j < n; j++) {
				cin >> towDimnArr[i][j];
			}
		}//这里的二维数组下标从( 0, 0 )开始
		vector<vector<int>> dp(m + 1, vector<int>(n + 1));
		for (int i = 1; i < m + 1; i++) {
			for (int j = 1; j < n + 1; j++) {
				dp[i][j] = dp[i - 1][j] + dp[i][j - 1] + towDimnArr[i - 1][j - 1] - dp[i - 1][j - 1];
			}
		}
		cout << "dp数组如下：" << endl;
		for (int i = 0; i < m + 1; i++) {
			for (int j = 0; j < n + 1; j++) {
				if (dp[i][j] < 10)
					cout << '0' << dp[i][j] << ' ';
				else
					cout << dp[i][j] << ' ';
			}
			cout << endl;
		}
		//创建并打印dp数组
		cout << "请输入你要计算的范围" << endl;;
		int x1, y1;
		int x2, y2;
		while (1) {
			cout << "范围1>:";
			cin >> x1 >> y1;
			cout << "范围2>:";
			cin >> x2 >> y2;
			int sum = dp[x2][y2] - dp[x2][y1 - 1] - dp[x1 - 1][y2] + dp[x1 - 1][y1 - 1];
			cout << "结果是>:" << sum << endl;
			cout << "是否继续>:(y/n)>:";
			char y;
			cin >> y;
			if (y == 'n') break;
		}
	}

}
//矩阵区域和
class Solution3 {
public:
	vector<vector<int>> matrixBlockSum(vector<vector<int>>& mat, int k) {
		int m = mat.size();
		int n = mat[0].size();
		vector<vector<int>> dp(m + 1, vector<int>(n + 1));
		for (int i = 1; i < m + 1; i++) {
			for (int j = 1; j < n + 1; j++) {
				dp[i][j] = dp[i - 1][j] + dp[i][j - 1] + mat[i - 1][j - 1] -
					dp[i - 1][j - 1];
			}
		}
		vector<vector<int>> ret(m, vector<int>(n));
		for (int x = 0; x < m; x++) {
			for (int y = 0; y < n; y++) {
				int x1 = max(x - k, 0) + 1;
				int y1 = max(y - k, 0) + 1;
				int x2 = min(x + k, m - 1) + 1;
				int y2 = min(y + k, n - 1) + 1;
				ret[x][y] = dp[x2][y2] - dp[x1 - 1][y2] - dp[x2][y1 - 1] +
					dp[x1 - 1][y1 - 1];
			}
		}
		return ret;
	}
};
//位1的个数
class Solution4 {
public:
	int hammingWeight(int n) {
		int count = 0;
		while (n) {
			n = n & (n - 1);//n&(n-1)的操作是将n的二进制中最右侧的1换为0
			count++;
		}
		return count;
	}
};
//比特位计数
class Solution5 {
public:
	int hammingWeight(int n) {
		int count = 0;
		while (n) {
			n = n & (n - 1);
			count++;
		}
		return count;
	}
	vector<int> countBits(int n) {
		vector<int> ret;
		for (int i = 0; i <= n; i++) {
			ret.push_back(hammingWeight(i));
		}
		return ret;
	}
};
//只出现一次的数字
class Solution6 {
public:
	int singleNumber(vector<int>& nums) {
		int ret = 0;
		for (auto x : nums) {
			ret ^= x;
		}
		return ret;
	}
};
//只出现一次的数字III
class Solution7 {
public:
	vector<int> singleNumber(vector<int>& nums) {
		int result = 0;
		for (auto x : nums) {
			result ^= x;
		}
		int tmp = (result == INT_MIN ? result : result & (-result));
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
//汉明距离
class Solution8 {
public:
	int hammingDistance(int x, int y) {
		int s = x ^ y;
		int ret = 0;
		while (s) {
			ret += s & 1;
			s >>= 1;
		}
		return ret;
	}
};


void test02() {
	Solution7 s7;
	vector<int> nums({ 1,2,1,3,2,5 });

	s7.singleNumber(nums);
}
void test03() {
	int a = 3;
	int b = 5;
	int c = a ^ b;
	cout << c << endl;
}
int main() {
	//solution2::test01();
	test02();
	//test03();
	return 0;
}