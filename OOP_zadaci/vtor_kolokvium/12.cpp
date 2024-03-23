/*
Да се креира класа за опишување на еден сервис за мобилни уреди. За секој мобилен телефон се чуваат податоци за модел (низа од 100 знаци), тип на уред (смартфон или компјутер), потребни часови за основна проверка (децимален број), година на производство (цел број). (5 поени)

Сите уреди имаат исто времетраење за основна проверка и истата изнесува 1 час. Оваа вредност може да се смени со одлука на сервисот. Дополнително, уредите кои се понови од 2015 година имаат потреба од дополнителени 1.5 часа за проверка. При проверка, лаптопите имаат потреба од дополнителни 2 часа за софтверска дијагностика (5 поени).

За оваа класа да се имплементира оператор << за печатење на уред во формат:

[modelnauredotl]
[tipnaured] [casovizaproverka]

Каде часовите за проверка се оние од основната проверка+ дополнителни 2 часа доколку уредот е понов од 2015 + 2 часа доколу уредот е лаптоп (5 поени)

Да се креира класа MobileServis во која се чува адреса (низа од 100 знаци), низа од уреди (динамички алоцирана низа) и број на уреди.(5 поени)

За класата да се обезбедат:

operatoror+= за додавање на нов уред во сервисот.(5 поени) Не смее да се дозволи годината на производство на уредот да биде поголема од 2019 или помала од 2000. Ако се направи обид за додавање на уред со невалидна година, треба да се генерира исклучок InvalidProductionDate. (10 поени)

Функција pecatiUredi со која се печатат сите уреди со времето потребно за нивната проверка во сервисот (5 поени).

Да се обезбедат сите дополнителни методи потребни за правилно функционирање на програмата. (5 поени)

For example:

Input	
3
TelService
6
iPhone
0
2020
Samsung
0
1999
Huawei
0
1990
Toshiba
1
2016
OnePlus
0
2009
Fujitsu
1
2010

Result
===== Testiranje na isklucoci ======
Невалидна година на производство
Невалидна година на производство
Невалидна година на производство
Ime: TelService
Toshiba
Laptop 5
OnePlus
Mobilen 1
Fujitsu
Laptop 3
*/

#include <iostream>
#include <cstring>

using namespace std;
enum tip {
    SMARTPHONE, COMPUTER
};

class InvalidProductionDate {
public:
    void print() {
        cout << "Невалидна година на производство" << endl;
    }
};

class Device {
protected:
    char model[101];
    tip type;
    int year;
    static float hours;
public:
    Device(char *model = " ", tip type = SMARTPHONE, int year = 0) {
        strcpy(this->model, model);
        this->type = type;
        this->year = year;
    }

    Device(const Device &other) {
        strcpy(this->model, other.model);
        this->type = other.type;
        this->year = other.year;
    }

    virtual ~Device() {}

    void setType(tip type) {
        Device::type = type;
    }

    void setYear(int year) {
        Device::year = year;
    }

    static void setPocetniCasovi(float hours) {
        Device::hours = hours;
    }

    float proverka() {
        float proverka = hours;
        if (year > 2015) {
            proverka += 2;
        }
        if (type == COMPUTER) {
            proverka += 2;
        }
        return proverka;
    }

    friend ostream &operator<<(ostream &os, Device &device) {
        os << device.model << endl;
        switch (device.type) {
            case SMARTPHONE:
                os << "Mobilen ";
                break;
            case COMPUTER:
                os << "Laptop ";
                break;
        }
        os << device.proverka() << endl;
        return os;
    }

    const char *getModel() const;

    tip getType() const;

    int getYear() const;

    static float getHours();
};

float Device::hours = 1;

const char *Device::getModel() const {
    return model;
}

tip Device::getType() const {
    return type;
}

int Device::getYear() const {
    return year;
}

float Device::getHours() {
    return hours;
}

class MobileServis {
private:
    char adresa[101];
    Device *devices;
    int n;
public:
    MobileServis(char *adresa = " ", Device *devices = 0, int n = 0) {
        strcpy(this->adresa, adresa);
        this->n=n;
        this->devices = new Device[n];
        for (int i = 0; i < n; i++) {
            this->devices[i] = devices[i];
        }
    }

    MobileServis(const MobileServis &other) {
        strcpy(this->adresa, other.adresa);
        this->n=other.n;
        this->devices = new Device[other.n];
        for (int i = 0; i < other.n; i++) {
            this->devices[i] = other.devices[i];
        }
    }

    virtual ~MobileServis() {}

    MobileServis &operator+=(const MobileServis &other) {
        if (this != &other) {
            delete[] devices;
            this->n=other.n;
            strcpy(this->adresa, other.adresa);
            this->devices = new Device[other.n];
            for (int i = 0; i < other.n; i++) {
                this->devices[i] = other.devices[i];
            }
        }
        return *this;
    }

    MobileServis &operator+=(Device &other) {
        if (other.getYear() > 2019 || other.getYear() < 2000) {
            throw InvalidProductionDate();
        } else {
            Device *temp = new Device[n + 1];
            for (int i = 0; i < n; i++) {
                temp[i] = devices[i];
            }
            temp[n++] = other;
            delete[] devices;
            devices = temp;
            return *this;
        }
    }

    void pecatiCasovi() {
        cout << "Ime: " << adresa << endl;
        for (int i = 0; i < n; i++) {
            cout << devices[i];
        }
    }
};

int main() {
    int testCase;
    cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
    if (testCase == 1) {
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> tipDevice;
        cin >> godina;
        Device ig(ime, (tip) tipDevice, godina);
        cin >> ime;
        MobileServis t(ime);
        cout << ig;
    }
    if (testCase == 2) {
        cout << "===== Testiranje na operatorot += ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            try {
                t += tmp;
            } catch (InvalidProductionDate e) {
                e.print();
            }

        }
        t.pecatiCasovi();
    }
    if (testCase == 3) {
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            try {
                t += tmp;
            } catch (InvalidProductionDate e) {
                e.print();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 4) {
        cout << "===== Testiranje na konstruktori ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            try {
                t += tmp;
            } catch (InvalidProductionDate e) {
                e.print();
            }
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    if (testCase == 5) {
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            try {
                t += tmp;
            } catch (InvalidProductionDate e) {
                e.print();
            }
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
        Device::setPocetniCasovi(2);
        t.pecatiCasovi();
    }

    if (testCase == 6) {
        cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            try {
                t += tmp;
            } catch (InvalidProductionDate e) {
                e.print();
            }
        }
        Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }

    return 0;

}

