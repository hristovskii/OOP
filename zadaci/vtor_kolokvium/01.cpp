/*
Издавачката куќа FINKI-Education издава онлајн и печатени книги. За секоја книга се чуваат податоци за ISBN бројот (низа од најмногу 20 знаци), насловот (низа од најмногу 50 знаци), авторот (низа од најмногу 30 знаци) и основната цена изразена во $ (реален број). Класата за опишување на книгите е апстрактна (5 поени).

За секоја онлајн книга дополнително се чуваат податоци за url од каде може да се симне (динамички резервирана низа од знаци) и големината изразена во MB (цел број). За секоја печатена книга дополнително се чуваат податоци за масата изразена во килограми (реален број) и дали ја има на залиха (логичка променлива). (5 поени)

За секој објект од двете изведени класи треба да бидат на располагање следниве методи:

Метод bookPrice, за пресметување на продажната цена на книгата на следниот начин: (10 поени)

За онлајн книга - цената се зголемува за 20% од основната цена ако книгата е поголема од 20MB

За печатена книга - цената се зголемува за 15% од основната цена ако масата на книгата е поголема од 0.7kg

Преоптоварен оператор > за споредба на две книги од каков било вид според нивната цена. (5 поени)

Преоптоварен оператор << за печатење на податоците за книгите во формат: (5 поени)
Да се имплементира функција mostExpensiveBook со потпис:

void mostExpensiveBook (Book** books, int n)

во која се печати вкупниот број на онлајн, односно, печатени книги во проследената низа посебно. (5 поени) Потоа се наоѓа и печати најскапата книга. (5 поени)

Да се обезбедат сите потребни функции за правилно функционирање на програмата. (5 поени)

For example:

Input	
4
3
1
0-312-31677-1
The Moscow Vector
Robert Ludlum
7
www.finki-education/olinebooks/book1.pdf
1
2
007-6092006565
Thinking in C++
Bruce Eckel
52
1.2
1
1
978-0672326974
C++ Primer Plus
Stephen Prata
20
www.finki-education/olinebooks/book2.pdf
30

Result
====== Testing method mostExpensiveBook() ======
FINKI-Education
Total number of online books: 2
Total number of print books: 1
The most expensive book is: 
007-6092006565: Thinking in C++, Bruce Eckel 59.8

*/

#include <iostream>
#include <cstring>

using namespace std;

class Book {
protected:
    char ISBN[21];
    char title[51];
    char author[31];
    float price;
public:
    Book(char *isbn = " ", char *title = " ", char *author = " ", float price = 0) : price(price) {
        strcpy(this->ISBN, isbn);
        strcpy(this->title, title);
        strcpy(this->author, author);
    }

    Book(const Book &other) {
        strcpy(this->ISBN, other.ISBN);
        strcpy(this->title, other.title);
        strcpy(this->author, other.author);
        price = other.price;
    }

    const char *getIsbn() const { return ISBN; }

    const char *getTitle() const { return title; }

    const char *getAuthor() const { return author; }

    float getPrice() const { return price; }

    void setPrice(float price) { this->price = price; }

    void setISBN(char *isbn) { strcpy(this->ISBN, isbn); }

    Book &operator=(const Book &other) {
        if (this != &other) {
            strcpy(this->ISBN, other.ISBN);
            strcpy(this->title, other.title);
            strcpy(this->author, other.author);
            price = other.price;
        }
        return *this;
    }

    virtual float bookPrice() = 0;

    bool operator>(Book &other) {
        return bookPrice() > other.bookPrice();
    }

    friend ostream &operator<<(ostream &os, Book &book) {
        os << book.ISBN << ": " << book.title << ", " << book.author << " " << book.bookPrice() << endl;
        return os;
    }

    virtual ~Book() {}
};

class OnlineBook : public Book {
private:
    char *url;
    int mb;
public:
    OnlineBook(char *isbn = " ", char *title = " ", char *author = " ", float price = 0, char *url = " ", int mb = 0)
            : Book(isbn, title, author,
                   price), mb(mb) {
        this->url = new char[strlen(url) + 1];
        strcpy(this->url, url);
    }

    OnlineBook(const OnlineBook &other) : Book(other) {
        this->mb = other.mb;
        this->url = new char[strlen(other.url) + 1];
        strcpy(this->url, other.url);
    }

    OnlineBook &operator=(const OnlineBook &other) {
        if (this != &other) {
            Book::operator=(other);
            this->mb = other.mb;
            delete[] url;
            this->url = new char[strlen(other.url) + 1];
            strcpy(this->url, other.url);
        }
        return *this;
    }

    float bookPrice() override {
        float update = price;
        if (mb > 20) {
            update = price * 1.2;
        }
        return update;
    }

    virtual ~OnlineBook() {
        delete[] url;
    }
};

class PrintBook : public Book {
private:
    float kg;
    bool stock;
public:
    PrintBook(char *isbn = " ", char *title = " ", char *author = " ", float price = 0, float kg = 0,
              bool stock = false) : Book(isbn, title, author,
                                         price), kg(kg),
                                    stock(stock) {
    }

    PrintBook(const PrintBook &other) : Book(other) {
        this->kg = other.kg;
        this->stock = other.stock;
    }

    PrintBook &operator=(const PrintBook &other) {
        if (this != &other) {
            Book::operator=(other);
            this->kg = other.kg;
            this->stock = other.stock;
        }
        return *this;
    }

    float bookPrice() override {
        float update = price;
        if (kg > 0.7) {
            update = price * 1.15;
        }
        return update;
    }

    virtual ~PrintBook() {}
};

void mostExpensiveBook(Book **books, int n) {
    int counter1 = 0;
    int counter2 = 0;
    Book *max = books[0];
    for (int i = 0; i < n; i++) {
        OnlineBook *casted1 = dynamic_cast<OnlineBook *>(books[i]);
        PrintBook *casted2 = dynamic_cast<PrintBook *>(books[i]);
        if (casted1) {
            counter1++;
        } else if (casted2) {
            counter2++;
        }
    }
    for (int i = 0; i < n; i++) {
        if (books[i]->bookPrice() > max->bookPrice()) {
            max = books[i];
        }
    }
    cout << "FINKI-Education" << endl;
    cout << "Total number of online books: " << counter1 << endl;
    cout << "Total number of print books: " << counter2 << endl;
    cout << "The most expensive book is:" << endl;
    cout << *max;
}

int main() {

    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++) {
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 2) {
        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
    }
    if (testCase == 3) {
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++) {
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 4) {
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++) {

            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1) {

                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);

            } else {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }

        mostExpensiveBook(books, n);
    }

    for (int i = 0; i < n; i++) delete books[i];
    delete[] books;
    return 0;
}
