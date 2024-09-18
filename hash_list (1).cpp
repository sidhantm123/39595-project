#include "hash_list.h"
#include <iostream>
hash_list::hash_list() : size(0), head(NULL) {}

/**-----------------------------------------------------------------------------------
 * START Part 1
 *------------------------------------------------------------------------------------*/

void hash_list::insert(int key, float value) {
    node* target = head;

    // Search list for any matching key
    while (target != NULL) {
        //std::cout << target->key << " , " << target->value << std::endl;
        if (target->key == key) {
            // Updating the key if there is a match
            target->value = value; 
            return;
        }
        target = target->next;
    }

    //If the key doesn't exist, insert new node
    node* newNode = new node;
    newNode->key = key;
    newNode->value = value;
    newNode->next = head;
    head = newNode;
    size++;
}

std::optional<float> hash_list::get_value(int key) const {
    // Setting the index to the start of the list
    node* current = head;

    // increment to the end of the list
    while (current != NULL) {
        // If the current indexed key is the correct value, then return
        if (current->key == key) {
            return current->value;
        }
        // Else increment to the next node
        current = current->next;
    }
    // Optional return if the value isn't found
    return std::nullopt; 
}

bool hash_list::remove(int key) { 
    // Checking if first node is the key match
    if (head != nullptr && head->key == key) {
        node* temp = head;
        head = head->next;
        delete temp;
        size--;
        return true;
    }

    // Going through list to find node to remove
    node* current = head;
    while (current != NULL && current->next != NULL) {
        if (current->next->key == key) {
            node* temp = current->next;
            current->next = current->next->next;
            delete temp;
            size--;
            return true;
        }
        current = current->next;
    }

    // Key wasn't found
    return false; 
}

size_t hash_list::get_size() const { 
    return size; 
}

hash_list::~hash_list() {
    node* current = head;
    node* nextn = NULL;
    while (current != NULL){
        nextn = current->next; 
        delete current;
        current = nextn;
    }
}

/**-----------------------------------------------------------------------------------
 * END Part 1
 *------------------------------------------------------------------------------------*/


/**-----------------------------------------------------------------------------------
 * START Part 2
 *------------------------------------------------------------------------------------*/

hash_list::hash_list(const hash_list &other) : size(other.size), head(nullptr) {
    if (other.head == nullptr) {
        return;  // If the other list is empty, nothing to copy
    }

    // Create a deep copy of the other list
    node* current_other = other.head;
    node* last_new = nullptr;

    while (current_other != nullptr) {
        node* new_node = new node;
        new_node->key = current_other->key;
        new_node->value = current_other->value;
        new_node->next = nullptr;

        if (last_new == nullptr) {
            head = new_node;  // Set the head for the new list
        } else {
            last_new->next = new_node;  // Link to the new node
        }
        last_new = new_node;
        current_other = current_other->next;
    }
}

hash_list &hash_list::operator=(const hash_list &other) {
    if (this == &other) {
        return *this;  // Self-assignment, no need to do anything
    }

    // Clean up the current list
    this->~hash_list();

    // Now copy the other list
    size = other.size;
    head = nullptr;

    if (other.head == nullptr) {
        return *this;  // If the other list is empty, nothing to copy
    }

    node* current_other = other.head;
    node* last_new = nullptr;

    while (current_other != nullptr) {
        node* new_node = new node;
        new_node->key = current_other->key;
        new_node->value = current_other->value;
        new_node->next = nullptr;

        if (last_new == nullptr) {
            head = new_node;  // Set the head for the new list
        } else {
            last_new->next = new_node;  // Link to the new node
        }
        last_new = new_node;
        current_other = current_other->next;
    }

    return *this;
}

void hash_list::reset_iter() {
    iter_ptr = head;  // Reset the iterator to the start of the list (head)
}

void hash_list::increment_iter() {
    if (iter_ptr != nullptr) {
        iter_ptr = iter_ptr->next;  // Move the iterator to the next node
    }
}

std::optional<std::pair<const int *, float *>> hash_list::get_iter_value() {
    if (iter_ptr == nullptr) {
        return std::nullopt;  // If the iterator is NULL, return empty optional
    }

    return std::make_optional(std::make_pair(&(iter_ptr->key), &(iter_ptr->value)));
}

bool hash_list::iter_at_end() {
    return iter_ptr == nullptr;  // Return true if the iterator is at the end (NULL)
}

/**-----------------------------------------------------------------------------------
 * END Part 2
 *------------------------------------------------------------------------------------*/
