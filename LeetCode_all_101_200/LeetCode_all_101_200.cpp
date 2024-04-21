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
    //136 只出现一次的数字
    int singleNumber(vector<int>& nums) {
        int result = 0;
        for (int num : nums) {
            result ^= num;
        }
        return result;
    }
};
int main()
{
    Solution solution;
    vector<int>  test = { 7,1,5,3,6,4 };
    cout<<solution.maxProfit(test);
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
