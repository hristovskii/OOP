/*
 Како успешен студент на ФИНКИ вие сте повикани да работите на подобрување на IKnow системот. Како дел од системот треба да се додаде нов дел кој ќе биде одговорен за обработување на дисциплински мерки, па како дел од тимот за развивање на софтверот ќе треба да ја имплементирате класата DisciplinaryAction која ќе ги чува следните информации:

Името на студентот (динамички алоцирана низа од карактери)
Индексот на студентот (int)
Причината за дисциплинската мерка (динамички алоцирана низа од карактери)
бројот на сесии во кои студентот нема право да полага (int)

Класата треба да ги има следните методи и конструктори:

Default конструктор
Copy конструктор
Конструктор со аргументи
Деструктор
Set и Get методи за индексот
Оператор =
оператор << за печатење на информации за студентот
оператор ++ за зголемување на бројот на сесии во кои студентот е казнет (во префикс нотација)
оператор >= за споредба на дисциплински постапки според бројот на сесии во кои студентот е казнет

Операторот << треба да печати според следниот формат:
Student: [Name]
Student's index: [Index]
Reason: [Reason]
Sessions: [Sessions]


При што вредностите во [] треба да се заменат со вредностите во класата!

!!! ДА НЕ СЕ ПРАВАТ ПРОМЕНИ ВО MAIN() ФУНКЦИЈАТА !!!

For example:

Input
1
Stefan 151020 Prepis 2

 Result
-- Testing operator = & operator <<  --
Student: Stefan
Student's index: 151020
Reason: Prepis
Sessions: 2

-- Testing copy constructor & set index --
-------------
Source:
-------------
Student: Stefan
Student's index: 151020
Reason: Prepis
Sessions: 2

-------------
Copied and edited:
-------------
Student: Stefan
Student's index: 112233
Reason: Prepis
Sessions: 2

-- Testing if array was inputted correctly --
Student: Stefan
Student's index: 151020
Reason: Prepis
Sessions: 2

Testing operator ++ and <<
Student: Stefan
Student's index: 151020
Reason: Prepis
Sessions: 3

Testing operator >=
 */

#include <iostream>
#include <string.h>

using namespace std;

class DisciplinaryAction {
private:
    char *name;
    int index;
    char *reason;
    int number;

    void copy(const DisciplinaryAction &other) {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        this->index = other.index;
        this->reason = new char[strlen(other.reason) + 1];
        strcpy(this->reason, other.reason);
        this->number = other.number;

    }

public:
    DisciplinaryAction(char *name = " ", int index = 0, char *reason = " ", int number = 0) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->index = index;
        this->reason = new char[strlen(reason) + 1];
        strcpy(this->reason, reason);
        this->number = number;
    }

    DisciplinaryAction(const DisciplinaryAction &other) {
        copy(other);
    }

    DisciplinaryAction &operator=(const DisciplinaryAction &other) {
        if (this != &other) {
            delete[]name;
            delete[]reason;
            copy(other);
            return *this;
        }
        return *this;
    }

    ~DisciplinaryAction() {
        delete[]name;
        delete[]reason;
    }

    char *getName() const {
        return name;
    }

    int getIndex() const {
        return index;
    }

    char *getReason() const {
        return reason;
    }

    void setName(char *name) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    void setIndex(int index) {
        DisciplinaryAction::index = index;
    }

    void setReason(char *reason) {
        this->reason = new char[strlen(reason) + 1];
        strcpy(this->reason, reason);
    }

    int getNumber() const {
        return number;
    }

    void setNumber(int number) {
        this->number = number;
    }

    friend ostream &operator<<(ostream &out, const DisciplinaryAction &other) {
        out << "Student: " << other.name << endl;
        out << "Student's index: " << other.index << endl;
        out << "Reason: " << other.reason << endl;
        out << "Sessions: " << other.number << endl;
        return out;
    }

    DisciplinaryAction &operator++() {
        ++number;
        return *this;
    }

    bool operator>=(const DisciplinaryAction &other) const {
        if (number >= other.number) {
            return true;
        } else {
            return false;
        }
    }
};


/// Do NOT edit the main() function

int main() {
    int n;
    cin >> n;

    /// Testing Default constructor and equal operator
    /// Array input

    DisciplinaryAction arr[n];

    for (int i = 0; i < n; i++) {
        char name[100];
        char reason[100];
        int index;
        int sessions;

        cin >> name >> index >> reason >> sessions;

        arr[i] = DisciplinaryAction(name, index, reason, sessions);
    }

    cout << "-- Testing operator = & operator <<  --\n";
    cout << arr[0];

    /// Testing copy constructor & set index

    DisciplinaryAction merka(arr[0]);
    merka.setIndex(112233);

    cout << "\n-- Testing copy constructor & set index --\n";
    cout << "-------------\n";
    cout << "Source:\n";
    cout << "-------------\n";
    cout << arr[0];

    cout << "\n-------------\n";
    cout << "Copied and edited:\n";
    cout << "-------------\n";
    cout << merka;

    /// Testing if array is OK

    cout << "\n-- Testing if array was inputted correctly --\n";

    for (int i = 0; i < n; i++)
        cout << arr[i];


    cout << "\nTesting operator ++ and <<" << endl;
    for (int i = 0; i < n; i++)
        cout << (++arr[i]);


    cout << "\nTesting operator >=" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                cout << i << " " << ((arr[i] >= arr[j]) ? ">= " : "< ") << j << endl;
            }
        }
    }

    return 0;
}