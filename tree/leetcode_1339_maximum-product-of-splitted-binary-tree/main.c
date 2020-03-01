/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define M 1000000007
long sum(struct TreeNode *root)
{
    if (!root) {
        return 0;
    }
    return (root->val + sum(root->left) + sum(root->right));
}
long cut(struct TreeNode *root, long *product, long total)
{
    long current_sum;

    if (!root) {
        return 0;
    }
    current_sum = root->val + cut(root->left, product, total) + cut(root->right, product, total);
    *product = MAX(*product, (total - current_sum)* current_sum);

    return current_sum;
}
int maxProduct(struct TreeNode* root){
    long product = 0;

    cut(root, &product, sum(root));

    return product % M;
}
