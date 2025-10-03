#include <iostream>
#include <string>
#include <ctime>

const int INITIAL_SIZE = 101;

struct Node {
    std::string key;
    int value;
    Node* next;
    Node(const std::string& k, int v) : key(k), value(v), next(nullptr) {} // Fixed!
};

class ScratchHash {
private:
    Node** table;
    int size;
    int entries;
    unsigned long long polyHash(const std::string& str) {
        unsigned long long hashVal = 0;
        unsigned long long p_pow = 1;
        const int p = 31, m = size;
        for (char c : str) {
            hashVal = (hashVal + (c - 'a' + 1) * p_pow) % m;
            p_pow = (p_pow * p) % m;
        }
        return hashVal;
    }
    void resize() {
        int oldSize = size;
        Node** oldTable = table;
        size *= 2;
        table = new Node*[size];
        for (int i = 0; i < size; ++i) table[i] = nullptr;
        entries = 0;
        for (int i = 0; i < oldSize; ++i) {
            Node* curr = oldTable[i];
            while (curr) {
                insert(curr->key, curr->value);
                Node* temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
        delete[] oldTable;
    }
public:
    ScratchHash() : size(INITIAL_SIZE), entries(0) {
        table = new Node*[size];
        for (int i = 0; i < size; ++i) table[i] = nullptr;
    }
    ~ScratchHash() {
        for (int i = 0; i < size; ++i) {
            Node* curr = table[i];
            while (curr) {
                Node* temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
        delete[] table;
    }
    void insert(const std::string& key, int value) {
        if (entries > size * 0.7) resize();
        unsigned long long index = polyHash(key);
        Node* newNode = new Node(key, value);
        newNode->next = table[index];
        table[index] = newNode;
        ++entries;
    }
    int* search(const std::string& key) {
        unsigned long long index = polyHash(key);
        Node* curr = table[index];
        while (curr) {
            if (curr->key == key) return &curr->value;
            curr = curr->next;
        }
        return nullptr;
    }
};

int main() {
    ScratchHash hashTable;
    hashTable.insert("AAPL", 150);
    int* price = hashTable.search("AAPL");
    if (price) std::cout << "Price: " << *price << std::endl;
    return 0;
}
