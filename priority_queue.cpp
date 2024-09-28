#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Task
{
public:
    Task(int p, string m) { priority = p; message = m; }

    int priority;
    string message;

    friend ostream& operator<<(ostream& os, const Task& obj) {
        os << obj.priority << "\t" << obj.message;
        return os;
    }

    bool operator<(const Task& other) const {
        return priority < other.priority;
    }

    bool operator<=(const Task& other) const {
        return priority <= other.priority;
    }

    bool operator>(const Task& other) const {
        return priority > other.priority;
    }

    bool operator>=(const Task& other) const {
        return priority >= other.priority;
    }
};

class PriorityQueue
{
public:
    Task at(int i) {
        return items.at(i);
    }

    Task nextTask() {
        if (size == 0) throw "Queue is empty";
        return items.at(0);
    }

    Task popNextTask() {
        Task next = nextTask();
        remove(0);
        return next;
    }

    void insert(Task task) {
        size++;
        items.push_back(task);
        reheap_up(size - 1);
    }

    void update(int i, Task task) {
        Task oldTask = items.at(i);
        items[i] = task;
        if (task > oldTask) { reheap_up(i); }
        else { reheap_down(i); }
    }

    void remove(int i) {
        size--;
        update(i, items.at(size));
    }

    void display(bool printHeader = true) const {
        if (size == 0) {
            cout << "Empty list" << endl;
            return;
        }
        if (printHeader) cout << "Index\tWeight\tTask" << endl;
        for (int i = 0; i < size; i++)
        {
            cout << i << "\t" << items.at(i) << endl;
        }
    }

    int getSize() const { return size; }
private:
    vector<Task> items;
    int size = 0;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return (i * 2) + 1; }
    int right(int i) { return (i * 2) + 2; }

    void reheap_up(int i) {
        if (i > 0) {
            int p = parent(i);
            int largest = p;
            if (p >= 0 && items.at(i) > items.at(p)) {
                swap(items.at(p), items.at(i));
                reheap_up(p);
            }
        }
    }
    void reheap_down(int i) {
        int l = left(i);
        int r = right(i);
        int largest = i;
        if (l < size && items.at(l) > items.at(largest)) {
            largest = l;
        }
        if (r < size && items.at(r) > items.at(largest)) {
            largest = r;
        }
        if (largest != i) {
            swap(items.at(i), items.at(largest));
            reheap_down(largest);
        }
    }
};

static int enterInteger(int min, int max, bool includeNegativeOne = true) {
    int intput;
    string input;
    do {
        cout << "Selection: ";      // prompt user for input
        getline(cin, input);
        try                         // try to convert it to an integer
        {
            intput = stoi(input);
        }
        catch (const std::invalid_argument&)
        {                           // if unsuccessful, yell at user and try again
            cout << "  Invalid input" << endl;
            continue;
        }
        if ((intput >= min && intput <= max) || (includeNegativeOne && intput == -1))
        {                           // if successful and input is within range, get out of the loop 
            break;
        }
        cout << "  Invalid input" << endl;
    } while (true);                 // continue looping until input is valid
    // input is valid, so return it
    return intput;

}

static Task enterTask() {
    string message;
    cout << "Enter a message for your new task: ";
    getline(cin, message);
    cout << "Enter a priority/weight for your new task (1-99999)." << endl;
    int priority = enterInteger(1, 99999, false);
    return Task(priority, message);
}

int main() {
    PriorityQueue todo;
    Task task(0, "");
    int selection;
    
    cout << "Welcome to your favorite to-do list app!" << endl;
    while (true) {
        cout << "========================================" << endl;
        cout << "Please select an option:" << endl;
        cout << "   1: See the next item" << endl;
        cout << "   2: Complete the next item" << endl;
        cout << "   3: View my list" << endl;
        cout << "   4: Insert items" << endl;
        cout << "   5: Update items" << endl;
        cout << "   6: Delete items" << endl;
        cout << endl;
        cout << "   -1: Exit" << endl;
        cout << "========================================" << endl;
        switch (enterInteger(1,6))
        {
        case 1:     // see next
            try { task = todo.nextTask(); }
            catch (char e[]) {
                cout << e << endl;
                break;
            }
            cout << todo.nextTask() << endl;
            break;
        case 2:     // remove next
            try { task = todo.nextTask(); }
            catch (char e[]) {
                cout << e << endl;
                break;
            }
            cout << "Removed task '" << todo.popNextTask().message << "' from the list." << endl;
            break;
        case 3:     // display
            todo.display();
            break;
        case 4:     // insert
            task = enterTask();
            todo.insert(task);
            break;
        case 5:     // update
            todo.display();
            cout << "Which would you like to update (select by index)?" << endl;
            selection = enterInteger(0, todo.getSize() - 1, false);
            task = todo.at(selection);
            cout << "Selected '" << task.message << "' with priority " << task.priority << "." << endl;
            cout << "What would you like to change?" << endl;
            cout << "   1: Priority" << endl;
            cout << "   2: Message" << endl;
            cout << "   3: Both" << endl;
            switch (enterInteger(1, 3, false))
            {
            case 1:
                cout << "Enter a new priority (1-99999)." << endl;
                task.priority = enterInteger(1, 99999, false);
                break;
            case 2:
                cout << "Enter a new message: ";
                getline(cin, task.message);
                break;
            case 3:
                task = enterTask();
                break;
            }
            todo.update(selection, task);
            cout << "   Successfully updated " << selection << " to be '" << task.message << "' with priority " << task.priority << "." << endl;
            break;
        case 6:     // delete
            todo.display();
            cout << "Which would you like to delete (select by index)?" << endl;
            selection = enterInteger(0, todo.getSize() - 1);
            if (selection == -1) {
                cout << "   Going back." << endl;
                break;
            }
            task = todo.at(selection);
            todo.remove(selection);
            cout << "   Successfully removed " << task << "." << endl;
            break;
        case -1:    // exit
            exit(0);
        default:    // error
            exit(1);
        }
    }
    return 0;
}