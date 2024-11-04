#include <string>

// 28. Find the Index of the First Occurrence in a String
// Given two strings needle and haystack, return the index of the first
// occurrence of needle in haystack, or -1 if needle is not part of haystack.
// Example 1:
//     Input: haystack = "sadbutsad", needle = "sad"
//     Output: 0
//     Explanation: "sad" occurs at index 0 and 6.
//     The first occurrence is at index 0, so we return 0.
// Example 2:
//     Input: haystack = "leetcode", needle = "leeto"
//     Output: -1
//     Explanation: "leeto" did not occur in "leetcode", so we return -1.
// Constraints:
//     1 <= haystack.length, needle.length <= 104
//     haystack and needle consist of only lowercase English characters.

class Solution {
public:
	int strStr(std::string haystack, std::string needle) {
		int len_haystack = haystack.length(), len_needle = needle.length();
		if (len_needle > len_haystack)
			return -1;
		for (int idx = 0; idx < (len_haystack + 1) - len_needle; ++idx)
			if (haystack[idx] == needle[0])
				for (int check = 0, at = idx; needle[check]; ++check, ++at) {
					if (haystack[at] != needle[check])
						break;
					if (!needle[check + 1])
						return idx;
				}
		return -1;
	}
};
