#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define LEFT 0
#define RIGHT 1

typedef struct tree_t{
	int key;
	int value;
	struct tree_t *left;
	struct tree_t *right;
}tree_t;

typedef struct tree_boot_t
{
	tree_t *boot;
}tree_boot_t;

tree_boot_t *tree_init(void)
{
	tree_boot_t *T;

	T = (tree_boot_t *)malloc(sizeof(tree_boot_t));
	assert(T != NULL);

	T->boot = NULL;

	return T;
}

void tree_print(tree_t *T)
{
	tree_t *p;
	p = T;

	if(p == NULL)
	{
		return;
	}

	printf("%s:%d\n",p->value ? "right" : "left", p->key);
	tree_print(p->left);
	tree_print(p->right);
}

tree_boot_t *tree_insert(tree_boot_t *T, int k)
{
	tree_t *x;
	tree_t *p;
	
	x = T->boot;
	while(x != NULL)
	{
		p = x;
		if(k < x->key)
			x = x->left;
		else
			x = x->right;
	}

	x = (tree_t *)malloc(sizeof(tree_t));

	x->key = k;
	x->left = NULL;
	x->right = NULL;
	
	if(T->boot == NULL)
	{
		T->boot = x;
		return T;
	}

	if(x->key < p->key)
	{
		x->value = LEFT;
		p->left = x;
	}
	else if(x->key > p->key)
	{
		x->value = RIGHT;
		p->right = x;
	}
	else
	{
		printf("key is exits!");
	}

	return T;
}

int main()
{
	tree_boot_t *T;
	T = tree_init();

	T = tree_insert(T, 6);
	T = tree_insert(T, 1);
	T = tree_insert(T, 10);
	T = tree_insert(T, 3);
	T = tree_insert(T, 20);
	T = tree_insert(T, 9);
	T = tree_insert(T, 2);
	T = tree_insert(T, 5);
	T = tree_insert(T, 13);
	T = tree_insert(T, 15);
	T = tree_insert(T, 0);

	tree_print(T->boot);

}
