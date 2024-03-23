/*
 Да се напише класа Book во која се чуваат информации за името на книгата (динамички алоцирана низа од знаци), isbn на книгата (динамички алоцирана низа од 5 цели броја) и број на страници (цел број). За класата да се обезбедат set и get методите што се користат и да се преоптоварат следните оператори:

оператор == за споредување на две книги според isbn-от

оператор << за печатење на податоци за книгата во формат Title: наслов ISBN:[x y z k l]

Да се напише класа BorrowABook за библиотека за изнајмување книги  во која се чуваат информација за името на бибилиотеката (низа од 100 знци), низа од книги (динамички алоцирана низа од објекти од класата Book) и број на книги со кој располага (цел број). Во класата BorrowABook да се напише конструктор со еден аргумент за иницијализација на името на библиотеката. При секое додавање на нова книга во библиотеката, динамички алоцираната низа да го зголемува капацитетот за 1 елемент. Во оваа класа да се преоптоварат операторите:

+= за додавање на нова книга во библиотеката и

-= за отстранување на дадена книга од библиотеката (онаа со веќепостоечки ISBN кој се поклопува со ISBN-от на друга книга).

На излез да се отпечатат името на библиотеката и листа на книги што таа ги изнајмува, а чиј број на страници е поголем од 150. Последново да се направи со функција printNumberOfPages(int max) што треба да се дефинира во класата BorrowABook.

Појаснување на main функцијата: Информациите за книгите се читаат од тастатура со операторот +=. Во последниот ред од влезот дадени се информации за книгата која што се внесува грешно бидејќи има ист isbn како и друга книга. Потребно е истата да биде избришана.
!!! ДА НЕ СЕ ПРАВАТ ПРОМЕНИ ВО MAIN() ФУНКЦИЈАТА !!!

For example:

Input	Result
3
Hamlet 4 5 6 7 4 200
Macbeth 2 3 4 1 2 120
Dracula 1 2 1 1 1 130
Rebecca 1 2 1 1 1 100

 Result
FINKI-Library
Title: Hamlet ISBN: [ 4 5 6 7 4 ]

 */

#include<iostream>
#include<cstring>
using namespace std;
//klasa Book
class Book
{
private:
    char *ime;//ime e dinamicki alocirana niza od karakteri (znaci)
    int *isbn;//isbn e dinamicki alocirana niza od celi broevi
    int brojNaStranici;
public:
    //Neskafe konstruktor (2 vo 1 konstruktor-->Neskafe konstruktorot(2 vo 1 konstruktor) e konstruktor koj e i defolten konstruktor i parametarski konstruktor)
    Book(char *ime=new char[0],int *isbn=new int[0],int brojNastranici=0)
    {
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        this->isbn=new int[5];
        for(int i=0;i<5;i++)
        {
            this->isbn[i]=isbn[i];
        }
        this->brojNaStranici=brojNastranici;
    }
    //Copy konstruktor(Copy konstruktor e konstruktor koj kreira kopija na objektot koj e prosleden kako vlezen argument na konstruktorot)
    Book(const Book &book)
    {
        this->ime=new char[strlen(book.ime)+1];
        strcpy(this->ime,book.ime);
        this->isbn=new int[5];
        for(int i=0;i<5;i++)
        {
            this->isbn[i]=book.isbn[i];
        }
        this->brojNaStranici=book.brojNaStranici;

    }
    //Operator =
    //Primer:A=B;
    Book &operator=(const Book &book)
    {
        if(this!=&book)
        {
            delete [] ime;
            this->ime=new char[strlen(book.ime)+1];
            strcpy(this->ime,book.ime);
            delete [] isbn;
            this->isbn=new int[5];
            for(int i=0;i<5;i++)
            {
                this->isbn[i]=book.isbn[i];
            }
            this->brojNaStranici=book.brojNaStranici;
        }
        return *this;
    }
    //Destruktor-->(Destruktor e metoda so koja se vrshi delokacija na memorijata koja bila alocirana za odreden objekt)
    ~Book()
    {
        delete [] ime;
        delete [] isbn;
    }
    //Operator == za sporeduvawe na dve knigi spored isbn
    //Primer:A==B;
    bool operator==(const Book &book)
    {
        for(int i=0;i<5;i++)
        {
            if(this->isbn[i]!=book.isbn[i])
            {
                return false;
            }
        }
        return true;
    }
    //Operator << za pecatewe na edna kniga vo format Title: naslov ISBN: [x y z k l]
    friend ostream &operator<<(ostream & out,const Book &book)
    {
        out<<"Title: "<<book.ime<<" ISBN: [ ";
        for(int i=0;i<5;i++)
        {
            if(i!=4)
            {
                out<<book.isbn[i]<<" ";

            }else
            {
                out<<book.isbn[i];
            }
        }
        out<<" ]"<<endl;
        return out;
    }
    //get metoda za brojnastranici
    int getbrojNaStranici()
    {
        return brojNaStranici;
    }

};
//klasa BorrowABook
class BorrowABook
{
private:
    char ime[101];//ime e niza od 100 karakteri plus eden karakter za null terminatorot dokolku korisnikot vnese poveke od 100 karakteri (znaci)
    Book *books;//books e dinamicki alocirana niza od knigi od klasata Book
    int brojNaKnigi;
public:
    //Parametarski konstruktor so eden parametar-->(Parametarski konstruktor e konstruktor koj prima parametri kako vlezni argumenti i istite gi postavuva kako privatni atributi na odrden objekt od odredena klasa)
    BorrowABook(char *ime=" ")
    {
        strcpy(this->ime,ime);
        this->books=new Book[0];
        this->brojNaKnigi=0;
    }
    //Copy konstruktor-->(Copy konstruktor e konstruktor koj pravi kopija na objekt prosleden kako vlezen argument na klasata)
    BorrowABook(const BorrowABook &borrowABook)
    {
        strcpy(this->ime,borrowABook.ime);
        this->brojNaKnigi=borrowABook.brojNaKnigi;
        this->books=new Book[brojNaKnigi];
        for(int i=0;i<brojNaKnigi;i++)
        {
            this->books[i]=borrowABook.books[i];
        }
    }
    //Operator =
    //Primer A=B;
    BorrowABook &operator=(const BorrowABook &borrowABook)
    {
        if(this!=&borrowABook)
        {
            strcpy(this->ime,borrowABook.ime);
            this->brojNaKnigi=borrowABook.brojNaKnigi;
            delete [] books;
            this->books=new Book[brojNaKnigi];
            for(int i=0;i<brojNaKnigi;i++)
            {
                this->books[i]=borrowABook.books[i];
            }
        }
        return *this;
    }
    //Destruktor-->(Destruktor e metoda koja vrshi delokacija na memorijata koja e alocirana od odreden objket)
    ~BorrowABook()
    {
        delete [] books;
    }
    //Operator += za dodavawe na nova kniga vo bibliotekata
    //Primer:A+=kniga;
    BorrowABook &operator+=(const Book &book)
    {
        Book *temp=new Book[brojNaKnigi+1];
        for(int i=0;i<brojNaKnigi;i++)
        {
            temp[i]=books[i];
        }
        temp[brojNaKnigi++]=book;
        delete [] books;
        books=temp;
        return *this;
    }
    //Operator -= za brisewe na odredena kniga ako toj ima ist isbn
    //Primer: A-=kniga;
    BorrowABook &operator-=(const Book &book)
    {
        Book *temp=new Book[brojNaKnigi-1];
        int j=0;
        for(int i=0;i<brojNaKnigi;i++)
        {
            if(books[i]==book)
            {
                continue;
            }else
            {
                temp[j]=books[i];
                j++;
            }
        }
        brojNaKnigi--;
        delete [] books;
        books=temp;
        return *this;
    }
    //printNumberOfPages(int max)
    void printNumberOfPages(int max)
    {
        cout<<ime<<endl;
        for(int i=0;i<brojNaKnigi;i++)
        {
            if(books[i].getbrojNaStranici()>max)
            {
                cout<<books[i];
            }
        }
    }
};
int main()
{
    BorrowABook library("FINKI-Library");
    int n;
    cin>>n;

    for (int i=0;i<n;i++)
    {
        char title[100];
        int isbn[5];
        int pages;

        cin>>title;

        for (int j=0;j<5;j++)
            cin>>isbn[j];

        cin>>pages;

        Book nov=Book(title,isbn,pages);

        //adding a new book
        library+=nov;

    }
    //the book which has the same isbn as some previous one
    char title[100];
    int isbn[5];
    int pages;
    cin>>title;
    for (int i=0;i<5;i++)
        cin>>isbn[i];
    cin>>pages;

    Book greshka=Book(title,isbn,pages);

    //deleting a book
    library-=greshka;

    library.printNumberOfPages(150);

    return 0;
}