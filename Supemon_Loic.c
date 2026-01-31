#include <stdio.h>
#include <stdlib.h>


int main() {
    printf("Hello and welcolme to Supemon game ! \n");
    char name;
    printf("First of all, what's your name ?");
    scanf("%s", &name);
    printf("Hello %s!\n", &name);
    printf("+--------------------------------+\n"
                 "|To begin, choose your starter : |\n"
                 "|    1 - Bulbizarre              |\n"
                 "|    2 - Salameche               |\n"
                 "|    3 - Carapuce                |\n"
                 "+--------------------------------+\n"
                 "1, 2 or 3 : ");
    int choice;
    scanf("%d", &choice);
    if (choice == 1) {
        printf("Your starter is Bulbizarre !\n");
    }
    if (choice == 2) {
        printf("Your starter is Salameche !\n");
    }
    if (choice == 3) {
        printf("Your starter is Carapuce !\n");
    }
    printf("+------------------------------+\n"
                 "|Where do you want to go ?     |\n"
                 "|    1 - Into the Wild         |\n"
                 "|    2 - In the shop           |\n"
                 "|    3 - In the Supemon center |\n"
                 "|    4 - Leave the game        |\n"
                 "+------------------------------+\n"
                 "1, 2, 3  or 4: ");
    int choice2;
    scanf("%d", &choice2);
    if (choice2 == 1) {
        printf("You go into the Wild!\n");
        printf("A savage Supemon appears !\n");
        printf("+----------------------------+\n"
                     "|Where do you do ?           |\n"
                     "|    1 - Attack              |\n"
                     "|    2 - Change Supemon      |\n"
                     "|    3 - Use an object       |\n"
                     "|    4 - Leave the fight     |\n"
                     "|    5 - Capture the Supemon |\n"
                     "+----------------------------+\n"
                     "1, 2, 3, 4  or 5: ");
        int battle;
        scanf("%d", &battle);

    }
    if (choice2 == 2) {
        printf("You go in the Shop!\n");
    }
    if (choice2 == 3) {
        printf("You go in the Supemon center!\n");
    }
    if (choice2 == 4) {
        printf("You leave the game!\n");
    }
}