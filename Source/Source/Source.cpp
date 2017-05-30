#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
#include <string.h> 
#include <locale.h>
#include <time.h>

struct tree {
	tree *left = NULL;
	tree *right = NULL;
	tree *parent = NULL;
	int count = 0;
	int number;
};
typedef tree *ptree;

void set_parent(ptree child, ptree parent) {
	if (child != NULL)	child->parent = parent;
}

void keep_parent(ptree v) {
	set_parent(v->left, v);
	set_parent(v->right, v);
}

void rotate(ptree parent, ptree child) {
	ptree gparent = parent->parent;
	if (gparent != NULL) 
		if (gparent->left == parent) {
			gparent->left = child;
		}
		else {
			gparent->right = child;
		}

		if (parent->left == child) {
			parent->left = child->right;
			child->right = parent;
		}
		else {
			parent->right = child->left;
			child->left = parent;
		}

		keep_parent(child);
		keep_parent(parent);
		child->parent = gparent;
	
}

ptree splay(ptree v) {
	if (v->parent == NULL)
		return v;
	ptree parent = v->parent;
	ptree gparent = parent->parent;
	if (gparent == NULL) {
		rotate(parent, v);
			return v;
	}
	else {
		// zig-zig
		if ((gparent->left == parent) == (parent->left == v)) {
			rotate(gparent, parent);
			rotate(parent, v);
		}
		else {
			// zig-zag
			rotate(parent, v);
			rotate(gparent, v);
		}
		return splay(v);
	}
}

ptree find(ptree v, int number) {
	if (v == NULL) return NULL;
	if (number == v->number)
		return splay(v);
	if ((number < v->number) && (v->left != NULL))
		return find(v->left, number);
	if ((number > v->number) && (v->right != NULL))
		return find(v->right, number);
	return splay(v);
}

void split(ptree left, ptree right, ptree root, int number) {
	if (root == NULL) {
		left = NULL;
		right = NULL;
	}
	root = find(root, number);
	if (root->number == number) {
		set_parent(root->left, NULL);
		set_parent(root->right, NULL);
		left = root->left;
		right = root->right;
	}
	if (root->number < number) {
		right = root->right;
		root->right = NULL;
		set_parent(right, NULL);
		left = root;
	}
	else {
		left = root->left;
		root->left = NULL;
		set_parent(left, NULL);
		right = root;
	}
}

void insert(ptree root, int number) {
	ptree left, right;
	split(left, right, root, number);
	root = new tree;
	root->number = number;
	root->left = left; 
	root->right = right;
	keep_parent(root);
}

ptree merge(ptree left, ptree right) {
	if (right == NULL)
		return left;
	if (left == NULL)
		return right;
	right = find(right, left->number);
	right->left = left;
	left->parent = right;
	return right;
}

ptree remove(ptree root, int number) {
	root = find(root, number);
	set_parent(root->left, NULL);
	set_parent(root->right, NULL);
	return merge(root->left, root->right);
}

void inc(ptree root, int number)
{
	while (root != NULL)
	{
		if (root->number == number)
		{
			root->count++;
		}
		if (number > root->number)
		{
			root = root->right;
		}
		else
		{
			root = root->left;
		}
	}
}

ptree add(ptree root, int number)
{
	if (root == NULL)
	{
		root = new tree;
		root->number = number;
		root->count = 1;
		root->left = NULL;
		root->right = NULL;
	}
	else if (number > root->number)
	{
		root->right = add(root->right, number);
		keep_parent(root);
	}
	else
	{
		root->left = add(root->left, number);
		keep_parent(root);
	}
	return root;
}

void printTree(tree *root)
{
	if (root != NULL)
	{
		printTree(root->left);
		printf("%d - %d times\n", root->number, root->count);
		printTree(root->right);
	}
}

ptree counts(ptree root, int number) {
	if (root == NULL) {
		return add(root, number);
	}
	while (root != NULL)
	{
		if (root->number == number)
		{
			root->count++;
			return splay(root);
		}
		if (number > root->number)
		{
			root = root->right;
		}
		else
		{
			root = root->left;
		}
	}
}

int ifInTree(ptree root, int number)
{
	while (root != NULL)
	{
		if (root->number == number)
		{
			return 1;
		}
		if (number > root->number)
		{
			root = root->right;
		}
		else
		{
			root = root->left;
		}
	}
	return 0;
}


int main()
{
	tree *tr = NULL;

	int neNado = 0;
	int def = 0;

	char inFile[100];
	printf("Input file name:");
	scanf("%s", &inFile);

	time_t t = clock();

	int i = 0, slkol = 0; //slkol - count of sleshes, which going podryad
	char cArray[10000], c = 'n', lc = 'n', s[10000], cc = 'n', ccc = 'n';
	int len = strlen(cArray);
	int kav1 = 0, kav2 = 0; // Kavichki. 1 - '_', 2 - "_"; 

	FILE *fin = fopen(inFile, "r");

	for (i = 0; i<10000; i++) { s[i] = cArray[i] = '\0'; }

	while (!feof(fin)) {
	xyz:
		c = fgetc(fin);
		if (feof(fin)) { break; }
	eto:
		//Kavichki tipa "_" 
		if (c == '\"') {
			i = 0;
			slkol = 0;
			lc = 'n';
			c = '#';
			while ((c != '\"') || (slkol % 2 != 0)) {
			repa:lc = c;
				c = fgetc(fin);
				if (feof(fin)) { goto tuda; }
				if (((c == '\n') && (lc == '\\') && (slkol % 2 == 1))) { slkol = 0; goto repa; }
				else { if (c == '\n') { goto xyz; } }
				if (c == '\\') {
					if (lc == '\"') { slkol = 1; }
					else { slkol++; }
				}
				else {
					if (c == '\"') {
						if (lc == '\"') {
							if (slkol % 2 == 1) {
								goto xyz;
							}
							else { slkol = 0; }
						}
					}
					else { slkol = 0; }
				}
			}
			goto xyz;
		}
		else {
		uidi:;
			//Kavichki tipa '_' 
			if (c == '\'') {
				i = 0;
				slkol = 0;
				lc = 'n';
				c = '#';
				while ((c != '\'') || (slkol % 2 != 0)) {
				repet:lc = c;
					c = fgetc(fin);
					if (feof(fin)) { goto tuda; }
					if (c == '\n') { goto xyz; }
					if (c == '\\') {
						if (lc == '\'') { slkol = 1; }
						else { slkol++; }
					}
					else {
						if (c == '\'') {
							if (lc == '\'') {
								if (slkol % 2 == 1) {
									goto xyz;
								}
								else { slkol = 0; }
							}
						}
						else { slkol = 0; }
					}
				}
				goto xyz;
			}
			else {
				//. 

				//Comments
				if (c == '/') {
					c = fgetc(fin); if (feof(fin)) { goto tuda; }
					if (c == '/') {
						while (1) {
							lc = c;
							c = fgetc(fin);
							if (feof(fin)) { goto tuda; }
							if (c == '\n') {
								if (lc == '\\') {
									continue;
								}
								else { break; }
							}
						}
						goto xyz;
					}
					else {
						if (c == '*') {
							cc = 'i'; ccc = 'i'; while ((cc != '*') || (ccc != '/')) { cc = ccc; ccc = fgetc(fin); if (feof(fin)) { goto tuda; } } goto xyz;
						}
						else {
							goto eto;
						}
					}
					goto xyz;
				}
				else {
//-------------------------------------------------------------------------------------------------
//Main program code for podschet and poisk chisel
					int minus = 0;
					if(c=='-') {
						c = fgetc(fin);
						if (feof(fin)) goto tuda; 
						if ((c < 48) || (c > 57)) {
							goto eto;
						}
						else minus = 1;
					}
					if ((c > 47) && (c < 58)) {
						int number = 0;
						while ((c > 47) && (c < 58)) {
							number = (number * 10) + c - 48;
							c = fgetc(fin);
							if (feof(fin)) goto tuda;
						}
						if (minus == 1) number = -number;
						//printf("%lld\n", number);
						if (ifInTree(tr, number)) tr = counts(tr, number); else tr = add(tr, number);
						goto eto;
					}
//-------------------------------------------------------------------------------------------------
//End of main program code
				}
			}
		}
		//----------------------Comments 

	}
tuda:
	fclose(fin);

	printf("Time - %d m %d s %d ms\n\n", (clock() - t) / 60000, ((clock() - t) % 60000) / 1000, (clock() - t) % 1000);
	
	printTree(tr);

	return 0;
}