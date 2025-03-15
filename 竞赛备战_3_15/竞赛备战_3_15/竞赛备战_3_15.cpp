#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<unordered_map>

//oj 山脉数组的顶峰索引（二分查找）
using namespace std;
class Solution1 {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        int left = 0;
        int right = arr.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] > arr[mid + 1] && arr[mid] < arr[mid - 1]) {
                right = right - 1;
            }
            else if (arr[mid] < arr[mid + 1] && arr[mid]>arr[mid - 1]) {
                left = left + 1;
            }
            else
                return mid;
        }
        return -1;
    }
};
//寻找峰值
class Solution2 {
public:
    int findPeakElement(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] > nums[mid + 1]) {
                right = mid;
            }
            else if (nums[mid] < nums[mid + 1]) {
                left = mid + 1;
            }
        }
        return left;
    }
};
//寻找旋转排序数组中的最小值
class Solution3 {
public:
    int findMin(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        int n = nums.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < nums[n]) {
                right = mid;
            }
            else if (nums[mid] > nums[n]) {
                left = mid + 1;
            }
        }
        return nums[left];
    }
};

//寻找缺失数字
class solution4 {
public:
    int findMiss(vector<int>& arr) {
        int left = 0;
        int right = arr.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] == mid) {
                left = mid + 1;
            }
            else if (arr[mid] != mid) {
                right = mid;
            }
        }
        return left == arr[left] ? left + 1 : left;
    }
};
void test01() {
    solution4 s4;
    vector<int> arr = { 0,1,2,3,4,5,7,8,9,10};
    int ret = s4.findMiss(arr);
    cout << ret << endl;
}

//编程题——前缀和
class Solution5 {
public:
    int rangeSum(int l, int r, vector<int> arr) {
        vector<long long> dp;//long long 防止溢出
        dp.push_back(0);
        for (int i = 0; i < arr.size(); i++) {
            dp.push_back(arr[i] + dp[i]);
        }
        int sum = dp[r] - dp[l-1];
        return sum;
    }
};

void test02() {
    Solution5 s5;
    int n,q, l, r;//    0,1,9,13, 
    cin >> n;
    cin >> q;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    while (q--) {
        cin >> l >> r;
        cout<<s5.rangeSum(l,r,arr);
    }
}
void test03() {
    vector<int> a(2);
    cout << a[0] << ' ' << a[1] << endl;
}
//编程题——二维数组前缀和
namespace solution6 {
    void test04() {
        int m, n, q;
        cin >> m >> n >> q;
        vector<vector<int>> towDimnArr(m + 1, vector<int>(n + 1));
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                if (i == 0 || j == 0)
                    towDimnArr[i][j] = 0;
                else
                    cin >> towDimnArr[i][j];
            }
        }
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                if (i == 0 || j == 0)
                    dp[i][j] = 0;
                else
                    dp[i][j] = dp[i][j - 1] + dp[i - 1][j] + towDimnArr[i][j] - dp[i - 1][j - 1];
            }
        }
        int x1, y1;
        int x2, y2;
        while (q--) {
            cin >> x1 >> y1 >> x2 >> y2;
            cout << dp[x2][y2] - dp[x2][y1 - 1] - dp[x1 - 1][y2] + dp[x1 - 1][y1 - 1];
        }
    }
}
int main() {
    //test01();
    //test02();
    //test03();
    solution6::test04();
    return 0;
}