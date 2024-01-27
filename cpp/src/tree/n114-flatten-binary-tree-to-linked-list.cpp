#include <iostream>
#include <vector>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode()
        : val(0)
        , left(nullptr)
        , right(nullptr)
    {
    }
    TreeNode(int x)
        : val(x)
        , left(nullptr)
        , right(nullptr)
    {
    }
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x)
        , left(left)
        , right(right)
    {
    }
};

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    void flatten(TreeNode* root)
    {
        std::vector<TreeNode*> vec;

        std::function<void(TreeNode*)> traverse = [&](TreeNode* node) {
            if (!node)
                return;

            vec.push_back(node);
            traverse(node->left);
            traverse(node->right);
        };

        // collect
        traverse(root);

        auto it = vec.begin();
        TreeNode* pre = nullptr;
        while (it < vec.end()) {
            if (!pre) {
                pre = *it;
            } else {
                pre->right = *it;
                pre->left = nullptr;
                pre = *it;
            }

            it++;
        }
        if (pre) {
            pre->left = nullptr;
        }
    }
};

int main(int argc, char* argv[])
{

    auto input = new TreeNode(
        1,
        new TreeNode(2,
            new TreeNode(3),
            new TreeNode(4)),
        new TreeNode(5,
            nullptr,
            new TreeNode(6)));

    Solution s;
    s.flatten(input);
    while (input) {
        std::cout << "node: " << input->val << std::endl;
        input = input->right;
    }

    return 0;
}
