// Link: https://www.hackerrank.com/challenges/insert-a-node-at-a-specific-position-in-a-linked-list/problem?isFullScreen=false

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */

SinglyLinkedListNode* insertNodeAtPosition(SinglyLinkedListNode* llist, int data, int position) {
    
    int i = 0;
    SinglyLinkedListNode *cur = llist, *last = NULL;
    SinglyLinkedListNode *newNode = (SinglyLinkedListNode*) malloc(sizeof(SinglyLinkedListNode));
        
    newNode->data = data;
    newNode->next = NULL;
    
    while(i++ < position && cur != NULL) { 
        last = cur;
        cur = cur->next; 
    } 
    
    if(last == NULL){ 
        newNode->next = llist;
        return newNode;
    } 
    newNode->next = cur;
    last->next = newNode;   
    return llist;
}