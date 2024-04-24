//
// Created by Simon on 24-04-2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct testNode
{
    int value;
    struct Node *next;
};

int push_front( struct testNode **head, int value )
{
    struct testNode *new_node = malloc( sizeof( struct testNode ) );
    int success = new_node != NULL;

    if ( success )
    {
        new_node->value = value;
        new_node->next = *head;

        *head = new_node;
    }

    return success;
}

void testDisplay( const struct testNode *head )
{
    for ( ; head != NULL; head = head->next )
    {
        printf( "%d -> ", head->value );
    }

    puts( "null" );
}

struct ListPair
{
    struct testNode *head1;
    struct testNode *head2;
};


struct ListPair split( struct testNode **head, size_t pos, size_t n )
{
    struct ListPair p = { .head1 = NULL, .head2 = NULL };

    struct testNode **current1 = &p.head1;
    struct testNode **current2 = &p.head2;

    for ( size_t i = 0; *head != NULL && i != pos; i++ )
    {
        *current2 = *head;
        *head = ( *head )->next;
        ( *current2 )->next = NULL;
        current2 = &( *current2 )->next;
    }

    while ( *head != NULL && n-- )
    {
        *current1 = *head;
        *head = ( *head )->next;
        ( *current1 )->next = NULL;
        current1 = &( *current1 )->next;
    }

    while ( *head != NULL )
    {
        *current2 = *head;
        *head = ( *head )->next;
        ( *current2 )->next = NULL;
        current2 = &( *current2 )->next;
    }

    return p;
}