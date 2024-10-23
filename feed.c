#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "feed.h"
#include "users.h"

void find_friend(retea *rt, post *p, int user_id)
{
	if (rt->db_matrix[p->user_id][user_id])
		printf("%s\n", get_user_name(p->user_id));

	if (p->events->n_children == 0)
		return;

	// cautam recursiv printre copii reposturile facute de prieteni
	for (int i = 0; i < p->events->n_children; i++)
		find_friend(rt, p->events->children[i], user_id);
}

void friends_repost(retea *rt, char *username, int id_post)
{
	int user_id = get_user_id(username);
	int idx = 0;
	while (rt->post_arr->arr[idx]->id != id_post && idx < rt->post_arr->size)
		idx++;

	post *original_post = rt->post_arr->arr[idx];

	// din postarea originala apelam find_friend pt toti copiii
	for (int i = 0; i < original_post->events->n_children; i++)
		find_friend(rt, original_post->events->children[i], user_id);
}

void view_reposts(retea *rt, int user_id, post *repost, post *original_post)
{
	// verificam daca autorul repostului este cel cautat
	if (repost->user_id == user_id)
		printf("Reposted: \"%s\"\n", original_post->title);

	if (repost->events->n_children == 0)
		return;

	// apelam recursiv functia care afiseaza reposturile incepand cu copiii
	// postarii originale
	for (int i = 0; i < repost->events->n_children; i++)
		view_reposts(rt, user_id, repost->events->children[i], original_post);
}

void view_profile(retea *rt, char *username)
{
	int user_id = get_user_id(username);

	// cautam postarile facute de user
	for (int i = 0; i < rt->post_arr->size; i++) {
		if (rt->post_arr->arr[i]->user_id == user_id)
			printf("Posted: \"%s\"\n", rt->post_arr->arr[i]->title);
	}

	// apelam view_reposts si cautam recursiv repostarile facute de acesta
	for (int i = 0; i < rt->post_arr->size; i++) {
		post *current = rt->post_arr->arr[i];
		for (int j = 0; j < current->events->n_children; j++)
			view_reposts(rt, user_id, current->events->children[j], current);
	}
}

void get_feed(retea *rt, char *username, int feed_size)
{
	int user_id = get_user_id(username);

	int cnt = feed_size;

	// cautam prin postari cele facute de user
	for (int i = rt->post_arr->size - 1; i >= 0 && cnt; i--) {
		int curr_user = rt->post_arr->arr[i]->user_id;
		if (rt->db_matrix[curr_user][user_id] || curr_user == user_id) {
			cnt--;
			printf("%s: \"%s\"\n", get_user_name(curr_user),
				   rt->post_arr->arr[i]->title);
		}
	}
}

void clica_bron(retea *rt, int *r, int *p, int *x, int r_size,
				int p_size, int x_size, int *final, int *final_size)
{
	// daca am epuizat P si X, am gasit o clica si verificam daca este maximala
	if (p_size == 0 && x_size == 0) {
		if (r_size > *final_size) {
			*final_size = r_size;
			for (int i = 0; i < r_size; i++)
				final[i] = r[i];
		}
		return;
	}

	for (int i = 0; i < p_size; i++) {
		int v = p[i];
		int *newr = calloc(MAX_PEOPLE, sizeof(int));
		int *newp = calloc(MAX_PEOPLE, sizeof(int));
		int *newx = calloc(MAX_PEOPLE, sizeof(int));

		// initializare newr - nodurile curente
		for (int j = 0; j < r_size; j++)
			newr[j] = r[j];

		newr[r_size] = v;
		// initializare newp - nodurile posibile
		int newp_size = 0;
		for (int j = 0; j < p_size; j++) {
			if (rt->db_matrix[v][p[j]])
				newp[newp_size++] = p[j];
		}

		// initializare newx - nodurile de evitat
		int newx_size = 0;
		for (int j = 0; j < x_size; j++) {
			if (rt->db_matrix[v][x[j]])
				newx[newx_size++] = x[j];
		}

		// apelam recursiv cu noii vectori
		clica_bron(rt, newr, newp, newx, r_size + 1, newp_size, newx_size,
				   final, final_size);

		// adaugam v in P
		for (int j = 0; j < p_size; j++) {
			if (p[j] == v) {
				for (int k = j; k < p_size - 1; k++)
					p[k] = p[k + 1];
				break;
			}
		}
		p_size--;

		// adaugam v in X
		x[x_size++] = v;
		free(newr);
		free(newp);
		free(newx);
	}
}

void clica(retea *rt, char *name)
{
	int idx = get_user_id(name);

	// initializam vectorii R, P, X
	int *r = calloc(MAX_PEOPLE, sizeof(int));
	int *p = calloc(MAX_PEOPLE, sizeof(int));
	int *x = calloc(MAX_PEOPLE, sizeof(int));
	int *final = calloc(MAX_PEOPLE, sizeof(int));
	int x_size = 0, r_size = 1, p_size = 0, final_size = 0, aux;

	// R va contine nodul care trebuie musai sa apara
	r[0] = idx;

	// in X punem vecinii
	for (int i = 0; i < MAX_PEOPLE; i++) {
		if (rt->db_matrix[idx][i])
			p[p_size++] = i;
	}
	printf("The closest friend group of %s is:\n", name);
	clica_bron(rt, r, p, x, r_size, p_size, x_size, final, &final_size);

	// ordonam vectorul final (clica) si afisam
	for (int i = 0; i < final_size - 1; i++) {
		for (int j = i + 1; j < final_size; j++) {
			if (final[i] > final[j]) {
				aux = final[i];
				final[i] = final[j];
				final[j] = aux;
			}
		}
	}
	for (int i = 0; i < final_size; i++) {
		char *name = get_user_name(final[i]);
		printf("%s\n", name);
	}
	free(final);
	free(r);
	free(p);
	free(x);
}

void handle_input_feed(retea *rt, char *input)
{
	char *commands = strdup(input);
	char *cmd = strtok(commands, "\n ");

	if (!cmd)
		return;

	if (!strcmp(cmd, "feed")) {
		char *par1 = strtok(NULL, "\n ");
		char *par2 = strtok(NULL, "\n ");
		int feed_size = atoi(par2);
		get_feed(rt, par1, feed_size);
	}

	else if (!strcmp(cmd, "view-profile")) {
		char *par1 = strtok(NULL, "\n ");
		view_profile(rt, par1);
	}

	else if (!strcmp(cmd, "friends-repost")) {
		char *par1 = strtok(NULL, "\n ");
		char *par2 = strtok(NULL, "\n ");
		int id = atoi(par2);
		friends_repost(rt, par1, id);
	}

	else if (!strcmp(cmd, "common-group")) {
		char *par1 = strtok(NULL, "\n ");
		clica(rt, par1);
	}
	free(commands);
}
