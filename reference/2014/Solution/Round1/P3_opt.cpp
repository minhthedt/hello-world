#include <stdio.h>
#include <memory.h>

struct trie_node ;

struct list {
	list () {}
	list (char x, trie_node* link, list* next) : next(next), x(x), link(link) {}

	~list () {
		delete link;
		if (next != NULL)
			delete next;
	}

	list* next;

	char x;
	trie_node* link;
};

struct trie_node {
	trie_node () : link (NULL), cnt_all (0), cnt_part (0) {}

	~trie_node () {
		if (link != NULL)
			delete link;
	}

	list* link;
	short cnt_all, cnt_part;
};

int n;
char str[1000][101];

trie_node* root;

int ans[1000];

void input ()
{
	scanf ("%d", &n);

	for (int i=0; i<n; i++)
		scanf ("%s", str[i]);
}

trie_node* find_child (list* l, char x)
{
	while (l != NULL) {
		if (l->x == x)
			return l->link;
		l = l->next;
	}

	return NULL;
}

void make_trie ()
{
	for (int i=0; i<n; i++) {
		for (int j=0; str[i][j]; j++) {
			// make trie nodes for string str[i][j~]
			trie_node* node = root;
			for (int k=j; str[i][k]; k++) {
				trie_node* child;

				if ((child = find_child (node->link, str[i][k])) == NULL) {
					node->link = new list (str[i][k], new trie_node, node->link);
					node = node->link->link;
				}
				else
					node = child;

				node->cnt_all ++;
			}
		}
	}
}

void find_answer ()
{
	memset (ans, 0, sizeof (int) * n);

	for (int i=0; i<n; i++) {
		// reset cnt variable of the nodes on the pathway of all substrings of str[i]
		for (int j=0; str[i][j]; j++) {
			trie_node* node = root;
			for (int k=j; str[i][k]; k++) {
				node = find_child (node->link, str[i][k]);
				node->cnt_part = 0;
			}
		}

		// find number of paths along all substrings of str[i]
		for (int j=0; str[i][j]; j++) {
			trie_node* node = root;
			for (int k=j; str[i][k]; k++) {
				node = find_child (node->link, str[i][k]);
				node->cnt_part++;
			}
		}
		
		// find "key substring" for string str[i] beginning with index j
		for (int j=0; str[i][j]; j++) {
			trie_node* node = root;
			for (int k=j; str[i][k]; k++) {
				node = find_child (node->link, str[i][k]);
				if (node->cnt_all == node->cnt_part) {
					if (ans[i]==0 || ans[i] > k-j+1)
						ans[i] = k-j+1;
					break;
				}
			}
		}
	}
}

void output ()
{
	for (int i=0; i<n; i++)
		printf ("%d\n", ans[i]);
}

int main()
{
	input ();
	root = new trie_node;
	make_trie ();
	find_answer ();
	delete root;
	output ();

	return 0;
}
