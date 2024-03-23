/*
Да се креира класа Customer за опишување на купувачи на една книжара. За секој купувач се чуваат податоци за:

името (низа од 50 знаци),
електронска адреса (низа од 50 знаци),
вид на купувач (стандардни, лојални или вип),
основен попуст (цел број изразен во проценти),
дополнителен попуст (цел број изразен во проценти) и
број на купени производи. (5 поени)
Сите лојални купувачи со покажување на клуб картичка имаат право на основниот попуст при купување од книжарата. Основниот попуст е ист за сите лојални купувачи и изнесува 10%. Оваа вредност може да се смени со одлука на раководството на книжарата. Дополнителниот попуст е фиксен и може да го користат само вип купувачите и изнесува 20%. Стандардните купувачи немаат право на попуст (5 поени).

За оваа класа да се имплементира оператор << за печатење на купувач во формат:

[ime_na_kupuvac]
[email_na_kupuvac]
[broj_na_proizvodi]
[vid_na_kupuvac] [popust_sto_moze_da_go_koristi]
каде попустот е 0% ако купувачот е стандарден, вредноста на основниот попуст, ако е лојален или збир од основниот и дополнителниот попуст, ако купувачот е вип. (5 поени)

Да се креира класа за онлајн книжара FINKI-bookstore во која се чува низа од регистрирани купувачи (динамички алоцирана низа) и број на купувачи. (5 поени) За класата да се обезбедат:

operator+= (10 поени) за додавање купувач во листата од купувачи, но само ако веќе не е дел од неа (ако во листата нема купувач со иста електронска адреса). Ако во листата постои корисник со иста електронска адреса, треба да се генерира исклучок UserExistsException. Потребно е да се обезбеди справување со исклучокот во функцијата main на означеното место. Во ваква ситуација се печати порака "The user already exists in the list" (5 поени).
Функција update со која сите стандардни купувачи со купени повеќе од 5 производи стануваат лојални, а сите лојални купувачи со над 10 купени производи, стануваат вип (5 поени).
Оператор << за печатење на информациите за сите регистрирани купувачи (5 поени).
Да се обезбедат сите дополнителни методи потребни за правилно функционирање на програмата. (10 поени)

For example:

Input	
6
5
Albert Einstein
einstein@finki.mk
1
2
Isaac Newton
newton@finki.mk
2
10
Galileo Galilei
galilei@finki.mk
1
12
Stephen Hawking
hawking@finki.mk
0
17
Nikola Tesla
tesla@finki.mk
0
7


Result
===== Test Case - update method  ======

Update:
Albert Einstein
einstein@finki.mk
2
loyal 10
Isaac Newton
newton@finki.mk
10
vip 30
Galileo Galilei
galilei@finki.mk
12
vip 30
Stephen Hawking
hawking@finki.mk
17
loyal 10
Nikola Tesla
tesla@finki.mk
7
loyal 10
*/

#include <iostream>
#include <cstring>

using namespace std;

const int MAX=50;

class UserExistsException {
public:
    void print() {
        cout << "The user already exists in the list!" << endl;
    }
};

enum typeC {
    STANDARD, LOYAL, VIP
};

class Customer {
protected:
    char name[51];
    char address[51];
    typeC type;
    static int discount;
    static const int plus_discount = 30;
    int number;
public:
    Customer(const char *name = " ", const char *address = " ", typeC type = STANDARD, int number = 0) : type(type),
                                                                                                         number(number) {
        strcpy(this->name, name);
        strcpy(this->address, address);
    }

    const char *getName() const {
        return name;
    }

    const char *getAddress() const {
        return address;
    }

    typeC getType() const {
        return type;
    }

    static int getDiscount() {
        return discount;
    }

    static const int getPlusDiscount() {
        return plus_discount;
    }

    int getNumber() const {
        return number;
    }

    void setType(typeC type) {
        Customer::type = type;
    }

    static void setDiscount1(int discount) {
        Customer::discount = discount;
    }

    void setNumber(int number) {
        Customer::number = number;
    }

    ~Customer() {};

    friend ostream &operator<<(ostream &os, const Customer &customer);

};

int Customer::discount = 10;

ostream &operator<<(ostream &os, const Customer &customer) {
    os << customer.name << endl;
    os << customer.address << endl;
    os << customer.number << endl;
    switch (customer.type) {
        case STANDARD:
            cout << "standard " << "0"<<endl;
            break;
        case LOYAL:
            cout << "loyal " << customer.discount<<endl;
            break;
        case VIP:
            cout << "vip " << customer.plus_discount<<endl;
            break;
    }

    return os;
}


class FINKI_bookstore {
private:
    Customer *customers;
    int n;
public:
    FINKI_bookstore(Customer *customers = 0, int n = 0) : n(n) {
        this->customers = new Customer[n];
        for (int i = 0; i < this->n; i++) {
            this->customers[i] = customers[i];
        }
    }

    ~FINKI_bookstore() {
        delete [] customers;
    }

    FINKI_bookstore &operator=(const FINKI_bookstore &other){
        if(this!=&other){
            delete [] customers;
            this->customers = new Customer[n];
            for (int i = 0; i < n; i++) {
                this->customers[i] = customers[i];
            }
        }
        return *this;
    }

    FINKI_bookstore &operator+=(const Customer &other) {
        int flag = 1;
        for (int i = 0; i < n; i++) {
            if (strcmp(other.getAddress(), customers[i].getAddress()) == 0) {
                throw UserExistsException();
            }
        }
        Customer *tmp = new Customer[n + 1];
        for (int i = 0; i < n; i++) {
            tmp[i] = customers[i];
        }
        tmp[n++] = other;
        delete[] customers;
        customers = tmp;
        return *this;
    }
    void update(){
        for(int i=0; i<n; i++){
            if(customers[i].getType()==STANDARD && customers[i].getNumber()>5){
                customers[i].setType(LOYAL);
            } else if(customers[i].getType()==LOYAL && customers[i].getNumber()>10){
                customers[i].setType(VIP);
            }
        }
    }

    friend ostream &operator<<(ostream &os, const FINKI_bookstore &bookstore) {
        for(int i=0; i<bookstore.n; i++){
            cout<<bookstore.customers[i];
        }
        return os;
    }

    void setCustomers(Customer *customers, int n) {
        delete[] this->customers;
        this->customers = new Customer[n];
        for (int i = 0; i < n; i++) {
            this->customers[i] = customers[i];
        }
        this->n = n;
    }

    void setN(int n) {
        FINKI_bookstore::n = n;
    }

};

int main() {
    int testCase;
    cin >> testCase;

    char name[MAX];
    char email[MAX];
    int tC;
    int discount;
    int numProducts;


    if (testCase == 1) {
        cout << "===== Test Case - Customer Class ======" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

    }

    if (testCase == 2) {
        cout << "===== Test Case - Static Members ======" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

        c.setDiscount1(5);

        cout << c;
    }

    if (testCase == 3) {
        cout << "===== Test Case - FINKI-bookstore ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << fc << endl;
    }

    if (testCase == 4) {
        cout << "===== Test Case - operator+= ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        try{
            fc += c;
        } catch (UserExistsException e){
            e.print();
        }


        cout << fc;
    }

    if (testCase == 5) {
        cout << "===== Test Case - operator+= (exception) ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        try {
            Customer c(name, email, (typeC) tC, numProducts);
            fc+=c;
        }
        catch (UserExistsException &e) {
            e.print();
        }
        cout << fc;
    }

    if (testCase == 6) {
        cout << "===== Test Case - update method  ======" << endl << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << "Update:" << endl;
        fc.update();
        cout << fc;
    }
    return 0;

}