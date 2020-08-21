#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "stack.h"

typedef enum Suit {
	HEART = 0,
	DIAMOND,
	CLUB,
	SPADE
} Suit;

typedef enum Rank {
	ACE = 0,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	JACK,
	QUEEN,
	KING
} Rank;

struct card {
	Suit suit;
	Rank rank;
};

struct card *create_card(Suit s, Rank r)
{
	struct card *new = malloc(sizeof(*new));
	new->suit = s;
	new->rank = r;

	return new;
}

void *cpy_card(void *c)
{
	struct card *card = (struct card *)c;
	struct card *new = create_card(card->suit, card->rank);

	return new;
}

void print_card(struct card *c)
{
	char suit;
	switch (c->suit) {
	case HEART:
		suit = 'H';
		break;
	case DIAMOND:
		suit = 'D';
		break;
	case CLUB:
		suit = 'C';
		break;
	case SPADE:
		suit = 'S';
		break;
	}

	char rank[] = {0, 0, 0};
	switch (c->rank) {
	case ACE:
		rank[0] = 'A';
		break;
	case TWO:
	case THREE:
	case FOUR:
	case FIVE:
	case SIX:
	case SEVEN:
	case EIGHT:
	case NINE:
		rank[0] = c->rank + 1 + '0';
		break;
	case TEN:
		rank[0] = '1';
		rank[1] = '0';
		break;
	case JACK:
		rank[0] = 'J';
		break;
	case QUEEN:
		rank[0] = 'Q';
		break;
	case KING:
		rank[0] = 'K';
		break;
	}

	printf("|%c-%s|", suit, rank);
}

int main(void)
{
	Stack deck = create_stack(free, cpy_card);

	void *c;
	/* add cards to deck */
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 13; ++j) {
			c = (void *)create_card(i, j);
			if (push_stack(c, deck) != 0)
				return -1;
		}
	}

	Stack cpy = copy_stack(deck);

	const int pop_n = 10;
	struct card *card;
	for (int i = 0; i < pop_n; ++i) {
		card = (struct card *)pop_stack(deck);
		print_card(card);
		free(card);
	}
	printf("\n");

	assert(size_stack(deck) == size_stack(cpy) - pop_n);

	destroy_stack(deck);
	
	for (int i = 0; i < pop_n; ++i) {
		card = (struct card *)pop_stack(cpy);
		print_card(card);
		free(card);
	}
	printf("\n");

	while (size_stack(cpy)) {
		card = (struct card *)pop_stack(cpy);
		free(card);
	}

	destroy_stack(cpy);

	return 0;
}

