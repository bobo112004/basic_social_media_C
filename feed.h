#ifndef FEED_H
#define FEED_H
#include "users.h"

// functia afiseaza reposturile prietenilor unui user
void find_friend(retea *rt, post *p, int user_id);

// functia care gaseste reposturile facute de prietenii unui user
void friends_repost(retea *rt, char *username, int id_post);

// functia care gaseste reposturile unui user
void view_reposts(retea *rt, int user_id, post *repost, post *original_post);

// functia afiseaza profilul unui user (si post/repost)
void view_profile(retea *rt, char *username);

// functia care afiseaza feed-ul unui user
void get_feed(retea *rt, char *username, int feed_size);

// functia care gaseste clica recursiv si prin backtracking
void clica_bron(retea *rt, int *r, int *p, int *x, int r_size,
				int p_size, int x_size, int *final, int *final_size);

// functia care apeleaxa clica_bron, se ocupa de init si afisare
void clica(retea *rt, char *name);

/**
 * Function that handles the calling of every command from task 3
 *
 * Please add any necessary parameters to the functions
*/

void handle_input_feed(retea *rt, char *input);

#endif // FEED_H
