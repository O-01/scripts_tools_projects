#include <climits>

// 7. Reverse Integer
// Given a signed 32-bit integer x, return x with its digits reversed.
// If reversing x causes the value to go outside the signed 32-bit integer range [-2^31, 2^31 - 1], then return 0.

// Assume the environment does not allow you to store 64-bit integers (signed or unsigned).
// Example 1:
//     Input: x = 123
//     Output: 321
// Example 2:
//     Input: x = -123
//     Output: -321
// Example 3:
//     Input: x = 120
//     Output: 21
// Constraints:
//     -2^31 <= x <= 2^31 - 1

class Solution {
public:
	int reverse(int x) {
		int rev = 0, sign = 1;

		if (x == INT_MIN)
			return 0;
		if (x < 0)
			sign = -(sign), x = -(x);
		for (; x; x /= 10) {
			if (rev > INT_MAX / 10)
				return 0;
			rev = rev * 10 + x % 10;
		}
		return sign * rev;
	}
};
