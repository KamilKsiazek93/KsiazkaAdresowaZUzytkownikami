#include <iostream>
#include <cstdlib>
#include <fstream>
#include <limits>
#include <windows.h>
#include <vector>

using namespace std;

struct Contact
{
    int id;
    int idOfUser;
    string name;
    string surname;
    string mail;
    string numberOfPhone;
    string address;
};

struct User
{
    int id;
    string nick;
    string password;
};

vector<User> sendUsers (vector<User> userBookOfAddresses);
vector<User> signUp (vector<User> userBookOfAddresses);
int logIn (vector<User> userBookOfAddresses);
void changeUserFile (vector<User> usersOfBook);
int countContacts ();
vector<Contact> sendTheContact();
int lastID ();
vector<Contact> sendContactToVector (int userID);
vector<Contact> addContact(vector<Contact> friends, int userID, int lastIdOfContact);
int findContactByName(vector<Contact> friends);
int findContactBySurname(vector<Contact> friends);
void showAllContact(vector<Contact> friends);
void changeFile (vector<Contact> friends, int idContact);
vector<Contact> deleteContact(vector<Contact> &friends);
vector<Contact> editContactByName(vector<Contact> friends, int idContact);
vector<Contact> editContactBySurname(vector<Contact> friends, int idContact);
vector<Contact> editContactByMail(vector<Contact> friends, int idContact);
vector<Contact> editContactByPhoneNumber(vector<Contact> friends, int idContact);
vector<Contact> editContactByAddress(vector<Contact> friends, int idContact);
vector<User> changePassword (vector<User> userBookOfAddresses, int userID);

int main()
{
    int id = 0;
    int userID;
    int changingMenu = 0;
    int lastIdOfContact;
    char choice;
    vector<User> usersBookOfAddresses;
    usersBookOfAddresses = sendUsers(usersBookOfAddresses);
    vector<Contact> friends;

    while (1)
    {
        if (changingMenu == 0)
        {
            system("cls");
            cout << "MENU" << endl;
            cout << "1. Logowanie" << endl;
            cout << "2. Rejestracja" << endl;
            cout << "3. Zakoncz program" << endl;
            cin >> choice;

            if (choice == '1')
            {
                userID = logIn (usersBookOfAddresses);
                friends = sendContactToVector(userID);
                changingMenu = 1;
            }
            else if (choice == '2')
                usersBookOfAddresses = signUp (usersBookOfAddresses);
            else if (choice == '3')
                exit(0);
        }
        if (changingMenu == 1)
        {
            system("cls");
            cout << "KSIAZKA ADRESOWA" << endl;
            cout << "1. Dodaj nowy kontakt" << endl;
            cout << "2. Wyszukaj znajomych po imieniu" << endl;
            cout << "3. Wyszukaj znajomych po nazwisku" << endl;
            cout << "4. Wyswietl wszystkie kontakty" << endl;
            cout << "5. Usun adresata" << endl;
            cout << "6. Edytuj adresata" << endl;
            cout << "7. Zmien haslo" << endl;
            cout << "8. Wyloguj sie" << endl;
            cout << "9. Zakoncz program" << endl;
            cin >> choice;

            if (choice == '1')
            {
                lastIdOfContact = lastID();
                friends = addContact(friends, userID, lastIdOfContact);
            }
            else if (choice == '2')
                findContactByName(friends);
            else if (choice == '3')
                findContactBySurname(friends);
            else if (choice == '4')
                showAllContact(friends);
            else if (choice == '5')
                friends = deleteContact(friends);
            else if (choice == '6')
                changingMenu+=1;
            else if (choice == '7')
                usersBookOfAddresses = changePassword (usersBookOfAddresses, userID);
            else if (choice == '8')
                {
                    friends.clear();
                    changingMenu = 0;
                }
            else if (choice == '9')
                exit(0);
        }
        else if (changingMenu == 2)
        {
            system("cls");
            cout << "EDYCJA" << endl;
            cout << "1. Imie" << endl;
            cout << "2. Nazwisko" << endl;
            cout << "3. Numer telefonu" << endl;
            cout << "4. Email" << endl;
            cout << "5. Adres" << endl;
            cout << "6. Powrot do menu" << endl;

            cout << "Podaj id uzytkownia, ktorego chcesz edytowac: ";
            cin >> id;
            cout << "Podaj ktora dane chcesz edytowac: ";
            cin >> choice;

            if (choice == '1')
                friends = editContactByName(friends, id);
            else if (choice == '2')
                friends = editContactBySurname(friends, id);
            else if (choice == '3')
                friends = editContactByPhoneNumber(friends, id);
            else if (choice == '4')
                friends = editContactByMail(friends, id);
            else if (choice == '5')
                friends = editContactByAddress(friends, id);
            else if (choice == '6')
                changingMenu = 1;
        }
    }
    return 0;
}

vector<User> sendUsers (vector<User> userBookOfAddresses)
{
    User newUser;
    char sign = '|';
    int numberOfSign = 0;
    string partOfLine;
    fstream file;
    file.open("Uzytkownicy.txt", ios::in);
    if (file.good() == true)
    {
        while(getline(file, partOfLine, sign))
        {
            switch(numberOfSign)
            {
            case 0:
                newUser.id = atoi(partOfLine.c_str());
                break;
            case 1:
                newUser.nick = partOfLine;
                break;
            case 2:
                newUser.password = partOfLine;
                break;
            }
            if (numberOfSign >= 2)
            {
                numberOfSign = 0;
                userBookOfAddresses.push_back(newUser);
            }
            else
                numberOfSign++;
        }
        file.close();
    }
    return userBookOfAddresses;
}

vector<User> signUp (vector<User> userBookOfAddresses)
{
    User newUser;
    int id = 0;
    if (userBookOfAddresses.size() == 0)
        id = 0;
    else
        id = userBookOfAddresses[userBookOfAddresses.size()-1].id;
    string nickname, userPassword;
    fstream file;
    cout << "Podaj nick nowego uzytkownika: ";
    cin >> nickname;
    for (int i = 0; i < userBookOfAddresses.size(); ++i)
    {
        while (userBookOfAddresses[i].nick == nickname)
        {
            cout << "Podana nazwa uzytkownika jest juz zajeta! Podaj inna nazwe: ";
            cin >> nickname;
        }
    }
    cout << "Podaj haslo: ";
    cin >> userPassword;
    newUser.id = id+1;
    newUser.nick = nickname;
    newUser.password = userPassword;
    userBookOfAddresses.push_back(newUser);
    file.open("Uzytkownicy.txt", ios::out | ios::app);
    file << newUser.id << '|';
    file << newUser.nick << '|';
    file << newUser.password << '|' << endl;
    file.close();
    cout << "Dodano nowego uzytkownika!" << endl;
    system("pause");
    return userBookOfAddresses;
}

int logIn (vector<User> userBookOfAddresses)
{
    string nickname, userPassword;
    cout << "PANEL LOGOWANIA" << endl;
    cout << endl;
    cout << "Podaj nick: ";
    cin >> nickname;
    cout << "Podaj haslo: ";
    cin >> userPassword;
    for (int i = 0; i < userBookOfAddresses.size(); ++i)
    {
        while (userBookOfAddresses[i].nick == nickname && userBookOfAddresses[i].password != userPassword)
        {
            cout << "Podane haslo jest niepoprawne. Sprobuj jeszcze raz: ";
            cin >> userPassword;
        }
        if (userBookOfAddresses[i].nick == nickname && userBookOfAddresses[i].password == userPassword)
            return userBookOfAddresses[i].id;
    }
    system("pause");
    return 0;
}

void changeUserFile (vector<User> usersOfBook)
{
    ofstream file("Uzytkownicy.txt", ios::in | ios::trunc);
    for (int i = 0; i < usersOfBook.size(); ++i)
    {
        file << usersOfBook[i].id << '|';
        file << usersOfBook[i].nick << '|';
        file << usersOfBook[i].password << '|' << endl;
    }
    file.close();
}

int countContacts ()
{
    int numberOfContacts = 0;
    ifstream file("MojeKontakty.txt");
    string line;
    while (getline(file, line))
        numberOfContacts++;
    return numberOfContacts;
}

vector<Contact> sendTheContact()
{
    vector<Contact> friends;
    Contact newContact;
    char sign = '|';
    int numberOfSign = 0;
    string partOfLine;
    fstream file;
    file.open("MojeKontakty.txt", ios::in);
    if (file.good() == true)
    {
        while(getline(file, partOfLine, sign))
        {
            switch(numberOfSign)
            {
            case 0:
                newContact.id = atoi(partOfLine.c_str());
                break;
            case 1:
                newContact.idOfUser = atoi(partOfLine.c_str());
                break;
            case 2:
                newContact.name = partOfLine;
                break;
            case 3:
                newContact.surname = partOfLine;
                break;
            case 4:
                newContact.numberOfPhone = partOfLine;
                break;
            case 5:
                newContact.mail = partOfLine;
                break;
            case 6:
                newContact.address = partOfLine;
                break;
            }
            if (numberOfSign >= 6)
            {
                numberOfSign = 0;
                friends.push_back(newContact);
            }
            else
            {
                numberOfSign++;
            }
        }
        file.close();
    }
    return friends;
}

int lastID ()
{
    vector<Contact> friends = sendTheContact();
    int sizeOfVector = countContacts();
    int findingId = friends[sizeOfVector-1].id;
    return findingId;
}

vector<Contact> sendContactToVector (int userID)
{
    vector<Contact> friends = sendTheContact();
    vector<Contact> findingVector;
    for (int i = 0; i < friends.size(); ++i)
    {
        if (friends[i].idOfUser == userID)
            findingVector.push_back(friends[i]);
    }
    return findingVector;
}

vector<Contact> addContact(vector<Contact> friends, int userID, int lastIdOfContact)
{
    int id = 0;
    Contact newContact;
    fstream file;
    id = lastIdOfContact;
    string name, surname, numberOfPhone, mail, address;
    cout << "Podaj imie nowego kontaktu: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);
    cout << "Podaj nazwisko nowego kontaktu: ";
    getline(cin, surname);
    cout << "Podaj e-mail: ";
    getline(cin, mail);
    cout << "Podaj numer telefonu: ";
    getline(cin, numberOfPhone);
    cout << "Podaj adres: ";
    getline(cin, address);
    newContact.id = id + 1;
    newContact.idOfUser = userID;
    newContact.name = name;
    newContact.surname = surname;
    newContact.mail = mail;
    newContact.numberOfPhone = numberOfPhone;
    newContact.address = address;
    friends.push_back(newContact);
    file.open("MojeKontakty.txt", ios::out | ios::app);
    file << newContact.id << '|';
    file << newContact.idOfUser << '|';
    file << newContact.name << '|';
    file << newContact.surname << '|';
    file << newContact.mail << '|';
    file << newContact.numberOfPhone << '|';
    file << newContact.address << '|' << endl;
    file.close();
    cout << "Dodano nowy kontakt!" << endl;
    system("pause");
    return friends;
}

int findContactByName(vector<Contact> friends)
{
    string findingName;
    cout << "Podaj imie: ";
    cin >> findingName;
    for (int i = 0; i < friends.size(); i++)
    {
        if (friends[i].name == findingName)
        {
            cout << friends[i].id << '|';
            cout << friends[i].idOfUser << '|';
            cout << friends[i].name << '|';
            cout << friends[i].surname << '|';
            cout << friends[i].mail << '|';
            cout << friends[i].numberOfPhone << '|';
            cout << friends[i].address << '|' << endl;
        }
    }
    system("pause");
    return 0;
}

int findContactBySurname(vector<Contact> friends)
{
    string findingSurname;
    cout << "Podaj nazwisko: ";
    cin >> findingSurname;
    for (int i = 0; i < friends.size(); i++)
    {
        if (friends[i].surname == findingSurname)
        {
            cout << friends[i].id << '|';
            cout << friends[i].idOfUser << '|';
            cout << friends[i].name << '|';
            cout << friends[i].surname << '|';
            cout << friends[i].mail << '|';
            cout << friends[i].numberOfPhone << '|';
            cout << friends[i].address << '|' << endl;
        }
    }
    system("pause");
    return 0;
}

void showAllContact(vector<Contact> friends)
{
    for (int i = 0; i < friends.size(); ++i)
    {
        cout << friends[i].id << '|';
        cout << friends[i].idOfUser << '|';
        cout << friends[i].name << '|';
        cout << friends[i].surname << '|';
        cout << friends[i].mail << '|';
        cout << friends[i].numberOfPhone << '|';
        cout << friends[i].address << '|' << endl;
    }
    system("pause");
}

void changeFile (vector<Contact> friends, int idContact)
{
    vector<Contact> allContacts = sendTheContact();
    fstream fileOrginal, fileTemporary;
    fileOrginal.open("MojeKontakty.txt", ios::in);
    fileTemporary.open("MojeKontaktyTymczasowy.txt", ios::out | ios::app);
    for (int i = 0; i < allContacts.size(); ++i)
    {
        if (allContacts[i].id != idContact)
        {
            fileTemporary << allContacts[i].id << '|';
            fileTemporary << allContacts[i].idOfUser << '|';
            fileTemporary << allContacts[i].name << '|';
            fileTemporary << allContacts[i].surname << '|';
            fileTemporary << allContacts[i].numberOfPhone << '|';
            fileTemporary << allContacts[i].mail << '|';
            fileTemporary << allContacts[i].address << '|' << endl;
        }
        else
        {
            for (int j = 0; j < friends.size(); ++j)
            {
                if (friends[j].id == idContact)
                {
                    fileTemporary << friends[j].id << '|';
                    fileTemporary << friends[j].idOfUser << '|';
                    fileTemporary << friends[j].name << '|';
                    fileTemporary << friends[j].surname << '|';
                    fileTemporary << friends[j].numberOfPhone << '|';
                    fileTemporary << friends[j].mail << '|';
                    fileTemporary << friends[j].address << '|' << endl;
                }
            }
        }
    }
    fileOrginal.close();
    fileTemporary.close();
    remove("MojeKontakty.txt");
    rename("MojeKontaktyTymczasowy.txt", "MojeKontakty.txt");
}

vector<Contact> deleteContact(vector<Contact> &friends)
{
    char ifErase;
    int userID = 0;
    cout << "Podaj id adresata, ktorego chcesz usunac: ";
    cin >> userID;
    for (vector<Contact>::iterator itr = friends.begin(); itr != friends.end(); ++itr)
    {
        if (itr->id == userID)
        {
            cout << "Czy na pewno chcesz usunac tego adresata z ksiazki? Jeœli tak wcisnij 't' ";
            cin >> ifErase;
            if (ifErase == 't')
            {
                friends.erase(itr);
                changeFile(friends, userID);
                return friends;
            }
            else
                return friends;
        }
    }
    system("pause");
    return friends;
}

vector<Contact> editContactByName(vector<Contact> friends, int idContact)
{
    string newName;
    for (int i =0; i < friends.size(); ++i)
    {
        if (friends[i].id == idContact)
        {
            cout << "Podaj nowe imie: ";
            cin >> newName;
            friends[i].name = newName;
            changeFile(friends, idContact);
        }
    }
    cout << "Dane zostaly zmienione!" << endl;
    system("pause");
    return friends;
}

vector<Contact> editContactBySurname(vector<Contact> friends, int idContact)
{
    string newSurname;
    for (int i =0; i < friends.size(); ++i)
    {
        if (friends[i].id == idContact)
        {
            cout << "Podaj nowe nazwisko: ";
            cin >> newSurname;
            friends[i].surname = newSurname;
            changeFile(friends, idContact);
        }
    }
    cout << "Dane zostaly zmienione!" << endl;
    system("pause");
    return friends;
}

vector<Contact> editContactByMail(vector<Contact> friends, int idContact)
{
    string newMail;
    for (int i =0; i < friends.size(); ++i)
    {
        if (friends[i].id == idContact)
        {
            cout << "Podaj nowy mail: ";
            cin >> newMail;
            friends[i].mail = newMail;
            changeFile(friends, idContact);
        }
    }
    cout << "Dane zostaly zmienione!" << endl;
    system("pause");
    return friends;
}

vector<Contact> editContactByPhoneNumber(vector<Contact> friends, int idContact)
{
    string newPhoneNumber;
    for (int i =0; i < friends.size(); ++i)
    {
        if (friends[i].id == idContact)
        {
            cout << "Podaj nowy numer telefonu: ";
            cin >> newPhoneNumber;
            friends[i].numberOfPhone = newPhoneNumber;
            changeFile(friends, idContact);
        }
    }
    cout << "Dane zostaly zmienione!" << endl;
    system("pause");
    return friends;
}

vector<Contact> editContactByAddress(vector<Contact> friends, int idContact)
{
    string newAddress;
    for (int i =0; i < friends.size(); ++i)
    {
        if (friends[i].id == idContact)
        {
            cout << "Podaj nowy adres: ";
            getline(cin, newAddress);
            friends[i].address = newAddress;
            changeFile(friends, idContact);
        }
    }
    cout << "Dane zostaly zmienione!" << endl;
    system("pause");
    return friends;
}

vector<User> changePassword (vector<User> userBookOfAddresses, int userID)
{
    string newPassword;
    cout << "Podaj nowe haslo: ";
    cin >> newPassword;
    for (int i = 0; i < userBookOfAddresses.size(); ++i)
    {
        if (userBookOfAddresses[i].id == userID)
        {
            userBookOfAddresses[i].password = newPassword;
        }
    }
    changeUserFile(userBookOfAddresses);
    return userBookOfAddresses;
}
