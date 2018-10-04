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

#define L(p) (p) = (p)->left
#define R(p) (p) = (p)->right



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
			L(p);
			continue;
		}
		else if(k > p->key)
		{
			R(p);
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
			L(x);
		}
		else if(k > x->key)
		{
			p = x;
			R(x);
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
						R(n);	
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

tree_t *tree_traverse(tree_boot_t *T, tree_t *x)
{
	tree_t *p;
	tree_t *m;
	m = T->boot;
	
	while(m != NULL)
	{
		p = m;
		if(x->key < m->key)
			L(m);
		else
			R(m);
	}

	return p;
}

tree_boot_t *tree_insert(tree_boot_t *T, tree_t *x)
{
	tree_t *p;

	p = tree_traverse(T, x);

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

tree_boot_t *create_new_in(tree_boot_t *T, int k)
{	
	tree_t *x;

	x = (tree_t *)malloc(sizeof(tree_t));
	if(x == NULL)
	{
		printf("malloc error");
		return T;
	}

	x->key = k;
	x->left = NULL;
	x->right = NULL;
	
	T = tree_insert(T, x);

	return T;
}

int main()
{
	tree_boot_t *T;

	T = tree_init();

	T = create_new_in(T, 20);
	T = create_new_in(T, 10);
	T = create_new_in(T, 30);
	T = create_new_in(T, 5);
	T = create_new_in(T, 15);
	T = create_new_in(T, 3);
	T = create_new_in(T, 4);
	T = create_new_in(T, 12);
	T = create_new_in(T, 18);
	T = create_new_in(T, 17);
	T = create_new_in(T, 19);
	T = create_new_in(T, 25);
	T = create_new_in(T, 40);
	T = create_new_in(T, 45);
	T = create_new_in(T, 50);
	T = create_new_in(T, 23);
	T = create_new_in(T, 14);
	T = create_new_in(T, 11);

	tree_print(T->boot);
	printf("===================\n");

	tree_search(T->boot, 5);
	
	printf("===================\n");
	T = tree_delete(T, 15);
	
	tree_print(T->boot);
	return 0;
}
