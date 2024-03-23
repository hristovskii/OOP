/*
Дадена е дел од дефиницијата на класата Karticka. За секоја картичка се чуваат информации за трансакциска сметка (низа од 15 знаци) , пин код (цел број) и дали има повеќе пин кодови (булова променлива).

За секој картичка може да се пресмета тежината за пробивање на картичката. Тежината на пробивање е бројот на цифрите на пин кодот.

Специјалните картички покрај еден задолжителен имаат уште неколку пин кодови . За овие корисници да се моделира соодветна класа SpecijalnaKaricka во која покрај дополнителните пин кодови (динамичко алоцирана низа од цели броеви) се чува и бројот на пин кодовите (цел број). Со дополнителните пин кодови се менува и тежината на пробивање на картичката и таа се зголемува за бројот на дополнителни пин кодови.

Максималниот број на дополнителни пин кодови кој може да има било која картичка е P. P има фиксна вредност 4 за сите картички и оваа вредност не може да се промени.

Во класите Karticka и SpecijalnaKarticka треба да се имплементираат потребните конструктори, функции за поставување и преземање и деструктор. (5 поени)

За сите објекти од класите треба да се обезбедат следните функции:

преоптоварен оператор << во кој се печатат информации за картичката во формат: smetka: tezina (5 поени)
tezinaProbivanje() – ја пресметува тежината за пробивање на картичката (5 поени)
Во класата SpecijalnaKarticka дефинирај ја функцијата:

преоптоварен оператор += за додавање на нов пин код (5 поени)
Ако се направи обид да се внесат повеќе од дозволениот број на пин кодови во безбедносниот код да се фрли исклучок (објект од класата OutOfBoundException). Фатете го исклучокот во главната функција каде што е потребно. Откако ќе го фатите отпечатете соодветна порака за грешка (Brojot na pin kodovi ne moze da go nadmine dozvolenoto) и справете се со исклучокот така да додадениот пин код не се зема предвид (10 поени)

Дадена е дел од дефиницијата на класата Banka во која се чуваат информаци за името на банката (низа од 30 знаци) и за картичките издадени од банката (низа од 20 покажувачи кон класата Karticka) како и бројот на такви картички.

Велиме дека картичката издадена од банката може да се пробие ако тежината за пробивање е најмногуLIMIT. Вредноста LIMIT е членка на класата Banka, има почетна вредност 7 и истата може да се промени со функцијата setLimit(). За сите банки оваа вредност е иста. (5 поени)

Во класата Banka имплементирај ги функциите:

функција pecatiKarticki() во која се печатат сите картички кои можат да се пробијат, секој во посебен ред. Претходно во првиот ред се печати: Vo bankata XXXXX moze da se probijat kartickite: (5 поени).

функција dodadiDopolnitelenPin(char * smetka, int novPin) во која на картичката со дадена трансакциона сметка се додава нов дополнителен пин код. Ако тоа не е можно функцијата не прави ништо (15 поени).

Комплетна функционалност (5 поени)

For example:

Input	
2
ab1232432 345 0
bh4555432 876 1
4
ab1232432 2
ab1112432 100
ab1232432 56
ab1211111 88


Result
Vo bankata Komercijalna moze da se probijat kartickite:
ab1232432: 3
bh4555432: 3
*/

#include<iostream>
#include<string.h>

using namespace std;

class OutOfBoundException {
public:
    void print() {
        cout << "Brojot na pin kodovi ne moze da go nadmine dozvolenoto" << endl;
    }
};

class Karticka {
protected:
    char smetka[16];
    int pin;
    bool povekjePin;
public:
    Karticka(char *smetka, int pin) {
        strcpy(this->smetka, smetka);
        this->pin = pin;
        this->povekjePin = false;
    }

    virtual int tezinaProbivanje() {
        int tezina = 0;
        int temp = pin;
        while (temp != 0) {
            temp /= 10;
            tezina++;
        }
        return tezina;
    }

    const char *getSmetka() const {
        return smetka;
    }

    int getPin() const {
        return pin;
    }

    bool getDopolnitelenPin() const {
        return povekjePin;
    }

    void setPin(int pin) {
        Karticka::pin = pin;
    }

    void setPovekjePin(bool povekjePin) {
        Karticka::povekjePin = povekjePin;
    }

    void setSmetka(char *smetka) {
        strcpy(this->smetka, smetka);
    }

    friend ostream &operator<<(ostream &os, Karticka &karticka) {
        os << karticka.smetka << ": " << karticka.tezinaProbivanje();
        return os;
    }

    Karticka &operator=(const Karticka &other) {
        if (this != &other) {
            strcpy(this->smetka, other.smetka);
            this->pin = other.pin;
            this->povekjePin = other.povekjePin;
        }
        return *this;
    }

    virtual ~Karticka() {}
};

class SpecijalnaKarticka : public Karticka {
private:
    int *dopolnitelnipin;
    int number;
    const static int p=4;
public:
    SpecijalnaKarticka(char *smetka=" ", int pin=0, int *dopolnitelnipin = 0, int number = 0) : Karticka(smetka, pin),
                                                                                                number(number) {
        this->dopolnitelnipin = new int[number];
        for (int i = 0; i < number; i++) {
            this->dopolnitelnipin[i] = dopolnitelnipin[i];
        }
        this->povekjePin = true;
    }
    SpecijalnaKarticka(const SpecijalnaKarticka& other) : Karticka(other) {
        number = other.number;
        dopolnitelnipin = new int[number];
        for (int i = 0; i < number; i++) {
            dopolnitelnipin[i] = other.dopolnitelnipin[i];
        }
    }
    ~SpecijalnaKarticka() override {
        delete[] dopolnitelnipin;
    }

    int *getDopolnitelenPin() {
        return dopolnitelnipin;
    }

    int getNumber() const {
        return number;
    }

    void setDopolnitelnipin(int *dopolnitelnipin) {
        SpecijalnaKarticka::dopolnitelnipin = dopolnitelnipin;
    }

    void setNumber(int number) {
        SpecijalnaKarticka::number = number;
    }

    int tezinaProbivanje() override {
        int tezina = Karticka::tezinaProbivanje();
        tezina += number;
        return tezina;
    }

    friend ostream &operator<<(ostream &os, SpecijalnaKarticka &karticka) {
        os << karticka.smetka << ": " << karticka.tezinaProbivanje();
        return os;
    }

    SpecijalnaKarticka &operator+=(int pin) {
        if (number == p) {
            throw OutOfBoundException();
        } else {
            int *tmp = new int[number+1];
            for (int i = 0; i < number; i++) {
                tmp[i] = dopolnitelnipin[i];
            }
            tmp[number++] = pin;
            delete[] dopolnitelnipin;
            dopolnitelnipin = tmp;
            return *this;
        }
    }

    SpecijalnaKarticka &operator=(const SpecijalnaKarticka &other) {
        if (this != &other) {
            Karticka::operator=(other);
            delete[] dopolnitelnipin;
            this->number = other.number;
            this->dopolnitelnipin = new int[number];
            for (int i = 0; i < number; i++) {
                this->dopolnitelnipin[i] = other.dopolnitelnipin[i];
            }
        }
        return *this;
    }
};

class Banka {
private:
    char naziv[30];
    Karticka *karticki[20];
    int broj;
    static int LIMIT;
public:
    Banka(char *naziv, Karticka **karticki, int broj) {
        strcpy(this->naziv, naziv);
        for (int i = 0; i < broj; i++) {
            //ako kartickata ima dopolnitelni pin kodovi
            if (karticki[i]->getDopolnitelenPin()) {
                this->karticki[i] = new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka *>(karticki[i]));
            } else this->karticki[i] = new Karticka(*karticki[i]);
        }
        this->broj = broj;
    }

    ~Banka() {
        for (int i = 0; i < broj; i++) delete karticki[i];
    }

    static void setLIMIT(int limit) {
        LIMIT = limit;
    };


    void pecatiKarticki() {
        cout << "Vo bankata " << naziv << " moze da se probijat kartickite:" << endl;
        for (int i = 0; i < broj; i++) {
            if (karticki[i]->tezinaProbivanje() <= LIMIT) {
                cout << *karticki[i] << endl;
            }
        }
    }

    void dodadiDopolnitelenPin(char *smetka, int novPin) {
        for (int i = 0; i < broj; i++) {
            if(karticki[i]->getDopolnitelenPin()){
                if (strcmp(smetka, karticki[i]->getSmetka()) == 0) {
                    try {
                        *dynamic_cast<SpecijalnaKarticka*>(karticki[i]) += novPin;
                    } catch (OutOfBoundException e) {
                        e.print();
                    }
                }
            }
        }
    }
};

int Banka::LIMIT = 4;

int main() {

    Karticka **niza;
    int n, m, pin;
    char smetka[16];
    bool daliDopolnitelniPin;
    cin >> n;
    niza = new Karticka *[n];
    for (int i = 0; i < n; i++) {
        cin >> smetka;
        cin >> pin;
        cin >> daliDopolnitelniPin;
        if (!daliDopolnitelniPin)
            niza[i] = new Karticka(smetka, pin);
        else
            niza[i] = new SpecijalnaKarticka(smetka, pin);
    }

    Banka komercijalna("Komercijalna", niza, n);
    for (int i = 0; i < n; i++) delete niza[i];
    delete[] niza;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> smetka >> pin;

        komercijalna.dodadiDopolnitelenPin(smetka, pin);

    }

    Banka::setLIMIT(5);

    komercijalna.pecatiKarticki();

}
