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

void tree_search(tree_t *T, int k)
{
	tree_t *p;
	p = T;

	if(p == NULL)
	{
		printf("tree is null!\n");
		return;	
	}
	while(p != NULL)
	{
		if(k == p->key)
		{
			printf("%d\n", p->value);
			return;
		}
		else if(k < p->key)
		{
			p = p->left;
			continue;
		}
		else if(k > p->key)
		{
			p = p->right;
			continue;
		}
	}
	printf("don't have the key:%d\n", k);
	return;
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

tree_boot_t *tree_delete(tree_boot_t *T, int k)
{
	tree_t *x;
	tree_t *p;
	tree_t *n;

	x = T->boot;

	if(x == NULL)
	{
		return T;
	}

	while(x != NULL)
	{
		if(k < x->key)
		{
			p = x;
			x = x->left;
		}
		else if(k > x->key)
		{
			p = x;
			x = x->right;
		}
		else
		{

			if(x->left != NULL && x->right !=NULL)
			{
				tree_t *v;
				n = x->left;
			
				if(n->right != NULL)
				{
					while(n->right != NULL)
					{
						v = n;
						n = n->right;	
					}

					v->right = NULL;
					n->left = x->left;
				}

				n->right = x->right;
				
				if(x == T->boot)
					T->boot = n;
				else if(p->left == x)
				{
					p->left = n;
					n->value = 0;
				}
				else
				{
					p->right = n;
					n->value = 1;
				}
			}
			else if(x->left != NULL && x->right == NULL)
			{
				if(x == T->boot)
					T->boot = x->left;
				else
					p->left = x->left;
			}
			else if(x->right != NULL && x->left == NULL)
			{
				if(x == T->boot)
					T->boot = x->right;
				else
					p->right = x->right;
			}
			else
			{
				if(x != T->boot)
				{
					if(x == p->right)
						p->right = NULL;
					else
						p->left = NULL;
				}
				else
					T->boot = NULL;
				 
			}
			break;
		}
	}
	free(x);
	return T;
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

	T = tree_insert(T, 20);
	T = tree_insert(T, 10);
	T = tree_insert(T, 30);
	T = tree_insert(T, 5);
	T = tree_insert(T, 15);
	T = tree_insert(T, 3);
	T = tree_insert(T, 4);
	T = tree_insert(T, 12);
	T = tree_insert(T, 18);
	T = tree_insert(T, 17);
	T = tree_insert(T, 19);
	T = tree_insert(T, 25);
	T = tree_insert(T, 40);
	T = tree_insert(T, 45);
	T = tree_insert(T, 50);
	T = tree_insert(T, 23);
	T = tree_insert(T, 14);
	T = tree_insert(T, 11);

	tree_print(T->boot);
//	tree_search(T->boot, 5);
//	tree_search(T->boot, 8);
	
	printf("===================\n");
	T = tree_delete(T, 15);
	tree_print(T->boot);
}
