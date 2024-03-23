/*

ISTA KAKO 15TA ZADACA

Да се дефинира структура RabotnaNedela во која се чуваат бројот на работни часови за секој работен ден во неделата (5 дена) и број на неделата. Потоа да се дефинира структура Rabotnik за кој се чува име (низа од 50 знаци) и низа од работни недели (макс 4).

Да се имплементираат следните функции:

int maxNedela(Rabotnik *r) која за проследениот работник ќе го врати бројот на неделата со најмногу работни часови
void table(Rabotnik *r, int n) која за низата од работници ќе отпечати приказ во следниот формат:
Пример

Rab     1   2   3   4   Vkupno
Brianna 192 238 226 225 881
Ava     236 231 184 212 863
Matthew 236 235 219 243 933
Alyssa  240 254 217 228 939
Emma    247 205 204 242 898 
каде во секој ред се печати името на работникот и вкупниот број на работни часови за секоја работна недела, како и вкупниот број на часови за сите недели. Во рамките на редот податоците се разделени со знак за табулатор \t.

For example:

Input	
5
Brianna
35 33 42 42 40
31 57 52 54 44
56 32 51 52 35
43 39 34 54 55
Ava
44 47 44 50 51
30 46 59 36 60
39 32 35 31 47
44 38 41 46 43
Matthew
51 37 39 55 54
36 60 54 38 47
41 57 41 39 41
56 34 43 54 56
Alyssa
59 55 57 37 32
60 54 50 37 53
54 38 34 36 55
57 55 36 41 39
Emma
58 54 42 49 44
30 45 47 44 39
52 39 44 32 37
40 50 44 56 52

Result
TABLE
Rab	1	2	3	4	Vkupno
Brianna	192	238	226	225	881
Ava	236	231	184	212	863
Matthew	236	235	219	243	933
Alyssa	240	254	217	228	939
Emma	247	205	204	242	898
MAX NEDELA NA RABOTNIK: Matthew
4
*/


//ISTA KAKO 15TA ZADACA


#include <stdio.h>
#include <string.h>

#define NEDELI 4
#define DENOVI 5

// ovde strukturata RabotnaNedela

typedef struct RabotnaNedela
{
    int casovi[DENOVI];
    int i;
} RN;

// ovde strukturata Rabotnik

typedef struct Rabotnik
{
    char ime[30];
    RN nedeli[NEDELI];
} R;

// ovde funkciite

int maxNedela(R *r)
{
    int max = 0;
    int index = 0;
    int s;

    for (int i = 0; i < NEDELI; i++)
    {
        s = 0;

        for (int j = 0; j < DENOVI; j++)
            s += r->nedeli[i].casovi[j];

        if (max < s)
        {
            max = s;
            index = i;
        }
    }

    return index + 1;
}

void table(R *r, int n)
{
    int a[NEDELI];
    int vkupno;

    printf("Rab\t1\t2\t3\t4\tVkupno\n");

    for (int i = 0; i < n; i++)
    {
        vkupno = 0;

        for (int j = 0; j < NEDELI; j++)
            a[j] = 0;

        for (int j = 0; j < NEDELI; j++)
            for (int k = 0; k < DENOVI; k++)
                a[j] += r[i].nedeli[j].casovi[k];

        printf("%s\t", r[i].ime);
        for (int j = 0; j < NEDELI; j++)
        {
            vkupno += a[j];
            printf("%d\t", a[j]);
        }
        printf("%d\n", vkupno);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    R rabotnici[n];
    int i;
    for (i = 0; i < n; ++i)
    {
        scanf("%s", rabotnici[i].ime);
        int j;
        for (j = 0; j < NEDELI; ++j)
        {
            int k;
            for (k = 0; k < DENOVI; ++k)
            {
                scanf("%d", &rabotnici[i].nedeli[j].casovi[k]);
            }

        }
    }
    printf("TABLE\n");
    table(rabotnici, n);
    printf("MAX NEDELA NA RABOTNIK: %s\n", rabotnici[n / 2].ime);
    printf("%d\n", maxNedela(&rabotnici[n / 2]));
    return 0;
}