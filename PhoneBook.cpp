#include <iostream>
#include <string>
using namespace std;

struct PhoneNo {
    string contactNo;
    PhoneNo* link;
};

struct Mobile {
    string name;
    PhoneNo* phonelink;
    Mobile* next;
};

class list {
    Mobile* headMobile;

public:
    list() : headMobile(NULL) {}
    ~list();

    void create();
    void display();
    void deleteContact();
    void makephonecall();
    void recentlydialed();
    void Recommendation();
};

list::~list() {
    Mobile* current = headMobile;
    while (current != NULL) {
        Mobile* next = current->next;
        PhoneNo* phone = current->phonelink;
        while (phone != NULL) {
            PhoneNo* temp = phone->link;
            delete phone;
            phone = temp;
        }
        delete current;
        current = next;
    }
}

void list::create() {
    Mobile* newMobile = new Mobile;
    cout << "\nEnter contact name: ";
    cin >> newMobile->name;
    newMobile->phonelink = NULL;
    newMobile->next = NULL;

    cout << "Enter the number of phone numbers to add: ";
    int count;
    cin >> count;
    PhoneNo* prev = NULL;

    for (int i = 0; i < count; ++i) {
        PhoneNo* newPhone = new PhoneNo;
        cout << "Enter phone number: ";
        cin >> newPhone->contactNo;
        newPhone->link = NULL;

        if (prev == NULL) {
            newMobile->phonelink = newPhone;
        } else {
            prev->link = newPhone;
        }
        prev = newPhone;
    }

    if (headMobile == NULL) {
        headMobile = newMobile;
    } else {
        Mobile* temp = headMobile;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newMobile;
    }
    cout << "Contact added successfully!\n";
}

void list::display() {
    if (headMobile == NULL) {
        cout << "\nThe contact list is empty.\n";
        return;
    }
    Mobile* ptr = headMobile;
    cout << "\nContacts:\n";
    while (ptr != NULL) {
        cout << "Name: " << ptr->name << "\nPhone Numbers: ";
        PhoneNo* itr = ptr->phonelink;
        while (itr != NULL) {
            cout << itr->contactNo << " ";
            itr = itr->link;
        }
        cout << "\n";
        ptr = ptr->next;
    }
}

void list::deleteContact() {
    if (headMobile == NULL) {
        cout << "\nThe contact list is empty.\n";
        return;
    }
    string name;
    cout << "\nEnter the name of the contact to delete: ";
    cin >> name;

    Mobile* cur = headMobile;
    Mobile* prev = NULL;

    while (cur != NULL && cur->name != name) {
        prev = cur;
        cur = cur->next;
    }

    if (cur == NULL) {
        cout << "\nContact not found.\n";
    } else {
        if (prev == NULL) {
            headMobile = cur->next;
        } else {
            prev->next = cur->next;
        }

        PhoneNo* phone = cur->phonelink;
        while (phone != NULL) {
            PhoneNo* temp = phone->link;
            delete phone;
            phone = temp;
        }
        delete cur;
        cout << "\nContact deleted successfully!\n";
    }
}

class Stack {
    int max;
    string* st;
    int top;

public:
    Stack(int stacksize) : max(stacksize), top(-1) {
        st = new string[stacksize];
    }
    ~Stack() { delete[] st; }

    bool is_empty() { return top == -1; }
    bool is_full() { return top == max - 1; }

    void push(string element) {
        if (!is_full()) {
            st[++top] = element;
        }
    }

    string pop() {
        if (!is_empty()) {
            return st[top--];
        }
        return "";
    }

    string get_top() {
        if (!is_empty()) {
            return st[top];
        }
        return "";
    }
};

Stack s1(50);
Stack s2(50);

void list::makephonecall() {
    if (headMobile == NULL) {
        cout << "\nThe contact list is empty.\n";
        return;
    }

    string name;
    cout << "\nEnter the contact name to call: ";
    cin >> name;

    Mobile* ptr = headMobile;
    while (ptr != NULL && ptr->name != name) {
        ptr = ptr->next;
    }

    if (ptr != NULL) {
        cout << "\nCalling " << ptr->name << "...\n";
        s1.push(ptr->name);
        s2.push(ptr->name);
    } else {
        cout << "\nContact not found.\n";
    }
}

void list::recentlydialed() {
    if (s2.is_empty()) {
        cout << "\nNo recent calls.\n";
        return;
    }

    cout << "\nRecently dialed contacts:\n";

    // Use a temporary stack to display without losing data
    Stack tempStack(50);
    while (!s2.is_empty()) {
        string contact = s2.pop();
        cout << contact << "\n";
        tempStack.push(contact);
    }

    // Restore the original stack
    while (!tempStack.is_empty()) {
        s2.push(tempStack.pop());
    }
}

void list::Recommendation() {
    if (headMobile == NULL) {
        cout << "\nThe contact list is empty.\n";
        return;
    }

    string prefix;
    cout << "\nEnter the starting characters of the contact name: ";
    cin >> prefix;

    Mobile* ptr = headMobile;
    bool found = false;
    cout << "\nRecommended contacts:\n";

    while (ptr != NULL) {
        if (ptr->name.substr(0, prefix.size()) == prefix) {
            cout << "Name: " << ptr->name << "\nPhone Numbers: ";
            PhoneNo* itr = ptr->phonelink;
            while (itr != NULL) {
                cout << itr->contactNo << " ";
                itr = itr->link;
            }
            cout << "\n";
            found = true;
        }
        ptr = ptr->next;
    }

    if (!found) {
        cout << "\nNo matching contacts found.\n";
    }
}

int main() {
    list l;
    int choice;

    do {
        cout << "\nPhonebook App:\n"
             << "1. Add Contact\n"
             << "2. Display Contacts\n"
             << "3. Delete Contact\n"
             << "4. Make a Call\n"
             << "5. Recently Dialed\n"
             << "6. Recommend Contact\n"
             << "7. Exit\n"
             << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                l.create();
                break;
            case 2:
                l.display();
                break;
            case 3:
                l.deleteContact();
                break;
            case 4:
                l.makephonecall();
                break;
            case 5:
                l.recentlydialed();
                break;
            case 6:
                l.Recommendation();
                break;
            case 7:
                cout << "\nThank you for using the phonebook app!\n";
                break;
            default:
                cout << "\nInvalid choice. Try again.\n";
        }
    } while (choice != 7);

    return 0;
}
