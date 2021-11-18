// Link: https://www.hackerrank.com/challenges/detect-whether-a-linked-list-contains-a-cycle/problem

bool has_cycle(SinglyLinkedListNode* head) {
    set<void*> visited;
    SinglyLinkedListNode* current = head;
    
    while(current != NULL){ 
        if(visited.count(current) != 0){
            return true;
        }
        visited.insert(current);
        current = current->next;
    }
    return false;
}