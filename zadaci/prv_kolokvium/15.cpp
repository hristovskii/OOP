/*
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
10
Andrew
44 55 48 34 30
37 35 31 55 59
36 55 57 37 32
57 45 60 42 46
Mia
58 58 56 57 51
56 55 44 56 38
58 34 36 50 45
37 51 45 31 45
Natalie
50 59 42 33 43
44 30 48 38 59
53 34 53 52 31
40 45 44 41 59
John
37 43 39 59 49
51 60 49 60 33
40 38 58 39 46
42 33 31 42 60
Brianna
60 51 52 57 40
55 31 55 34 59
32 58 32 49 40
38 41 50 48 35
Samantha
40 35 45 55 38
39 31 56 55 40
55 46 38 36 32
46 31 56 47 57
Samantha
38 40 54 57 45
31 33 39 47 55
32 49 46 33 36
30 51 44 39 41
Ashley
32 39 49 31 38
45 54 41 45 55
41 59 47 35 30
45 43 40 37 53
Jacob
44 48 51 45 60
56 48 31 54 35
48 50 38 30 32
55 41 60 53 57
John
50 46 59 59 42
44 31 35 37 39
60 58 45 60 60
52 35 55 37 37

Result
TABLE
Rab	1	2	3	4	Vkupno
Andrew	211	217	217	250	895
Mia	280	249	223	209	961
Natalie	227	219	223	229	898
John	227	253	221	208	909
Brianna	260	234	211	212	917
Samantha	213	221	207	237	878
Samantha	234	205	196	205	840
Ashley	189	240	212	218	859
Jacob	248	224	198	266	936
John	256	186	283	216	941
MAX NEDELA NA RABOTNIK: Samantha
4
*/

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