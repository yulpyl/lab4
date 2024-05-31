#include <iostream>
using namespace std;

struct TreeNode {
    int value;
    TreeNode* children[10]; 
    int child_count;
};

TreeNode* createNode(int value) {
    TreeNode* newNode = new TreeNode;
    newNode->value = value;
    newNode->child_count = 0;
    for (int i = 0; i < 10; i++) {
        newNode->children[i] = nullptr;
    }
    return newNode;
}

void addChild(TreeNode* parent, int value) {
    if (parent->child_count < 10) {
        parent->children[parent->child_count] = createNode(value);
        parent->child_count++;
    }
    else {
        cout << "Node can't have more than 10 children" << endl;
    }
}

TreeNode* getNodeByPath(TreeNode* root, int path[], int path_len) {
    TreeNode* node = root;
    for (int i = 0; i < path_len; i++) {
        int index = path[i];
        if (index < node->child_count) {
            node = node->children[index];
        }
        else {
            return nullptr;
        }
    }
    return node;
}

void addNodeByPath(TreeNode* root, int path[], int path_len, int value) {
    TreeNode* parent = getNodeByPath(root, path, path_len);
    if (parent != nullptr) {
        addChild(parent, value);
    }
}

void printTreeBrackets(TreeNode* node) {
    cout << node->value;
    if (node->child_count > 0) {
        cout << "(";
        for (int i = 0; i < node->child_count; i++) {
            printTreeBrackets(node->children[i]);
            if (i < node->child_count - 1) {
                cout << ", ";
            }
        }
        cout << ")";
    }
}

TreeNode* removeNodeByPath(TreeNode* root, int path[], int path_len) {
    if (path_len == 0) return nullptr;
    TreeNode* parent = getNodeByPath(root, path, path_len - 1);
    if (parent != nullptr) {
        int index = path[path_len - 1];
        if (index < parent->child_count) {
            TreeNode* removedNode = parent->children[index];
            for (int i = index; i < parent->child_count - 1; i++) {
                parent->children[i] = parent->children[i + 1];
            }
            parent->children[parent->child_count - 1] = nullptr;
            parent->child_count--;
            return removedNode;
        }
    }
    return nullptr;
}

struct BinaryTreeNode {
    int value;
    BinaryTreeNode* left;
    BinaryTreeNode* right;
};

BinaryTreeNode* createBinaryNode(int value) {
    BinaryTreeNode* newNode = new BinaryTreeNode;
    newNode->value = value;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

void addBinaryNode(BinaryTreeNode*& root, int value) {
    if (root == nullptr) {
        root = createBinaryNode(value);
    }
    else if (value < root->value) {
        addBinaryNode(root->left, value);
    }
    else {
        addBinaryNode(root->right, value);
    }
}

void printBinaryTree(BinaryTreeNode* node) {
    if (node == nullptr) return;
    cout << node->value;
    if (node->left || node->right) {
        cout << "(";
        if (node->left) {
            printBinaryTree(node->left);
        }
        if (node->right) {
            if (node->left) cout << ", ";
            printBinaryTree(node->right);
        }
        cout << ")";
    }
}

void interactiveMode(TreeNode*& root) {
    int choice, value, path_len;
    int path[10];
    while (true) {
        cout << "1. Add node\n2. Print tree\n3. Remove node\n4. Exit\nEnter choice: ";
        cin >> choice;
        if (choice == 1) {
            cout << "Enter value to add: ";
            cin >> value;
            cout << "Enter path length: ";
            cin >> path_len;
            cout << "Enter path (space separated indices): ";
            for (int i = 0; i < path_len; i++) {
                cin >> path[i];
            }
            addNodeByPath(root, path, path_len, value);
        }
        else if (choice == 2) {
            printTreeBrackets(root);
            cout << endl;
        }
        else if (choice == 3) {
            cout << "Enter path length: ";
            cin >> path_len;
            cout << "Enter path (space separated indices): ";
            for (int i = 0; i < path_len; i++) {
                cin >> path[i];
            }
            TreeNode* removedNode = removeNodeByPath(root, path, path_len);
            if (removedNode) {
                cout << "Removed node with value: " << removedNode->value << endl;
                delete removedNode;
            }
            else {
                cout << "Node not found " << endl;
            }
        }
        else if (choice == 4) {
            break;
        }
        else {
            cout << "Invalid choice. Try again " << endl;
        }
    }
}

void demoMode(TreeNode*& root) {
    cout << "Demonstrating Mode: Adding nodes 4 and 5 to the first child of root (value 2)" << endl;
    int path1[] = { 0 };
    addNodeByPath(root, path1, 1, 4);
    addNodeByPath(root, path1, 1, 5);
    cout << "Tree after adding nodes 4 and 5: ";
    printTreeBrackets(root);
    cout << endl;

    cout << "Adding node 6 to the second child of root (value 3)" << endl;
    int path2[] = { 1 };
    addNodeByPath(root, path2, 1, 6);
    cout << "Tree after adding node 6: ";
    printTreeBrackets(root);
    cout << endl;

    cout << "Deleting first child of root (value 2)" << endl;
    removeNodeByPath(root, path1, 1);
    cout << "Tree after deleting: ";
    printTreeBrackets(root);
    cout << endl;
}

void binaryInteractiveMode(BinaryTreeNode*& root) {
    int choice, value;
    while (true) {
        cout << "1. Add node\n2. Print binary tree\n3. Remove node\n4. Exit\nEnter choice: ";
        cin >> choice;
        if (choice == 1) {
            cout << "Enter value to add: ";
            cin >> value;
            addBinaryNode(root, value);
        }
        else if (choice == 2) {
            printBinaryTree(root);
            cout << endl;
        }
        else if (choice == 3) {
            break;
        }
        else {
            cout << "Invalid choice. Try again " << endl;
        }
    }
}

void binaryDemoMode(BinaryTreeNode*& root) {
    cout << "Demonsration mode: adding nodes 4, 2, 6, 1, 3, 5, 7 to the binary tree" << endl;
    addBinaryNode(root, 4);
    addBinaryNode(root, 2);
    addBinaryNode(root, 6);
    addBinaryNode(root, 1);
    addBinaryNode(root, 3);
    addBinaryNode(root, 5);
    addBinaryNode(root, 7);
    cout << "Binary tree after adding nodes: ";
    printBinaryTree(root);
    cout << endl;
}

int main() {
    TreeNode* root = createNode(1);
    addChild(root, 2);
    addChild(root, 3);
    int mode;
    cout << "Enter mode for the multiple tree:\n1. Interactive\n2. Demonstration\nEnter choice: ";
    cin >> mode;
    if (mode == 1) {
        interactiveMode(root);
    }
    else if (mode == 2) {
        demoMode(root);
    }
    else {
        cout << "Incorrect mode" << endl;
    }

    BinaryTreeNode* binaryRoot = nullptr;
    cout << "Enter mode for the binary tree:\n1. Interactive\n2. Demonstration\nEnter choice: ";
    cin >> mode;
    if (mode == 1) {
        binaryInteractiveMode(binaryRoot);
    }
    else if (mode == 2) {
        binaryDemoMode(binaryRoot);
    }
    else {
        cout << "Incorrect mode " << endl;
    }
    return 0;
}
