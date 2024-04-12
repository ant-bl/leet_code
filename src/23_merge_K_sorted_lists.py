# You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
# Merge all the linked-lists into one sorted linked-list and return it.

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next

class Solution:

    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        merged_head = ListNode(0)
        merged_iter = merged_head

        while True:
            min_ = None
            min_idx = None
            for idx, iter_ in enumerate(lists):
                if iter_ is not None:
                    if min_ is None:
                        min_ = iter_
                        min_idx = idx
                    else:
                        if min_.val > iter_.val:
                            min_ = iter_
                            min_idx = idx
            
            if min_idx is None:
                return merged_head.next

            merged_iter.next = lists[min_idx]
            merged_iter = merged_iter.next

            lists[min_idx] = lists[min_idx].next

