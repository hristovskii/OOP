/*
Да се дефинира класа Vozac во која се чуваат информации за:

име (низа од максимум 100 знаци)
возраст (цел број)
број на трки (цел број)
дали е ветеран (да/не).
Да се преоптоварат:

операторот << за печатење кој ќе ги печати името, возраст, бројот на трки и дали е ветеран (се печати VETERAN)
операторот == за споредување на два возачи според заработувачката по трка.
Од оваа класа да се изведат две нови класи Avtomobilist и Motociklist.

За автомобилистот дополнително се чува:

цена на автомобилот (децимален број).
За мотоциклистот дополнително се чува:

моќност на мотор (цел број).
Заработувачката по трка на возачите се пресметува како:

за автомобилостот заработувачката по трка е $\frac{CENA_{AVTOMOBIL}}{5}$
за мотоциклистот заработувачката по трка е $MOKJNOST_NA_MOTOR * 20$
Секој автомобилист плаќа данок на заработка. Да се напишат соодветни методи за пресметување данок:

за автомобилисти: ако бројот на трки е поголем од 10 стапката на данок е 15% од заработката, инаку 10% од заработката.
за мотоциклисти: ако е ветеран стапката на данок е 25% од заработката, инаку 20% од заработката.
Да се напше надворешна функција soIstaZarabotuvachka која како аргументи прима низа од покажувачи од класата Vocac, нивниот број, како и покажувач кон ојбект од возач и враќа како резултат бројот на возачи кои имаат иста заработувачка по трка со проследениот возач.

For example:

Input	
5
1
Hamilton 30 95 0 55000
Vetel 26 88 1 800
Barrichello 38 198 0 810
Rossi 32 130 1 800
Lorenzo 24 45 0 900
VozacX 38 198 1 800

Result
=== DANOK ===
Hamilton
30
95
1650
Vetel
26
88
VETERAN
4000
Barrichello
38
198
3240
Rossi
32
130
VETERAN
4000
Lorenzo
24
45
3600
=== VOZAC X ===
VozacX
38
198
VETERAN
=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===
2

*/

#include <iostream>
#include <cstring>

using namespace std;

class Vozac {
protected:
    char name[101];
    int age;
    int races;
    bool veteran;

public:
    Vozac(char *name = "", int age = 0, int races = 0, bool veteran = false) : age(age), races(races),
                                                                               veteran(veteran) {
        strcpy(this->name, name);
    }

    Vozac(const Vozac &other) {
        strcpy(this->name, name);
        this->age = age;
        this->races = races;
        this->veteran = veteran;
    }

    Vozac &operator=(const Vozac &other) {
        if (this != &other) {
            strcpy(this->name, name);
            this->age = age;
            this->races = races;
            this->veteran = veteran;
        }
        return *this;
    }

    const char *getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    void setAge(int age) {
        Vozac::age = age;
    }

    int getRaces() const {
        return races;
    }

    void setRaces(int races) {
        Vozac::races = races;
    }

    bool isVeteran() const {
        return veteran;
    }

    void setVeteran(bool veteran) {
        Vozac::veteran = veteran;
    }

    virtual float zarabotuvacka() = 0;

    virtual float danok() = 0;

    bool operator==(Vozac &other) {
        return zarabotuvacka() == other.zarabotuvacka();
    }

    friend ostream &operator<<(ostream &os, const Vozac &vozac) {
        os << vozac.name << endl;
        os << vozac.age << endl;
        os << vozac.races << endl;
        if (vozac.veteran) {
            os << "VETERAN" << endl;
        }
        return os;
    }

    virtual ~Vozac() {}
};

class Avtomobilist : public Vozac {
private:
    float price;
public:
    Avtomobilist(char *name = "", int age = 0, int races = 0, bool veteran = false, float price = 0) : Vozac(name, age,
                                                                                                             races,
                                                                                                             veteran),
                                                                                                       price(price) {}

    Avtomobilist(const Avtomobilist &other) : Vozac(other) {
        this->price = other.price;
    };

    ~Avtomobilist() override {}

    float zarabotuvacka() override {
        return price / 5;
    }

    float danok() override {
        if (races > 10) {
            return zarabotuvacka() * 15 / 100.0;
        } else {
            return zarabotuvacka() * 10 / 100.0;
        }
    };
    };
    class Motociklist : public Vozac {
    private:
        int power;
    public:
        Motociklist(char *name = "", int age = 0, int races = 0, bool veteran = false, int power = 0) : Vozac(name, age,
                                                                                                              races,
                                                                                                              veteran),
                                                                                                        power(power) {}

        Motociklist(const Motociklist &other) : Vozac(other) {
            this->power = power;
        }

        ~Motociklist() override {}

        float zarabotuvacka() override{
            return power*20;
        }

        float danok() override{
            if(veteran){
                return zarabotuvacka() *25/100.0;
            }
            else{
                return zarabotuvacka()*20/100.0;
            }
        }
    };

    int soIstaZarabotuvachka(Vozac **vozaci, int n, Vozac *vozac ){
        int counter=0;
        for (int i = 0; i < n; ++i) {
            if(*vozaci[i]==*vozac){
                counter++;
            }
            
        }
        return counter;
    }



int main() {
	int n, x;
	cin >> n >> x;
	Vozac **v = new Vozac*[n];
	char ime[100];
	int vozrast;
	int trki;
	bool vet;
	for(int i = 0; i < n; ++i) {
		cin >> ime >> vozrast >> trki >> vet;
		if(i < x) {
			float cena_avto;
			cin >> cena_avto;
			v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
		} else {
			int mokjnost;
			cin >> mokjnost;
			v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
		}
	}
	cout << "=== DANOK ===" << endl;
	for(int i = 0; i < n; ++i) {
		cout << *v[i];
		cout << v[i]->danok() << endl;
	}
	cin >> ime >> vozrast >> trki >> vet;
	int mokjnost;
	cin >> mokjnost;
	Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
	cout << "=== VOZAC X ===" << endl;
	cout << *vx;
	cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
	cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
	return 0;
}