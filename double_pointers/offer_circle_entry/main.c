#include <stdio.h>
#include <stdlib.h>

struct list_node {
	int value;
	struct list_node *next;
};

struct list_node *list_contain_circle(struct list_node *head)
{
	struct list_node *fast = head;
	struct list_node *slow = head;

	/* fast move 2 step each time
	 * slow move 1 step each time
	 */
	for (;;) {
		/* fast pointer will goto NULL, no circle */
		if ((fast->next == NULL) || (fast->next->next == NULL)) {
			return NULL;
		}
		fast = fast->next->next;
		slow = slow->next;
		/* fast pointer equal to slow, circle
		 * put check after fast and slow update,
		 * as fast and slow are both initialized to head.
		 */
		if (fast == slow) {
			return fast;
		}
	}
}

int list_circle_length(struct list_node *circle_node)
{
	int circle_len = 0;
	struct list_node *curr = circle_node->next;

	while (curr != circle_node) {
		circle_len++;
		curr = curr->next;
	}

	return circle_len + 1;
}

struct list_node *list_circle_entry(struct list_node *head)
{
	struct list_node *before = head;
	struct list_node *after = head;
	struct list_node *node_in_circle = list_contain_circle(head);
	int circle_len = 0;
	int step = 0;

	if (!node_in_circle) {
		return NULL;
	}
	circle_len = list_circle_length(node_in_circle);

	/* before pointer move circle_len step */
	for (step = 0; step < circle_len; step++) {
		before = before->next;
	}

	/* move together */
	while (before != after) {
		before = before->next;
		after = after->next;
	}

	return before;
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
	/* set circle */
	p->next = head->next->next;

	p = list_circle_entry(head);
	if (p) {
		printf("%d\n", p->value);
	} else {
		printf("no circle\n");
	}

	/* you should free the memory allocated for list */
	return 0;
}
