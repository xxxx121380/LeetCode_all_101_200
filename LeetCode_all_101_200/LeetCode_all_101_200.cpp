// LeetCode_all_101_200.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <stack>
#include <cmath>
#include <algorithm>
#include <string>
#include <regex>
#include <unordered_map>
#include <limits>
#include <stdexcept>
#include <functional>
using namespace std;

class Solution {
public:
    //118 杨辉三角
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> result;
        vector<int> first = { 1 };
        result.push_back(first);
        for (int i = 0; i < numRows-1; i++) {
            vector<int>nowFloor = { 1 }; 
            for (int j = 0; j < i; j++) {
                nowFloor.push_back(result[i][j]+result[i][j+1]);
            }
            nowFloor.push_back(1);
            result.push_back(nowFloor);
        }
        return result;
    }   
    //119 杨辉三角II
    vector<int> getRow(int rowIndex) {
        vector<int> first = { 1 };
        if (rowIndex == 0)return first;
        vector<int>second;
        for (int i = 0; i < rowIndex; i++) {
            second.clear();
            second.push_back(1);
            for (int j = 0; j < i; j++) {
                second.push_back(first[j] +first[j + 1]);
            }
            second.push_back(1);
            first = second;
        }
        return second;
    }
    //121 买卖股票的最佳时机
    //检测到目前为止的最低价与当日价格差值是否更高
    int maxProfit(vector<int>& prices) {
        int result = 0;
        int temp1 = 100001;
        for (int i = 0; i < prices.size(); i++) {
            if (prices[i] < temp1)
                temp1 = prices[i];
            if (prices[i] - temp1 > result)
                result = prices[i] - temp1;
        }
        return result;
    }
    //125 验证回文串
    //题目虽然没说内存限制，但是把s处理后赋值给新字符串一定爆内存
    bool isPalindrome(string s) {
        int left = 0; int right = s.size() - 1;
        while (left < right) {
            char lw, rw;
            if (s[left] <= 'Z' && s[left] >= 'A')
            {
                lw = s[left] + 32;
            }
            else if ((s[left] <= 'z' && s[left] >= 'a') || (s[left] <= '9' && s[left] >= '0'))
                lw = s[left];
            else {
                left++;
                continue;
            }
            if (s[right] <= 'Z' && s[right] >= 'A')
            {
                rw = s[right] + 32;
            }
            else if ((s[right] <= 'z' && s[right] >= 'a') || (s[right] <= '9' && s[right] >= '0'))
                rw = s[right];
            else {
                right--;
                continue;
            }
            if (lw != rw)return false;
            left++;
            right--;
        }
        return true;
    }
    //136 只出现一次的数字
    //hash 空间复杂度不符合要求，位运算最快（题目限制比较足）
    int singleNumber(vector<int>& nums) {
        int result = 0;
        for (int num : nums) {
            result ^= num;
        }
        return result;
    }
    //157 用 Read4 读取 N 个字符
    //重点在于理解题意，相当于吧read4的内容多次读取出来，并且直接给到read的buf中
    /**
    * @param buf Destination buffer
    * @param n   Number of characters to read
    * @return    The number of actual characters read
    */
    int read(char* buf, int n) {

        int totalRead = 0;
        char* temp = new char[4];
        int currentRead = 0;

        do {
            //本地没写read4的API
            //currentRead = read4(temp);
            currentRead = 4;
            int spaceLeft = n - totalRead;
            int toCopy = std::min(currentRead, spaceLeft);
            //这样是过不去题解的，得用strncpy
            //strncpy(buf + totalRead,temp, toCopy);
            strncpy_s(buf + totalRead, spaceLeft,temp, toCopy);
            totalRead += toCopy;
        } while (currentRead == 4 && totalRead < n);

        delete[] temp;
        return totalRead;
    }
    //163 缺失的区间
    //找范围就行，考虑好左右边界
    vector<vector<int>> findMissingRanges(vector<int>& nums, int lower, int upper) {
        vector<vector<int>>result;
        if (nums.empty()) {
            vector<int> temp;
            temp.push_back(lower);
            temp.push_back(upper);
            result.push_back(temp);
            return result;
        }
        int left = lower;
        int right = upper;
        int t = 0;
        //左额外区间
        if (nums[0] > left) {
            vector<int> temp;
            temp.push_back(left);
            temp.push_back(nums[0] - 1);
            left = nums[0] + 1;
            t++;
            result.push_back(temp);
        }
        while (t < nums.size()) {
            if (nums[t] > left) {
                vector<int> temp;
                temp.push_back(left);
                temp.push_back(nums[t] - 1);
                result.push_back(temp);
            }
            left = nums[t] + 1;
            t++;
        }
        t--;
        if (nums[t] < right) {
            vector<int> temp;
            temp.push_back(nums[t] + 1);
            temp.push_back(right);
            result.push_back(temp);
        }
        return result;
    }
    //168 Excel表列名称
    //真难算啊，先找最大值，再往逐渐减少
    string convertToTitle(int columnNumber) {
        string s = "";
        long long t = 26;
        long long sum = 26;
        while (columnNumber > sum) {
            t *= 26;
            sum += t;
        }
        t /= 26;
        while (columnNumber > 26) {
            int b = (columnNumber - t / 26) / t;
            char temp = '@' + b;
            s = s + temp;
            columnNumber = columnNumber - t * b;
            t /= 26;
        }
        char f = '@' + columnNumber;
        s = s + f;
        return s;
    }
    //169 多数元素
    //读两遍
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> sum;
        int result=0;
        for (int i = 0; i < nums.size(); i++) {
            sum[nums[i]]++;
        }
        for (const auto& pair : sum) {
            if (pair.second > nums.size() / 2)
                result= pair.first;
        }
        return result;
    }
    //171 Excel 表列序号
    int titleToNumber(string columnTitle) {
        string s = columnTitle;
        int result = 0;
        long long t = 1;
        reverse(s.begin(), s.end());
        for (int i = 0; i < s.size(); i++) {
            char b = s[i];
            result = result + t * (b - 'A'+1);
            t *= 26;
        }
        return result;
    }
    //175 组合两个表
    //From 表名 表简写可以方便查询语句书写
    //其中From基本以一张主表进行
    //左连接的格式是 LEFT JOIN 表名 ON 相等栏条件
    /*
    Select p.firstName,p.lastName,a.city,a.state From Person p
    LEFT JOIN Address a ON p.PersonId = a.PersonId
    */
    //183 从不订购的客户
    //运用数据库的左连接，首先是Select 栏目名 As 显示内容
    //然后是From 从某个表
    //左连接的意思把两个表连起来，并且以左边的为主表是，其中C表的id需要=O表的顾客id
    //如果没有 就认为是没订购过的，输出结果
    /*
    SELECT Customers.name AS Customers
    FROM Customers
    LEFT JOIN Orders ON Customers.id = Orders.customerId
    WHERE Orders.id IS NULL;
    */
    //190 颠倒二进制位
    uint32_t reverseBits(uint32_t n) {
        uint32_t reversedNum = 0;
        do {
            uint32_t lastDigit = n % 2;  // 获取最后一位
            reversedNum = reversedNum * 2 + lastDigit;  // 添加到反转数中
            n /= 2;  // 移除最后一位
        } while (n > 0);
        return reversedNum;
    }
    //191 位1的个数
    //辗转相除得1位
    int hammingWeight(int n) {
        int result=0;
        while (n > 0) {
            result += n % 2;
            n = n / 2;
        }
        return result;
    }
};
int main()
{
    Solution solution;
    vector<int>  test = { -1 };
    //string s = "A man, a plan, a canal: Panama";
    uint32_t t = 0b1111111111111111111111111111101;
    solution.reverseBits(t);
   // cout<<solution.maxProfit(test);
    //solution.divide(7,-3);
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
