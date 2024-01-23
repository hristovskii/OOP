/*
 За програмски јазик да се употреби C.

Да се напише програма во која од стандарден влез се внесува бројот N (бројот на трансакции), а потоа N трансакциски сметки и како резултат ги печати идентификацискиот број и вкупната сума (со провизија) на сите трансакции платени со кредитна картичка. Во случај да нема трансакција платена со кредитна картичка да се испечати "No credit card transaction".

Во структурата Трансакција (Transaction) треба да се чуваат следните информации:
- Идентификациски број (int)
- Платена сума (int)
- Провизија (int)
- Дали е платено со дебитна или кредитна картичка (0 - дебитна, 1 - кредитна)

Ограничување: 0 < N < 100

Структура на влезните податоци:
N
id1 sum1 commission1 type1
...
idn sumn Commissionn typen

For example:

Input
3
1 100 10 0
2 202 20 1
3 10 1 1

Result
2 222
3 11
 */

#include <stdio.h>
typedef struct Transakcija{
    int id, provizija, suma, nacin;
}Transakcija;

int main() {
    int i, n, f=0;
    scanf("%d", &n);
    for(i=0; i<n; i++){
        Transakcija transakcija;
        scanf("%d %d %d %d", &transakcija.id, &transakcija.suma, &transakcija.provizija, &transakcija.nacin);
        if (transakcija.nacin==1) {
            printf("%d %d\n", transakcija.id, transakcija.provizija+transakcija.suma);
            f = 1;
        }

    }
    if (f == 0) {
        printf("No credit card transaction");
    }
    return 0;
}
