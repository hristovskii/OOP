/*
Да се креира апстрактна класа Pizza за опишување пици. (5 поени) За секоја пица се чуваат следните информации:

име (низа од максимум 20 знаци)
состојки (низа од максимум 100 знаци)
основна цена (реален број)
Од оваа класа да се изведат класите FlatPizza и FoldedPizza за опишување на рамни и преклопени пици соодветно (5 поени).

За секоја рамна пица дополнително се чува големина (enum - една од три можности: мала, голема и фамилијарна). За секоја преклопена пица дополнително се чува информација дали тестото е од бело брашно или не (boolean).

За секоја пица треба да се обезбеди метод за пресметување на нејзината продажна цена:

цената на рамната пица се пресметува така што основната цена се зголемува за 10%, 20% и 30% за мала, голема и фамилијарна пица соодветно.
цената на преклопената пица се пресметува така што основната цена се зголемува за 10% ако е тестото е од бело брашно, а во спротивно за 30%. (10 поени)
Да се преоптоварат следните оператори:

оператор << - за печатење сите податоци за пиците во следниов формат:

За рамна пица:[име]: [состојки], [големина] - [продажната цена на пицата]. 
За преклопена пица: [име]: [состојки], [wf - ако е со бело брашно / nwf - ако не е со бело брашно] - [продажната цена на пицата]
(5 поени)

оператор < - за споредување на пиците од каков било вид според нивната продажна цена. (5 поени)
Да се дефинира глобална функција еxpensivePizza што на влез прима низа од покажувачи кон објекти од класата Pizza и нивниот број, а како резултат ги печати информациите за пицата со највисока продажна цена. Ако има повеќе пици со иста највисока цена, се печати првата. (10 поени)

Да се дефинираат потребните конструктори и методи во класите за правилно функционирање на програмата. (5 поени)

For example:

Input	
5
Margarita
Tomato sauce, cheese, mozzarella, basil, oregano
100
2
Margarita
Tomato sauce, cheese, mozzarella, basil, oregano
100
0
Capricciosa calzone
Tomato sauce, cheese, ham, fresh mushrooms
140
Capricciosa calzone
Tomato sauce, cheese, ham, fresh mushrooms
140

Result
Margarita: Tomato sauce, cheese, mozzarella, basil, oregano, family - 130
Margarita: Tomato sauce, cheese, mozzarella, basil, oregano, small - 110
Capricciosa calzone: Tomato sauce, cheese, ham, fresh mushrooms, wf - 154
Capricciosa calzone: Tomato sauce, cheese, ham, fresh mushrooms, nwf - 182
Lower price: 
110
130
110
154
*/

#include <cstring>
#include <iostream>

using namespace std;

class Pizza {
protected:
    char name[21];
    char ingredients[101];
    float base_price;
public:
    Pizza(char *name = "", char *ingredients = "", float basePrice = 0) : base_price(basePrice) {
        strcpy(this->name, name);
        strcpy(this->ingredients, ingredients);
    }

    Pizza(const Pizza &other) {
        strcpy(this->name, other.name);
        strcpy(this->ingredients, other.ingredients);
        this->base_price = other.base_price;
    }

    Pizza &operator=(const Pizza &other) {
        if (this != &other) {
            strcpy(this->name, other.name);
            strcpy(this->ingredients, other.ingredients);
            this->base_price = other.base_price;
        }
        return *this;
    }

    const char *getName() const {
        return name;
    }

    const char *getIngredients() const {
        return ingredients;
    }

    float getBasePrice() const {
        return base_price;
    }

    void setBasePrice(float basePrice) {
        base_price = basePrice;
    }

    bool operator<(Pizza &rhs) {
        return price() < rhs.price();
    }

    virtual float price() = 0;

    virtual ~Pizza() {}
};

enum Size {
    SMALL, LARGE, FAMILY
};

class FlatPizza : public Pizza {
private:
    Size size;
public:
    FlatPizza(char *name = "", char *ingredients = "", float basePrice = 0.0, Size size = SMALL) : Pizza(name,
                                                                                                         ingredients,
                                                                                                         basePrice),
                                                                                                   size(size) {}

    FlatPizza(const FlatPizza &other) : Pizza(other) {
        this->size = other.size;
    }


    FlatPizza &operator=(const FlatPizza &other) {
        if (this != &other) {
            Pizza::operator=(other);
            this->size = other.size;
        }
        return *this;
    }

    Size getSize() const {
        return size;
    }

    void setSize(Size size) {
        FlatPizza::size = size;
    }

    float price() override {
        if (size == SMALL) {
            return base_price * 1.1;
        } else if (size == LARGE) {
            return base_price * 1.2;
        } else if (size == FAMILY) {
            return base_price * 1.3;
        }
    }

    friend ostream &operator<<(ostream &os, FlatPizza &pizza) {
        os << pizza.name << ": ";
        os << pizza.ingredients << ", ";
        switch (pizza.size) {
            case SMALL:
                cout << "small" << " - ";
                break;
            case LARGE:
                cout << "large" << " - ";
                break;
            case FAMILY:
                cout << "family" << " - ";
                break;
        }
        os << pizza.price() << endl;
        return os;
    }

    ~FlatPizza() override {};
};

class FoldedPizza : public Pizza {
private:
    bool WhiteFlour;
public:
    FoldedPizza(char *name="", char *ingredients="", float basePrice=0.0, bool whiteFlour=true) : Pizza(name, ingredients, basePrice) {
        this->WhiteFlour=whiteFlour;
    }

    ~FoldedPizza() override {}

    FoldedPizza(const FoldedPizza &other) : Pizza(other) {
        this->WhiteFlour = other.WhiteFlour;
    }

    FoldedPizza &operator=(const FoldedPizza &other) {
        if (this != &other) {
            Pizza::operator=(other);
            this->WhiteFlour = other.WhiteFlour;
        }
        return *this;
    }

    bool isWhiteFlour() const {
        return WhiteFlour;
    }

    void setWhiteFlour(bool whiteFlour) {
        WhiteFlour = whiteFlour;
    }

    float price() override {
        if (WhiteFlour) {
            return base_price * 1.1;
        } else {
            return base_price * 1.3;
        }
    }


    friend ostream &operator<<(ostream &os, FoldedPizza &pizza) {
        os << pizza.name << ": ";
        os << pizza.ingredients << ", ";
        if (pizza.WhiteFlour) {
            os << "wf" << " - ";
        } else {
            os << "nwf" << " - ";
        }
        os << pizza.price() << endl;
        return os;
    }

};

void expensivePizza(Pizza **pizzas, int n){
    Pizza *max= pizzas[0];
    for (int i = 0; i <n; ++i) {
        if(pizzas[i]->price()>max->price()){
            max=pizzas[i];
        }
    }
    FlatPizza *casted1 = dynamic_cast<FlatPizza *>(max);
    FoldedPizza *casted2 = dynamic_cast<FoldedPizza *>(max);

    if(casted1){
        cout<<*casted1<<endl;
    }
    else if(casted2){
        cout<<*casted2<<endl;
    }
}


int main() {
    int test_case;
    char name[20];
    char ingredients[100];
    float inPrice;
    Size size;
    bool whiteFlour;

    cin >> test_case;
    if (test_case == 1) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FlatPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 2) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        int s;
        cin >> s;
        FlatPizza fp(name, ingredients, inPrice, (Size) s);
        cout << fp;

    } else if (test_case == 3) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 4) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        fp.setWhiteFlour(false);
        cout << fp;

    } else if (test_case == 5) {
        // Test Cast - operator <, price
        int s;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        cin >> s;
        FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size) s);
        cout << *fp1;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        cin >> s;
        FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size) s);
        cout << *fp2;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
        cout << *fp3;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
        fp4->setWhiteFlour(false);
        cout << *fp4;

        cout << "Lower price: " << endl;
        if (*fp1 < *fp2)
            cout << fp1->price() << endl;
        else cout << fp2->price() << endl;

        if (*fp1 < *fp3)
            cout << fp1->price() << endl;
        else cout << fp3->price() << endl;

        if (*fp4 < *fp2)
            cout << fp4->price() << endl;
        else cout << fp2->price() << endl;

        if (*fp3 < *fp4)
            cout << fp3->price() << endl;
        else cout << fp4->price() << endl;

    } else if (test_case == 6) {
        // Test Cast - expensivePizza
        int num_p;
        int pizza_type;

        cin >> num_p;
        Pizza **pi = new Pizza *[num_p];
        for (int j = 0; j < num_p; ++j) {

            cin >> pizza_type;
            if (pizza_type == 1) {
                cin.get();
                cin.getline(name, 20);

                cin.getline(ingredients, 100);
                cin >> inPrice;
                int s;
                cin >> s;
                FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size) s);
                cout << (*fp);
                pi[j] = fp;
            }
            if (pizza_type == 2) {

                cin.get();
                cin.getline(name, 20);
                cin.getline(ingredients, 100);
                cin >> inPrice;
                FoldedPizza *fp =
                        new FoldedPizza(name, ingredients, inPrice);
                if (j % 2)
                    (*fp).setWhiteFlour(false);
                cout << (*fp);
                pi[j] = fp;

            }
        }

        cout << endl;
        cout << "The most expensive pizza:\n";
        expensivePizza(pi, num_p);


    }
    return 0;
}
