#include <string>

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
