/*
Во рамките на еден телекомуникациски оператор, СМС пораките се делат на регуларни и специјални. За секојa СМС порака се знае:

основна цена за една порака до 160 знаци (реален број)
претплатнички број на кој е испратена (низа од знаци со должина 12)
Класата за опишување на СМС пораки е апстрактна (5 поени).

За секоја Регуларна СМСдополнително се чуваат податоци за текстот на пораката и тоа дали е користена роаминг услуга (bool променлива). За секоја Специјална СМС дополнително се чуваат податоци за тоа дали е наменета за хуманитарни цели (bool променлива). (5 поени)

За секој објект од двете изведени класи треба да бидат на располагање следниве методи:

Метод SMS_cena(), за пресметување на цената на испратена СМС порака на следниот начин: (10 поени)

За регуларна СМС - цената се зголемува за 300% од основната цена ако е испратена од странство, а 18% од дома и цената се формира врз база на тоа во колку СМС пораки ќе го собере текстот што сакаме да го испратиме. Една регуларна порака може да собере најмногу 160 знаци. Притоа, доколку се надмине 160-от знак, се започнува нова порака и цената се пресметува како за две или повеќе пораки (пр. за 162 знаци, цената на СМС е иста како и за 320 знаци).
За специјална СМС - цената се зголемува за 150% од основната цена ако пораката HE е наменета за хуманитарни цели. Доколку е наменета за тоа, данокот од 18% не се пресметува на цената.
Пресметувањето 18% данок на цената на сите СМС пораки е фиксен и не се менува, додека пак процентот од 300% за регуларни и 150% за специјални СМС е променлив и во зависност од операторот може да се менува. Да се обезбеди механизам за можност за нивно менување. (5 поени)
Преоптоварен оператор << за печатење на податоците за СМС пораките во формат: (5 поени)

Тел.број: цена
Да се имплементира функција vkupno_SMS со потпис:

void vkupno_SMS(SMS** poraka, int n)
во која се печати вкупниот број на регуларни СМС пораки и нивната вкупна цена, како и бројот на специјални СМС пораки и нивната вкупна цена во проследената низа посебно. (15 поени)

Да се обезбедат сите потребни функции за правилно функционирање на програмата (5 поени).

For example:

Input	
4
0038971123456
5
Test poraka za testiranje na promena na procentot?
1
0038971123456
5
Test poraka za testiranje na promena na procentot?
1
350

Result
====== Testing RegularSMS class with a changed percentage======
Tel: 0038971123456 - cena: 20den.
Tel: 0038971123456 - cena: 22.5den.
*/

#include <iostream>
#include <cstring>

using namespace std;
class SMS {
protected:
    float baseprice;
    char tel[14];
    static const float danok;
public:
    SMS(float baseprice = 0, char *tel = " ") {
        this->baseprice = baseprice;
        strcpy(this->tel, tel);
    }

    SMS(const SMS &other) {
        this->baseprice = other.baseprice;
        strcpy(this->tel, other.tel);
    }

    virtual ~SMS() {}

    float getBaseprice() const {
        return baseprice;
    }

    void setBaseprice(float baseprice) {
        SMS::baseprice = baseprice;
    }

    const char *getTel() const {
        return tel;
    }

    virtual float SMS_cena() = 0;

    friend ostream &operator<<(ostream &os, SMS &sms) {
        os << "Tel: " << sms.tel << " - cena: " << sms.SMS_cena() << "den." << endl;
        return os;
    }

    SMS &operator=(const SMS &other) {
        if (this != &other) {
            this->baseprice = other.baseprice;
            strcpy(this->tel, other.tel);
        }
        return *this;
    }
};

const float SMS::danok = 1.18;

class RegularSMS : public SMS {
private:
    bool roaming;
    char *text;
    static float rProcent;
public:
    RegularSMS(char *tel = " ", float baseprice = 0, char *text = " ", bool roaming = false) : SMS(baseprice, tel) {
        this->roaming = roaming;
        this->text = new char[strlen(text) + 1];
        strcpy(this->text, text);
    }

    RegularSMS(const RegularSMS &other) : SMS(other) {
        this->roaming = other.roaming;
        this->text = new char[strlen(other.text) + 1];
        strcpy(this->text, other.text);
    }

    RegularSMS &operator=(const RegularSMS &other) {
        if (this != &other) {
            delete[] text;
            SMS::operator=(other);
            this->roaming = other.roaming;
            this->text = new char[strlen(other.text) + 1];
            strcpy(this->text, other.text);
        }
        return *this;
    }

    ~RegularSMS() override {}

    bool isRoaming() const {
        return roaming;
    }

    void setRoaming(bool roaming) {
        RegularSMS::roaming = roaming;
    }

    static void set_rProcent(float rProcent) {
        RegularSMS::rProcent = (rProcent/100)+1;
    }

    float SMS_cena() override {
        float cena = baseprice;
        int counter = (strlen(text) / 160) + 1;
        if (roaming) {
            cena = cena*rProcent*counter;
        } else {
            cena = cena*danok*counter;
        }

        return cena;
    }
};

float RegularSMS::rProcent = 4.0;

class SpecialSMS : public SMS {
private:
    bool humanitarian;
    static float sProcent;
public:
    SpecialSMS(char *tel = " ", float baseprice = 0, bool humanitarian = false) : SMS(baseprice, tel) {
        this->humanitarian = humanitarian;
    }

    SpecialSMS(const SpecialSMS &other) : SMS(other) {
        this->humanitarian = other.humanitarian;
    }

    ~SpecialSMS() override {}

    bool isHumanitarian() const {
        return humanitarian;
    }

    void setHumanitarian(bool humanitarian) {
        SpecialSMS::humanitarian = humanitarian;
    }

    static void set_sProcent(float sProcent);

    float SMS_cena() override {
        float cena = baseprice;
        if (!humanitarian) {
            cena *= sProcent;
        } else {
            return cena;
        }

        return cena;
    }
};

float SpecialSMS::sProcent = 2.5;

void SpecialSMS::set_sProcent(float sProcent) {
    SpecialSMS::sProcent = (sProcent/100)+1;
}

void vkupno_SMS(SMS **poraka, int n) {
    int counter1 = 0, counter2 = 0;
    float finalprice1 = 0, finalprice2 = 0;
    for (int i = 0; i < n; i++) {
        RegularSMS *casted1 = dynamic_cast<RegularSMS *>(poraka[i]);
        SpecialSMS *casted2 = dynamic_cast<SpecialSMS *>(poraka[i]);
        if (casted1) {
            counter1++;
            finalprice1 += casted1->SMS_cena();
        } else if (casted2) {
            counter2++;
            finalprice2 += casted2->SMS_cena();
        }
    }
    cout << "Vkupno ima " << counter1 << " regularni SMS poraki i nivnata cena e: " << finalprice1 << endl;
    cout << "Vkupno ima " << counter2 << " specijalni SMS poraki i nivnata cena e: " << finalprice2 << endl;
}
int main(){

	char tel[20], msg[1000];
	float cena;
	float price;
    int p;
	bool roam, hum;
	SMS  **sms;
	int n;
	int tip;

	int testCase;
	cin >> testCase;

	if (testCase == 1){
		cout << "====== Testing RegularSMS class ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i < n; i++){
			cin >> tel;
			cin >> cena;
            cin.get();
			cin.getline(msg, 1000);
			cin >> roam;
			cout << "CONSTRUCTOR" << endl;
			sms[i] = new RegularSMS(tel, cena, msg, roam);
			cout << "OPERATOR <<" << endl;
			cout << *sms[i];
		}
        for (int i = 0; i<n; i++) delete sms[i];
		delete[] sms;
	}
	if (testCase == 2){
		cout << "====== Testing SpecialSMS class ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i < n; i++){
			cin >> tel;
			cin >> cena;
			cin >> hum;
			cout << "CONSTRUCTOR" << endl;
			sms[i] = new SpecialSMS(tel, cena, hum);
			cout << "OPERATOR <<" << endl;
			cout << *sms[i];
		}
        for (int i = 0; i<n; i++) delete sms[i];
		delete[] sms;
	}
	if (testCase == 3){
		cout << "====== Testing method vkupno_SMS() ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i<n; i++){

			cin >> tip;
			cin >> tel;
			cin >> cena;
			if (tip == 1) {

				cin.get();
				cin.getline(msg, 1000);
                cin >> roam;
				
				sms[i] = new RegularSMS(tel, cena, msg, roam);

			}
			else {
				cin >> hum;

				sms[i] = new SpecialSMS(tel, cena, hum);
			}
		}

		vkupno_SMS(sms, n);
        for (int i = 0; i<n; i++) delete sms[i];
		delete[] sms;
	}
    if (testCase == 4){
		cout << "====== Testing RegularSMS class with a changed percentage======" << endl;	
        SMS *sms1, *sms2;	
        	cin >> tel;
			cin >> cena;
            cin.get();
			cin.getline(msg, 1000);
			cin >> roam;
			sms1 = new RegularSMS(tel, cena, msg, roam);
			cout << *sms1;
        
            cin >> tel;
			cin >> cena;
            cin.get();
			cin.getline(msg, 1000);
			cin >> roam;	
        	cin >> p;
        	RegularSMS::set_rProcent(p);
        	sms2 = new RegularSMS(tel, cena, msg, roam);
        	cout << *sms2;
        
        delete sms1, sms2;
	}
    if (testCase == 5){
		cout << "====== Testing SpecialSMS class with a changed percentage======" << endl;	
        SMS *sms1, *sms2;	
        	cin >> tel;
			cin >> cena;
			cin >> hum;
			sms1 = new SpecialSMS(tel, cena, hum);
			cout << *sms1;
        
            cin >> tel;
			cin >> cena;
			cin >> hum;	
        	cin >> p;
        	SpecialSMS::set_sProcent(p);
        	sms2 = new SpecialSMS(tel, cena, hum);
        	cout << *sms2;
        
        delete sms1, sms2;
	}
	
	return 0;
}
