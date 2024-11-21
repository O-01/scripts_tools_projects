// 3. Longest Substring Without Repeating Characters
// Given a string s, find the length of the longest substring without repeating characters.
// Example 1:
//     Input: s = "abcabcbb"
//     Output: 3
//     Explanation: The answer is "abc", with the length of 3.
// Example 2:
//     Input: s = "bbbbb"
//     Output: 1
//     Explanation: The answer is "b", with the length of 1.
// Example 3:
//     Input: s = "pwwkew"
//     Output: 3
//     Explanation: The answer is "wke", with the length of 3.
//     Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
// Constraints:
//     0 <= s.length <= 5 * 10^4
//     s consists of English letters, digits, symbols and spaces.

#include <algorithm>
#include <string>
#include <vector>

class Solution {
public:
	int lengthOfLongestSubstring(std::string s) {
		int max_len = 0, s_len = s.length();
		std::vector<int> char_idx(127, -1);

		for (int left = 0, right = 0; right < s_len; ++right) {
			if (char_idx[s[right]] >= left)
				left = char_idx[s[right]] + 1;
			char_idx[s[right]] = right;
			max_len = std::max(max_len, right - left + 1);
		}
		return max_len;
	}
};
