#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure des compétences
struct Competence {
    char name[20];
    int damage;         // Dégâts de la compétence
    char stat_effect[10]; // Quelle stat est modifiée
    int stat_change;    // Valeur du changement
};

// Structure du Supémon
struct Supemon {
    char name[50];
    int level;
    int xp;

    // PV (Actuels et Max)
    int hp;
    int max_hp;

    // Attaque (Courante et Base)
    int attack;
    int base_attack;

    // Défense (Courante et Base)
    int defense;
    int base_defense;

    // Evasion (Courante et Base)
    int evasion;
    int base_evasion;

    // Précision (Courante et Base)
    int accuracy;
    int base_accuracy;

    int speed;

    // Liste des attaques
    struct Competence moves[2];
};

// 2.3 - Structure du Joueur
struct Player {
    char name[50];
    struct Supemon team[6]; // Une équipe de vrais Supémons 
    int nb_supemons;
    int selected_supemon;   // Index du Supémon actif (0 à 5)
    int supcoins;           // Argent

    // Inventaire (Liste d'objets simplifiée en compteurs pour l'instant)
    int potions;
    int super_potions;
    int rare_candies;
};

int main() {

    struct Player p;
    p.nb_supemons = 0;
    p.supcoins = 1000; // On lui donne un peu d'argent de base
    p.potions = 0;
    p.super_potions = 0;
    p.rare_candies = 0;
    p.selected_supemon = 0; // Le premier par défaut

    printf("Hello and welcolme to Supemon game ! \n");
    printf("First of all, what's your name ? ");
    scanf("%s", p.name);
    printf("Hello %s!\n", p.name);

    printf("+--------------------------------+\n"
           "|To begin, choose your starter : |\n"
           "|    1 - Supmander               |\n"
           "|    2 - Supasaur                |\n"
           "|    3 - Supirtle                |\n"
           "+--------------------------------+\n"
           "1, 2 or 3 : ");

    int choice;
    scanf("%d", &choice);

    // Initialisation du Starter selon les stats données en 2.4
    if (choice == 1) {
        printf("Your starter is Supmander !\n");
        struct Supemon s = { "Supmander",
                             1, 0,
                             10, 10,        // HP, MaxHP
                             1, 1,          // Atk, BaseAtk
                             1, 1,          // Def, BaseDef
                             1, 1,          // Eva, BaseEva
                             2, 2,          // Acc, BaseAcc
                             1 };           // Speed

        // Définition des attaques de Supmander
        struct Competence m1 = {"Scratch", 3, "NONE", 0};
        struct Competence m2 = {"Grawl", 0, "ATK", 1};
        s.moves[0] = m1;
        s.moves[1] = m2;

        p.team[0] = s; // On ajoute le Supémon complet à l'équipe
    }

    if (choice == 2) {
        printf("Your starter is Supasaur !\n");
        struct Supemon s = { "Supasaur", 1, 0,
                             9, 9,          // HP, MaxHP
                             1, 1,          // Atk, BaseAtk
                             1, 1,          // Def, BaseDef
                             3, 3,          // Eva, BaseEva
                             2, 2,          // Acc, BaseAcc
                             2 };           // Speed

        // Définition des attaques de Supasaur
        struct Competence m1 = {"Pound", 2, "NONE", 0};
        struct Competence m2 = {"Foliage", 0, "EVA", 1};
        s.moves[0] = m1;
        s.moves[1] = m2;

        p.team[0] = s;
    }

    if (choice == 3) {
        printf("Your starter is Supirtle !\n");
        struct Supemon s = { "Supirtle", 1, 0,
                             11, 11,        // HP, MaxHP
                             1, 1,          // Atk, BaseAtk
                             2, 2,          // Def, BaseDef
                             2, 2,          // Eva, BaseEva
                             1, 1,          // Acc, BaseAcc
                             2 };           // Speed

        // Définition des attaques de Supirtle
        struct Competence m1 = {"Pound", 2, "NONE", 0};
        struct Competence m2 = {"Shell", 0, "DEF", 1};
        s.moves[0] = m1;
        s.moves[1] = m2;

        p.team[0] = s;
    }

    p.nb_supemons = 1;

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
        printf("Your coins: %d\n", p.supcoins);
        // Ici on pourra lister les objets
    }

    if (choice2 == 3) {
        printf("You go in the Supemon center!\n");
        // Soin simple : remettre pv_actuel = pv_max
        p.team[0].hp = p.team[0].max_hp;
        printf("%s is fully healed!\n", p.team[0].name);
    }

    if (choice2 == 4) {
        printf("You leave the game!\n");
    }

    return 0;
}

