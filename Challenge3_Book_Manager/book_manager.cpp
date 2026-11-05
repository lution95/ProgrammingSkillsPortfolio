#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdexcept>
using namespace std;
class Book
{
private:
    string title;
    string author;
    int pages;
    int id;
    bool borrowed;
public:
    Book(string t, string a, int p, int i, bool b)
        : title(t), author(a), pages(p), id(i), borrowed(b) {}
    int getId() const { return id; }
    // Prevent duplicate status changes.
    bool setBorrowed(bool state)
    {
        if (borrowed == state)
        {
            return false;
        }
        borrowed = state;
        return true;
    }
    void displaySummary() const
    {
        cout << right << setfill('0') << setw(3) << id << setfill(' ') << "  " << left
             << setw(32) << title << setw(24) << author
             << (borrowed ? "Borrowed" : "Available") << endl;
    }
    void displayDetails() const
    {
        cout << "\nTitle:  " << title << "\nAuthor: " << author << "\nPages:  " << pages
             << "\nID:     " << right << setfill('0') << setw(3) << id << setfill(' ')
             << "\nStatus: " << (borrowed ? "Borrowed" : "Available") << endl;
    }
    void writeTo(ostream &out) const
    {
        out << title << "," << author << "," << pages << "," << right << setfill('0') << setw(3)
            << id << setfill(' ') << "," << (borrowed ? "true" : "false") << endl;
    }
};
// Validate and load records.
vector<Book> loadBooks(const string &filename)
{
    vector<Book> books;
    ifstream file(filename);
    string line;
    while (getline(file, line))
    {
        if (!line.empty() && line.back() == '\r')
        {
            line.pop_back();
        }
        stringstream ss(line);
        string title, author, pages, id, status;
        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, pages, ',');
        getline(ss, id, ',');
        getline(ss, status, ',');
        try
        {
            size_t pEnd, iEnd;
            int p = stoi(pages, &pEnd), i = stoi(id, &iEnd);
            if (pEnd != pages.size() || iEnd != id.size() || p <= 0 || i <= 0
                || title.empty() || author.empty() || (status != "true" && status != "false"))
                throw invalid_argument("Invalid record");
            for (const Book &book : books)
                if (book.getId() == i) throw invalid_argument("Duplicate ID");
            books.push_back(Book(title, author, p, i, status == "true"));
        }
        catch (const exception &)
        {
            cout << "Invalid record skipped." << endl;
        }
    }
    return books;
}
// Save current book availability.
bool saveBooks(const vector<Book> &books, const string &filename)
{
    ofstream file(filename);
    if (!file) return false;
    for (const Book &book : books)
    {
        book.writeTo(file);
    }
    file.close();
    return !file.fail();
}
Book *askForBook(vector<Book> &books)
{
    string input;
    int wanted;
    cout << "Book ID: ";
    getline(cin, input);
    istringstream stream(input);
    if (stream >> wanted && (stream >> ws).eof())
    {
        for (Book &book : books)
        {
            if (book.getId() == wanted)
            {
                return &book;
            }
        }
    }
    cout << "Invalid ID." << endl;
    return nullptr;
}

int main()
{
    const string FILENAME = "bookData.txt";
    vector<Book> books = loadBooks(FILENAME);
    if (books.empty())
    {
        cout << "No books loaded." << endl;
        return 1;
    }

    string choice;
    do
    {
        cout << "\nBook Manager\n1. List books\n2. View book\n"
             << "3. Borrow book\n4. Return book\n5. Quit\nChoice: ";
        if (!getline(cin, choice))
        {
            break;
        }

        if (choice == "1")
        {
            cout << "ID   " << left << setw(32) << "Title" << setw(24) << "Author" << "Status\n";
            for (const Book &book : books)
            {
                book.displaySummary();
            }
        }
        else if (choice == "2" || choice == "3" || choice == "4")
        {
            Book *book = askForBook(books);
            if (book == nullptr)
            {
                continue;
            }
            if (choice == "2")
            {
                book->displayDetails();
            }
            else if (book->setBorrowed(choice == "3"))
            {
                if (saveBooks(books, FILENAME))
                    cout << (choice == "3" ? "Book borrowed." : "Book returned.") << endl;
                else {
                    book->setBorrowed(choice != "3");
                    cout << "Save failed. Change cancelled." << endl;
                }
            }
            else
            {
                cout << (choice == "3" ? "Already borrowed."
                                       : "Already available.") << endl;
            }
        }
        else if (choice != "5")
        {
            cout << "Invalid choice. Use 1-5." << endl;
        }
    } while (choice != "5");

    cout << "Goodbye!" << endl;
    return 0;
}
