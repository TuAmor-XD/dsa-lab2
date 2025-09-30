#include <iostream>
#include <string>
using namespace std;

struct User {
    string username;
    string password;
    string role;    
    User* next;

    User(string u, string p, string r = "viewer") {
        username = u;
        password = p;
        role = r;
        next = nullptr;
    }
};

bool insertUser(User*& head, const string& username, const string& password, const string& role = "viewer") {
    if (!head) {
        head = new User(username, password, role);
        return true;
    }
    User* curr = head;
    while (curr) {
        if (curr->username == username) return false; 
        if (!curr->next) break;
        curr = curr->next;
    }
    curr->next = new User(username, password, role);
    return true;
}

User* findUser(User* head, const string& username) {
    User* curr = head;
    while (curr) {
        if (curr->username == username) return curr;
        curr = curr->next;
    }
    return nullptr;
}

bool authenticate(User* head, const string& username, const string& password) {
    User* u = findUser(head, username);
    return (u && u->password == password);
}

bool removeFront(User*& head) {
    if (!head) return false;
    User* temp = head;
    head = head->next;
    delete temp;
    return true;
}

bool removeByUsername(User*& head, const string& username) {
    if (!head) return false;
    if (head->username == username) {
        return removeFront(head);
    }
    User* curr = head;
    while (curr->next) {
        if (curr->next->username == username) {
            User* temp = curr->next;
            curr->next = curr->next->next;
            delete temp;
            return true;
        }
        curr = curr->next;
    }
    return false;
}

// clearList
void clearList(User*& head) {
    while (head) {
        removeFront(head);
    }
}

// size
size_t size(User* head) {
    size_t count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

// printUsers
void printUsers(User* head) {
    while (head) {
        cout << head->username << " (" << head->role << ")" << " -> ";
        head = head->next;
    }
    cout << "NULL" << endl;
}

int main() {
    User* head = nullptr;

    insertUser(head, "alice", "123", "admin");
    insertUser(head, "bob", "456", "editor");
    insertUser(head, "charlie", "789"); 

    printUsers(head);

    cout << "Size: " << size(head) << endl;

    removeByUsername(head, "bob");
    printUsers(head);

    clearList(head);
    printUsers(head);

    return 0;
}
