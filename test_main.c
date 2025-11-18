/* main.c just for simple tests card.h / card.c */
#include <stdio.h>
#include "Card.h"

int main(void)
{
    /* create some cards */
    Card c1 = { .suit = HEART,  .rank = RANK_ACE };
    Card c2 = { .suit = HEART,  .rank = RANK_KING };
    Card c3 = { .suit = SPADE,  .rank = RANK_ACE };
    Card c4 = { .suit = CLUB,   .rank = RANK_TWO };
    Card c_null = { .suit = 0, .rank = 0 };

    char buf[64];

    /* print using both wrappers */
    printf("Using printCard: ");
    printCard(&c1);
    printf("\n");

    printf("Using Card_print: ");
    Card_print(&c2);
    printf("\n");

    /* toString */
    Card_toString(&c3, buf, sizeof(buf));
    printf("Card_toString(c3) => %s\n", buf);

    /* matches: same suit */
    printf("Card_matches(c1, c2) (same suit) => %d (expect 1)\n", Card_matches(&c1, &c2));

    /* matches: same rank */
    printf("Card_matches(c1, c3) (same rank Ace) => %d (expect 1)\n", Card_matches(&c1, &c3));

    /* equal */
    printf("Card_equal(c1, c3) (same rank but diff suit) => %d (expect 0)\n", Card_equal(&c1, &c3));
    printf("Card_equal(c1, c1) => %d (expect 1)\n", Card_equal(&c1, &c1));

    /* compare: rank primary, suit secondary */
    printf("Card_compare(c2 (K?), c3 (A?)) => %d (expect -1 since K < A)\n", Card_compare(&c2, &c3));
    printf("Card_compare(c1 (A?), c3 (A?)) => %d (depends on suit order HEART vs SPADE)\n", Card_compare(&c1, &c3));

    /* test behavior with invalid/edge card */
    Card_toString(&c_null, buf, sizeof(buf));
    printf("Card_toString(invalid) => \"%s\"\n", buf);

    /* null-safety checks these expect functions handle NULL gracefully */
    printf("Card_matches(NULL, &c1) => %d (expect 0)\n", Card_matches(NULL, &c1));
    printf("Card_equal(NULL, NULL) => %d (expect 0 or 1 depending on semantics; your impl returns 0)\n", Card_equal(NULL, NULL));
    printf("Card_compare(NULL, NULL) => %d (expect 0)\n", Card_compare(NULL, NULL));

    return 0;
}
