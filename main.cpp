
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <stack>

class HashTable {

private:
    std::pair<std::string, std::string>* arr;
    size_t cap;

    int hash(const std::string& str) {
        int sum = 0;
        for (char i : str) {
            sum += i;
        }

        int hash = sum % cap;
        if (hash < 0) hash *= -1;


        return hash;

    }

public:
    HashTable(size_t size) {
        arr = new std::pair<std::string, std::string>[size];
        cap = size;
        for (int i = 0; i < size; i++) {
            arr[i].first = "\0";
            arr[i].second = "\0";
        }

    }

    size_t size() {
        return cap;
    }

    struct Map_Val {
        std::pair<std::string, std::string>* arr;
        //ключ значение

        std::string key;
        int hash;
        int sz;

        Map_Val(int hashh, const std::string& k, std::pair<std::string, std::string>* l, int size) : hash(hashh), key(k), arr(l), sz(size) {
        }

        std::string value() {
            if (arr[hash].first == key) {
                return arr[hash].second;
            }

            for (int i = 0; i < sz; i++) {
                if (arr[i].first == key) {
                    return arr[i].second;
                }
            }

            std::string a = "\0";
            return a;

        }


        std::string& operator= (const std::string& val) {
            //если ячейка пуста или элемент с таким ключом
            if ((arr[hash].first == "\0") || (arr[hash].first == key)) {
                arr[hash].first = key;
                arr[hash].second = val;
                return arr[hash].second;
            }

            //Если ячейка занята или найден элемент с таким ключом
            for (int i = 0; i < sz; i++) {
                if ((arr[i].first == "\0") || (arr[i].first == key)) {
                    arr[i].first = key;
                    arr[i].second = val;
                    return arr[i].second;
                }
            }


        }

    };

    Map_Val operator[](const std::string& key) {
        return Map_Val(hash(key), key, arr, cap);
    }


    std::pair<std::string, std::string>* get_data() {
        return arr;
    }

    ~HashTable() {
        delete[] arr;
    }


};

int main(){
    std::cout << "lab13" << std::endl;
    std::ifstream f;
    f.open("example.txt");
    if (f.is_open()) {
        int len_of_words = 0;
        std::string str;
        std::vector<std::string> words;
        while (!f.eof()) {
            f >> str;
            words.push_back(str);
        }
        HashTable h_table(words.size() * 2);
        for (auto& word : words) {

            switch (word.back())
            {
            case '.':
                h_table["."] = ".";
                word.pop_back();
                break;
            case ',':
                h_table[","] = ",";
                word.pop_back();
                break;
            case ';':
                h_table[";"] = ";";
                word.pop_back();
                break;
            case ':':
                h_table[":"] = ":";
                word.pop_back();
                break;
            case '?':
                h_table["?"] = "?";
                word.pop_back();
                break;
            case '!':
                h_table["!"] = "!";
                word.pop_back();
                break;
            }
            h_table[word] = word;
        }
        std::cout << h_table["keep"].value() << std::endl;
        std::ofstream out;
        out.open("table.txt");
        for (int i = 0; i < h_table.size(); i++) {
            out << i << " : \"" << h_table.get_data()[i].second << "\"" << std::endl;
        }
        out.close();
    }
    f.close();
    return 0;
}


/*
#include <iostream>
#include <fstream>
#include <vector>

using std::cout;
using std::string;
using std::endl;
using std::vector;
using std::pair;

class HashTableWithLists {
public:

    HashTableWithLists(int size) : sz(size) {
        arr = new vector<pair<string, string>>[size];
    }
    HashTableWithLists(const HashTableWithLists& table) {
        sz = table.sz;
        arr = new vector<pair<string, string>>[sz];
        memcpy(arr, table.arr, sizeof(arr));
    }
    ~HashTableWithLists() {
        delete[] arr;
    }

    int size() {
        return sz;
    }

    vector<pair<string, string>>* data() {
        return arr;
    }

    string& operator [](const string& key) {
        for (auto& el : arr[hash(key)]) {
            if (el.first == key) return el.second;
        }

        arr[hash(key)].push_back({ key, "\0" });

        return arr[hash(key)].back().second;
    }

private:
    int hash(const string& str) {
        int hash = 0;
        for (char i : str) {
            hash += i;
        }
        if (hash < 0) hash *= -1;
        hash %= sz;
        return hash;
    }

    vector<pair<string, string>>* arr;
    int sz;
};

int main(){
    setlocale(LC_ALL, "RUS");
    cout << "lab14" << endl;
    std::ifstream f;
    f.open("example.txt");

    if (f.is_open()) {
        int len_of_words = 0;
        string str;
        vector<string> words;
        while (!f.eof()) {
            f >> str;
            words.push_back(str);
        }

        HashTableWithLists h_table(words.size() * 2);

        for (auto& word : words) {

            switch (word.back())
            {
            case '.':
                h_table["."] = ".";
                word.pop_back();
                break;
            case ',':
                h_table[","] = ",";
                word.pop_back();
                break;
            case ';':
                h_table[";"] = ";";
                word.pop_back();
                break;
            case ':':
                h_table[":"] = ":";
                word.pop_back();
                break;
            case '?':
                h_table["?"] = "?";
                word.pop_back();
                break;
            case '!':
                h_table["!"] = "!";
                word.pop_back();
                break;
            }
            h_table[word] = word;
        }
        h_table["keep"] = "Hello World!";


        std::ofstream out;
        out.open("table.txt");
        for (int i = 0; i < h_table.size(); i++) {
            out << i << " : { ";
            for (int j = 0; j < h_table.data()[i].size(); j++) {
                out << "\"" << h_table.data()[i][j].second << "\" ";
            }
            out << "}\n";
        }

        out.close();


    }

    f.close();

}
*/
/*
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <string>

using std::string;
using std::cin;
using std::cout;
using std::endl;

namespace BTree {

    struct Node {
        Node* left = nullptr;
        Node* right = nullptr;
        int value;
        Node(int val = NULL) : value(val) {}
    };

    class BinaryTree {
    public:
        BinaryTree(int value = NULL);
        BinaryTree(const BinaryTree& tree);
        ~BinaryTree();

        void init_with_string(const string& line);

        void  _insert(int value);
        Node* _search(int value);
        void  _delete(int value);

        //Обходы https://i.ytimg.com/vi/WLvU5EQVZqY/maxresdefault.jpg
        void preorder_traversal();
        void inorder_traversal();
        void postorder_traversal();
        void stack_preorder_travelsal();

        void print_node(Node* node);
        void print();

    private:
        void copy(Node* dest, Node* src);

        void preorder_traversal(Node* node);
        void inorder_traversal(Node* node);
        void postorder_traversal(Node* node);
        void stack_preorder_travelsal(Node* node);

        Node* get_min(Node* node);
        void  _insert(Node* node, int value);
        Node* _search(Node* node, int value);
        Node* _delete(Node* node, int value);

        bool is_digit(char c);
        void print_node(const std::wstring& prefix, const Node* node, bool isLeft);
        void clear_node(Node* node);

        Node* root;
    };
}

BTree::BinaryTree::BinaryTree(int value)
{
    root = new Node(value);
}

BTree::BinaryTree::BinaryTree(const BinaryTree& tree)
{
    root = new Node();
    copy(root, tree.root);
}

BTree::BinaryTree::~BinaryTree()
{
    clear_node(root);
}

void BTree::BinaryTree::_insert(int value)
{
    _insert(root, value);
}

BTree::Node* BTree::BinaryTree::_search(int value)
{
    return _search(root, value);
}

void BTree::BinaryTree::_delete(int value)
{
    root = _delete(root, value);
    if (root == nullptr) root = new Node();
    return;
}

void BTree::BinaryTree::preorder_traversal()
{
    preorder_traversal(root);
}

void BTree::BinaryTree::inorder_traversal()
{
    inorder_traversal(root);
}

void BTree::BinaryTree::postorder_traversal()
{
    postorder_traversal(root);
}

void BTree::BinaryTree::stack_preorder_travelsal()
{
    stack_preorder_travelsal(root);
}

void BTree::BinaryTree::init_with_string(const string& line)
{
    string number;
    std::vector<int> numbers;
    bool num_read = false;
    for (char c : line) {
        if ((c == '-') || (is_digit(c))) {
            number += c;
            num_read = true;
        }
        else {
            if (num_read) {
                num_read = false;
                numbers.push_back(atoi(number.c_str()));
                number.clear();
            }

        }
    }

    if (!number.empty()) {
        numbers.push_back(atoi(number.c_str()));
    }

    for (auto num : numbers) {
        _insert(root, num);
    }
}

void BTree::BinaryTree::print_node(Node* node)
{
    std::wcout << L"Дерево" << endl;
    print_node(L"", node, false);
}

void BTree::BinaryTree::print()
{
    print_node(root);
}

void BTree::BinaryTree::copy(Node* dest, Node* src)
{
    _insert(dest, src->value);
    if (src->left != nullptr) copy(dest, src->left);
    if (src->right != nullptr) copy(dest, src->right);
}

void BTree::BinaryTree::preorder_traversal(Node* node)
{
    if (node == nullptr) return;
    cout << node->value << " ";
    preorder_traversal(node->left);
    preorder_traversal(node->right);
}

void BTree::BinaryTree::inorder_traversal(Node* node)
{
    if (node == nullptr) return;
    inorder_traversal(node->left);
    cout << node->value << " ";
    inorder_traversal(node->right);
}

void BTree::BinaryTree::postorder_traversal(Node* node)
{
    if (node == nullptr) return;
    postorder_traversal(node->left);
    postorder_traversal(node->right);
    cout << node->value << " ";
}

void BTree::BinaryTree::stack_preorder_travelsal(Node* node)
{
    Node* temp = node;
    std::stack<Node*> nodes;
    while ((temp != nullptr) || (!nodes.empty())) {
        if (!nodes.empty()) {
            temp = nodes.top();
            nodes.pop();
        }

        while (temp != nullptr) {
            cout << temp->value << " ";

            if (temp->right != nullptr) {
                nodes.push(temp->right);
            }

            temp = temp->left;
        }
    }
}

BTree::Node* BTree::BinaryTree::get_min(Node* node)
{
    if (node == nullptr) return node;
    if (node->left == nullptr) return node;
    return get_min(node->left);
}

void BTree::BinaryTree::_insert(Node* node, int value)
{
    if (node->value == NULL) {
        node->value = value;
        return;
    }

    if (value < node->value) {
        if (node->left == nullptr) {
            node->left = new Node(value);
        }
        else _insert(node->left, value);
    }
    else if (value > node->value) {
        if (node->right == nullptr) {
            node->right = new Node(value);
        }
        else _insert(node->right, value);
    }
    else if (value == node->value) return;
}

BTree::Node* BTree::BinaryTree::_search(Node* node, int value)
{
    if (node == nullptr) return node;

    if (node->value == value) return node;

    if (value < node->value) {
        return _search(node->left, value);
    }
    else {
        return _search(node->right, value);
    }
}

BTree::Node* BTree::BinaryTree::_delete(Node* node, int value)
{
    if (node == nullptr) return node;

    else if (value < node->value) {
        node->left = _delete(node->left, value);
    }
    else if (value > node->value) {
        node->right = _delete(node->right, value);
    }
    else {
        if ((node->left == nullptr) || (node->right == nullptr)) {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else {
                Node* temp = node->left;
                delete node;
                return temp;
            }
        }
        else {
            Node* min_right = get_min(node->right);
            node->value = min_right->value;
            node->right = _delete(node->right, min_right->value);
            return node;
        }
    }


}

bool BTree::BinaryTree::is_digit(char c)
{
    return (c >= 48) && (c <= 57);
}

void BTree::BinaryTree::print_node(const std::wstring& prefix, const Node* node, bool isLeft)
{
    if (node != nullptr)
    {
        std::wcout << prefix;

        std::wcout << (isLeft ? L"│L " : L"│R ");

        std::cout << node->value << std::endl;
        print_node(prefix + (isLeft ? L"│  " : L"   "), node->left, true);
        print_node(prefix + (isLeft ? L"│  " : L"   "), node->right, false);
    }
}

void BTree::BinaryTree::clear_node(Node* node)
{
    if (node->left != nullptr)   clear_node(node->left);
    if (node->right != nullptr)  clear_node(node->right);
    if (node != nullptr) delete node;
}


void write_cmds() {
    cout << "Выберете действие" << endl;
    cout << "[1] Добавить" << endl;
    cout << "[2] Удалить" << endl;
    cout << "[3] Поиск" << endl;
    cout << "[4] Прямой обход" << endl;
    cout << "[5] Центрированный обход" << endl;
    cout << "[2] Концевой обход" << endl;
    cout << "[7] Нерекурсивный прямой обход" << endl;
    cout << "[8] Выйти" << endl;
}

int main()
{
    std::setlocale(LC_ALL, "RUS");
    BTree::BinaryTree tree;
    tree.init_with_string("8 (3 (1, 6(4,7)), 10 (, 14(13,)))");

    tree.print();
    write_cmds();

    string a;
    cin >> a;

    while (true) {
        int num;
        switch (a[0])
        {
        case '1':
            system("cls");
            tree.print();
            cout << "[1] Добавить" << endl;
            cout << "Введите значение: ";
            cin >> num;
            tree._insert(num);
            system("cls");
            break;
        case '2':
            system("cls");
            tree.print();
            cout << "[2] Удалить" << endl;
            cout << "Введите значение: ";
            cin >> num;
            tree._delete(num);
            system("cls");
            break;
        case '3': {
            system("cls");
            cout << "[3] Поиск" << endl;
            cout << "Введите значение: ";
            cin >> num;
            BTree::Node* sub_tree = tree._search(num);

            if (sub_tree == nullptr) {
                cout << "Результат: Не найдено" << endl;
            }
            else {
                cout << "Результат:" << endl;
                tree.print_node(sub_tree);
            }
            cout << "\n\n";
            break;
        }
        case '4':
            system("cls");
            cout << "[4] Прямой обход: ";
            tree.preorder_traversal();
            cout << "\n\n";
            break;
        case '5':
            system("cls");
            cout << "[5] Центрированный обход: ";
            tree.inorder_traversal();
            cout << "\n\n";
            break;
        case '6':
            system("cls");
            cout << "[6]Концевой обход: ";
            tree.postorder_traversal();
            cout << "\n\n";
            break;
        case '7':
            system("cls");
            cout << "[7]Нерекурсивный прямой обход: ";
            tree.stack_preorder_travelsal();
            cout << "\n\n";
            break;
        case '8':
            system("cls");
            return 0;
        default:
            system("cls");
            break;
        }
        tree.print();
        write_cmds();
        cin >> a;
    }
    return 0;
}
*/
