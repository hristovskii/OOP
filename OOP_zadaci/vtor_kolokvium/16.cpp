/*
Туристичка агенција нуди различни понуди за транспорт на патници. За секоја понуда се чуваат податоци за дестинацијата (низа од знаци), основна цена (цел број) и податок за растојанието до дестинацијата изразено во km (цел број).

Од класата Transport да се изведат класите AvtomobilTransport и KombeTransport за моделирање на понудите за транспорт кои нудат транспорт со автомобил или комбе, соодветно. За секоја понуда за транспорт со автомобил се чува податок за тоа дали во понудата има платен шофер (булова променлива), а за транспорт со комбе бројот на луѓе кои може да се превезат во комбето (цел број). (5 поени)

За секој објект од двете изведени класи треба да бидат на располагање следниве методи:

конструктор со аргументи што одговараат на податочните членови и set и get методи за податочните членови (5 поени)
метод cenaTransport, за пресметување на цената на понудата на следниот начин:
За транспорт со автомобил - основната цена се зголемува за 20% ако има платен шофер
За транспорт со комбе - основната цена ќе се намали зависно од бројот на патници во комбето. За секој патник во комбето цената се намалува за 200 (10 поени)
преоптоварен оператор < за споредба на две понуди за транспорт на патник според растојанието до дестинацијата. (5 поени)
Да се имплементира функција pecatiPoloshiPonudi што на влез прима низа од понуди за транспорт на патник, бројот на елементите од низата и една понуда T. Функцијата ја печати дестинацијата, растојанието до дестинацијата и цената за понудите од низата кои се поскапи од понудата T сортирани во растечки редослед по растојанието до дестинацијата (погледни го повикот на функцијата) (10 поени)

Комплетна функционалност на кодот (5 поени)

For example:

Input	
3
1 Belgrad 3200 900 1
1 Bitola 2500 400 0
2 Sofija 5000 1040 2

Result
Bitola 400 2500
Belgrad 900 3840
Sofija 1040 4600
*/

#include <iostream>
#include <cstring>

using namespace std;

class Transport {
protected:
    char destination[100];
    int base_price;
    int distance;
public:
    Transport(char *destination = " ", int base_price = 0, int distance = 0) {
        strcpy(this->destination, destination);
        this->base_price = base_price;
        this->distance = distance;
    }

    Transport(const Transport &other) {
        strcpy(this->destination, other.destination);
        this->base_price = other.base_price;
        this->distance = other.distance;
    }

    const char *getDestination() const {
        return destination;
    }

    int getBasePrice() const {
        return base_price;
    }

    void setBasePrice(int basePrice) {
        base_price = basePrice;
    }

    int getDistance() const {
        return distance;
    }

    void setDistance(int distance) {
        Transport::distance = distance;
    }

    virtual ~Transport() {}

    virtual float cenaTransport() {
        return base_price;
    }

    bool operator<(const Transport &rhs) const {
        return distance < rhs.distance;
    }

    Transport &operator=(const Transport &other) {
        if (this != &other) {
            strcpy(this->destination, other.destination);
            this->base_price = other.base_price;
            this->distance = other.distance;
        }
        return *this;
    }
};

class AvtomobilTransport : public Transport {
private:
    bool driver;
public:
    AvtomobilTransport(char *destination = " ", int basePrice = 0, int distance = 0, bool driver = false) : Transport(
            destination, basePrice,
            distance) {
        this->driver = driver;
    }

    AvtomobilTransport(const AvtomobilTransport &other) : Transport(other) {
        this->driver = other.driver;
    }

    ~AvtomobilTransport() override {}

    bool isDriver() const {
        return driver;
    }

    void setDriver(bool driver) {
        AvtomobilTransport::driver = driver;
    }

    float cenaTransport() override {
        if (driver) {
            return Transport::cenaTransport() * 1.2;
        } else {
            return Transport::cenaTransport();
        }
    }

    AvtomobilTransport &operator=(const AvtomobilTransport &other) {
        if (this != &other) {
            Transport::operator=(other);
            this->driver = other.driver;
        }
        return *this;
    }
};

class KombeTransport : public Transport {
private:
    int number;
public:
    KombeTransport(char *destination = " ", int basePrice = 0, int distance = 0, int number = 0) : Transport(
            destination, basePrice,
            distance) {
        this->number = number;
    }

    KombeTransport(const KombeTransport &other) : Transport(other) {
        this->number = other.number;
    }

    ~KombeTransport() override {}

    int getNumber() const {
        return number;
    }

    void setNumber(int number) {
        KombeTransport::number = number;
    }

    float cenaTransport() override {
        return Transport::cenaTransport() - (200 * number);
    }

    KombeTransport &operator=(const KombeTransport &other) {
        if (this != &other) {
            Transport::operator=(other);
            this->number = other.number;
        }
        return *this;
    }
};

void pecatiPoloshiPonudi(Transport **transporti, int n, Transport &ponuda) {
    int counter = 0;
    for (int i = 0; i < n; i++) {
        if (transporti[i]->cenaTransport() > ponuda.cenaTransport()) {
            counter++;
        }
    }
    Transport **temp;
    temp = new Transport *[counter];
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (transporti[i]->cenaTransport() > ponuda.cenaTransport()) {
            temp[j++] = transporti[i];
        }
    }

    for (int i = 0; i < counter; ++i) {
        for (int j = i + 1; j < counter; ++j) {
            if (temp[i]->cenaTransport() > temp[j]->cenaTransport()) {
                Transport *temp2 = temp[i];
                temp[i] = temp[j];
                temp[j] = temp2;
            }
        }
    }
    for (int i = 0; i < counter; i++) {
        cout << temp[i]->getDestination() << " " << temp[i]->getDistance() << " "
             << temp[i]->cenaTransport() << endl;
    }
}
int main(){

char destinacija[20];
int tip,cena,rastojanie,lugje;
bool shofer;
int n;
cin>>n;
Transport  **ponudi;
ponudi=new Transport *[n];

for (int i=0;i<n;i++){

    cin>>tip>>destinacija>>cena>>rastojanie;
    if (tip==1) {
        cin>>shofer;
        ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

    }
    else {
        cin>>lugje;
        ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
    }


}

AvtomobilTransport nov("Ohrid",2000,600,false);
pecatiPoloshiPonudi(ponudi,n,nov);

for (int i=0;i<n;i++) delete ponudi[i];
delete [] ponudi;
return 0;
}
