#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

struct Node
{
    string name;
    string phone;
    string email;
    Node *next;

    Node(string n, string p, string e)
    {
        name = n;
        phone = p;
        email = e;
        next = NULL;
    }
};

class PhoneBook
{
private:
    Node *head;

public:
    PhoneBook()
    {
        head = NULL;
        loadFromFile();
    }

    ~PhoneBook()
    {
        saveToFile();
    }

    void insertAtBeginning(string name, string phone, string email)
    {
        Node *newNode = new Node(name, phone, email);

        if(head == NULL)
        {
            head = newNode;
        }
        else
        {
            newNode->next = head;
            head = newNode;
        }
    }

    void insertAtEnd(string name, string phone, string email)
{
    Node *temp = head;

    while(temp != NULL)
    {
        if(temp->phone == phone)
        {
            cout << "\nContact already exists!\n";
            return;
        }
        temp = temp->next;
    }

    Node *newNode = new Node(name, phone, email);

    if(head == NULL)
    {
        head = newNode;
        return;
    }

    temp = head;

    while(temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
}


void display()
{
    sortContacts();

    if(head == NULL)
    {
        cout << "\nPhone Book is Empty!\n";
        return;
    }

    Node *temp = head;

    cout << "\n";
    cout << "-----------------------------------------------------------------------------------------\n";
    cout << left
         << setw(20) << "NAME"
         << setw(20) << "PHONE"
         << setw(35) << "EMAIL" << endl;
    cout << "-----------------------------------------------------------------------------------------\n";

    while(temp != NULL)
    {
        cout << left
             << setw(20) << temp->name
             << setw(20) << temp->phone
             << setw(35) << temp->email
             << endl;

        temp = temp->next;
    }

    cout << "-----------------------------------------------------------------------------------------\n";
}
    void saveToFile()
    {
        ofstream fout("contacts.txt");

        Node *temp = head;

        while(temp != NULL)
        {
            fout << temp->name << endl;
            fout << temp->phone << endl;
            fout << temp->email << endl;

            temp = temp->next;
        }

        fout.close();
    }

    void loadFromFile()
    {
        ifstream fin("contacts.txt");

        if (!fin)
            return;

        string name, phone, email;

        while(getline(fin, name))
        {
            getline(fin, phone);
            getline(fin, email);

            insertAtEnd(name, phone, email);
        }

        fin.close();
    }
        void insertSorted(string name, string phone, string email)
{
    Node *temp = head;

    while(temp != NULL)
    {
        if(temp->phone == phone)
        {
            cout << "\nContact already exists!\n";
            return;
        }
        temp = temp->next;
    }

    Node *newNode = new Node(name, phone, email);

    if(head == NULL || name < head->name)
    {
        newNode->next = head;
        head = newNode;
        return;
    }

    temp = head;

    while(temp->next != NULL && temp->next->name < name)
        temp = temp->next;

    newNode->next = temp->next;
    temp->next = newNode;
}

    void searchContact(string key)
    {
        Node *temp = head;
        bool found = false;

        while(temp != NULL)
        {
            if(temp->name.find(key) != string::npos ||
               temp->phone.find(key) != string::npos)
            {
                cout << "\nName  : " << temp->name << endl;
                cout << "Phone : " << temp->phone << endl;
                cout << "Email : " << temp->email << endl;
                cout << "------------------------\n";
                found = true;
            }
            temp = temp->next;
        }

        if(!found)
        {
            cout << "\nContact not found.\n";
        }
    }

    void deleteByName(string name)
    {
        if(head == NULL)
        {
            cout << "\nPhone Book is Empty.\n";
            return;
        }

        if(head->name == name)
        {
            Node *del = head;
            head = head->next;
            delete del;
            cout << "\nContact Deleted.\n";
            return;
        }

        Node *temp = head;

        while(temp->next != NULL && temp->next->name != name)
        {
            temp = temp->next;
        }

        if(temp->next == NULL)
        {
            cout << "\nContact Not Found.\n";
            return;
        }

        Node *del = temp->next;
        temp->next = del->next;
        delete del;

        cout << "\nContact Deleted.\n";
    }

    void deleteByPhone(string phone)
    {
        if(head == NULL)
        {
            cout << "\nPhone Book is Empty.\n";
            return;
        }

        if(head->phone == phone)
        {
            Node *del = head;
            head = head->next;
            delete del;
            cout << "\nContact Deleted.\n";
            return;
        }

        Node *temp = head;

        while(temp->next != NULL && temp->next->phone != phone)
        {
            temp = temp->next;
        }

        if(temp->next == NULL)
        {
            cout << "\nContact Not Found.\n";
            return;
        }

        Node *del = temp->next;
        temp->next = del->next;
        delete del;

        cout << "\nContact Deleted.\n";
    }
        void displayWithPagination()
    {
        sortContacts();
        if(head == NULL)
        {
            cout << "\nPhone Book is Empty.\n";
            return;
        }

        Node *temp = head;
        int count = 0;
        string choice;

        while(temp != NULL)
        {
            cout << "\nName  : " << temp->name << endl;
            cout << "Phone : " << temp->phone << endl;
            cout << "Email : " << temp->email << endl;
            cout << "---------------------------" << endl;

            count++;
            temp = temp->next;

            if(count % 5 == 0 && temp != NULL)
            {
                cout << "Press Enter to continue...";
                cin.ignore();
                cin.get();
            }
        }
    }

    Node* sortedMerge(Node* a, Node* b)
    {
        if(a == NULL)
            return b;

        if(b == NULL)
            return a;

        Node* result;

        if(a->name <= b->name)
        {
            result = a;
            result->next = sortedMerge(a->next, b);
        }
        else
        {
            result = b;
            result->next = sortedMerge(a, b->next);
        }

        return result;
    }

    void splitList(Node* source, Node** front, Node** back)
    {
        Node* slow = source;
        Node* fast = source->next;

        while(fast != NULL)
        {
            fast = fast->next;

            if(fast != NULL)
            {
                slow = slow->next;
                fast = fast->next;
            }
        }

        *front = source;
        *back = slow->next;
        slow->next = NULL;
    }

    Node* mergeSort(Node* h)
    {
        if(h == NULL || h->next == NULL)
            return h;

        Node *a, *b;

        splitList(h, &a, &b);

        a = mergeSort(a);
        b = mergeSort(b);

        return sortedMerge(a, b);
    }

    void sortContacts()
    {
        head = mergeSort(head);
        cout << "\nContacts Sorted Successfully.\n";
    }
    
};
bool isValidPhone(string phone)
{
    if(phone.length() != 10)
        return false;

    for(char ch : phone)
    {
        if(!isdigit(ch))
            return false;
    }

    return true;
}
int main()
{
    PhoneBook pb;

    int choice;
    string name, phone, email, key;

    do
    {
        cout << "\n========== PHONE BOOK ==========\n";
        cout << "1. Insert at Head\n";
        cout << "2. Insert at Tail\n";
        cout << "3. Insert in Sorted Order\n";
        cout << "4. Delete by Name\n";
        cout << "5. Delete by Phone\n";
        cout << "6. Search Contact\n";
        cout << "7. Display Contacts\n";
        cout << "8. Display with Pagination\n";
        cout << "9. Sort Contacts\n";
        cout << "10. Save Contacts\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch(choice)
        {
        case 1:
    cout << "Enter Name: ";
    getline(cin, name);

   
    do
{
    cout << "Enter Phone (10 digits): ";
    getline(cin, phone);

    if(!isValidPhone(phone))
        cout << "Invalid Phone Number! Please enter exactly 10 digits.\n";

} while(!isValidPhone(phone));

    cout << "Enter Email: ";
    getline(cin, email);

    if(email.find('@') == string::npos)
    {
        cout << "Invalid Email Address!\n";
        break;
    }

    pb.insertAtBeginning(name, phone, email);
    cout << "Contact Added Successfully!\n";
    break;
            
       case 2:
    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter Phone: ";
    getline(cin, phone);

    if(phone.length() != 10)
    {
        cout << "Invalid Phone Number! Please enter exactly 10 digits.\n";
        break;
    }

    cout << "Enter Email: ";
    getline(cin, email);

    if(email.find('@') == string::npos)
    {
        cout << "Invalid Email Address!\n";
        break;
    }

    pb.insertAtEnd(name, phone, email);
    cout << "Contact Added Successfully!\n";
    break;

        case 3:
    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter Phone: ";
    getline(cin, phone);

    if(phone.length() != 10)
    {
        cout << "Invalid Phone Number! Please enter exactly 10 digits.\n";
        break;
    }

    cout << "Enter Email: ";
    getline(cin, email);

    if(email.find('@') == string::npos)
    {
        cout<< "Invalid Email Address!\n";
        break;
    }

    pb.insertSorted(name, phone, email);
    cout << "Contact Added Successfully!\n";
    break;


        case 4:
            cout << "Enter Name: ";
            getline(cin, name);
            pb.deleteByName(name);
            break;

        case 5:
            cout << "Enter Phone: ";
            getline(cin, phone);
            pb.deleteByPhone(phone);
            break;

        case 6:
            cout << "Enter Name or Phone to Search: ";
            getline(cin, key);
            pb.searchContact(key);
            break;

        case 7:
            pb.sortContacts();
            pb.display();
            break;

        case 8:
            pb.displayWithPagination();
            break;

        case 9:
            pb.sortContacts();
            break;

        case 10:
            pb.saveToFile();
            cout << "Contacts Saved Successfully.\n";
            break;

        case 0:
            pb.saveToFile();
            cout << "Thank You!\n";
            break;

        default:
            cout << "Invalid Choice!\n";
        }

    } while(choice != 0);

    return 0;
}