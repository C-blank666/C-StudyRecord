#include<iostream>
#include<vector>
#include<map>
#include<unordered_map>
//寻找数组的中心下标（前缀和）法一
using namespace std;
class Solution1 {
public:
    int pivotIndex(vector<int>& nums) {
        vector<int> dp(nums.size() + 1);
        for (int i = 1; i < dp.size(); i++) {
            dp[i] = dp[i - 1] + nums[i - 1];
        }
        if (dp[dp.size() - 1] - dp[1] == 0)
            return 0;
        for (int i = 1; i < dp.size() - 1; i++) {
            if (dp[dp.size() - 1] - dp[i + 1] == dp[i])
                return i;
        }
        if (dp[dp.size() - 2] == 0)
            return nums.size() - 1;
        return -1;
    }
};
//法二
class Solution2 {
public:
    int pivotIndex(vector<int>& nums) {
        vector<int> fx(nums.size());
        for (int i = 1; i < fx.size(); i++) {
            fx[i] = fx[i - 1] + nums[i - 1];
        }//fx[i]表示前i-1项的和
        vector<int> gx(nums.size());
        for (int i = gx.size() - 2; i >= 0; i--) {
            gx[i] = gx[i + 1] + nums[i + 1];
        }//gx[i]表示i+1到n-1所有项的和
        for (int i = 0; i < nums.size(); i++) {
            if (gx[i] == fx[i])
                return i;
        }
        return -1;
    }
};

//除自身以外数组的乘积
class Solution3 {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> f(nums.size(), 1);
        for (int i = 1; i < nums.size(); i++) {
            f[i] = f[i - 1] * nums[i - 1];
        }
        vector<int> g(nums.size(), 1);
        for (int i = nums.size() - 2; i >= 0; i--) {
            g[i] = g[i + 1] * nums[i + 1];
        }
        vector<int> ret(nums.size());
        for (int i = 0; i < nums.size(); i++) {
            ret[i] = g[i] * f[i];
        }
        return ret;
    }
};
//和为k的子数组（前缀和及哈希表）
class Solution4 {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> hash;
        hash[0] = 1;
        int sum = 0, ret = 0;
        for (auto x : nums) {
            sum += x;
            if (hash.count(sum - k)) ret += hash[sum - k];
            hash[sum]++;
        }
        return ret;
    }
};
//能被k整除的子数组
class Solution4 {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
        unordered_map<int, int> hash;
        hash[0 % k] = 1;
        int sum = 0, ret = 0;
        for (auto x : nums) {
            sum += x;
            int r = (sum % k + k) % k;
            if (hash.count(r))ret += hash[r];
            hash[r]++;
        }
        return ret;
    }
};
void test01() {
    vector<int> nums({ 1,7,3,6,5,6 });
    Solution2 s2;
    s2.pivotIndex(nums);

}
int main() {
    test01();
    return 0;
}