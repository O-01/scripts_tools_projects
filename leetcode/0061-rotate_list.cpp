// 61. Rotate List
// Given the head of a linked list, rotate the list to the right by k places.
// Example 1:
//     Input: head = [1,2,3,4,5], k = 2
//     Output: [4,5,1,2,3]
// Example 2:
//     Input: head = [0,1,2], k = 4
//     Output: [2,0,1]
// Constraints:
//     The number of nodes in the list is in the range [0, 500].
//     -100 <= Node.val <= 100
//     0 <= k <= 2 * 10^9

/**
 * Definition for singly-linked list.
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
	ListNode* rotateRight(ListNode* head, int k) {
		if (!head || !head->next || !k)
			return head;

		int size = 1;
		ListNode *tmp = head;

		for (; tmp && tmp->next; ++size, tmp = tmp->next)
			;
		tmp->next = head;
		for (k %= size, size -= k; size; --size)
			tmp = tmp->next;
		head = tmp->next;
		tmp->next = nullptr;
		return head;
	}
};
