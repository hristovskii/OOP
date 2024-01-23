/*
 Во програмскиот јазик C да се креира структура VideoGame за опишување на една видео игра во рамките на една стриминг платформа. Структурата за видео игра треба да содржи: (5 поени)

Име (низа од 100 знаци)

Рејтинг (реален број)

Цена (реален број)

Да се креира структура StreamingPlatform, што содржи: (5 поени)

Име на стриминг платформата (низа од 50 знаци)

Низа од достапни видео игри (низа од максимум 30 елементи од структурата Game)

Број на елементи во низата (цел број)

Да се креира глобална функција print за печатење на информациите за дадена стриминг платформа во следниот формат: (10 поени)

[Ime na streaming platformata]

[ImeIgra1] [Cena1]

[ImeIgra2] [Cena2]

[ImeIgra3] [Cena3]

...

Да се креира функција showBestValueService, што прима низа од променливи од типот StreamingPlatform, и променлива rating. Оваа функција треба да го испечати името на стриминг платформата која нуди најевтина видео игра со рејтинг поголем од пратената променлива rating. Ако има повеќе такви стриминг платформи со иста минимална цена на видео игра со поголем рејтинг од  бараниот, се печати последната платформа.(15 поени)

Да се дополни функцијата main (5 поени).
 */

#include <stdio.h>
#include <string.h>

typedef struct {
    char name[100];
    float rating;
    float price;
} VideoGame;

typedef struct {
    char name[50];
    VideoGame games[30];
    int num_games;
} StreamingPlatform;

void print(StreamingPlatform platform) {
    printf("%s\n", platform.name);
    for (int i = 0; i < platform.num_games; i++) {
        printf("%s %.2f\n", platform.games[i].name, platform.games[i].price);
    }
}

void showBestValueService(StreamingPlatform platforms[], int num_platforms, float rating) {
    float min_price = -1.0;
    int best_platform_index = -1;

    for (int i = 0; i < num_platforms; i++) {
        for (int j = 0; j < platforms[i].num_games; j++) {
            if (platforms[i].games[j].rating > rating) {
                if (min_price < 0 || platforms[i].games[j].price <= min_price) {
                    min_price = platforms[i].games[j].price;
                    best_platform_index = i;
                }
            }
        }
    }

    if (best_platform_index >= 0) {
        printf("Best value platform is: %s\n", platforms[best_platform_index].name);
    } else {
        printf("No suitable platform found.\n");
    }
}

int main() {
    int num_platforms;
    scanf("%d", &num_platforms);
    StreamingPlatform platforms[num_platforms];

    for (int i = 0; i < num_platforms; i++) {
        scanf("%s %d", platforms[i].name, &platforms[i].num_games);
        for (int j = 0; j < platforms[i].num_games; j++) {
            scanf("%s %f %f", platforms[i].games[j].name, &platforms[i].games[j].rating, &platforms[i].games[j].price);
        }
    }

    float rating;
    scanf("%f", &rating);

    for (int i = 0; i < num_platforms; i++) {
        print(platforms[i]);
    }

    showBestValueService(platforms, num_platforms, rating);

    return 0;
}
