
/*
data-time 2020-03-12 14:14:53
题目描述:

309. 最佳买卖股票时机含冷冻期

给定一个整数数组，其中第 i 个元素代表了第 i 天的股票价格 。​

设计一个算法计算出最大利润。在满足以下约束条件下，你可以尽可能地完成更多的交易（多次买卖一支股票）:

你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
卖出股票后，你无法在第二天买入股票 (即冷冻期为 1 天)。
示例:

输入: [1,2,3,0,2]
输出: 3 
解释: 对应的交易状态为: [买入, 卖出, 冷冻期, 买入, 卖出]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-cooldown
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

*/
/*
使用动规划的方法。dp[i][j]记录第i天的不同状态时的利润
j=0,1,2;0表示卖出，1表示买入,2表示过渡期
dp[i][0]=max(dp[i-1][2],dp[i-1][0]);
dp[i][1]=max(dp[i-1][1],dp[i-1][0]-prices[i]);
dp[i][2]=dp[i-1][1]+prices[i];
时间复杂度O(n)；空间复杂度O(3*n)
 */
#include <cmath>
#include <cctype>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <cstdint>

using namespace std;


//关闭流输出
static auto static_lambda = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    return 0;
}();
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len=prices.size();
        if(len<=1) return 0;
        if(len<2) return  abs(prices[0]-prices[1]);
        int dp[len][3];
        memset(&dp,0,len*3*sizeof(int));
        dp[0][1]-=prices[0];
        for(int i=1;i<len;++i){
            dp[i][0]=max(dp[i-1][2],dp[i-1][0]);
            dp[i][1]=max(dp[i-1][1],dp[i-1][0]-prices[i]);
            dp[i][2]=dp[i-1][1]+prices[i];
        }
        // int dp_i_0=0,dp_i_1=0,dp_i_2=0;
        // dp_i_1-=prices[0];
        // for(int i=1;i<len;++i){
        //     int temp0=dp_i_0,temp1=dp_i_1,temp2=dp_i_2;
        //     dp_i_0=max(temp2,temp0);
        //     dp_i_1=max(temp1,temp0-prices[i]);
        //     dp_i_2=temp1+prices[i];
        // }
        // return max(dp_i_0,dp_i_2);
        return max(dp[len-1][0],dp[len-1][2]);
    }
};

int main(int argc char* argv[]){
    Solution a;
    a.maxProfit({1,2,3,0,2});
    return 0;
}

/**
优质代码1：使用临时的变量，代替dp数据；
时间复杂度O(n);空间复杂度O(1)
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int dp_0=0;
        int dp_1=INT_MIN;
        int last=0;
        for(auto& price:prices){
            int tmp=dp_0;
            dp_0=max(dp_0,dp_1+price);
            dp_1=max(dp_1,last-price);
            last=tmp;
        }
        return dp_0;
    }
};

//官方题解：

//优质解析：
https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/solution/yi-ge-fang-fa-tuan-mie-6-dao-gu-piao-wen-ti-by-lab/

*/
