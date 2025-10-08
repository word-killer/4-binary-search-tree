using namespace std;

template <class T>
class BinarySearchTree {
public:
    struct Node {
        Node* Left;
        Node* Right;
        T Value;
    };

private:
    Node* root;

    void deleteTree(Node* node) {
        if (node) {
            deleteTree(node->Left);
            deleteTree(node->Right);
            delete node;
        }
    }

public:
    BinarySearchTree() : root(nullptr) {}

    ~BinarySearchTree() {
        deleteTree(root);
    }

    void Add(const T& value) {
        Node* newNode = new Node{nullptr, nullptr, value};
        
        if (!root) {
            root = newNode;
            return;
        }
        
        Node* curr = root;
        while (true) {
            if (value < curr->Value) {
                if (!curr->Left) {
                    curr->Left = newNode;
                    return;
                }
                curr = curr->Left;
            } else {
                if (!curr->Right) {
                    curr->Right = newNode;
                    return;
                }
                curr = curr->Right;
            }
        }
    }

    Node* Find(const T& value) {
        Node* curr = root;
        while (curr) {
            if (value == curr->Value) return curr;
            if (value < curr->Value) curr = curr->Left;
            else curr = curr->Right;
        }
        return nullptr;
    }

    void Remove(Node* node) {
        if (!node) return;
        
        Node* parent = nullptr;
        Node* curr = root;
        while (curr && curr != node) {
            parent = curr;
            if (node->Value < curr->Value) curr = curr->Left;
            else curr = curr->Right;
        }
        
        if (node->Left && node->Right) {
            Node* minParent = node;
            Node* min = node->Right;
            while (min->Left) {
                minParent = min;
                min = min->Left;
            }
            node->Value = min->Value;
            node = min;
            parent = minParent;
        }
        
        Node* child = node->Left ? node->Left : node->Right;
        
        if (!parent) root = child;
        else if (parent->Left == node) parent->Left = child;
        else parent->Right = child;
        
        delete node;
    }
    
    // задание 2 - метод для поперечного обхода (inorder)
    void inorderTraversal(Node* node) {
        if (!node) return;
        inorderTraversal(node->Left);
        cout << node->Value << " ";
        inorderTraversal(node->Right);
    }

    // задание 3 - кастомный метод для подсчета узлов на каждом уровне
    vector<T> countNodesPerLevel() {
        vector<T> result;
        if (!root) return result;

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size(); 
            result.push_back(levelSize);

            for (int i=0; i<levelSize; i++) {
                Node* current = q.front();
                q.pop();
                if (current->Left) q.push(current->Left);
                if (current->Right) q.push(current->Right);
            }
        }

        return result;
    }
};
