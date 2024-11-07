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
	ListNode* swapPairs(ListNode* head) {
		if (!head || !head->next)
			return head;
		ListNode *tmp = head, *next_pair = tmp->next->next;
		if (tmp == head)
			head = tmp->next;
		for (; tmp && tmp->next; tmp = next_pair) {
			next_pair = tmp->next->next;
			tmp->next->next = tmp;
			if (next_pair && next_pair->next)
				tmp->next = next_pair->next;
			else
				tmp->next = next_pair;
		}
		return head;
	}
};
