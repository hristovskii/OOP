/*
 Да се дефинира класа Flight во која што ќе се чуваат податоци за лет:

име на лет (низа од максимум 100 карактери)
полетување од (низа од максимум 50 карактери)
пристигнување во (низа од максимум 50 карактери)
цена на лет (цел број)
За класата да се дефинира copy конструктор, default конструктор и конструктор со аргументи.
Доколку е потребно да се креираат и get методи.

Потоа да се креира класа Airport во која што се чуваат следните податоци:

име на аеродром (низа од максимум 50 карактери)
број на летови на аеродромот(цел број)
низа од летови на аеродромот(низа од објекти од Flight класата, max 100)
Да се креира конструктор со аргументи за класата.
Доколку е потребно да се креира и get методи.

Во класата да се креира функција cheapestFlight што ќе го врати најевтиниот лет на аеродромот.

ДА НЕ СЕ МЕНУВА MAIN ФУНКЦИЈАТА.

 For example:

Input
SkopjeInternationalAirport
5
OS776 SKOPJE(SKP) VIENNA(VIE) 100
W67719 SKOPJE(SKP) PARIS(BVA) 70
LTNSKP112 LONDON(LTN) SKOPJE(SKP) 150
IATA110 SKOPJE(SKP) ISTANBUL(IST) 80
TK1004 ISTANBUL(IST) SKOPJE(SKP) 101

 Result
The cheapest flight is: W67719 from SKOPJE(SKP) to PARIS(BVA) and it costs 70$
 */

#include <iostream>
#include <cstring>

using namespace std;

class Flight {
private:
    char FlightName[100];
    char From[50];
    char To[50];
    int Price;
public:
    Flight() {}

    Flight(char *FlightName, char *From, char *To, int Price) {
        strcpy(this->FlightName, FlightName);
        strcpy(this->From, From);
        strcpy(this->To, To);
        this->Price = Price;
    }

    Flight(const Flight &f) {
        strcpy(this->FlightName, f.FlightName);
        strcpy(this->From, f.From);
        strcpy(this->To, f.To);
        this->Price = f.Price;
    }

    const char *getFlightName() const {
        return FlightName;
    }

    const char *getFrom() const {
        return From;
    }

    const char *getTo() const {
        return To;
    }

    int getPrice() const {
        return Price;
    }

    void setPrice(int Price) {
        Flight::Price = Price;
    }
};

class Airport{
private:
    char ime_aer[50];
    int letovi;
    Flight flights[100];
public:
    Airport(){}
    Airport(char *ime_aer, int letovi, Flight *flights){
        strcpy(this->ime_aer, ime_aer);
        this->letovi=letovi;
        for(int i=0; i<letovi; i++){
            this->flights[i]=flights[i];
        }
    }

    Flight cheapestFlight() {
        int minI = 0, min = flights[0].getPrice();
        for (int i = 0; i < letovi; i++) {


            if (flights[i].getPrice() < min) {
                min = flights[i].getPrice();
                minI = i;
            }
        }
        return flights[minI];
    }
};

// DO NOT CHANGE THE MAIN FUNCTION
int main() {
    char airport_name[10];
    int n;
    // testing default constructor
    Flight flights[100];
    cin >> airport_name >> n;
    for (int i = 0; i < n; i++) {
        char flight_name[100], from[50], to[50];
        int price;
        cin >> flight_name >> from >> to;
        cin >> price;

        // testing constructor with parameters
        Flight flight(flight_name, from, to, price);

        // testing copy constructor
        flights[i] = Flight(flight);
    }
    // testing constructor with parameters for Airport
    Airport airport(airport_name, n, flights);
    Flight cheapest = airport.cheapestFlight();
    // testing cheapestFlight method
    cout << "The cheapest flight is: " << cheapest.getFlightName() << " from " << cheapest.getFrom() << " to "
         << cheapest.getTo() << " and it costs " << cheapest.getPrice() << "$";

    return 0;
}


