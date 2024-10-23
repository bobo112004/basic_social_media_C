#ifndef POSTS_H
#define POSTS_H

#include "users.h"
#include "friends.h"

// functia creeaza o postare (in array-ul de postari)
void create_post(retea * rt, char *user, char *title);

// functia returneaza un repost cu un anume id, incepand din postul aferent
post *get_parent(post *root, int id);

// functia creeaza un repost (il adauga drept copil in structura arborescenta)
void create_repost(retea *rt, char *name, char *id_post, char *id_repost);

// functia printeaza toate reposturile recursiv incepand dintr-un repost
void print_reposts(post *repost);

// functia obtine toate reposturile, incepand dintr-un post/repost
void get_reposts(retea *rt, int id_p, int id_rp);

// actualizeaza like-ul (adauga/sterge) la o postare/repost
void like(retea *rt, char *user, int id_p, int id_rp);

// functia obtine nr de like-uri de la o postare/repost
void get_likes(retea *rt, int id_p, int id_rp);

// functia verifica cine are cele mai multe like-uri recursiv
void get_max_likes(int *curr_max, int *id_max, post *curr_repost);

// verifica daca o postare e sau nu ratio'd de alte reposturi
void ratio(retea *rt, int id_post);

// least-common-ancestor, afiseaza parintele comun a doua reposturi
void get_common_parent(retea *rt, int id_p, int idx1, int idx2);

// sterge un repost/post din structura aferenta acesteia
void delete(retea *rt, int id_p, int id_r);

/**
 * Function that handles the calling of every command from task 2
 *
 * Please add any necessary parameters to the functions
*/

void handle_input_posts(retea *rt, char *input);

#endif // POSTS_H
