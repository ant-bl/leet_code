# Given the head of a linked list, remove the nth node from the end of the list and return its head.

# Definition for singly-linked list.
class ListNode:
   
    def __init__(self, val=0, next_=None):
        self.val = val
        self.next = next_

def count(head):
    i = 0
    while head is not None:
        head = head.next
        i = i + 1
    return i

def delete(head, idx):
    i = 0
    prev = None
    if idx == 0:
        return head.next

    while head is not None:
        prev = head
        head = head.next
        i = i + 1
        if i == idx:
            prev.next = head.next
            return


class Solution:
    def removeNthFromEnd(self, head: Optional[ListNode], n: int) -> Optional[ListNode]:
        length = count(head)
        idx = length - n
        delete(head, idx)

        
