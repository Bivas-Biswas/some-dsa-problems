
#include <bits/stdc++.h>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* getCrossNode(ListNode *head){

    if(!head || !head->next) return nullptr;

    ListNode *fast = head, *slow = head;

    while(fast != nullptr && fast->next != nullptr){
        // cout << slow->val << " " << fast->val << endl;
        slow = slow->next;
        fast = fast->next->next;

        if(slow == fast) break;
    }

    if(!fast || !fast->next) return nullptr;

    ListNode* temp = head;
    while(temp != slow){
        temp = temp->next;
        slow = slow->next;
    }
    
    return temp;
}



pair<ListNode*,int> cycleInLinkedList(ListNode* head) {
    //Complete the function

    ListNode *cross_node = getCrossNode(head);

    if(!cross_node) return make_pair(nullptr, -1);

    int n = 1;

    ListNode *curr = cross_node->next;
    while(curr && curr != cross_node){
        n++;
        curr = curr->next;
    }

    return make_pair(cross_node, n);
}


ListNode* GetList(int n, vector<int> &num, int lastLink) {
    ListNode* head = nullptr;

    if(num.empty()) {
        return head;
    }

    ListNode* cur = head;
    
    for(int i  = 0; i < n; i++) {
        ListNode* temp = new ListNode(num[i]);
        if(!cur) {
            cur = temp;
            head = cur;
        }
        else {
            cur->next = temp;
            cur = temp;
        }
    }

    if(lastLink) {
        ListNode* temp = head;
        for(int i = 0; i < lastLink - 1; i++) {
            temp = temp->next;
        }
        cur->next = temp;
    }
    
    return head;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;

    vector<int> num;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        num.push_back(x);
    }

    int lastLink;
    cin >> lastLink;

    ListNode* head = GetList(n, num, lastLink);

    pair<ListNode*,int> ans = cycleInLinkedList(head);

    cout << (ans.first ? ans.first->val : -1) << " " << ans.second << "\n";
    
    return 0;
}
