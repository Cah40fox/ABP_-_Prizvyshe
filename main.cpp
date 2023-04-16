#include <iostream>
#include <queue>

using namespace std;


class BinarySearchTree {
private:
    struct Node {
        int data;
        Node* left;
        Node* right;
    };
    Node *origin;

    Node *paste(Node *origin, int data) {
        if (origin == nullptr) {
            Node *newNode = new Node();
            newNode->data = data;
            newNode->left = nullptr;
            newNode->right = nullptr;
            return newNode;
        }
        if (data < origin->data) {
            origin->left = paste(origin->left, data);
        } else if (data > origin->data) {
            origin->right = paste(origin->right, data);
        }
        return origin;
    }
    Node *remove(Node *origin, int data) {
        if (origin == nullptr) {
            return origin;
        }
        if (data < origin->data) {
            origin->left = remove(origin->left, data);
        } else if (data > origin->data) {
            origin->right = remove(origin->right, data);
        } else {
            if (origin->left == nullptr && origin->right == nullptr) {
                delete origin;
                origin = nullptr;
            } else if (origin->left == nullptr) {
                Node *prov = origin ;
                origin = origin->right;
                delete prov;
            } else if (origin->right == nullptr) {
                Node *prov = origin;
                origin = origin->left;
                delete prov;
            } else {
                Node *prov = minValueNode(origin->right);
                origin->data = prov->data;
                origin->right = remove(origin->right, prov->data);
            }
        }
        return origin;
    }

    Node *minValueNode(Node *node) {
        Node *current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    void printInOrder(Node *origin) {
        if (origin == nullptr) {
            return;
        }
        printInOrder(origin->left);
        cout << origin->data << " ";
        printInOrder(origin->right);
    }

    void printPreOrder(Node *origin) {
        if (origin == nullptr) {
            return;
        }
        cout << origin->data << " ";
        printPreOrder(origin->left);
        printPreOrder(origin->right);
    }

    void printPostOrder(Node *origin) {
        if (origin == nullptr) {
            return;
        }
        printPostOrder(origin->left);
        printPostOrder(origin->right);
        cout << origin->data << " ";
    }

    void outputTree(Node *origin, int x) {
        int i;
        if (origin != nullptr) {
            outputTree(((*origin).right), x + 1);
            for (i = 1; i <= x; i++) cout << " ";
            cout << (*origin).data << endl;
            outputTree(((*origin).left), x + 1);
        }
    }

public:
    BinarySearchTree() {
        origin = nullptr;
    }

    void paste(int data) {
        origin = paste(origin, data);
    }

    void remove(int data) {
        origin = remove(origin, data);
    }



    void print() {
        outputTree(origin, 0);
        cout << endl;
        cout << "Infix traversal:" << endl;
        printInOrder(origin);
        cout << endl;
        cout << "Prefix traversal:" << endl;
        printPreOrder(origin);
        cout << endl;
        cout << "Post-fix traversal:" << endl;
        printPostOrder(origin);
        cout << endl;
    }

    int getNearestVertex(Node *origin, int target) {
        queue<pair<Node *, int>> q;
        q.push(make_pair(origin, 0));
        while (!q.empty()) {
            Node *current = q.front().first;
            int currentDepth = q.front().second;
            q.pop();
            if (current->data == target) {
                return currentDepth;
            }
            if (current->left != nullptr) {
                q.push(make_pair(current->left, currentDepth + 1));
            }
            if (current->right != nullptr) {
                q.push(make_pair(current->right, currentDepth + 1));
            }
        }
        return -1;
    }

    void range(int data) {
        int distance = getNearestVertex(origin, data);
        if (distance == -1) {
            cout << "Value " << data << " did'not find in tree." <<
                 endl;
        } else {
            cout << "The shortest path length to " << data << " it's " <<
                 distance << "." << endl;
        }
    }


    int depth_helper(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        int left_depth = depth_helper(node->left);
        int right_depth = depth_helper(node->right);
        return (left_depth > right_depth ? left_depth : right_depth) + 1;
    }

    int depth() {
        if (origin == nullptr) {
            return 0;
        }
        return depth_helper(origin);
    }
};
int input() {
    int I;
    while (true) {
        if (!(cin >> I) || (cin.peek() != '\n')) {
            cin.clear();
            while (cin.get() != '\n');
            cout << "Try again!" << endl;
            continue;
        }
        return I;
    }
}

int main() {
    int choice;
    int data;
    BinarySearchTree tree;
    while (true) {
        cout << "1 - Add elements\n"
                "2 - Remove elements\n"
                "3 - Print  tree\n"
                "4 - Search by tree\n"
                "5 - Depth of the tree\n";
        choice = input();
        switch (choice) {
            default:
                cout << "The task doesn't exist" << endl;
                break;
            case 0:
                exit(0);
            case 1:
                cout << "Enter the value:" << endl;
                while (true){
                    data = input();
                    if (data == 0) break;
                    tree.paste(data);
                }
                break;
            case 2:
                cout << "What number to delete:" << endl;
                data = input();
                tree.remove(data);
                break;
            case 3:
                cout << " output " << endl;
                tree.print();
                break;
            case 4:
                cout << "Enter a value to search for:";
                data = input();
                tree.range(data);
                break;
            case 5:
                int tree_depth = depth(tree.get_origin());
                std::cout << "Depth of the tree is: " << tree_depth << std::endl;
        }
    }
}
