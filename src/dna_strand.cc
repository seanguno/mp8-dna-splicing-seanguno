#include "dna_strand.hpp"

#include <stdexcept>



 //if pattern not found, throw an exception
    //if empty pattern || empty to_splice_in -> return
    //if &to_splice_in == this -> return
    //basically longest consec subs from dna forensics
    //keep track of latest one found
    
    //see if the pattern has finished or not
    //need to make sure that if checking for pattern, when reach tail


void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
   
    if (pattern[0] == '\0') return;
    if (to_splice_in.head_ == nullptr) return;
    if (&to_splice_in == this) return;
    int count = 0;
    for (unsigned int i = 0; pattern[i] != '\0'; ++i) {
            count++;
    }
    int loc = FindMatch(pattern, count);
    if (loc == -1) {
        throw std::runtime_error("pattern not found");
    }
    Node* current = head_;
    Node* prev = head_;
    Node* to_delete = head_;
    if (loc == 0) {
        head_ = to_splice_in.head_;
        for (unsigned int i = 0; pattern[i] != '\0'; ++i) {
            current = current->next;
        }
        to_splice_in.tail_->next = current;
    } else {
        for (int i = 0; i < loc; ++i) {
            prev = current;
            current = current->next;
        }
        to_delete = current;
        for (unsigned int i = 0; pattern[i] != '\0'; ++i) {
            current = current->next;
        }
        prev->next = to_splice_in.head_;
        to_splice_in.tail_->next = current;
    }
    to_splice_in.tail_ = nullptr;
    to_splice_in.head_ = nullptr;
    DeleteFromNode(*to_delete, count);
}

    //splice at loc
    //keep track of previous so that once match is found, the previous pointer can point to the new
    //location of the pattern you want to splice in
    //always have access to the next pointer and then just point the inserted pattern to the tail
    //make sure to get reference to next before deleting node so that you can delete the original memory
    //edge cases
    //literally head and tail
    //if head, then there is no previous node, so move around tail pointer that you're inserting
    //if tail, then instead of setting tail value to next, just set to nullptr


int DNAstrand::FindMatch(const char* pattern, int count) {
    Node* current = head_;
    int i = 0;
    int max = 0;
    bool match = false;
    while (current != nullptr) {
        if (current->data == pattern[0]) {
            if (CheckMatch(pattern, *current)) {
                max = i;
                match = true;
                /*
                for (unsigned int j = 0; pattern[j] != '\0'; ++j) {}
                    current = current->next;
                    i++;
                }
                need to implement code to skip over what already gone over
                */
               //increm by count - 2(?) 1(?)
               //increm by count - 1
               //for loop, < count - 1, current = current -> next
               
               i += count - 1;
               for (int j = 0; j < count - 1; j++) {
                current = current -> next;
               }
            }
        }
        current = current->next;
        i++;
    }
    if (!match) return -1;
    return max;
}

bool DNAstrand::CheckMatch(const char* pattern, Node& start) {
    Node* current = &start; 
    for (unsigned int i = 0; pattern[i] != '\0'; ++i) {
        if (current == nullptr) {
            return false;
        }
        if (current->data != pattern[i]) {
            return false;
        }
        current = current->next; 
    }
    return true;
}

//create a walk to function that returns the address of what i need

DNAstrand::~DNAstrand() {
    //std::string test;
    if (head_ == nullptr) {
        return;
    }
    while (head_->next != nullptr) {
        //test = head_->data;
        Node* next = head_->next;
        delete head_;
        head_ = next;
    }
    delete head_;
}

void DNAstrand::DeleteFromNode(Node& start, int count) {
    Node* head = &start;
    //std::string test;
   for (int i = 0; i < count - 1; ++i) {
        //test = head->data;
        Node* next = (head)->next;
        delete head;
        head = next;
    }
    delete head;
}

/*

void DNAstrand::SetTail(char to_add) {
    tail_ = new Node(to_add);
}



DNAstrand::DNAstrand(Node& head)
: head_(&head), tail_(&head) {

}

void DNAstrand::PushBack(char to_add) {
    if (head_ == nullptr) {
        tail_ = new Node(to_add);
        head_ = tail_;
    } else {
        Node* tmp = new Node(to_add);
        tail_->next = tmp;
        tail_ = tmp;
    }
}

std::string DNAstrand::ToString() {
    Node* current = head_;
    std::string to_return;
    while (current != nullptr) {
        to_return += current->data;
        current = current->next;
    }
    return to_return;
}

*/
