#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <ctime>
using namespace std;

class Admin {
private:
    struct Book {
        string title;
        string author;
        int year;
        int bookNum;
        int quantity;
        string borrower;
    };
    
    struct Credentials {
        string username;
        string password;
    };

public:
    vector<Book> library;
    
    Admin() {}

    bool login(const string& username, const string& password) const {
        ifstream file("textFile/admin.txt");
        if (!file.is_open()) {
            cerr << "Failed to load admin credentials\n";
            return false;
        }
        Credentials adminCredentials;
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            getline(iss, adminCredentials.username, ',');
            getline(iss, adminCredentials.password, ',');
            if (adminCredentials.username == username && adminCredentials.password == password) {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }

    void saveFile(const vector<Book>& library, const string &filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Failed to access file to write\n";
            return;
        }
        for (const auto& book : library) {
            file << book.bookNum << "," << book.title << "," << book.author << "," << book.year << "," << book.quantity << "," << book.borrower << endl;
        }
        file.close();
    }
        void checkBookAvailability(const vector<Book>& library) {
        if (library.empty()) {
            cout << "Library is empty, no books available.\n";
            return;
        }

        cout << "Enter the Book Number to check availability: ";
        int bookNum;
        cin >> bookNum;
        cin.ignore();

        bool found = false;
        for (const auto& book : library) {
            if (book.bookNum == bookNum) {
                found = true;
                cout << "\nBook Details:\n";
                cout << "Book Number: " << book.bookNum << "\n"
                     << "Title: " << book.title << "\n"
                     << "Author: " << book.author << "\n"
                     << "Year: " << book.year << "\n"
                     << "Quantity Available: " << book.quantity << "\n";
                break;
            }
        }

        if (!found) {
            cout << "Book with number " << bookNum << " not found in the library.\n";
        }
    }
    void addBook(vector<Book>& library) {
        Book newBook;
        cout << "Enter Book Title: ";
        getline(cin, newBook.title);
        cout << "Enter Book Author: ";
        getline(cin, newBook.author);
        cout << "Enter Book Year: ";
        cin >> newBook.year;
        cout << "Enter Book Number: ";
        cin >> newBook.bookNum;
        cout << "Enter Book Quantity: ";
        cin >> newBook.quantity;
        cin.ignore();
        newBook.borrower = "";

        library.push_back(newBook);
        saveFile(library, "textFile/book.txt");
    }

    void displayBooks(const vector<Book>& library) const {
        if (library.empty()) {
            cout << "Library is empty.\n";
            return;
        }
        cout << "\nList of Books:\n";
        for (const auto& book : library) {
            cout << "Book Number: " << book.bookNum << "\n"
                 << "Title: " << book.title << "\n"
                 << "Author: " << book.author << "\n"
                 << "Year: " << book.year << "\n"
                 << "Quantity: " << book.quantity << "\n"
                 << "\n";
        }
    }

    void deleteBook(vector<Book>& library) {
        if (library.empty()) {
            cout << "Library is empty, cannot delete.\n";
            return;
        }

        displayBooks(library);
        cout << "Enter the index of the book to delete: ";
        int index;
        cin >> index;
        cin.ignore();

        if (index >= 1 && index <= library.size()) {
            library.erase(library.begin() + index - 1);
            cout << "Book deleted successfully.\n";
            saveFile(library, "textFile/book.txt");
        } else {
            cout << "Invalid index.\n";
        }
    }

    void loadFile(vector<Book>& library, const string & filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Failed to load the file\n";
            return;
        }
        library.clear();
        string line;
        while (getline(file, line)) {
            Book book;
            istringstream iss(line);
            string field;
            if (getline(iss, field, ',')) {
                book.bookNum = stoi(field);
            } else {
                cerr << "Error reading book number\n";
                continue;
            }
            if (getline(iss, field, ',')) {
                book.title = field;
            } else {
                cerr << "Error reading title\n";
                continue;
            }
            if (getline(iss, field, ',')) {
                book.author = field;
            } else {
                cerr << "Error reading author\n";
                continue;
            }
            if (getline(iss, field, ',')) {
                book.year = stoi(field);
            } else {
                cerr << "Error reading year\n";
                continue;
            }
            if (getline(iss, field, ',')) {
                book.quantity = stoi(field);
            } else {
                cerr << "Error reading quantity\n";
                continue;
            }
            if (getline(iss, field, ',')) {
                book.borrower = field;
            } else {
                book.borrower = "";
            }
            library.push_back(book);
        }
        file.close();
    }
void allBorrower() {
    ifstream file("textFile/borrow.txt");
    if (!file.is_open()) {
        cerr << "Failed to open borrow file\n";
        return;
    }
    string line;
    cout << "All Borrowed Books:\n";
    while (getline(file, line)) {
        istringstream iss(line);
        string username, bookNum, title, quantity;
        getline(iss, username, ',');
        getline(iss, bookNum, ',');
        getline(iss, title, ',');
        getline(iss, quantity);
        cout << "Username: " << username << "\n"
             << "Book Num: " << bookNum << "\n"
             << "Title: " << title << "\n"
             << "Quantity: " << quantity << "\n\n";
    }
    file.close();
}
void allBookReturned() {
    std::ifstream file("textFile/return.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open return file\n";
        return;
    }

    std::string line;
    std::cout << "All Returned Books:\n";
    while (std::getline(file, line)) {
        if (!line.empty()) {
            std::istringstream iss(line);
            std::string username, bookNum, title, quantity;

            std::getline(iss, username, ',');
            std::getline(iss, bookNum, ',');
            std::getline(iss, title, ',');
            std::getline(iss, quantity);

            std::cout << "Username: " << username << "\n"
                      << "Book Num: " << bookNum << "\n"
                      << "Title: " << title << "\n"
                      << "Quantity: " << quantity << "\n";
            std::cout << "------------------------\n";
        }
    }

    file.close();
}

void updateBook(vector<Book>& library) {
    if (library.empty()) {
        cout << "Library is empty, cannot update.\n";
        return;
    }

    displayBooks(library);

    cout << "Enter the index of the book to update: ";
    int index;
    cin >> index;
    cin.ignore();

    if (index >= 1 && index <= library.size()) {
        Book& bookToUpdate = library[index - 1];
        int updateOption;
        do {
            cout << "\nUpdate Book\n";
            cout << "1. Book Number\n";
            cout << "2. Title\n";
            cout << "3. Author\n";
            cout << "4. Year\n";
            cout << "5. Quantity\n";
            cout << "6. Exit\n";
            cout << "-> ";
            cin >> updateOption;
            cin.ignore();

            switch (updateOption) {
                case 1: {
                    cout << "Enter new Book Number: ";
                    cin >> bookToUpdate.bookNum;
                    cin.ignore();
                    break;
                }
                case 2: {
                    cout << "Enter new Title: ";
                    getline(cin, bookToUpdate.title);
                    break;
                }
                case 3: {
                    cout << "Enter new Author: ";
                    getline(cin, bookToUpdate.author);
                    break;
                }
                case 4: {
                    cout << "Enter new Year: ";
                    cin >> bookToUpdate.year;
                    cin.ignore();
                    break;
                }
                case 5: {
                    cout << "Enter new Quantity: ";
                    cin >> bookToUpdate.quantity;
                    cin.ignore();
                    break;
                }
                case 6: {
                    cout << "Exiting update menu.\n";
                    break;
                }
                default: {
                    cout << "Invalid option. Try again.\n";
                    break;
                }
            }
        } while (updateOption != 6);

        saveFile(library, "textFile/book.txt");
        cout << "Book updated successfully!\n";
    } else {
        cout << "Invalid index.\n";
    }
}

};

void createAccount() {
    ofstream file("textFile/user.txt", ios::app);
    string fullname, username, password;
    cout << "Enter Fullname: ";
    getline(cin, fullname);
    cout << "Enter Username: ";
    getline(cin, username);
    cout << "Enter Password: ";
    getline(cin, password);
    if (file.is_open()) {
        file << username << "," << password << "," << fullname << endl;
        file.close();
        cout << "Account created.\n";
    } else {
        cerr << "Failed to open file for appending.\n";
    }
}

class User {
private:
    struct Credentials {
        string username;
        string password;
    };

public:
    string username;

    User() {}

    bool login(const string& username, const string& password) {
        ifstream file("textFile/user.txt");
        if (!file.is_open()) {
            cerr << "Failed to load user credentials\n";
            return false;
        }
        Credentials userCredentials;
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            getline(iss, userCredentials.username, ',');
            getline(iss, userCredentials.password, ',');
            if (userCredentials.username == username && userCredentials.password == password) {
                this->username = username;
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }

    bool borrowBook(Admin& admin, int bookNum, int quantity) {
        for (auto& book : admin.library) {
            if (book.bookNum == bookNum) {
                if (book.quantity >= quantity) {
                    book.quantity -= quantity;
                    book.borrower = username;
                    admin.saveFile(admin.library, "textFile/book.txt");

                    ofstream borrowFile("textFile/borrow.txt", ios::app);
                    if (!borrowFile.is_open()) {
                        cerr << "Failed to open borrow file\n";
                        return false;
                    }
                    borrowFile << username << "," << book.bookNum << "," << book.title << "," << quantity << endl;
                    borrowFile.close();

                    cout << "Book borrowed successfully!\n";
                    return true;
                } else {
                    cout << "Not enough books available for borrowing.\n";
                    return false;
                }
            }
        }
        cout << "Book not found.\n";
        return false;
    }
    void returnBook(Admin& admin) {
    std::ifstream borrowFile("textFile/borrow.txt");
    if (!borrowFile.is_open()) {
        std::cerr << "Failed to load borrow file\n";
        return;
    }

    std::vector<std::string> borrowList;
    std::string line;
    bool found = false;

    // Display borrowed books
    std::cout << "\nBooks you have borrowed:\n";
    while (std::getline(borrowFile, line)) {
        std::istringstream iss(line);
        std::string user, bookNumStr, title, quantityStr;
        if (std::getline(iss, user, ',') && user == username &&
            std::getline(iss, bookNumStr, ',') &&
            std::getline(iss, title, ',') &&
            std::getline(iss, quantityStr, ',')) {
            
            std::cout << "Book Number: " << bookNumStr << "\n"
                      << "Title: " << title << "\n"
                      << "Quantity: " << quantityStr << "\n\n";
            borrowList.push_back(line);
            found = true;
        }
    }
    borrowFile.close();

    if (!found) {
        std::cout << "You have not borrowed any books.\n";
        return;
    }

    // Prompt for book number to return
    std::cout << "Enter the book number you want to return: ";
    int bookNum;
    std::cin >> bookNum;
    std::cin.ignore();

    std::ofstream tempFile("textFile/temp_borrow.txt");
    std::ifstream readBorrowFile("textFile/borrow.txt");
    std::ofstream returnFile("textFile/return.txt", std::ios::app);

    if (!tempFile.is_open() || !readBorrowFile.is_open() || !returnFile.is_open()) {
        std::cerr << "Failed to process borrow or return files\n";
        return;
    }

    bool returnSuccess = false;
    while (std::getline(readBorrowFile, line)) {
        std::istringstream iss(line);
        std::string user, bookNumStr, title, quantityStr;
        if (std::getline(iss, user, ',') &&
            std::getline(iss, bookNumStr, ',') &&
            std::getline(iss, title, ',') &&
            std::getline(iss, quantityStr, ',')) {
            
            if (user == username && std::stoi(bookNumStr) == bookNum) {
                int quantity = std::stoi(quantityStr);
                for (auto& book : admin.library) {
                    if (book.bookNum == bookNum) {
                        book.quantity += quantity;
                        admin.saveFile(admin.library, "textFile/book.txt");
                        returnFile << username << "," << book.bookNum << "," << book.title << "," << quantity << std::endl;
                        std::cout << "Book returned successfully!\n";
                        returnSuccess = true;
                    }
                }
            } else {
                tempFile << line << std::endl;
            }
        }
    }

    readBorrowFile.close();
    tempFile.close();
    returnFile.close();

    if (returnSuccess) {
        std::remove("textFile/borrow.txt");
        std::rename("textFile/temp_borrow.txt", "textFile/borrow.txt");
    } else {
        std::cerr << "Failed to return the book\n";
    }
}
    
    void displayBorrow(const string& borrowFilename, const string& username) {
    ifstream borrowFile(borrowFilename);
    if (!borrowFile.is_open()) {
        cerr << "Failed to open borrow file\n";
        return;
    }

    string line;
    bool found = false;

    cout << "Borrowed Books:\n";
    while (getline(borrowFile, line)) {
        istringstream iss(line);
        string user, bookNumStr, title, quantityStr;
        if (getline(iss, user, ',') && user == username &&
            getline(iss, bookNumStr, ',') &&
            getline(iss, title, ',') &&
            getline(iss, quantityStr, ',')) {
            cout << "Book Number: " << bookNumStr << "\n"
                 << "Title: " << title << "\n"
                 << "Quantity: " << quantityStr << "\n\n";
            found = true;
        }
    }

    borrowFile.close();

    if (!found) {
        cout << "No borrowed books found for user " << username << ".\n";
    }
}

void displayReturned(const string& returnFilename, const string& username) {
    ifstream returnFile(returnFilename);
    if (!returnFile.is_open()) {
        cerr << "Failed to open return file\n";
        return;
    }

    string line;
    bool found = false;

    cout << "Returned Books:\n";
    while (getline(returnFile, line)) {
        istringstream iss(line);
        string user, bookNumStr, title, quantityStr;
        if (getline(iss, user, ',') && user == username &&
            getline(iss, bookNumStr, ',') &&
            getline(iss, title, ',') &&
            getline(iss, quantityStr, ',')) {
            cout << "Book Number: " << bookNumStr << "\n"
                 << "Title: " << title << "\n"
                 << "Quantity: " << quantityStr << "\n\n";
            found = true;
        }
    }

    returnFile.close();

    if (!found) {
        cout << "No returned books found for user " << username << ".\n";
    }
}

};

int main() {
    Admin admin;
    User user;
    admin.loadFile(admin.library, "textFile/book.txt");

    string username, password;
    int choices;

    cout << "-----WELCOME TO BOOK BORROWING SYSTEM!-----\n";
    while (true) {
        cout << "  Who is using now?\n";
        cout << "     1. Admin\n";
        cout << "     2. User\n";
        cout << "     3. Create Account\n";
        cout << "     4. Quit\n";
        cout << "->";
        cin >> choices;
        cin.ignore();
        if (choices == 1) {
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter password: ";
            getline(cin, password);

            if (admin.login(username, password)) {
                cout << "Login successful!\n";
                int option;
                do {
                    cout << "\nLibrary System Menu\n";
                    cout << "1. Add Book\n";
                    cout << "2. Delete Book\n";
                    cout << "3. Display Books\n";
                    cout << "4. Update Books\n";
                    cout << "5. View Borrowed Books\n";
                    cout << "6. View Returned Books\n";
                    cout << "7. View Book Availability\n";
                    cout << "8. Logout\n";
                    cout << "->";
                    cin >> option;
                    cin.ignore();

                    switch (option) {
                    case 1:
                        admin.addBook(admin.library);
                        break;
                    case 2:
                        admin.deleteBook(admin.library);
                        break;
                    case 3:
                        admin.displayBooks(admin.library);
                        break;
                    case 4:
                        admin.updateBook(admin.library);
                        break;
                    case 5:
                        admin.allBorrower();
                        break;
                    case 6:
                        admin.allBookReturned();
                        break;
                    case 7:
                        admin.checkBookAvailability(admin.library);
                        break;
                    case 8:
                        cout << "Quitting...\n";
                        break;
                    default:
                        cout << "Invalid choice. Try again.\n";
                    }
                } while (option != 8);
            } else {
                cout << "Invalid username or password.\n";
            }
        } else if (choices == 2) {
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter password: ";
            getline(cin, password);
            if (user.login(username, password)) {
                int option;
                do {
                    cout << "\nLibrary System Menu\n";
                    cout << "1. Show Books\n";
                    cout << "2. Borrow\n";
                    cout << "3. Return\n";
                    cout << "4. Borrowed\n";
                    cout << "5. Returned\n";
                    cout << "6. Logout\n";
                    cout << "->";
                    cin >> option;
                    cin.ignore();

                    switch (option) {
                    case 1:
                        admin.displayBooks(admin.library);
                        break;
                    case 2:
                        admin.displayBooks(admin.library);
                        cout << "Enter Book Number to Borrow: ";
                        int bookNum;
                        cin >> bookNum;
                        cout << "Enter Quantity to Borrow: ";
                        int quantity;
                        cin >> quantity;
                        cin.ignore();
                        user.borrowBook(admin, bookNum, quantity);
                        break;
                    case 3:
                        user.returnBook(admin);
                        break;
                    case 4:
                        user.displayBorrow("textFile/borrow.txt", username);
                        break;
                    case 5:
                        user.displayReturned("textFile/return.txt", username);
                        break;
                    case 6:
                        cout << "\nLogout Successfully\n\n";
                        break;
                    default:
                        cout << "Invalid choice. Try again.\n";
                    }
                } while (option != 6);
            } else {
                cout << "Invalid username or password, Try Again\n";
            }
        } else if (choices == 3) {
            createAccount();
        } else if (choices == 4) {
            cout << "Thanks for using! Don't forget to return the books\n";
            break;
        }
    }
    return 0;
}
