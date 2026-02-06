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


struct Supemon supemon1 = {
    "Supmander", 1, 0,
    10, 10,
    2, 2,
    1, 1,
    1, 1,
    2, 2,
    2,
    {
                {"Scratch", 3, "NONE", 0},
                {"Growl",   0, "ATK",  1}
    }
};

struct Supemon supemon2 = {
    "Supasaur", 1, 0,
    9, 9,
    1, 1,
    1, 1,
    3, 3,
    2, 2,
    2,
    {
                {"Pound",   2, "NONE", 0},
                {"Foliage", 0, "EVA",  1}
    }
};

struct Supemon supemon3 = {
    "Supirtle", 1, 0,
    11, 11,
    1, 1,
    2, 2,
    2, 2,
    1, 1,
    2,
    {
                {"Pound", 2, "NONE", 0},
                {"Shell", 0, "DEF",  1}
    }
};

struct Supemon supemon4 = {
    "Supfox", 1, 0,
    8, 8,
    2, 2,
    1, 1,
    2, 2,
    3, 3,
    3,
    {
                {"Peck",  2, "NONE", 0},
                {"Focus", 0, "ACC",  1}
    }
};

struct Supemon supemon5 = {
    "Suprock", 1, 0,
    12, 12,
    1, 1,
    3, 3,
    1, 1,
    1, 1,
    1,
    {
                {"Smash", 2, "NONE", 0},
                {"Guard", 0, "DEF",  1}
    }
};

struct Supemon supemon6 = {
    "Supmind", 1, 0,
    9, 9,
    1, 1,
    1, 1,
    2, 2,
    3, 3,
    2,
    {
                {"Pulse",  2, "NONE", 0},
                {"Focus",  0, "ACC",  1}
    }
};

struct Supemon* create_random_enemy(struct Supemon *supemon_list, int count) {
    int index = rand() % count;

    struct Supemon *enemy = malloc(sizeof(struct Supemon));
    if (!enemy) return NULL;

    *enemy = supemon_list[index]; // Copie complÃ¨te (moves inclus)

    return enemy;
}


int tentative_toucher(struct Supemon attaquant, struct Supemon cible) {

    float proba = (float)attaquant.accuracy / (attaquant.accuracy + cible.evasion) + 0.1f;

    float jet = (float)rand() / (float)RAND_MAX;

    if (jet <= proba) {
        return 1;
    }
    return 0;
}




int main() {
    struct Supemon *all_supemons = malloc(6*  sizeof(struct Supemon));

    all_supemons[0] = supemon1;
    all_supemons[1] = supemon2;
    all_supemons[2] = supemon3;
    all_supemons[3] = supemon4;
    all_supemons[4] = supemon5;
    all_supemons[5] = supemon6;


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

    int running = 1; // Variable pour garder le jeu allumé
    while (running) {
        printf("\n+------------------------------+\n"
               "|Where do you want to go ?     |\n"
               "|    1 - Into the Wild         |\n"
               "|    2 - In the shop           |\n"
               "|    3 - In the Supemon center |\n"
               "|    4 - Leave the game        |\n"
               "+------------------------------+\n"
               "1, 2, 3 or 4: ");

        int choice2;
        scanf("%d", &choice2);

        if (choice2 == 1) {
            struct Supemon enemy;
            int type = rand()%3;
            if (type == 0) {
                strcpy(enemy.name, "Savage Supmander");
                enemy.hp = 10; enemy.max_hp = 10;
                enemy.attack = 1; enemy.base_attack = 1;
                enemy.defense = 1; enemy.base_defense = 1;
                enemy.evasion = 1; enemy.base_evasion = 1;
                enemy.accuracy = 2; enemy.base_accuracy = 2;
                enemy.speed = 1;
                }
            if (type == 1) {
                strcpy(enemy.name,"Savage Supasaur");
                enemy.hp =9; enemy.max_hp = 9;
                enemy.attack=1; enemy.base_attack =1;
                enemy.defense = 1; enemy.base_defense = 1;
                enemy.evasion = 3; enemy.base_evasion = 3;
                enemy.accuracy = 2; enemy.base_accuracy = 2;
                enemy.speed = 2;
            }
            if (type == 2) {
                strcpy(enemy.name,"Savage Supirtle");
                enemy.hp =11; enemy.max_hp = 11;
                enemy.attack=1; enemy.base_attack =1;
                enemy.defense = 2; enemy.base_defense = 2;
                enemy.evasion = 2; enemy.base_evasion = 2;
                enemy.accuracy = 1; enemy.base_accuracy = 1;
                enemy.speed = 2;
            }
            int combat = 1;
            int turn_p=1;
            printf("You go into the Wild!\n");
            printf("A %s appears !\n", enemy.name);
            while (combat == 1) {
                while (turn_p==1) {
                    printf("+----------------------------+\n"
                                 "|Where do you do ?           |\n"
                                 "|    1 - Attack              |\n"
                                 "|    2 - Change Supemon      |\n"
                                 "|    3 - Use an object       |\n"
                                 "|    4 - Run away            |\n"
                                 "|    5 - Capture the Supemon |\n"
                                 "+----------------------------+\n"
                                 "1, 2, 3, 4  or 5: ");
                    int battle;
                    scanf("%d", &battle);
                    int i = p.selected_supemon;
                    if (battle==1) {
                        printf("+-----------------------------------+\n"
                                     "|What attack do you want to launch? |\n"
                                     "|     1 - %-26s|\n""|     2 - %-26s|\n"
                                     "+-----------------------------------+\n"
                                     "1 or 2 :", p.team[i].moves[0].name, p.team[i].moves[1].name);
                        int attack;
                        scanf("%d",&attack);
                        if (attack == 1) {
                            printf("+-----------------------------------+\n"
                                         "|You make %-26s|\n",p.team[i].moves[0].name);
                            if (tentative_toucher(p.team[i], enemy)) {
                                int degats = p.team[i].moves[0].damage;
                                enemy.hp -= degats;
                                printf("BANG! %s lose %d HP.\n", enemy.name, degats);
                                if (enemy.hp < 0) enemy.hp = 0;
                                printf("Enemy HP remaining: %d/%d\n", enemy.hp, enemy.max_hp);
                                turn_p = 0;
                            } else {
                                printf("| Missed! The enemy dodged it.      |\n");
                            }
                            printf("+-----------------------------------+\n");
                        }
                        if (attack == 2) {
                            printf("+-----------------------------------+\n"
                                         "|You make %-26s|\n",p.team[i].moves[1].name);
                        }
                    }
                    if (battle==2) {
                        printf("+---------------------------------------+\n"
                                     "|Which Supemon would you like to trade? |\n"
                                     "|     1 - %-30s|\n"
                                     "+---------------------------------------+\n",p.team[i].name);
                    }
                    if (battle==3) {
                        printf("+---------------------------------------+\n");
                    }
                    if (battle==4) {
                        printf("+----------------------------------------+\n"
                                     "|Are you sure you want to quit the fight?|\n"
                                     "      1 - Yes !                          |\n"
                                     "      2 - No !                           |\n"
                                     "+----------------------------------------+\n"
                                     "1 or 2 :");
                        int leave;
                        scanf("%d",&leave);
                        if (leave == 1) {

                        }
                        if (leave == 2) {
                            return 0;
                        }
                    }
                    if (battle==5) {
                        printf("+---------------------------------------+\n");
                    }
                }
            }

        }
        //#####################################
        // 2 -        THE SHOP
        //#####################################
        if (choice2 == 2) {
            int shop_running = 1;
            while (shop_running) {
                printf("\n=== WELCOME TO THE SHOP ===\n");
                printf("Your balance: %d Supcoins\n", p.supcoins);
                printf("1 - Buy items\n");
                printf("2 - Sell items\n");
                printf("3 - Leave shop\n");
                printf("Choice: ");
                int shop_mode;
                scanf("%d", &shop_mode);

                if (shop_mode == 1) {
                    // MODE ACHAT
                    printf("\n--- BUYING MODE ---\n");
                    printf("1 - Potion (Heals 5 HP) : 100 Supcoins\n");
                    printf("2 - Super Potion (Heals 10 HP) : 300 Supcoins\n");
                    printf("3 - Rare Candy (Level up) : 700 Supcoins\n");
                    printf("4 - Back\n");
                    printf("Choice: ");
                    int buy_choice;
                    scanf("%d", &buy_choice);

                    if (buy_choice == 1 && p.supcoins >= 100) {
                        p.potions++;
                        p.supcoins -= 100;
                        printf("Bought 1 Potion!\n");
                    } else if (buy_choice == 2 && p.supcoins >= 300) {
                        p.super_potions++;
                        p.supcoins -= 300;
                        printf("Bought 1 Super Potion!\n");
                    } else if (buy_choice == 3 && p.supcoins >= 700) {
                        p.rare_candies++;
                        p.supcoins -= 700;
                        printf("Bought 1 Rare Candy!\n");
                    } else if (buy_choice == 4) {
                        // Retour au menu shop
                    } else {
                        printf("Not enough money or invalid choice!\n");
                    }
                }
                else if (shop_mode == 2) {
                    // MODE VENTE (Prix d'achat / 2)
                    printf("\n--- SELLING MODE ---\n");
                    printf("1 - Sell Potion (Get 50 Supcoins) | You have: %d\n", p.potions);
                    printf("2 - Sell Super Potion (Get 150 Supcoins) | You have: %d\n", p.super_potions);
                    printf("3 - Sell Rare Candy (Get 350 Supcoins) | You have: %d\n", p.rare_candies);
                    printf("4 - Back\n");
                    printf("Choice: ");
                    int sell_choice;
                    scanf("%d", &sell_choice);

                    if (sell_choice == 1 && p.potions > 0) {
                        p.potions--;
                        p.supcoins += 50;
                        printf("Sold 1 Potion.\n");
                    } else if (sell_choice == 2 && p.super_potions > 0) {
                        p.super_potions--;
                        p.supcoins += 150;
                        printf("Sold 1 Super Potion.\n");
                    } else if (sell_choice == 3 && p.rare_candies > 0) {
                        p.rare_candies--;
                        p.supcoins += 350;
                        printf("Sold 1 Rare Candy.\n");
                    } else if (sell_choice == 4) {
                        // Retour
                    } else {
                        printf("Nothing to sell or invalid choice!\n");
                    }
                }
                else if (shop_mode == 3) {
                    shop_running = 0;
                }
            }
        }
        //#####################################
        // 3 -    SUPEMON CENTER
        //#####################################
        if (choice2 == 3) {
            printf("\n=== WELCOME TO THE SUPEMON CENTER ===\n");
            printf("Here are your Supemons:\n");

            // On affiche tous les Supémons du joueur
            for (int i = 0; i < p.nb_supemons; i++) {
                printf("%d - %s (HP: %d/%d)\n", i + 1, p.team[i].name, p.team[i].hp, p.team[i].max_hp);
            }

            printf("\nDo you want to heal them for free? (1: Yes / 2: No): ");
            int heal_choice;
            scanf("%d", &heal_choice);

            if (heal_choice == 1) {
                for (int i = 0; i < p.nb_supemons; i++) {
                    p.team[i].hp = p.team[i].max_hp;
                }
                printf("All your Supemons are full HP! Good luck!\n");
            } else {
                printf("See you soon!\n");
            }

        }
        //#####################################
        // 4 -     LEAVE THE GAME
        //#####################################
        if (choice2 == 4) {
            printf("Goodbye %s!\n", p.name);
            running = 0;
        }
    }

    return 0;
}
