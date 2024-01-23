/*
 Да се креира структура наречена Student која ги содржи следните информации: name (низа од знаци), age (цел број), marks (низа од 5 целобројни вредности), и average (реален број).

Напишете програма во која се внесуваат N студенти со горенаведените детали за нив, па потоа се пресметува нивниот просек на оценки, и на излез се печатат деталите за студентот со највисок просек. Aко има повеќе студенти со ист просек се печати последниот студент со таков просек.


Да се направи функција:

void calculate_average(Student *student)
кoja што го враќа просекот на оценките на даден студент

Напомена: Прво од тастатура се чита бројот на студенти. Притоа за секој студент се чита име, години и петте оценки. На излез се печатат името, годините, оценките и просекот на студентот со највисок просек.

For example:

Input
5
Jane 20 6 6 7 7 8
Theo 19 10 10 8 8 8
Oliver 21 7 7 7 7 7
Amelia 22 10 10 10 10 8
Sarah 21 9 10 10 10 9

 Result
Ime: Sarah
Godini: 21
Ocenki: 9 10 10 10 9
Prosek: 9.600000

 */

#include <stdio.h>

#define MAX 100

typedef struct Student{
    char ime[MAX];
    int god;
    int marks[5];
    float average;
}Student;

void calculate_average(Student *student, int n) {
    int i, j;
    float zbir = 0;
    for (i = 0; i < n; i++) {
        zbir=0;
        for (j = 0; j < 5; j++) {
            zbir +=student[i].marks[j];
        }
        student[i].average=zbir/5;
    }

}

int main() {
    Student Student[MAX];
    int i, j, n, index = -1;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%s %d", Student[i].ime, &Student[i].god);
        for (j = 0; j < 5; j++) {
            scanf("%d", &Student[i].marks[j]);
        }
    }

    calculate_average(Student, n);


    float avg = -1;
    for (i = 0; i < n; i++) {
        if(avg<=Student[i].average){
            avg=Student[i].average;
            index=i;
        }
    }
    printf("Ime: %s\n", Student[index].ime);
    printf("Godini: %d\n", Student[index].god);
    printf("Ocenki: ");
    for(int k=0; k<5; k++){
        printf("%d ", Student[index].marks[k]);
    }
    printf("\nProsek: %f\n", Student[index].average);
    return 0;
}

