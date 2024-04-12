#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
    Given a binary tree root, a node X in the tree is named good
    if in the path from root to X there are no nodes with a value
    greater than X.

    Return the number of good nodes in the binary tree.

    Constraints:

    The number of nodes in the binary tree is in the range [1, 10^5].
    Each node's value is between [-10^4, 10^4].
*/

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

static int iter(struct TreeNode *node, int max) {

    if(node == NULL)
        return 0;

    if(node->val >= max)
        return 1 + iter(node->left, node->val) + iter(node->right, node->val);
    else
        return iter(node->left, max) + iter(node->right, max);
}

static int goodNodes(struct TreeNode *root) {
    return iter(root, root->val);
}

static struct TreeNode * alloc_node(int val) {
    struct TreeNode * node;

    node = calloc(1, sizeof(struct TreeNode));
    assert(node != NULL);
    node->val = val;

    return node;
}

int main(void) {

    int num;
    struct TreeNode * root;

    /*
     Input: root = [3,1,4,3,null,1,5]
     Output: 4

     Explanation: Nodes in blue are good.

     Root Node (3) is always a good node.
     Node 4 -> (3,4) is the maximum value in the path starting from the root.
     Node 5 -> (3,4,5) is the maximum value in the path
     Node 3 -> (3,1,3) is the maximum value in the path.
    */

    root = alloc_node(3);

    root->left = alloc_node(1);
    root->right = alloc_node(4);
    root->right->left = alloc_node(1);
    root->right->right = alloc_node(5);

    root->left->left = alloc_node(3);

    num = goodNodes(root);
    assert(num == 4);
    
    /*
     Input: root = [3,3,null,4,2]

     Output: 3

     Explanation: Node 2 -> (3, 3, 2) is not good, because "3" is higher than it.
    */

    root = alloc_node(3);
    root->left = alloc_node(3);
    root->left->left = alloc_node(4);
    root->left->right = alloc_node(2);

    num = goodNodes(root);
    assert(num == 3);

    return 0;
}
