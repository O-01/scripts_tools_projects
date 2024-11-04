// 2. Add Two Numbers
// You are given two non-empty linked lists representing two non-negative
// integers. The digits are stored in reverse order, and each of their nodes
// contains a single digit. Add the two numbers and return the sum as a linked
// list.
// You may assume the two numbers do not contain any leading zero, except the
// number 0 itself.
// Example 1:
//     Input: l1 = [2,4,3], l2 = [5,6,4]
//     Output: [7,0,8]
//     Explanation: 342 + 465 = 807.
// Example 2:
//     Input: l1 = [0], l2 = [0]
//     Output: [0]
// Example 3:
//     Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
//     Output: [8,9,9,9,0,0,0,1]
// Constraints:
//     The number of nodes in each linked list is in the range [1, 100].
//     0 <= Node.val <= 9
//     It is guaranteed that the list represents a number that does not have leading zeros.

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		int hold = 0, sum = 0;
		ListNode *result = addNode(sumCalc(l1->val + l2->val, &hold)), *add = result;
		for (l1 = l1->next, l2 = l2->next; l1 || l2; add = add->next, sum = 0) {
			if (l1)
				sum += l1->val, l1 = l1->next;
			if (l2)
				sum += l2->val, l2 = l2->next;
			add->next = addNode(sumCalc(sum, &hold));
		}
		if (hold)
			add->next = addNode(hold);
		return result;
	}
private:
	ListNode* addNode(int digit) {
		return new ListNode(digit);
	}
	int sumCalc(int num, int *hold) {
		int sum = num + *hold;
		if (sum > 9)
			return *hold = 1, sum % 10;
		*hold = 0;
		return sum;
	}
	// int extractNumber(ListNode* head) {
	//     int number = 0, place = 1;
	//     for (ListNode* tmp = head; tmp; tmp = tmp->next, place *= 10)
	//         number += (tmp->val * place);
	//     return number;
	// }
	// ListNode* composeNumber(int value) {
	//     ListNode* result = addNode(value % 10), * tmp = result;
	//     for (value /= 10; value; tmp = tmp->next, value /= 10)
	//         tmp->next = addNode(value % 10);
	//     return result;
	// }
};
