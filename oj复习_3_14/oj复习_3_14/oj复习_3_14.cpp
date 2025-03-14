#include<iostream>
#include<vector>
using namespace std;
//移动零（双指针复习）
class Solution1 {
public:
    void moveZeroes(vector<int>& nums) {
        int des = -1;
        int cur = 0;
        while (cur < nums.size()) {
            if (nums[cur]) {
                swap(nums[++des], nums[cur]);
            }
            cur++;
        }
    }
};
//复写零（双指针复习）
class Solution2 {
public:
    void duplicateZeros(vector<int>& arr) {
        int cur = 0, des = -1;
        while (1) {
            if (arr[cur]) des++;
            else des += 2;
            if (des >= arr.size() - 1) break;
            cur++;
        }
        if (des == arr.size()) {
            arr[--des] = 0;
            --des;
            --cur;
        }
        while (cur >= 0) {
            if (arr[cur]) {
                swap(arr[cur], arr[des]);
            }
            else {
                arr[des--] = 0;
                arr[des] = 0;
            }
            cur--;
            des--;
        }
    }
};
//快乐数（双指针复习）
class Solution {
public:
    int ret(int n) {
        int sum = 0;
        while (n) {
            int m = n % 10;
            sum += m * m;
            n /= 10;
        }
        return sum;
    }

    bool isHappy(int n) {
        int slow = ret(n);
        int fast = ret(ret(n));
        while (fast != slow) {
            slow = ret(slow);
            fast = ret(ret(fast));
        }
        return fast == 1;
    }
};