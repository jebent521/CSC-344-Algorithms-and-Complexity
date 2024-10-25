/* 
Name(s): Jonah Ebent and Evan Whitmer 
Class: CSC-344-A :Algorithms and Complexity
Date: October 10, 2024
Description:
Write a program in C++ that stores user info in a 13-slot hash table using open addressing.

Each "person" object has members "ID", "name", "quest" and "favorite color."

The program should prompt the user to enter their name, their quest and their favorite color,
and then generate a 5-digit ID number randomly and put the "person" object in a slot in the hash
table according to some hashing function of your choice.  

Your hashing function must avoid primary and secondary clustering.

After each person is added to the table, output your table NEATLY in order, listing the table
location next to each person's ID, name, quest, and color, including blank spots
(this is useful for debugging).  

Write a driver with test data to demonstrate the functionality of your code.
*/
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

// Data class using in the HashTable class
struct Person {
    int id{};
    string name{};
    string quest{};
    string color{};

    // NIL initialization
    Person() {}

    // standard inititalization
    Person(string name, string quest, string color) :
        name(name), quest(quest), color(color) {
        id = rand() % 100000;
    }

    // Initialization used for debugging
    Person(int id, string name, string quest, string color) :
        id(id), name(name), quest(quest), color(color) { }

    // convert the variables into a single string variable, accounts for small ids using padding of 0s
    string toString() const {
        return string(5 - to_string(id).length(), '0') + to_string(id) + ", " + name + ", " + quest + ", " + color;
    }

    // overloading the == to work with person class variables
    bool operator==(const Person& other) const {
        return id == other.id
            && name == other.name
            && quest == other.quest
            && color == other.color;
    }

    // overloading the != to work with person class variables
    bool operator!=(const Person& other) const {
        return !(*this == other);
    }

    // overloading the << to work with person class variables
    static friend ostream& operator<<(ostream& os, const Person& obj) {
        os << obj.toString();
        return os;
    }
};

// Table class of Person Class structured via a vector
class HashTable {
    const int size = 13; // prime size for the number of elements storable in the HashTable
    const int prime = 7; // a prime lower than size used in hash2 function
    const Person NIL = Person(); // used in HashTable for slots that are still available 
    int numEntries = 0; // tracks how many spaces in HashTable are used
    vector<Person> data = vector<Person>(size, NIL); // Table implemented as a vector of Persons

    // calculates the original hash index
    int hash1(int id) const {
        return id % size;
    }

    // calculates the offset from the original hash 
    int hash2(int id) const {
        return prime - (id % prime);
    }

    // calculates the index of the given id accounting for collisions
    int doubleHash(int id) const {
        int index = hash1(id);
        while (data.at(index) != NIL) {
            index = (index + hash2(id)) % size;
        }
        return index;
    }

public:
    // inserting new element into HashTable if space available
    void insert(Person p) {
        if (numEntries >= size) {
            cout << "Could not enter " << p.name << " into the table, since it's full" << endl;
            return;
        }
        data[doubleHash(p.id)] = p;
        numEntries++;
    }
    
    //Displays the current contents of the HashTable
    void display() {
        for (int i = 0; i < data.size(); i++) {
            Person p = data.at(i);
            cout << i << "\t" << (p == NIL ? "" : p.toString()) << endl;
        }
    }
};

int main() {
    //driver code
    srand(time(NULL)); // seeds random number generator using current time
    HashTable people;  // Initialize HashTable
    for (int i = 0; i < 13; i++) {
        // for loop gets name, quest, color for new elements until HashTable is full
        string name, quest, color;
        cout << "What is your name? " << endl;
        getline(cin, name);
        cout << "What is your quest? " << endl;
        getline(cin, quest);
        cout << "What is your favorite color? " << endl;
        getline(cin, color);
        people.insert(Person(name, quest, color));
        people.display();
        cout << endl;
    }
}