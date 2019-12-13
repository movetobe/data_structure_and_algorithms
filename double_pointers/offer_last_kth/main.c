#include <stdio.h>
#include <stdlib.h>

struct list_node {
	int value;
	struct list_node *next;
};

struct list_node *find_last_kth_node(struct list_node *head, int k)
{
	int step = 0;
	struct list_node *before = head;
	struct list_node *after = head;

	/* before pointer move k step */
	for (step = 0; step < k; step++) {
		if (!before) {
			break;
		}
		before = before->next;
	}

	/* list length < k */
	if ((!before) && (step < k)) {
		return NULL;
	}

	/* traverse until before is NULL */
	while (before) {
		before = before->next;
		after = after->next;
	}

	return after;
}

int main(void)
{
	struct list_node *head = NULL;
	struct list_node *p = NULL;
	struct list_node *new_node = NULL;
	int i = 0;
	int k = 0;
	int list_len = 0;

	scanf("%d", &list_len);
	for (i = 0; i < list_len; i++) {
		new_node = calloc(1, sizeof(struct list_node));
		scanf("%d", &new_node->value);
		new_node->next = NULL;
		if (!p) {
			head = new_node;
			p = head;
			continue;
		}
		p->next = new_node;
		p = p->next;
	}

	scanf("%d", &k);
	p = find_last_kth_node(head, k);
	if (p) {
		printf("%d\n", p->value);
	} else {
		printf("list too short\n");
	}

	while (head) {
		p = head;
		head = head->next;
		free(p);
	}

	return 0;
}
