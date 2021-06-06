#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
   public:
    void reverse0(ListNode* todo, ListNode* done, int k) {
        ListNode* doing;
        for (int i = 0; i < k; i++) {
            doing = todo;
            todo = doing->next;
            doing->next = done;
            done = doing;
        }
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        if (k <= 1 || head == nullptr) return head;
        ListNode pre(0, head);
        ListNode* start = &pre;
        ListNode* end = start;
        int i = 0;
        while (end->next != nullptr) {
            end = end->next;
            i++;
            if (i == k) {
                ListNode* tmp = start->next;
                reverse0(start->next, end->next, k);
                start->next = end;
                start = tmp;
                end = start;
                i = 0;
            }
        }
        return pre.next;
    }
};