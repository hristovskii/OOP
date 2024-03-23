/*
 За да се овозможи прецизна контрола и евиденција за состојбата на книгите во една библиотека, потребно е да се имплементира модул со следниве класи и функционалности:

Да се имплементира класа Book во која ќе се чуваат информации за:

ISBN (низа од најмногу 13 знаци)
Наслов (динамички алоцирана низа од знаци)
Издавачка куќа (низа од најмногу 20 знаци)
Состојба (една книга може да се најде во состојба НЕИЗНАЈМЕНА, СЕ_РЕПАРИРА или ИЗНАЈМЕНА)
Вкупен број на изнајмувања (цел број)
За класата да се имплементираат потребните конструктори, оператор = и методи за да функционира решението. (10 поени). Дополнително за класата да се имплементира метод void print() за печатење на информациите за книгата (според тест примерите). (5 поени)

Да се имплементира класа BookService во која ќе се чуваат информации за:

Име на библиотека каде се наоѓа сервисот (низа од најмногу 20 знаци)
Листа на книги кои моментално се наоѓаат во сервисот (динимички алоцирана низа од објекти од класата Book, иницијално без елементи)
Број на книги во сервисот (број на елементи во низата со книги - цел број, иницијално е 0)
За класата да се имплементираат потребните конструктори и методи со цел да функционира решението. (5 поени) Дополнително во класата да се имплементираат:

метод void addBook (Book book) - за додавање нoва книга во сервисот (5 поени). Една книга може да се додаде во сервисот само ако се наоѓа во состојба НЕИЗНАЈМЕНА. Дополнително, ако веќе во сервисот има книга со иста издавачка куќа како книгата која сакаме да ја додадеме, потребно е во сервисот да остане книгата со поголем број на изнајмувања. Кога книгата се додава во сервисот нејзината состојба преминува во состојба СЕ_РЕПАРИРА (10 поени).
метод Book repairNewestBook() - за репарирање на најновата книга. За најнова книга се смета онаа книга од листата која има најмал број на изнајмувања. Репарирањето на една книга означува:

Потребно е книгата да биде избришана од листата со книги во сервисот
Книгата треба да премине од состојба СЕ_РЕПАРИРА во состојба НЕИЗНАЈМЕНА
Доколку има повеќе книги со ист број на изнајмувања при одредувањето на најнова книга, тогаш потребно е да се избрише книгата чија што издавачка куќа е всушност библиотеката каде што се наоѓа сервисот. Во ваква ситуација, секогаш само една од книгите ќе има издавачка книга иста со библиотеката на сервисот. (15 поени)
метод void print() - за печатење на информации за сите книги кои моментално се наоѓаат на репарирање во сервисот (формат во тест примери) (10 поени)
For example:

Input	Result
4
 Result
TESTING CONSTRUCTOR FOR BOOKSERVICE
TEST PASSED
5
2
966-13-43-11
FINKI-OOP
FINKI
13
0
966-13-43-53
FINKI-ONWD
FINKITEAM
13
1
 Result
TESTING ADD() AND PRINT() FOR BOOKSERVICE
FINKI
ISBN: 966-13-43-11 - REPAIRING FINKI-OOP, 13, FINKI

 */

#include <iostream>
#include <cstring>
using namespace std;

enum state{
    AVAILABLE, REPAIRING, NOT_AVAILABLE
};

class Book{
private:
    char ISBN[13];
    char *title;
    char publishing_house[20];
    int total_rents;
    state s;
public:
    Book(char *ISBN="", char *title="", char *publishing_house="", int total_rents=0, int ss = 0){
        this->title = new char[strlen(title)+1];
        strcpy(this->title, title);
        strcpy(this->ISBN, ISBN);
        strcpy(this->publishing_house, publishing_house);
        this->total_rents=total_rents;
        s=(state)ss;
    }
    Book(const Book &a){
        this->title = new char[strlen(a.title)+1];
        strcpy(this->title, a.title);
        strcpy(this->ISBN, a.ISBN);
        strcpy(this->publishing_house, a.publishing_house);
        this->total_rents=a.total_rents;
        s=a.s;
    }
    Book &operator=(const Book &a){
        if(this!=&a){
            delete [] title;
            this->title = new char[strlen(a.title)+1];
            strcpy(this->title, a.title);
            strcpy(this->ISBN, a.ISBN);
            strcpy(this->publishing_house, a.publishing_house);
            this->total_rents=a.total_rents;
            s=a.s;
        }
        return *this;
    }
    ~Book(){
        delete [] title;
    }
    void print(){
        cout<<"ISBN: "<<ISBN<<" - ";
        if(s==0)
        {
            cout<<"AVAILABLE ";
        }
        else if(s==1)
        {
            cout<<"REPAIRING ";
        }
        else cout <<"NOT AVAILABLE ";
        cout<<title<<", "<<total_rents<<", "<<publishing_house<<endl;
    }
    state get_state(){
        return s;
    }
    char *get_publishing_house(){
        return publishing_house;
    }
    int get_total_rents(){
        return total_rents;
    }
    void set_state(int k){
        s = (state)k;
    }
};

class BookService{
private:
    char library_name[20];
    Book *arr;
    int n;
public:
    BookService(char *library_name=""){
        strcpy(this->library_name, library_name);
        arr = new Book[0];
        n=0;
    }
    BookService(const BookService &a){
        strcpy(this->library_name, a.library_name);
        n=a.n;
        arr = new Book[n];
        for(int i=0; i<n; i++){
            arr[i] = a.arr[i];
        }
    }
    BookService &operator=(const BookService &a){
        if(this!=&a){
            delete [] arr;
            strcpy(this->library_name, a.library_name);
            n=a.n;
            arr = new Book[n];
            for(int i=0; i<n; i++){
                arr[i] = a.arr[i];
            }
        }
        return *this;
    }
    ~BookService(){
        delete [] arr;
    }
    void print(){
        cout<<library_name<<endl;
        if(n>0){
            for(int i=0; i<n; i++){
                arr[i].print();
            }
        }else{
            cout<<"-- EMPTY --"<<endl;
        }
    }
    void addBook(Book p){
        if(p.get_state()==0){
            p.set_state(1);
            for(int i=0; i<n; i++){
                if(strcmp(arr[i].get_publishing_house(),p.get_publishing_house())==0){
                    if(p.get_total_rents()>arr[i].get_total_rents()){
                        arr[i]=p;
                    }
                    return;
                }
            }
            Book *tmp = new Book[n+1];
            for(int i=0; i<n; i++){
                tmp[i] = arr[i];
            }
            tmp[n++] = p;
            delete [] arr;
            arr = tmp;
        }
    }
    Book repairNewestBook(){
        Book newest = arr[0];
        int index = 0;
        for(int i=1; i<n; i++){
            if(arr[i].get_total_rents()<newest.get_total_rents()){
                newest=arr[i];
                index=i;
            }else if(arr[i].get_total_rents()==newest.get_total_rents()){
                if(strcmp(arr[i].get_publishing_house(), library_name)==0){
                    newest=arr[i];
                    index=i;
                }
            }
        }
        Book *tmp = new Book[n-1];
        for(int i=0, j=0; i<n; i++){
            if(i!=index){
                tmp[j++] = arr[i];
            }
        }
        n--;
        delete [] arr;
        arr = tmp;
        newest.set_state(0);
        return newest;
    }
};

int main() {
    int testCase;
    cin >> testCase;
    char ISBN[13];
    char title[20];
    char publishing_house[20];
    int total_rents;
    int state;
    if (testCase == 1) {
        cout << "TESTING CONSTRUCTOR FOR BOOK" << endl;
        Book a;
        cout << "TEST FOR DEFAULT CONSTRUCTOR PASSED" << endl;
        Book a1("966-13-43-72", "FINKI-ONWD", "FINKI", 25);
        cout << "TEST FOR CONSTRUCTOR WITH 3 ARGUMENTS PASSED" << endl;
        Book a2("966-13-43-11", "FINKI-OOP", "FINKI", 20, 0);
        cout << "TEST FOR CONSTRUCTOR WITH 4 ARGUMENTS PASSED" << endl;
    } else if (testCase == 2) {
        cout << "TESTING COPY-CONSTRUCTOR AND OPERATOR = (ASSIGNMENT) FOR BOOK" << endl;
        Book a("966-13-43-11", "FINKI-OOP", "FINKI", 20, 0);
        Book a1(a);
        cout << "TEST FOR COPY CONSTRUCTOR PASSED" << endl;
        Book a2;
        a2 = a;
        cout << "TEST FOR OPERATOR = (ASSIGNMENT) PASSED" << endl;
    } else if (testCase == 3) {
        cout << "TESTING PRINT() FOR BOOK" << endl;
        cin>>ISBN>>title>>publishing_house>>total_rents>>state;
        Book a(ISBN, title, publishing_house, total_rents, state);
        a.print();
    } else if (testCase == 4) {
        cout << "TESTING CONSTRUCTOR FOR BOOKSERVICE" << endl;
        BookService as("FINKI");
        cout << "TEST PASSED" << endl;
    } else if (testCase == 5) {
        cout << "TESTING ADD() AND PRINT() FOR BOOKSERVICE" << endl;
        BookService as("FINKI");
        int n;
        cin>>n;
        for(int i=0; i<n; i++){
            cin>>ISBN>>title>>publishing_house>>total_rents>>state;
            Book a(ISBN, title, publishing_house, total_rents, state);
            as.addBook(a);
        }
        as.print();
    } else if (testCase == 6) {
        cout << "TESTING repairNewestBook() AND PRINT() FOR BOOKSERVICE" << endl;
        BookService as("FINKI");
        int n;
        cin>>n;
        for(int i=0; i<n; i++){
            cin>>ISBN>>title>>publishing_house>>total_rents>>state;
            Book a(ISBN, title, publishing_house, total_rents, state);
            as.addBook(a);
        }
        Book p = as.repairNewestBook();
        cout<<"Repaired book:"<<endl;
        p.print();
        cout<<"-----------------"<<endl;
        as.print();
    }  else if (testCase == 7) {
        cout << "TESTING COPY CONSTRUCTOR AND OPERATOR = FOR BOOKSERVICE" << endl;
        BookService as("FINKI");
        Book a2("966-13-43-11", "FINKI-OOP", "FINKI", 20, 0);
        as.addBook(a2);

        BookService s1 = as; //copy constructor
        BookService s2;
        s2 = s1; //operator =
        s1.print();
        s2.print();
    }
    return 0;
}

