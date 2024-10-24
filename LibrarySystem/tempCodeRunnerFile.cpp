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