/**

34  Find First and Last Position of Element in Sorted Array

Given an array of integers nums sorted in non-decreasing order, find the starting and ending position of a given target value.

If target is not found in the array, return [-1, -1].

You must write an algorithm with O(log n) runtime complexity.

Input: nums = [5,7,7,8,8,10], target = 8
Output: [3,4]

Input: nums = [7,7,7,7], target = 7
Output: [0,3]

Url https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/

*/

class Solution {
public:
    vector<int> searchRange(vector<int>& v, int target) {
      if(v.size() == 0)
        return vector<int>{-1,-1};
      return _searchRange(v, target, 0, v.size()-1) ;
    }
  
    vector<int> _searchRange(vector<int>& v, int target, int l, int r) {
      
      pair<int,int> result = std::make_pair(-1,-1);
        
      if(l == r){
        result = (target == v[l]) ? std::make_pair(l,r) : std::make_pair(-1,-1);
      } else if ( target < v[l] || target > v[r]) {
        result =  std::make_pair(-1,-1);
      } else if (v[l] == target && v[r] == target){
        result =  std::make_pair(l,r);
      } else {
        
          int m = (l+r)/2;

          vector<int> leftc = _searchRange(v,target, l, m); // [a,b]
          vector<int> rightc = _searchRange(v,target, m+1, r); // [c,d]

          if(leftc[0] != -1 || rightc[0] != -1){
            result.first = (leftc[0] != -1) ? leftc[0] : rightc[0];
            result.second = (rightc[1] != -1) ? rightc[1] : leftc[1];
          }
      }

      vector<int> vres;
      vres.push_back(result.first);
      vres.push_back(result.second);
        
      return vres;
    } 
};
