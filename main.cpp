#include <iostream>
#include <vector>
#include <regex>

using namespace std;

struct Node
{
    string name;
    int id;
    int height = 1;
    Node* left;
    Node* right;
    Node(string _name, int _id) : name(_name), id(_id), left(nullptr), right(nullptr) {};
};

class AVLTree {
private:
    Node* head;
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    Node* rotateLeftRight(Node* node);
    Node* rotateRightLeft(Node* node);
    int balanceFactor(Node* node);
    Node* searchIDHelper(int id, Node* node);
    void searchNameHelper(string name, Node* node, vector<Node*>& nodes);
    Node* insertHelper(Node *root, string name, int id);
    void inorder(Node* node,vector<Node*>& nodes);
public:
    void insert(string name, string id);
    Node* remove(Node* root, int id);
    void searchID(int id);
    void searchName(string name);
    void printInorder(Node* node);
    void printPreorder(Node* node);
    void printPostorder(Node* node);
    int printLevelCount();
    void removeInorder(int n);
    Node* getHead() { return head; };
    AVLTree() : head(nullptr) {};
    //TODO: CREATE DESTRUCTOR, MEMORY MANAGEMENT
};

Node* AVLTree::rotateLeft(Node *node)
{
    Node* grandchild = node->right->left;
    Node* root = node->right;
    root->left = node;
    node->height -= 2;
    node->right = grandchild;
    return root;
}

Node* AVLTree::rotateRight(Node *node)
{
    Node* grandchild = node->left->right;
    Node* root = node->left;
    root->right = node;
    node->height -= 2;
    node->left = grandchild;
    return root;
}

Node* AVLTree::rotateRightLeft(Node *node)
{
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

Node* AVLTree::rotateLeftRight(Node* node)
{
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

int AVLTree::balanceFactor (Node* root) {
    if (root == nullptr) return 0;

    if (root->left == nullptr) {
        if (root->right == nullptr) {
            return 0;
        } else {
            return -1*root->right->height;
        }
    } else if (root->right == nullptr) {
        return root->left->height;
    } else {
        return root->left->height - root->right->height;
    }
}

Node* AVLTree::insertHelper(Node* root, string name, int id) {
    if (root == nullptr) {
        cout << "successful" << endl;
        return new Node(name,id);
    } else if (id == root->id) {
        cout << "unsuccessful" << endl;
        return root;
    } else if (id < root->id) {
        root->left = insertHelper(root->left,name,id);
    } else {
        root->right = insertHelper(root->right,name,id);
    }
    if (root->right == nullptr ^ root->left == nullptr) {
        root->height++;
    } else {
        root->height = 1 + max(root->left->height, root->right->height);
    }
    if (balanceFactor(root) < -1) {
        if (balanceFactor(root->right) > 0) {
            root = rotateRightLeft(root);
        } else {
            root = rotateLeft(root);
        }
    } else if (balanceFactor(root) > 1) {
        if (balanceFactor(root->left) < 0) {
            root = rotateLeftRight(root);
        } else {
            root = rotateRight(root);
        }
    }
    return root;
}

void AVLTree::insert(string name, string id)
{
    name = name.substr(1,name.size()-2);
    if (!regex_search(name,regex("^[A-Za-z\\s]+$"))
        || !regex_search(id,regex("^\\d+$"))) {
        cout << "unsuccessful" << endl;
        return;
    }
    head = insertHelper(head,name,stoi(id));
}

Node* AVLTree::remove(Node* root, int id)
{
    if (searchIDHelper(id,root)==nullptr) {
        cout << "unsuccessful" << endl;
        return root;
    }
    if (root == nullptr) {
        return root;
    } else if (id < root->id) {
        root->left = remove(root->left,id);
    } else if (id > root->id) {
        root->right = remove(root->right,id);
    } else {
        if (root->left == nullptr && root->right == nullptr) {
            return nullptr;
        } else if (root->left == nullptr) {
            Node* right = root->right;
            delete root;
            return right;
        } else if (root->right == nullptr) {
            Node* left = root->left;
            delete root;
            return left;
        }

        Node* inorderSuccessor = root->right;
        while (inorderSuccessor->left != nullptr) {
            inorderSuccessor = inorderSuccessor->left;
        }
        root->id = inorderSuccessor->id;
        root->name = inorderSuccessor->name;
        root->right = remove(root->right,inorderSuccessor->id);
    }
    cout << "successful" << endl;
    return root;
}

Node* AVLTree::searchIDHelper(int id, Node* node)
{
    if (node != nullptr) {
        if (id == node->id) {
            return node;
        } else if (id < node->id) {
            return searchIDHelper(id,node->left);
        } else {
            return searchIDHelper(id,node->right);
        }
    } else {
        return nullptr;
    }
}

void AVLTree::searchID(int id)
{
    Node* searchNode = searchIDHelper(id, head);
    if (searchNode == nullptr) {
        cout << "unsuccessful" << endl;
    } else {
        cout << searchNode->name << endl;
    }
}

void AVLTree::searchNameHelper(string name, Node *node, vector<Node*>& nodes)
{
    if (node != nullptr) {
        if (node->name == name) {
            nodes.push_back(node);
        }
        searchNameHelper(name,node->left,nodes);
        searchNameHelper(name,node->right,nodes);
    }
}

void AVLTree::searchName(string name)
{
    vector<Node*> nameNodes;
    searchNameHelper(name.substr(1,name.size()-2),head,nameNodes);
    if (nameNodes.size() == 0) {
        cout << "unsuccessful" << endl;
    } else {
        for (int i=0; i<nameNodes.size(); i++) {
            cout << nameNodes[i]->id << endl;
        }
    }
}

void AVLTree::printInorder(Node* node)
{
    if (node != nullptr) {
        printInorder(node->left);
        if (node->left) cout << ", ";
        cout << node->name;
        if (node->right) cout << ", ";
        printInorder(node->right);
    }
}

void AVLTree::printPreorder(Node* node)
{
    if (node != nullptr) {
        cout << node->name;
        if (node->left || node->right) cout << ", ";
        printPreorder(node->left);
        if (node->left && node->right) cout << ", ";
        printPreorder(node->right);
    }
}

void AVLTree::printPostorder(Node* node)
{
    if (node != nullptr) {
        printPostorder(node->left);
        if (node->left || node->right) cout << ", ";
        printPostorder(node->right);
        if (node->left && node->right) cout << ", ";
        cout << node->name;
    }
}

int AVLTree::printLevelCount()
{
    int levelCount = (head == nullptr ? 0 : head->height);
    cout << levelCount << endl;
    return levelCount;
}

void AVLTree::inorder(Node* node, vector<Node*>& nodes) {
    if (node != nullptr) {
        inorder(node->left,nodes);
        nodes.push_back(node);
        inorder(node->right,nodes);
    }
}

void AVLTree::removeInorder(int n)
{
    vector<Node*> nodeList;
    inorder(head,nodeList);
    head = remove(head,nodeList[n]->id);
}


int main()
{
    AVLTree tree;
    int numArgs;
    cin >> numArgs;
    for (int i=0; i<numArgs; i++) {
        string command, strArg1, strArg2;
        int intArg;
        cin >> command;
        if (command=="insert"){
            cin >> strArg1;
            cin >> strArg2;
            tree.insert(strArg1,strArg2);
        } else if (command=="remove"){
            cin >> intArg;
            tree.remove(tree.getHead(),intArg);
        } else if (command=="search"){
            cin >> strArg1;
            bool isID = true;
            for (char c : strArg1) {
                if (isdigit(c)==0) {
                    isID = false;
                    break;
                }
            }
            isID ? tree.searchID(stoi(strArg1)) : tree.searchName(strArg1);
        } else if (command=="printInorder"){
            tree.printInorder(tree.getHead());
            cout << endl;
        } else if (command=="printPreorder"){
            tree.printPreorder(tree.getHead());
            cout << endl;
        } else if (command=="printPostorder"){
            tree.printPostorder(tree.getHead());
            cout << endl;
        } else if (command=="printLevelCount"){
            tree.printLevelCount();
        } else if (command=="removeInorder"){
            cin >> intArg;
            tree.removeInorder(intArg);
        }
    }
}
