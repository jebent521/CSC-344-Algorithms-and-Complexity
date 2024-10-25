/*
Name(s): Jonah Ebent and Evan Whitmer
Date: October 26, 2024
Class: CSC-344-A : Algorithms and Complexity 
Description: Write a C++ program that takes a list of strings and groups anagrams together
*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;


// Hash table that maps string anagrams to the same bucket
class HashTable {
    struct Node {
        string data{};
        Node* next = nullptr;
    };

    int size;
    vector<Node*> table;

    // makes string lowercase, removes whitespace, and sorts in alphabetical order
    string normalize(string str) {
        // to lowercase
        transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return tolower(c); });
        // remove spaces
        str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
        // alphabetize
        sort(str.begin(), str.end());
        return str;
    }

    // returns a hash index between 0 and size-1 for the given normalized string
    int hash(string str) const {
        unsigned int sum = 0;
        for (int i = 0; i < str.size(); i++) {
            unsigned char c = str[i];
            sum += (c-97) * (int)pow(26, i) % size;
        }
        return sum % size;
    }

    // traverses the linked list, printing each node separated by sep
    void displayLinkedList(Node* item, string sep = ", ") {
        if (item) {
            while (item->next) {
                cout << item->data << sep;
                item = item->next;
            }
            cout << item->data;
        }
    }

public:
    HashTable(int size) : size(size) {
        table = vector<Node*>(size, nullptr);
    }

    // inserts a string into the table, where anagrams
    // map to the same value, thereby being grouped together
    void insert(string item) {
        int index = hash(normalize(item));
        Node* current = table.at(index);
        Node* newNode = new Node;
        newNode->data = item;
        newNode->next = current;
        table[index] = newNode;

        // occurs if table is not large enough
        if (current && normalize(current->data) != normalize(item)) {
            cout << "COLLISION DETECTED: " << current->data << " and "
                << item << " have the same index: (" 
                << hash(normalize(current->data)) << ", "
                << index << ")" << endl;
            cout << "Try using a larger table size" << endl;
        }
    }

    // displays entire table
    void display() {
        for (int i = 0; i < size; i++) {
            Node* item = table.at(i);
            cout << i;
            if (item) {
                cout << " -> ";
                displayLinkedList(item, " -> ");
            }
            cout << endl;
        }
    }

    // displays anagrams and there similars
    void showAnagrams() {
        for (Node* item : table) {
            if (item) {
                displayLinkedList(item);
                cout << endl;
            }
        }
    }

    // clears the entire table, not memory safe => can cause memory leaks
    void clear() {
        table = vector<Node*>(size, nullptr);
    }
};

int main() {
    // examples to copy and paste for testing
    // "Orb", "bro", "ate", "eden", "eat", "need", "joe", "code", "coed"
    // "Listen", "silent", "rat", "tar", "enlist", "art", "tinsel", "night", "thing", "live", "vile", "inlets"
    // "Plan", "man", "stan", "can", "chan", "jan", "clan", "ban", "pan", "urban"
    // Dormitory, dirty room, the eyes, they see, a gentleman, elegant man, funeral, real fun

    //driver code
    HashTable anagrams(307);
    while (true) {
        cout << "Input a list of strings, separated by commas (empty line to exit)" << endl;
        // get input
        string line;
        getline(cin, line);
        if (line.empty()) break;

        // parse input
        stringstream ss(line);
        string token;
        while (getline(ss, token, ',')) { 
            // trim left
            token.erase(
                token.begin(),
                find_if(
                    token.begin(),
                    token.end(),
                    [](unsigned char ch) { return !isspace(ch); }
                )
            );
            // trim right
            token.erase(
                find_if(
                    token.rbegin(),
                    token.rend(),
                    [](unsigned char ch) { return !isspace(ch); }
                ).base(),
                token.end()
            );
            // remove quotation marks
            token.erase(remove(token.begin(), token.end(), '"'), token.end());
            // add to hash table
            if (!token.empty()) anagrams.insert(token);
        }

        // display results
        cout << endl;
        anagrams.showAnagrams();
        anagrams.clear();
        cout << endl;
    }
}
