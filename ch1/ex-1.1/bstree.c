#include <stdio.h>
#include <string.h>
#include "util.h"

typedef struct tree *T_tree;
struct tree {
	T_tree left;
	string key;
	void *data;
	T_tree right;
};

//for 'persistent' we get memory leak, expected?
T_tree Tree(T_tree l, string k, T_tree r)
{
	T_tree t = checked_malloc(sizeof(*t));
	t->left=l; t->key=k; t->right=r;

	printf("  %s ", k);
	if (t->left) printf("left->%s ", t->left->key); else printf("left->NULL ");
	if (t->right) printf("right->%s ", t->right->key); else printf("right->NULL ");
	printf("#head: (%p)\n", t);

	return t;
}
T_tree insert(string key, T_tree t)
{
	if (t == NULL)
		return Tree(NULL, key, NULL);
	else if (strcmp(key, t->key) < 0)
		return Tree(insert(key,t->left), t->key, t->right);
	else if (strcmp(key,t->key) > 0)
		return Tree(t->left, t->key, insert(key,t->right));
	else
		return Tree(t->left, key, t->right);
}
bool member(string key, T_tree t)
{
	if (t == NULL)
		return FALSE;
	else if (strcmp(key, t->key) < 0)
		return member(key, t->left);
	else if (strcmp(key, t->key) > 0)
		return member(key, t->right);
	else
		return TRUE;
}

T_tree Tree2(T_tree l, string k, void *binding, T_tree r)
{
	T_tree t = checked_malloc(sizeof(*t));
	t->left=l; t->key=k; t->data=binding, t->right=r;
	return t;
}
T_tree insert2(string key, void *binding, T_tree t)
{
	if (t == NULL)
		return Tree2(NULL, key, binding, NULL);
	else if (strcmp(key, t->key) < 0)
		return Tree2(insert2(key, binding, t->left), t->key, t->data, t->right);
	else if (strcmp(key,t->key) > 0)
		return Tree2(t->left, t->key, t->data, insert2(key, binding, t->right));
	else
		return Tree2(t->left, key, binding, t->right);
}

void * lookup(string key, T_tree t)
{
	if (t == NULL)
		return NULL;
	else if (strcmp(key, t->key) < 0)
		return lookup(key, t->left);
	else if (strcmp(key, t->key) > 0)
		return lookup(key, t->right);
	else
		return t->data;
}

int main(int argc, char *argv[])
{
	T_tree t = NULL;
	for (int i=1; i < argc; i++) {
		printf("insert %s to (%p)\n", argv[i], t);
		t = insert(argv[i], t);
	}

	printf("\n");
	return 0;
}
