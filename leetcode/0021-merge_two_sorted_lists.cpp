// 21. Merge Two Sorted Lists
// You are given the heads of two sorted linked lists list1 and list2.

// Merge the two lists into one sorted list. The list should be made by splicing
// together the nodes of the first two lists.

// Return the head of the merged linked list.
// Example 1:
//     Input: list1 = [1,2,4], list2 = [1,3,4]
//     Output: [1,1,2,3,4,4]
// Example 2:
//     Input: list1 = [], list2 = []
//     Output: []
// Example 3:
//     Input: list1 = [], list2 = [0]
//     Output: [0]
// Constraints:
//     The number of nodes in both lists is in the range [0, 50].
//     -100 <= Node.val <= 100
//     Both list1 and list2 are sorted in non-decreasing order.

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

#define SET(x, y) ((x)->val < (y)->val ? (x) : (y))
#define ADV(x, y, z) ((z) == (x) ? (x) = (x)->next : (y) = (y)->next)
#define SETADV(x, y, z) ((z) = SET((x), (y)), ADV((x), (y), (z)))

class Solution {
public:
	ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
		ListNode *head = nullptr, *tmp = nullptr;

		if (!list1 || !list2)
			return list1 ? list1 : list2;
		SETADV(list1, list2, tmp);
		for (head = tmp; list1 && list2; tmp = tmp->next)
			SETADV(list1, list2, tmp->next);
		tmp->next = list1 ? list1 : list2;
		return head;
	}
};
