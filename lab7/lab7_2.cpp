/*
 Потребно е да имплементирате класа Hero во рамки на некоја игра. Таа треба да ги содржи следниве информации:

име - динамички алоцирана низа од знаци
класа - низа од максумум 40 знаци
attack damage - децимален број
attack speed - децимален број
ability power - децимален број
За оваа класа потребно е да креирате:

Default constructor
Constructor со параметри
Copy constructor
Оператор =
Destructor
Getters и setters
Функција power што ја враќа вкупната моќ на херојот. (се пресметува со формуалта (0.4*attack damage)+(0.25*attack speed)+(0.35*ability power))
Функција print која ги печати информациите за херојот во формат:
[Име] - [Класа]
Attack damage: [attack damage]
Attack speed: [attack speed]
Ability power: [ability power]
Power: [power]
Треба да ја имплементирате и класата LegendaryHero која треба да наследува од класата Hero и дополнително да ги има следниве информации:

legendary attack damage - децимален број
legendary attack speed - децимален број
legendary ability power - децимален број
За оваа класа потребно е да креирате:

Default constructor
Constructor со параметри
Copy constructor
Оператор =
Destructor
Функција legendaryPower што ја враќа „легендарната“ моќ на херојот. (се пресметува со формуалта (0.25*attack damage)+(0.35*attack speed)+(0.4*ability power))
Функција power што ја враќа вкупната моќ на херојот. (се пресметува како средна вредност на „обичната“ моќ и „легендарната“ моќ на херојот)
Функција print што ги печати информациите за легендарниот херој:
[Име] - [Класа]
Attack damage: [attack damage]
Attack speed: [attack speed]
Ability power: [ability power]
Power: [power]
Legendary Power: [legendary power]
New Power: [power]

For example:

Input
1
Hero1 Class1 55 43 70
Hero2 Class2 70 32 65
Hero3 Class3 55 55 55
Hero4 Class2 60 35 80
Hero5 Class3 62 39 76

 Result
HEROES:
=====================================
Hero1 - Class1
Attack damage: 55
Attack speed: 43
Ability power: 70
Power: 57.25
Hero2 - Class2
Attack damage: 70
Attack speed: 32
Ability power: 65
Power: 58.75
Hero3 - Class3
Attack damage: 55
Attack speed: 55
Ability power: 55
Power: 55
Hero4 - Class2
Attack damage: 60
Attack speed: 35
Ability power: 80
Power: 60.75
Hero5 - Class3
Attack damage: 62
Attack speed: 39
Ability power: 76
Power: 61.15
 */

#include <iostream>
#include <cstring>

using namespace std;

class Hero {
protected:
    char *name;
    char klasa[40];
    float damage;
    float speed;
    float pow;

public:
    Hero(char *name="", char *klasa="", float damage=0, float speed=0, float pow=0) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        strcpy(this->klasa, klasa);
        this->damage = damage;
        this->speed = speed;
        this->pow = pow;
    }

    Hero(const Hero &other) {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        strcpy(this->klasa, other.klasa);
        this->damage = other.damage;
        this->speed = other.speed;
        this->pow = other.pow;
    }

    ~Hero() {
        delete[] name;
    }

    Hero &operator=(const Hero &other) {
        if (this != &other) {
            delete[] name;
            this->name = new char[strlen(other.name) + 1];
            strcpy(this->name, other.name);
            strcpy(this->klasa, other.klasa);
            this->damage = other.damage;
            this->speed = other.speed;
            this->pow = other.pow;
        }
        return *this;
    }

    char *getName() const {
        return name;
    }

    void setName(char *name) {
        Hero::name = name;
    }

    const char *getKlasa() const {
        return klasa;
    }

    float getDamage() const {
        return damage;
    }

    void setDamage(float damage) {
        Hero::damage = damage;
    }

    float getSpeed() const {
        return speed;
    }

    void setSpeed(float speed) {
        Hero::speed = speed;
    }

    float getPower() const {
        return pow;
    }

    void setPower(float pow) {
        Hero::pow = pow;
    }

    float power() {
        return (0.4 * getDamage()) + (0.25 * getSpeed()) + (0.35 * getPower());
    }

    void print() {
        cout << name << " - " << klasa << endl;
        cout << "Attack damage: " << damage << endl;
        cout << "Attack speed: " << speed << endl;
        cout << "Ability power: " << pow << endl;
        cout << "Power: " << power() << endl;
    }
};

class LegendaryHero : public Hero {
private:
    float l_damage;
    float l_speed;
    float l_pow;
public:
//    LegendaryHero() : Hero() {
//        l_damage = 0;
//        l_speed = 0;
//        l_pow = 0;
//    }

    LegendaryHero(char *name="", char *klasa="", float damage=0, float speed=0, float pow=0,
                  float l_damage=0, float l_speed=0,
                  float l_pow=0) : Hero(name, klasa, damage, speed, pow) {
        this->l_damage = l_damage;
        this->l_speed = l_speed;
        this->l_pow = l_pow;
    }

    LegendaryHero(const Hero &other, float l_damage, float l_speed, float l_pow) :
            Hero(other) {
        this->l_damage = l_damage;
        this->l_speed = l_speed;
        this->l_pow = l_pow;
    }

    LegendaryHero(const LegendaryHero &other) : Hero(other){

        this->l_damage = other.l_damage;
        this->l_speed = other.l_speed;
        this->l_pow = other.l_pow;
    }

    LegendaryHero &operator=(const LegendaryHero &other) {
        if (this != &other) {
            Hero::operator=(other);
            this->l_damage = other.l_damage;
            this->l_speed = other.l_speed;
            this->l_pow = other.l_pow;
        }
        return *this;
    }

    float legedaryPower() {
        return (0.25 * l_damage) + (0.35 * l_speed) + (0.4 * l_pow);
    }

    float power() {

        return (Hero::power() + legedaryPower()) / 2.0;
    }

    void print() {
        Hero::print();
        cout << "Legendary Power: " << legedaryPower() << endl;
        cout << "New Power: " << power() << endl;

    }
};

//DO NOT EDIT THE MAIN FUNCTION

int main() {

    char name[50];
    char klasa[40];
    double attackDamage;
    double attackSpeed;
    double abilityPower;
    double legendaryAttackDamage;
    double legendaryAttackSpeed;
    double legendaryAbilityPower;

    Hero *heroes = new Hero[5];
    LegendaryHero *legendaryHeroes = new LegendaryHero[5];
    int n;
    cin >> n;

    if (n == 1) {

        cout << "HEROES:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < 5; ++i) {
            cin >> name >> klasa >> attackDamage >> attackSpeed >> abilityPower;
            heroes[i] = Hero(name, klasa, attackDamage, attackSpeed, abilityPower);
            heroes[i].print();
        }
    } else if (n == 2) {

        for (int i = 0; i < 5; ++i) {
            cin >> name >> klasa >> attackDamage >> attackSpeed >> abilityPower;
            cin >> legendaryAttackDamage >> legendaryAttackSpeed >> legendaryAbilityPower;
            heroes[i] = Hero(name, klasa, attackDamage, attackSpeed, abilityPower);
            legendaryHeroes[i] = LegendaryHero(heroes[i], legendaryAttackDamage, legendaryAttackSpeed,
                                               legendaryAbilityPower);
        }

        cout << "HEROES:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < 5; ++i)
            heroes[i].print();

        cout << "LEGENDARY HEROES:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < 5; ++i)
            legendaryHeroes[i].print();

    } else if (n == 3) {

        for (int i = 0; i < 5; ++i) {
            cin >> name >> klasa >> attackDamage >> attackSpeed >> abilityPower;
            cin >> legendaryAttackDamage >> legendaryAttackSpeed >> legendaryAbilityPower;
            legendaryHeroes[i] = LegendaryHero(name, klasa, attackDamage, attackSpeed, abilityPower,
                                               legendaryAttackDamage, legendaryAttackSpeed, legendaryAbilityPower);
        }
        cout << "LEGENDARY HEROES:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < 5; ++i)
            legendaryHeroes[i].print();

    }

    delete[] heroes;
    delete[] legendaryHeroes;
}