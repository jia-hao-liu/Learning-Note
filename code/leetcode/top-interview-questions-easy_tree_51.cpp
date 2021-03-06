/* 
data-time 2019-10-02 14:12:56


题目描述:
将有序数组转换为二叉搜索树

将一个按照升序排列的有序数组，转换为一棵高度平衡二叉搜索树。

本题中，一个高度平衡二叉树是指一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过 1。

示例:

给定有序数组: [-10,-3,0,5,9],

一个可能的答案是：[0,-3,9,-10,null,5]，它可以表示下面这个高度平衡二叉搜索树：

      0
     / \
   -3   9
   /   /
 -10  5

链接:https://leetcode-cn.com/explore/interview/card/top-interview-questions-easy/7/trees/51/

/*

主要思路：将数组中间的i数作为根节点，进行递归调用，i-1为左节点，i+1为右节点。每次取中间的数，因此基本上不会有太大的误差
        时间复杂度O(n);空间复杂度O(1)
        注意NULL一般被定义为0，在g++中被定义为__null
        https://blog.csdn.net/wowoooxx/article/details/78386112
*/

#include <iostream>
#include <vector>
#include <math.h>
#include <time.h>
#include <string>
#include <sstream>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <queue>
using namespace std;


struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
//注意这里使用队列作为辅助单位进行存储

void FromArrayToTree(TreeNode* node,vector<int> int_array){
    TreeNode* work_pointer=node;
    TreeNode* work_pointer2=nullptr;
    std::queue<TreeNode*> work_queue;
    int i=0;
    if(node->val==NULL){node->val=int_array.at(0);++i;}
    work_queue.push(node);
    while(i<int_array.size()){
        if(!work_queue.empty()){
            work_pointer2=work_queue.front();
            if(work_pointer2->left==nullptr){
                if(i>=int_array.size()){break;}
                TreeNode* temp_node=new TreeNode(int_array.at(i));
                work_pointer2->left=temp_node;
                work_queue.push(temp_node);
                ++i;
            }
            if(work_pointer2->right==nullptr){
                if(i>=int_array.size()){break;}
                TreeNode* temp_node2=new TreeNode(int_array.at(i));
                work_pointer2->right=temp_node2;
                work_queue.push(temp_node2);
                ++i;
            }
            work_queue.pop();
        }
    }
}
//使用层次遍历来进行节点的输出

void PrintfTree(TreeNode* node){
    std::cout<<"\n \t ====start printf ==== \t "<<std::endl;
    std::queue<TreeNode*> print_queue;
    std::string temp_reslation="";
    //这里再使用一个节点，记录每层的最后一个节点
    TreeNode* last_node=node;
    print_queue.push(node);
    while (!print_queue.empty())
    {
        TreeNode* temp=print_queue.front();
        if(temp!=nullptr){
            printf("%d ",temp->val);
            //刷新缓冲输出
            fflush(stdout);
        }
        if(temp->left!=nullptr){
            print_queue.push(temp->left);
            temp_reslation+="| ";
        }
        if(temp->right!=nullptr){
            print_queue.push(temp->right);
             temp_reslation+="\\ ";
        }
        if(temp==last_node){
            printf("\n");
            last_node=print_queue.back();
            std::cout<<temp_reslation<<std::endl;
        }
        print_queue.pop();
    }
    std::cout<<"\n \t ====end printf ==== \t"<<std::endl;
    
}
void DeleteTree(TreeNode* node){
    if(node==nullptr){return ;}
    if(node->left!=nullptr){
        DeleteTree(node->left);
    }
    if(node->right!=nullptr){
        DeleteTree(node->right);
    }
     if (node!=nullptr)
    {
        delete node;
        node=nullptr;
    }
    
}
//关闭流输出
static auto static_lambda = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    return 0;
}();
//main function
class Solution {
public:
    TreeNode* getTreeNode(vector<int >& nums,int left,int right){
        TreeNode* root=nullptr; 
        if(right<left){
            return root;
        }
        if(left>=0&&right<nums.size()){
            int index=(left+right)/2;
            root=new TreeNode(nums.at(index));
            root->left=getTreeNode(nums,left,index-1);
            root->right=getTreeNode(nums,index+1,right);
        }
        return root;
    }
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        TreeNode *result=nullptr;
        int left=0, right =nums.size()-1;
        result=getTreeNode(nums,left,right);
        return result;
    }
};
int main(int argc, char const *argv[]) {
    Solution my_solution;
    //input string
   	//创建第一组数据
    vector<int> vector_temp={9,9,9};
    vector<int> vector_temp2={1,2,4};
    TreeNode* node_ptr=new TreeNode(NULL);
    FromArrayToTree(node_ptr,vector_temp);
    //FromArrayToList(node_ptr2,vector_temp2);
    PrintfTree(node_ptr);
    int test_int=1; 
	int time_point_1=clock();
    auto result=my_solution.sortedArrayToBST(vector_temp);
    int time_point_2=clock();
	printf("\n \t Time :%d ms \n",time_point_2-time_point_1);
    DeleteTree(node_ptr);
    return 0;
}
/*
//优质解答：思路相同，代码略有不同
时间复杂度O(n),空间复杂度O(1);

class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        if (nums.empty())
            return NULL;
        
        return ToBst(nums, 0, nums.size() - 1);
    }
    
    TreeNode* ToBst(vector<int>& nums, int left, int right) {
        if (left > right)   return NULL;
        int mid = (left + right)/2;
        TreeNode* retnode = new TreeNode(nums[mid]);
        retnode->left = ToBst(nums, left, mid - 1);
        retnode->right = ToBst(nums, mid + 1, right);
        return retnode;
    }
};
//优质解答2：思路相同代码略有不同

class Solution {
public:
    TreeNode* to_bst(vector<int>& nums, int left, int right)
    {
        if (left > right)
        {
            return nullptr;
        }
        int mid = (left + right) / 2;
        TreeNode* node = new TreeNode(nums[mid]);
        //node->val = nums[mid];
        node->left = to_bst(nums, left, mid - 1);
        node->right = to_bst(nums, mid + 1, right);
        return node;
    }
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return to_bst(nums, 0, nums.size() - 1);
    }
};
*/
