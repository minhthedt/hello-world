#include "Common.h"
#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

namespace LeetCode
{
    
    class Solution {
    public:
        static int lengthOfLongestSubstring2(std::string s) {
            int n = s.length();
            set<char> set;
            int ans = 0, i = 0, j = 0;
            while (i < n && j < n) {
                // try to extend the range [i, j]
                if (set.find(s.at(j)) != set.end()) {
                    set.insert(s.at(j++));
                    ans = max(ans, j - i);
                }
                else {
                    set.erase(s.at(i++));
                }
            }
            return ans;
        }

        static int lengthOfLongestSubstring(std::string s) {
            int n = s.length();
            int ans = 0;
            for (int i = 0; i < n; i++)
                for (int j = i + 1; j <= n; j++)
                    if (allUnique(s, i, j)) ans = max(ans, j - i);
            return ans;
        }

        static bool allUnique(std::string s, int start, int end) {
             set<char> myset;
            for (int i = start; i < end; i++) {
                char ch = s.at(i);
                std::set<char>::iterator it;
                it = myset.find(ch);
                if (it != myset.end()) return false;
                myset.insert(ch);
            }
            return true;
        }
    };

   

    void Main()
    {
        int len = Solution::lengthOfLongestSubstring2("pwwkew");
        printf("%d\n",len);
    }
   
}