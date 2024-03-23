/*
 (1) Да се дефинира класа FoodProduct во која ќе се чуваат информации за:

Име на продуктот (низа од карактери со максимална должина 50)
Количина на продуктот (int)
Цена на продуктот (int)
Класата треба да ги има следните методи:

конструктор (default, copy и со параметри)
set и get методи за количина и цена
print() метод
Печатењето да е според следниот формат:
Name: [Name of product]
Amount available: [Amount]
Price: [Price of product]

При што вредностите во [] треба да се заменат со вредностите во класата!

(2) Следно треба да се имплементира класата Menu која ќе ги чува следните информации:

Име на ресторанот (низа од карактери со максимална должина 50)
Број на продукти (int)
Низа од продукти (низа од FoodProduct со максимална должина 50)

За класата да се имплементираат следните методи:

Конструктор (default, copy и конструктор со еден параметар за име)
Set и get методи (за името на ресторанот и бројот на продукти)
void addProduct(FoodProduct p) - додава продукт во низата, при што не може да се додат повеќе од 50 продукти во низата
print() метод
Печатењето да е според следниот формат:

Name: [Name of restaurant]
Products:
[Product 1]
[Product 2]
 …
[Product N]

При што вредностите во [] треба да се заменат со вредностите во класата!

int totalIncome() - која ќе го враќа збирот на заработувачката на секој продукт, така што заработувачката на продуктот е производ од неговата количина и цена (income = amount * price)

(3) Надвор од класата треба да се напише следната функција:

void printWorstMenu(Menu * menus, int n) - од дадените n менија го печати менито со најмала вкупна заработувачка

!!! ДА НЕ СЕ ПРАВАТ ПРОМЕНИ ВО MAIN() ФУНКЦИЈАТА !!!

For example:

Input
2
Los_Pollos_Hermanos 2
Fried_Chicken 10 5
Sugar 10 5000
Madzo3.0 1
Burger 10 350

 Result
-- Testing add product & getNumberOfProducts() --

Number of products before adding: 0
Number of products after adding: 1
Name: test
Products:
Name: test
Amount available: 0
Price: 0

-- Testing copy constructor & setName() --
-------------
Source:
-------------
Name: Los_Pollos_Hermanos
Products:
Name: Fried_Chicken
Amount available: 10
Price: 5
Name: Sugar
Amount available: 10
Price: 5000

-------------
Copied and edited:
-------------
Name: Tester Name
Products:
Name: Fried_Chicken
Amount available: 10
Price: 5
Name: Sugar
Amount available: 10
Price: 5000

-- Testing printWorstMenu() --
Name: Madzo3.0
Products:
Name: Burger
Amount available: 10
Price: 350
 */

#include <iostream>
#include <cstring>

using namespace std;


class FoodProduct {
private:
    char product[50];
    int amount, price;
public:
    FoodProduct() {}

    FoodProduct(char *product, int amount, int price) {
        strcpy(this->product, product);
        this->amount = amount;
        this->price = price;
    }

    FoodProduct(const FoodProduct &f) {
        strcpy(product, f.product);
        amount = f.amount;
        price = f.price;
    }

    void setamount(int a) {
        this->amount = amount;
    }

    void setprice(int price) {
        this->price = price;
    }

    int const getamount() {
        return amount;
    }

    int const getprice() {
        return price;
    }

    void print() {
        cout << "Name: " << product << endl;
        cout << "Amount available: " << amount << endl;
        cout << "Price: " << price << endl;
    }

};

class Menu {
private:
    char Name[50];
    int NumberOfProducts;
    FoodProduct foodProduct[50];
public:
    Menu() {}

    Menu(char *Name) {
        NumberOfProducts = 0;
        strcpy(this->Name, Name);
    }

    Menu(const Menu &menu) {
        strcpy(Name, menu.Name);
        NumberOfProducts = menu.NumberOfProducts;
        for (int i = 0; i < NumberOfProducts; i++) {
            foodProduct[i] = menu.foodProduct[i];
        }
    }

    void setName(char *Name) {
        strcpy(this->Name, Name);
    }

    void setnumberofProducts(int NumberOfProducts) {
        this->NumberOfProducts = NumberOfProducts;
    }

    char *const getname() {
        return Name;
    }

    int const getNumberOfProducts() {
        return NumberOfProducts;
    }

    void addProduct(FoodProduct price) {
        foodProduct[NumberOfProducts] = price;
        NumberOfProducts++;
    }

    void print() {
        cout << "Name: " << Name << endl;
        cout << "Products: " << endl;
        for (int i = 0; i < NumberOfProducts; i++) {
            foodProduct[i].print();
        }
    }

    int totalIncome() {
        int income = 0;
        for (int i = 0; i < NumberOfProducts; i++) {
            income += ((foodProduct[i].getamount()) * (foodProduct[i].getprice()));
        }
        return income;
    }

};

void printWorstMenu(Menu *menues, int n) {
    int min = menues[0].totalIncome();
    int index = 0;
    for (int i = 0; i < n; i++) {
        if ( menues[i].totalIncome()<min) {
            min = menues[i].totalIncome();
            index = i;
        }
    }
    menues[index].print();
}

//DO NOT CHANGE main() FUNCTION
int main() {
    int n;
    cin >> n;

    /// BASIC INPUT & ADD PRODUCT
    Menu menus[n];

    for(int i = 0; i < n; i++) {
        int m;
        char name[50];

        cin >> name >> m;
        menus[i] = Menu(name);

        for(int j = 0; j < m; j++) {
            char itemName[50];
            int amount, price;

            cin >> itemName >> amount >> price;

            FoodProduct product(itemName, amount, price);
            menus[i].addProduct(product);
        }
    }

    /// TESTING ADD PRODUCT

    cout << "-- Testing add product & getNumberOfProducts() --\n\n";

    char tempName[50] = "test";
    Menu temp(tempName);

    cout << "Number of products before adding: " << temp.getNumberOfProducts() << '\n';

    temp.addProduct(FoodProduct(tempName, 0, 0));

    cout << "Number of products after adding: " << temp.getNumberOfProducts() << '\n';
    temp.print();

    /// TESTING COPY CONSTRUCTOR

    Menu tester(menus[0]);
    std::strcpy(tempName, "Tester Name");
    tester.setName(tempName);

    cout << "\n-- Testing copy constructor & setName() --\n";
    cout << "-------------\n";
    cout << "Source:\n";
    cout << "-------------\n";
    menus[0].print();

    cout << "\n-------------\n";
    cout << "Copied and edited:\n";
    cout << "-------------\n";
    tester.print();

    /// TESTING WORST PRODUCT

    cout << "\n-- Testing printWorstMenu() --\n";
    printWorstMenu(menus, n);
    return 0;
}