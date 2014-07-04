/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        ListNode *result=NULL;

        ListNode *last=result;
        int sum,carry=0;
        while(l1!=NULL || l2!=NULL){
            sum=(l1?l1->val:0)+(l2?l2->val:0)+carry;
            carry=sum/10;
            sum%=10;

            ListNode *tmp=new ListNode(sum);
            if(last==NULL)
                result=tmp;
            else 
                last->next=tmp;

            last=tmp;
            l1=(l1?l1->next:l1);
            l2=(l2?l2->next:l2);
        }
        if(carry)
            last->next=new ListNode(carry);

        return result;
    }
};
