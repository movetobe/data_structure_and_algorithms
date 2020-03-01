/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool sub_path(struct ListNode* head, struct TreeNode* root){
    /* end */
    if (!head) {
        return true;
    }
    if (!root) {
        return false;
    }
    if (head->val != root->val) {
        return false;
    }
    /* options */
    return (sub_path(head->next, root->left) || sub_path(head->next, root->right));
}

bool isSubPath(struct ListNode* head, struct TreeNode* root){
    /* end */
    if (!head) {
        return true;
    }
    if (!root) {
        return false;
    }

    /* options */
    return (sub_path(head, root) || isSubPath(head, root->left) || isSubPath(head, root->right));
}
