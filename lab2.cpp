#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct User {
    string username;
    string password;
    vector<string> permissions; 
    User* next;

    User(const string& u, const string& p, const vector<string>& perms = {"view"}) {
        username = u;
        password = p;
        permissions = perms;
        next = nullptr;
    }
};

// Updated insertUser to accept permissions
bool insertUser(User*& head, const string& username, const string& password, const vector<string>& perms = {"view"}) {
    if (!head) {
        head = new User(username, password, perms);
        return true;
    }
    User* curr = head;
    while (curr) {
        if (curr->username == username) return false;
        if (!curr->next) break;
        curr = curr->next;
    }
    curr->next = new User(username, password, perms);
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
    if (head->username == username) return removeFront(head);
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

void clearList(User*& head) {
    while (head) removeFront(head);
}

size_t size(User* head) {
    size_t count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

void printUsers(User* head) {
    while (head) {
        cout << head->username << " [";
        for (size_t i = 0; i < head->permissions.size(); ++i) {
            cout << head->permissions[i];
            if (i + 1 < head->permissions.size()) cout << ", ";
        }
        cout << "] -> ";
        head = head->next;
    }
    cout << "NULL" << endl;
}


bool authorize(User* head, const string& username, const string& action) {
    User* u = findUser(head, username);
    if (!u) return false;
    for (const string& perm : u->permissions) {
        if (perm == action) return true;
    }
    return false;
}

int main() {
    User* head = nullptr;

    // Insert users with permissions
    insertUser(head, "alice", "123", {"view", "edit", "create"});
    insertUser(head, "bob", "456", {"view", "edit"});
    insertUser(head, "charlie", "789");      
    insertUser(head, "dave", "000", {"view"}); 

    printUsers(head);
    cout << "Size: " << size(head) << endl;


    cout << "Authenticate bob/456: " << authenticate(head, "bob", "456") << endl;
    cout << "Authenticate alice/999: " << authenticate(head, "alice", "999") << endl;


    cout << "Alice can create: " << authorize(head, "alice", "create") << endl;
    cout << "Bob can create: " << authorize(head, "bob", "create") << endl;
    cout << "Charlie can edit: " << authorize(head, "charlie", "edit") << endl;
    cout << "Dave can view: " << authorize(head, "dave", "view") << endl;
    cout << "Unknown user can view: " << authorize(head, "eve", "view") << endl;

    // Remove users
    removeByUsername(head, "bob");
    printUsers(head);

    removeFront(head);
    printUsers(head);

    clearList(head);
    printUsers(head);

    return 0;
}
