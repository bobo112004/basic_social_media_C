#include <errno.h>
#include "users.h"

#ifndef FRIENDS_H
#define FRIENDS_H

/**
 * Function that handles the calling of every command from task 1
 *
 * Please add any necessary parameters to the functions
*/

// functia care seteaza doi useri ca prieteni
void add_friend(retea *rt, char *friend1, char *friend2);

// functia elimina prietenia dintre doi useri
void remove_friend(retea *rt, char *friend1, char *friend2);

// functia care gaseste cea mai mica distanta dintre doi prieteni
void get_distance(retea *rt, char *friend1, char *friend2);

// functia care da sugestii pentru un user
void get_suggestions(retea *rt, char *user);

// functia care aifseaza prietenii comuni dintre doi useri
void get_common_friends(retea *rt, char *friend1, char *friend2);

// functie care calculeaza nr de prieteni pt un user
int get_nr_of_friends(retea *rt, char *user);

// functie care afiseaza numarul de prieteni pt un user
void show_nr_of_friends(retea *rt, char *user);

// functia care gaseste cel mai popular user dintre un user si prietenii lui
void get_popular(retea *rt, char *user);

void handle_input_friends(retea *rt, char *input);

#endif // FRIENDS_H
