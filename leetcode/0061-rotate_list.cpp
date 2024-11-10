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
