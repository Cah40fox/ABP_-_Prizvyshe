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
    Node *root;

    Node *insert(Node *root, int data) {
        if (root == nullptr) {
            Node *newNode = new Node();
            newNode->data = data;
            newNode->left = nullptr;
            newNode->right = nullptr;
            return newNode;
        }
        if (data < root->data) {
            root->left = insert(root->left, data);
        } else if (data > root->data) {
            root->right = insert(root->right, data);
        }
        return root;
    }

    Node *minValueNode(Node *node) {
        Node *current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    Node *remove(Node *root, int data) {
        if (root == nullptr) {
            return root;
        }
        if (data < root->data) {
            root->left = remove(root->left, data);
        } else if (data > root->data) {
            root->right = remove(root->right, data);
        } else {
            if (root->left == nullptr && root->right == nullptr) {
                delete root;
                root = nullptr;
            } else if (root->left == nullptr) {
                Node *temp = root;
                root = root->right;
                delete temp;
            } else if (root->right == nullptr) {
                Node *temp = root;
                root = root->left;
                delete temp;
            } else {
                Node *temp = minValueNode(root->right);
                root->data = temp->data;
                root->right = remove(root->right, temp->data);
            }
        }
        return root;
    }

    void printInOrder(Node *root) {
        if (root == nullptr) {
            return;
        }
        printInOrder(root->left);
        cout << root->data << " ";
        printInOrder(root->right);
    }

    void printPreOrder(Node *root) {
        if (root == nullptr) {
            return;
        }
        cout << root->data << " ";
        printPreOrder(root->left);
        printPreOrder(root->right);
    }

    void printPostOrder(Node *root) {
        if (root == nullptr) {
            return;
        }
        printPostOrder(root->left);
        printPostOrder(root->right);
        cout << root->data << " ";
    }

    void printTree(Node *root, int l) {
        int i;
        if (root != nullptr) {
            printTree(((*root).right), l + 1);
            for (i = 1; i <= l; i++) cout << " ";
            cout << (*root).data << endl;
            printTree(((*root).left), l + 1);
        }
    }

public:
    BinarySearchTree() {
        root = nullptr;
    }

    void insert(int data) {
        root = insert(root, data);
    }

    void remove(int data) {
        root = remove(root, data);
    }



    void print() {
        printTree(root, 0);
        cout << endl;
        cout << "Інфіксний обхід:" << endl; //ліве піддерево,
        printInOrder(root);
        cout << endl;
        cout << "Префіксний обхід:" << endl; //корінь, ліве
        printPreOrder(root);
        cout << endl;
        cout << "Постфіксний обхід:" << endl; //ліве піддерево,
        printPostOrder(root);
        cout << endl;
    }

    int getNearestVertex(Node *root, int target) {
        queue<pair<Node *, int>> q;
        q.push(make_pair(root, 0));
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

    void distanceTo(int data) {
        int distance = getNearestVertex(root, data);
        if (distance == -1) {
            cout << "Значення " << data << " не знайдено в дереві." <<
                 endl;
        } else {
            cout << "Найменша довжина шляху до " << data << " це " <<
                 distance << "." << endl;
        }
    }


    int getDepth(Node* root) {
        if (root == nullptr) {
            return -1;
        }

        int leftDepth = getDepth(root->left);
        int rightDepth = getDepth(root->right);
        return max(leftDepth, rightDepth) + 1;
    }
};
int input() {
    int N;
    while (true) {
        if (!(cin >> N) || (cin.peek() != '\n')) {
            cin.clear();
            while (cin.get() != '\n');
            cout << "Помилка! Введіть повторно!" << endl;
            continue;
        }
        return N;
    }
}

int main() {
    int choice;
    int data;
    BinarySearchTree tree;
    while (true) {
        cout << "1 - Додати елементи\n"
                "2 - Вилучити елементи\n"
                "3 - Вивід дерева\n"
                "4 - Пошук по дереву\n"
                "5 - Глибина дерева\n";
        choice = input();
        switch (choice) {
            default:
                cout << "Задачі не існує" << endl;
                break;
            case 0:
                exit(0);
            case 1:
                cout << "Вводьте значення:" << endl;
                while (true){
                    data = input();
                    if (data == 0) break;
                    tree.insert(data);
                }
                break;
            case 2:
                cout << "Значення для видалення:" << endl;
                data = input();
                tree.remove(data);
                break;
            case 3:
                cout << "print" << endl;
                tree.print();
                break;
            case 4:
                cout << "Введіть значення для пошуку:";
                data = input();
                tree.distanceTo(data);
                break;
            case 5:
                tree.depth();
        }
    }
}
