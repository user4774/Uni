#include <iomanip>
#include "binarytree.h"


BinaryTree::BinaryTree() {
    root = nullptr;
}

void BinaryTree::insert(int data) {
    if (this->root == nullptr) {
        this->root = std::make_shared<Node>(&data);
    } else {
        insert(data, this->root);
    }
}

void BinaryTree::insert(int data, const std::shared_ptr<Node> node) {
    if (data < node->data) {
        if (node->left == nullptr) {
            node->left = std::make_shared<Node>(&data);
        } else {
            insert(data, node->left);
        }
    } else if (data > node->data) {
        if (node->right == nullptr) {
            node->right = std::make_shared<Node>(&data);
        } else {
            insert(data, node->right);
        }
    } else {
        std::cout << "Value already present in tree" << std::endl;
    }
}

/**
 * Method to check weather or not a given node exists in the tree.
 * @param target Target value to find from the tree.
 * @return Boolean value. True if target node is found, false otherwise.
 */
int BinaryTree::find_i(int target) {
    std::shared_ptr<Node> node = this->root;    // Sets node to this trees root.
    if (!node) {
        return -1;
    }
    while (node != nullptr) {                   // Loop while node has value.
        if (node->data == target) {             // Check if node is the one we're looking for.
            return 1;                        // Return true.
        } else if (node->data > target) {       // Check if current node is bigger than target.
            node = node->left;                  // Move to node on the left of current node.
        } else {
            node = node->right;                 // Move to node on the right of current node.
        }
    }
    return 0;                               // Return false.
}

/**
 * Recursively search binary tree for target value.
 * @param target Value to look for in tree
 * @return Boolean value. True if target is in the tree, false otherwise.
 */
int BinaryTree::find_r(int target) {
    if (this->root) {                                       // Check if root exists.
        if (this->_find_r(target, this->root)) {      // Check if _find_r returns true.
            return 1;
        }
        return 0;
    } else {
        return -1;
    }
}

/**
 * Helper method to find_r. Recursively moves through the tree to find target value.
 * @param target Target value to look for in the tree.
 * @param node Shared pointer to a node in the tree.
 * @return Boolean true if value is found, false otherwise.
 */
bool BinaryTree::_find_r(int target, std::shared_ptr<Node> node) {
    if (target > node->data && node->right) {               // Check if target is larger than node and node to the right.
        return this->_find_r(target, node->right);    // Return the result of recursively called _find_r with right node.
    } else if (target < node->data && node->left) {         // Check if target is larger than node and node to the right.
        return this->_find_r(target, node->left);     // Return the result of recursively called _find_r with right node.
    }
    if (target == node->data) {                            // Check if target is the current node.
        return true;
    }
    return false;
}

/**
 * Method to remove target node from the binary tree. Also reorganises the tree after the node removal.
 * @param target Target node to be removed from the tree.
 * @return Returns a boolean value true if target was successfully removed, false otherwise.
 */
bool BinaryTree::remove(int target) {
    if (this->root == nullptr) {        // Check to see if tree has any nodes
        return false;                   // Return false if tree doesn't have a root
    } else if (this->root->data == target) {        // Check if root node is target node
        if (this->root->left == nullptr && this->root->right == nullptr) {      // Check if root has leaf nodes
            this->root = nullptr;       // If leaf nodes don't exist, set root to null
            return true;                // return true if no nodes present
        } else if (this->root->left && this->root->right == nullptr) {      // If only left leaf node exists
            this->root = this->root->right;     // Set first node to the left as new root
            return true;
        } else if (this->root->left == nullptr && this->root->right) {      // If only right leaf node exists
            this->root = this->root->right;     // Set first node to the right as new root
            return true;
        } else if (this->root->left && this->root->right) {     // If both sides have nodes
            leftRight(this->root);                        // Call leftRight helper function to handle
            return true;
        }
    }
    std::shared_ptr<Node> parent = nullptr;     // Set a smart shared pointer as nullptr to parent variable
    std::shared_ptr<Node> node = this->root;    // Set a smart shared pointer to tree root into node variable

    while (node && node->data != target) {      // Loop while there are nodes to look at and target isn't found yet
        parent = node;                          // put node into parent node
        if (target < node->data) {              // Check if target is smaller than current node
            node = node->left;                  // If true, move to left node
        } else if (target > node->data) {       // Check if target is larger than current node
            node = node->right;                 // If true, move to right node
        }
    }
    if (node == nullptr || node->data != target) {      // Check if node doesn't exist or data doesn't equal target
        return false;
    } else if (node->left == nullptr && node->right == nullptr) {       // Check if left and right sides are empty
        if (target < parent->data) {                                    // Check if target is smaller than parent node
            parent->left = nullptr;                                     // Set parent nodes left side to null
        } else {
            parent->right = nullptr;                                    // Set parent nodes right side to null
        }
        return true;
    } else if (node->left && node->right == nullptr) {      // Check if node has only a leaf node on the left
        if (target < parent->data) {                        // Check if target is smaller than parent node
            parent->left = node->left;                      // Set parents left side to the current node's left node
        } else {
            parent->right = node->left;                     // Set parents right side to the current node's left node
        }
    } else if (node->left == nullptr && node->right) {      // Check if node has only a leaf node on the right
        if (target < parent->data) {                        // Check if target is smaller than parent node
            parent->right = node->right;                    // Set parents right side to the current node's right node
        } else {
            parent->left = node->right;                     // Set parents left side to the current node's right node
        }
    } else {
        leftRight(node);                                    // Call leftRight to handle existence of both nodes
        return true;
    }
    return false;
}

/**
 * Helper function to the remove function. Used to resolve a situation where the node to be removed has nodes on
 * both the left and right sides.
 * @param node Node that is being removed.
 */
void BinaryTree::leftRight(std::shared_ptr<Node> node) {
    std::shared_ptr<Node> delNodeParent = node;     // Store node into delNodeParent
    std::shared_ptr<Node> delNode = node->right;    // Store node to the right of current node in delNode

    while (delNode->left) {                         // Loop while there are nodes to the left
        delNodeParent = delNode;                    // Set delNode as new parent node
        delNode = delNode->left;                    // Set delNode's left node as new delNode
    }
    node->data = delNode->data;                     // Change node's data to delNode's data

    if (delNode->right) {                               // Check if there is a node to the right of delNode
        if (delNodeParent->data > delNode->data) {      // Check of delNodeParent is larger than delNode
            delNodeParent->left = delNode->right;       // Set parent node's left node to delNode's right node
        } else {
            delNodeParent->right = delNode->right;  //Set node to right of delNodeParent to the right node of delNode
        }
    } else {
        if (delNode->data < delNodeParent->data) {      // Check of delNode is smaller than delNodeParent
            delNodeParent->left = nullptr;              // Remove node to left of delNodeParent
        } else {
            delNodeParent->right = nullptr;             // Remove node to right of delNodeParent
        }
    }
}
