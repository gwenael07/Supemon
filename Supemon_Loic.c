#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Structure des compétences
struct Competence {
    char name[20];
    int damage;         // Dégâts de la compétence
    int stat_effect; // Quelle stat est modifiée
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

// Struture du joueur
struct Player {
    char name[50];
    struct Supemon team[6]; 
    int nb_supemons;
    int selected_supemon;  
    int supcoins;           // Argent

    
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
                {"Scratch", 3, 0, 0},
                {"Growl",   0, 1,  1}
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
                {"Pound",   2, 0, 0},
                {"Foliage", 0, 3,  1}
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
                {"Pound", 2, 0, 0},
                {"Shell", 0, 2,  1}
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
                {"Peck",  2, 0, 0},
                {"Focus", 0, 4,  1}
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
                {"Smash", 2, 0, 0},
                {"Guard", 0, 2,  1}
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
                {"Pulse",  2, 0, 0},
                {"Focus",  0, 4,  1}
    }
};

struct Supemon* create_random_enemy(struct Supemon *supemon_list, int count) {
    int index = rand() % count;

    struct Supemon *enemy = malloc(sizeof(struct Supemon));
    if (!enemy) return NULL;

    *enemy = supemon_list[index];

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

int random_int(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}


int tentative_capture(struct Supemon target) {
    float hp_perdu = (float)(target.max_hp - target.hp);
    float probability = (hp_perdu / target.max_hp) - 0.5f;


    if (probability < 0) probability = 0;

    printf("[DEBUG] Capture Chance: %.1f%%\n", probability * 100);

    float jet = (float)rand() / (float)RAND_MAX;
    if (jet <= probability) return 1; // Capturé
    return 0; // Échec
}


int boost_stat(int val) {
    float new_val = val * 1.30f;
    int integer_part = (int)new_val;
    float decimal_part = new_val - integer_part;

    if (decimal_part == 0.0f) {
        return integer_part;
    }

    if ((rand() % 2) == 0) {
        return integer_part;
    } else {
        return integer_part + 1;
    }
}

void check_level_up(struct Supemon *s) {
    int xp_add = 500 + (s->level - 1) * 1000;

    while (s->xp >= xp_add) {
        s->xp -= xp_add;
        s->level++;

        printf("\n*** LEVEL UP! %s is now level %d! ***\n", s->name, s->level);

        // Augmentation des statistiques de 30%
        s->max_hp = boost_stat(s->max_hp);
        s->hp = s->max_hp;

        s->attack = boost_stat(s->attack);
        s->base_attack = s->attack;

        s->defense = boost_stat(s->defense);
        s->base_defense = s->defense;

        s->evasion = boost_stat(s->evasion);
        s->base_evasion = s->evasion;

        s->accuracy = boost_stat(s->accuracy);
        s->base_accuracy = s->accuracy;

        s->speed = boost_stat(s->speed);

        xp_add = 500 + (s->level - 1) * 1000;

        printf("Stats increased by 30%%! HP is now %d.\n", s->max_hp);
    }
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
    p.selected_supemon = 0; 

    printf("Hello and welcolme to Supemon game ! \n");
    printf("First of all, what's your name ? ");
    while (scanf("%s", p.name) != 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
        printf(">> Invalid input! Please enter a valid name: ");
    }
    printf("Hello %s!\n", p.name);

    printf("+--------------------------------+\n"
           "|To begin, choose your starter : |\n"
           "|    1 - Supmander               |\n"
           "|    2 - Supasaur                |\n"
           "|    3 - Supirtle                |\n"
           "+--------------------------------+\n"
           "1, 2 or 3 : ");

    int choice;
    int starter_choisi = 0;
    while (starter_choisi == 0) {
        if (scanf("%d", &choice) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { }

            printf(">> Invalid input! Please enter a valid number: ");
        }
        else if (choice < 1 || choice > 3) {
            printf(">> Please choose between 1 and 3.\n");
        }
        else {
            starter_choisi = 1; 
        }
    }

    
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
        struct Competence m1 = {"Scratch", 3, 0, 0};
        struct Competence m2 = {"Grawl", 0, 1, 1};
        s.moves[0] = m1;
        s.moves[1] = m2;

        p.team[0] = s; 
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
        struct Competence m1 = {"Pound", 2, 0, 0};
        struct Competence m2 = {"Foliage", 0, 3, 1};
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
        struct Competence m1 = {"Pound", 2, 0, 0};
        struct Competence m2 = {"Shell", 0, 2, 1};
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
        while (scanf("%d", &choice2) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { }

            printf(">> Invalid input! Please enter a valid number: ");
        }
        if (choice2 < 1 || choice2 > 4) {
            printf(">> Please choose between 1 and 4.\n");
            continue; 
        }

        // #####################################
        // 1 -        INTO THE WILD
        // #####################################
        if (choice2 == 1) {

            int type = rand() % 6;
            struct Supemon enemy = all_supemons[type];

            char wild_name[50];
            sprintf(wild_name, "Savage %s", enemy.name);
            strcpy(enemy.name, wild_name);

            int combat = 1;
            int i = p.selected_supemon;

            printf("You go into the Wild!\n");
            printf("A %s appears!\n", enemy.name);

            while (combat == 1) {
                int i = p.selected_supemon;


                printf("  %-20s            %-20s\n", "YOUR SUPEMON", "WILD ENEMY");
                printf("  %-20s            %-20s\n", p.team[i].name, enemy.name);
                printf("+--------------------------+    +--------------------------+\n");
                printf("| HP:  %3d / %-3d          |    | HP:  %3d / %-3d          |\n", p.team[i].hp, p.team[i].max_hp, enemy.hp, enemy.max_hp);
                printf("| ATK: %2d   DEF: %2d       |    | ATK: %2d   DEF: %2d       |\n", p.team[i].attack, p.team[i].defense, enemy.attack, enemy.defense);
                printf("| ACC: %2d   EVA: %2d       |    | ACC: %2d   EVA: %2d       |\n", p.team[i].accuracy, p.team[i].evasion, enemy.accuracy, enemy.evasion);
                printf("| SPD: %2d                  |    | SPD: %2d                  |\n", p.team[i].speed, enemy.speed);
                printf("+--------------------------+    +--------------------------+\n");


                printf("\n+----------------------------+\n"
                       "| What do you do?            |\n"
                       "|    1 - Attack              |\n"
                       "|    2 - Change Supemon      |\n"
                       "|    3 - Use an object       |\n"
                       "|    4 - Run away            |\n"
                       "|    5 - Capture             |\n"
                       "+----------------------------+\n"
                       "1, 2, 3, 4 or 5: ");

                int battle_choice;
                while (scanf("%d", &battle_choice) != 1) {
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF) { }
                    printf(">> Invalid input! Please enter a number: ");
                }
                if (battle_choice < 1 || battle_choice > 5) {
                    printf(">> Please choose between 1 and 5.\n");
                    continue; 
                }

                if (battle_choice == 1) {

                    printf("+-----------------------------------+\n"
                           "| What attack do you want to launch?|\n"
                           "|      1 - %-25s|\n"
                           "|      2 - %-25s|\n"
                           "+-----------------------------------+\n"
                           "1 or 2 : ", p.team[i].moves[0].name, p.team[i].moves[1].name);

                    int move_idx;
                    while (scanf("%d", &move_idx) != 1) {
                        int c;
                        while ((c = getchar()) != '\n' && c != EOF) { }
                        printf(">> Invalid input! Please enter a valid number: ");
                    }
                    if (move_idx < 1 || move_idx > 2) {
                        printf(">> Please choose between 1 and 2.\n");
                        continue; 
                    }
                    move_idx--;

                    printf("+-----------------------------------+\n"
                           "| You use %-26s|\n", p.team[i].moves[move_idx].name);
                    if (tentative_toucher(p.team[i], enemy)) {
                        int degats = p.team[i].moves[move_idx].damage;


                        if (degats > 0) {

                            int total_dmg = degats + (p.team[i].attack - enemy.defense);
                            if (total_dmg < 1) total_dmg = 1; 

                            enemy.hp -= total_dmg;
                            printf("| BANG! %s lose %d HP.          |\n", enemy.name, total_dmg);
                        } else {

                            switch (p.team[i].moves[move_idx].stat_effect) {
                                case 1:
                                    p.team[i].attack+=p.team[i].moves[move_idx].stat_change;
                                    printf("Attack increase by 1.\n");
                                    break;
                                case 2:
                                    p.team[i].defense+=p.team[i].moves[move_idx].stat_change;
                                    printf("Defense increase by 1.\n");
                                    break;
                                case 3:
                                    p.team[i].evasion+=p.team[i].moves[move_idx].stat_change;
                                    printf("Evasion increase by 1.\n");
                                    break;
                                case 4:
                                    p.team[i].accuracy+=p.team[i].moves[move_idx].stat_change;
                                    printf("Accuracy increase by 1.\n");
                                    break;
                            }
                        }
                    } else {
                        printf("| Missed! The enemy dodged it.      |\n");
                    }
                    printf("+-----------------------------------+\n");

                    
                    if (enemy.hp <= 0) {
                        printf("\nVictory! %s is defeated!\n", enemy.name);
                        int add_supcoins = random_int(100,500);
                        p.supcoins += add_supcoins;
                        int add_xp = random_int(100,500)*enemy.level;
                        p.team[i].xp+= add_xp;
                        printf("You earned %d Supcoins and your supemon earned %d xp.\n",add_supcoins, add_xp);
                        check_level_up(&p.team[i]);
                        combat = 0;
                        break;
                    }

                    //TOUR DE L'ENNEMI
                    int enemy_move = rand() % 2;

                    if (tentative_toucher(enemy, p.team[i])) {
                        int e_degats = enemy.moves[enemy_move].damage;
                        if (e_degats > 0) {
                            int total_e_dmg = e_degats + (enemy.attack - p.team[i].defense);
                            if (total_e_dmg < 1) total_e_dmg = 1;

                            p.team[i].hp -= total_e_dmg;
                            printf("Ouch! %s loses %d HP!\n", p.team[i].name, total_e_dmg);
                        } else {
                            printf("%s uses %s, but nothing happens.\n", enemy.name, enemy.moves[enemy_move].name);
                        }
                    } else {
                        printf("%s missed the attack!\n", enemy.name);
                    }
                    
                    if (p.team[i].hp <= 0) {
                        p.team[i].hp = 0;
                        printf("\n%s fainted! You must go to the Center.\n", p.team[i].name);
                        combat = 0;
                    }
                }
                else if (battle_choice == 2) {
                    printf("+-------------------------------------+\n"
                                 "| Which Supemon do you want to send ? |\n");
                    for (int k = 0; k < p.nb_supemons; k++) {
                        printf("| %d - %s (HP: %d/%d) %s |\n",
                               k + 1,
                               p.team[k].name,
                               p.team[k].hp,
                               p.team[k].max_hp,
                               (k == p.selected_supemon) ? "[ACTIVE]" : "");
                    }
                    printf("| %d - Back                            |\n"
                                 "+-------------------------------------+\n", p.nb_supemons + 1);

                    int new_choice;
                    while (scanf("%d", &new_choice) != 1) {
                        int c; while ((c = getchar()) != '\n' && c != EOF) {}
                        printf(">> Enter a number: ");
                    }
                    if (new_choice >= 1 && new_choice <= p.nb_supemons) {
                        int target_index = new_choice - 1;
                        if (target_index == p.selected_supemon) {
                            printf(">> %s is already fighting!\n", p.team[target_index].name);
                        }
                        else if (p.team[target_index].hp <= 0) {
                            printf(">> %s is fainted and cannot fight!\n", p.team[target_index].name);
                        }
                        else {
                            p.selected_supemon = target_index;
                            printf(">> Come back %s! Go %s!\n", p.team[i].name, p.team[target_index].name);
                        }
                    }
                }
                else if (battle_choice == 3) {
                    printf("+-----------------------------------+\n"
                                 "| Your items :                      |\n"
                                 "|     1 - Potion -> +5HP(x%d)        |\n"
                                 "|     2 - Super Potion -> +10HP(x%d) |\n"
                                 "|     3 - Rare Candy -> +1level(x%d) |\n"
                                 "|     4 - Back                      |\n"
                                 "+-----------------------------------+\n"
                                 "1, 2, 3 or 4 :",p.potions,p.super_potions,p.rare_candies);


                    int item_choice;
                    while (scanf("%d", &item_choice) != 1) {
                        int c; while ((c = getchar()) != '\n' && c != EOF) {}
                        printf(">> Enter a number: ");
                    }
                    if (item_choice < 1 || item_choice > 4) {
                        printf(">> Please choose between 1 and 4.\n");
                        continue;
                    }
                    if (item_choice == 1) {
                        if (p.potions > 0) {
                            p.team[i].hp += 5;
                            if (p.team[i].hp > p.team[i].max_hp) {
                                p.team[i].hp = p.team[i].max_hp;
                            }
                            p.potions--;
                            printf("You used 1 Potion ! %s feels better !\n", p.team[i].name);
                        } else {
                            printf("You don't have a potion !\n");
                        }
                    }
                    else if (item_choice == 2) {
                        if (p.super_potions > 0) {
                            p.team[i].hp += 10;
                            if (p.team[i].hp > p.team[i].max_hp) {
                                p.team[i].hp = p.team[i].max_hp;
                            }
                            p.super_potions--;
                            printf("You used 1 Super Potion ! %s feels better !\n",p.team[i].name);
                        }else {
                            printf("You don't have a super potion !\n");
                        }
                    }
                    else if (item_choice == 3) {
                        if (p.rare_candies > 0) {
                            p.team[i].level += 1;
                            p.rare_candies--;
                            printf("You used 1 Rare Candies ! %s increase !\n", p.team[i].name);
                        }else {
                            printf("You don't have a rare candies !\n");
                        }
                    }
                    else if (item_choice == 4) {

                    }
                }
                else if (battle_choice == 4) {
                    int i = p.selected_supemon;
                    float run_chance = (float)p.team[i].speed / (p.team[i].speed + enemy.speed);
                    float jet = (float)rand() / (float)RAND_MAX;
                    printf("You try to flee...\n");
                    if (jet <= run_chance) {
                        printf("Got away safely!\n");
                        combat = 0; 
                    } else {
                        printf("Can't escape! The enemy blocked your way!\n");
                    }
                    
                    //TOUR DE L'ENNEMI
                    int enemy_move = rand() % 2;

                    if (tentative_toucher(enemy, p.team[i])) {
                        int e_degats = enemy.moves[enemy_move].damage;
                        if (e_degats > 0) {
                            int total_e_dmg = e_degats + (enemy.attack - p.team[i].defense);
                            if (total_e_dmg < 1) total_e_dmg = 1;

                            p.team[i].hp -= total_e_dmg;
                            printf("Ouch! %s loses %d HP!\n", p.team[i].name, total_e_dmg);
                        } else {
                            printf("%s uses %s, but nothing happens.\n", enemy.name, enemy.moves[enemy_move].name);
                        }
                    } else {
                        printf("%s missed the attack!\n", enemy.name);
                    }
                    
                    if (p.team[i].hp <= 0) {
                        p.team[i].hp = 0;
                        printf("\n%s fainted! You must go to the Center.\n", p.team[i].name);
                        combat = 0;
                    }
                }
                else if (battle_choice == 5) {
                    printf("You throw a Supball!\n");
                    if (p.nb_supemons >= 6) {
                        printf("Team full! Cannot capture.\n");
                    } else {
                        if (tentative_capture(enemy)) {
                            printf("Gotcha! %s was caught!\n", enemy.name);
                            strcpy(enemy.name, all_supemons[type].name);
                            p.team[p.nb_supemons] = enemy;
                            p.nb_supemons++;
                            combat = 0; 
                        } else {
                            printf("You're capture failed!\n");
                        }
                    }
                    
                    //TOUR DE L'ENNEMI
                    int enemy_move = rand() % 2;

                    if (tentative_toucher(enemy, p.team[i])) {
                        int e_degats = enemy.moves[enemy_move].damage;
                        if (e_degats > 0) {
                            int total_e_dmg = e_degats + (enemy.attack - p.team[i].defense);
                            if (total_e_dmg < 1) total_e_dmg = 1;

                            p.team[i].hp -= total_e_dmg;
                            printf("Ouch! %s loses %d HP!\n", p.team[i].name, total_e_dmg);
                        } else {
                            printf("%s uses %s, but nothing happens.\n", enemy.name, enemy.moves[enemy_move].name);
                        }
                    } else {
                        printf("%s missed the attack!\n", enemy.name);
                    }
                    
                    if (p.team[i].hp <= 0) {
                        p.team[i].hp = 0;
                        printf("\n%s fainted! You must go to the Center.\n", p.team[i].name);
                        combat = 0;
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
                printf("+----------------------------------------------+\n"
                             "| Welcolme in the Supshop ! What do you want ? |\n"
                             "|     1 - Buy items                            |\n"
                             "|     2 - Sell items                           |\n"
                             "|     3 - Leave shop                           |\n"
                             "+----------------------------------------------+\n"
                             "1, 2 or 3 :");
                int shop_mode;
                while (scanf("%d", &shop_mode) != 1) {
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF) { }
                    printf(">> Invalid input! Please enter a valid number: ");
                }
                if (shop_mode < 1 || shop_mode > 3) {
                    printf(">> Please choose between 1 and 3.\n");
                    continue;
                }

                if (shop_mode == 1) {
                    // MODE ACHAT
                    printf("+---------------------------------------------------+\n"
                                 "| What do you want to buy ?                         |\n"
                                 "| You have %d Supcoins.                             |\n"
                                 "|     1 - Potion (Heals 5 HP) : 100 Supcoins        |\n"
                                 "|     2 - Super Potion (Heals 10 HP) : 300 Supcoins |\n"
                                 "|     3 - Rare Candy (Level up) : 700 Supcoins      |\n"
                                 "|     4 - Back                                      |\n"
                                 "+---------------------------------------------------+\n"
                                 "1, 2, 3 or 4 :",p.supcoins);
                    int buy_choice;
                    while (scanf("%d", &buy_choice) != 1) {
                        int c;
                        while ((c = getchar()) != '\n' && c != EOF) { }
                        printf(">> Invalid input! Please enter valid a number: ");
                    }
                    if (buy_choice < 1 || buy_choice > 4) {
                        printf(">> Please choose between 1 and 4.\n");
                        continue; 
                    }

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
                    
                    } else {
                        printf("Not enough money or invalid choice!\n");
                    }
                }
                else if (shop_mode == 2) {

                    printf("+--------------------------------------------------------+\n"
                                 "| What do you want to sell ?                             |\n"
                                 "|     1 - Potion (Get 50 Supcoins) | You have: %d        |\n"
                                 "|     2 - Super Potion (Get 150 Supcoins) | You have: %d |\n"
                                 "|     3 - Rare Candy (Get 350 Supcoins) | You have: %d   |\n"
                                 "|     4 - Back                                           |\n"
                                 "+--------------------------------------------------------+\n"
                                 "1, 2, 3 or 4 :",p.potions,p.super_potions,p.rare_candies);
                    int sell_choice;
                    while (scanf("%d", &sell_choice) != 1) {
                        int c;
                        while ((c = getchar()) != '\n' && c != EOF) { }
                        printf(">> Invalid input! Please enter a valid number: ");
                    }
                    if (sell_choice < 1 || sell_choice > 4) {
                        printf(">> Please choose between 1 and 4.\n");
                        continue; 
                    }

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
            printf("+------------------------------------+\n"
                         "| Here are your Supemons:            |\n");
            for (int i = 0; i < p.nb_supemons; i++) {
                printf("| %d - %s (HP: %d/%d) |\n", i + 1, p.team[i].name, p.team[i].hp, p.team[i].max_hp);
            }

            printf("| Do you want to heal them for free? |\n"
                         "|     1 - Yes                        |\n"
                         "|     2 - No                         |\n"
                         "+------------------------------------+\n"
                         "1 or 2:");
            int heal_choice;
            while (scanf("%d", &heal_choice) != 1) {
                int c;
                while ((c = getchar()) != '\n' && c != EOF) { }
                printf(">> Invalid input! Please enter a valid number: ");
            }
            if (heal_choice < 1 || heal_choice > 2) {
                printf(">> Please choose between 1 and 2.\n");
                continue;
            }

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


