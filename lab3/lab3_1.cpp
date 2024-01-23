/*
 Да се дефинира класа MobilePhone во која ќе се чуваат податоци за еден мобилен телефон:

модел (низа од карактери не подолга од 20 карактери)
број на модел (цел број)
година на издавање (цел број)
За класата да се дефинира default конструктор, конструктор со аргументи, copy конструктор, деструктор и доколку има потреба get методи. Исто така да се дефинира и фунцкија за печатење на информации за класата која ќе печати во следниот формат „(модел) (број на модел) release year: (година на издавање)“.

Потоа да се дефинира класа Owner во која се чуваат следните информации:

име (низа од карактери не подолга од 20 карактери)
презиме (низа од карактери не подолга од 20 карактери)
мобилен телефон (објект од класа MobilePhone)
Да се креира default конструктор, конструктор со аргументи, деструктор и доколку има потреба get методи. Исто така да се дефинира и функција за печатење на информации за класата која ќе печати во следниот формат:

„(име) (презиме) has a mobile phone:

(информации за мобилен телефон)“

ДА НЕ СЕ МЕНУВА MAIN ФУНКЦИЈАТА!!!

For example:

Input
1
Iphone
12
2020
Marko
Petrov
 Result
Marko Petrov has a mobile phone:
Iphone 12 release year: 2020
 */

#include <iostream>
#include <cstring>

using namespace std;

class MobilePhone {
private:
    char model[20];
    int modelNumber, year;
public:
    MobilePhone(char *model = " ", int broj_na_model = 0, int year = 0) {
        strcpy(this->model, model);
        this->modelNumber = broj_na_model;
        this->year = year;
    }

    MobilePhone(const MobilePhone &other) {
        strcpy(this->model, other.model);
        this->modelNumber = other.modelNumber;
        this->year = other.year;
    }

    ~MobilePhone() {}

    const char *getModel() const {
        return model;
    }

    int getmodelNumber() const {
        return modelNumber;
    }

    void setBrojNaModel(int brojNaModel) {
        modelNumber = brojNaModel;
    }

    int getYear() const {
        return year;
    }

    void setGodina(int godina) {
        MobilePhone::year = year;
    }

    void print() {
        cout << model << " " << modelNumber << " release year: " << year << endl;
    }
};

class Owner {
private:
    char name[20];
    char surname[20];
    MobilePhone phone;

public:
    Owner(char *name = "", char *surname = "", const MobilePhone &phone = "") {
        strcpy(this->name, name);
        strcpy(this->surname, surname);
        this->phone = phone;
    }

    ~Owner() {}

    const char *getName() const {
        return name;
    }

    const char *getSurname() const {
        return surname;
    }

    const MobilePhone &getPhone() const {
        return phone;
    }

    void setPhone(const MobilePhone &phone) {
        this->phone = phone;
    }
    void print(){
        cout<<name<<" "<<surname<<" has a mobile phone:"<<endl;
        phone.print();
    }
};

//DO NOT CHANGE THE MAIN FUNCTION
int main() {
    char model[20];
    int modelNumber;
    int year;
    char name[20];
    char surname[20];
    int testCase;

    cin >> testCase;
    cin >> model;
    cin >> modelNumber;
    cin >> year;
    cin >> name;
    cin >> surname;

    if (testCase == 1) {
        MobilePhone mobilePhone(model, modelNumber, year);
        Owner owner(name, surname, mobilePhone);
        owner.print();
    }

    if (testCase == 2) {
        MobilePhone mobilePhone(MobilePhone(model, modelNumber, year));
        Owner owner(name, surname, mobilePhone);
        owner.print();
    }

}