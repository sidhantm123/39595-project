#include "hash_map.h"
#include "hash_list.h"

void hash_map::insert(int key, float value) {
    // Compute the index for the bucket using a hash function
    size_t index = key % _capacity; // Assuming a simple modulo hash function

    // Insert the key/value pair into the appropriate hash_list
    _head[index].insert(key, value);

    // Optionally, increase the map's size only if a new key was inserted
    // The hash_list::insert function already handles updating existing keys.
}

std::optional<float> hash_map::get_value(int key) const {
    // Compute the index for the bucket using a hash function
    size_t index = key % _capacity; // Assuming a simple modulo hash function

    // Use the hash_list's get_value method to find the value associated with the key
    return _head[index].get_value(key);
}

bool hash_map::remove(int key) {
    // Compute the index for the bucket using a hash function
    size_t index = key % _capacity; // Assuming a simple modulo hash function

    // Use the hash_list's remove method to remove the key
    return _head[index].remove(key);
}

size_t hash_map::get_size() const {
    size_t total_size = 0;

    // Aggregate sizes from all hash_list objects
    for (size_t i = 0; i < _capacity; ++i) {
        total_size += _head[i].get_size();
    }

    return total_size;
}

size_t hash_map::get_capacity() const {
    return _capacity;
}

void hash_map::get_all_keys(int *keys) {
    size_t index = 0;

    // Iterate over each bucket in the hash_map
    for (size_t i = 0; i < _capacity; ++i) {
        hash_list& list = _head[i];

        // Iterate over each node in the current hash_list
        node* current = list.head;
        while (current != nullptr) {
            keys[index++] = current->key;
            current = current->next;
        }
    }
}

void hash_map::get_bucket_sizes(size_t *buckets) {
    // Iterate over each bucket in the hash_map
    for (size_t i = 0; i < _capacity; ++i) {
        // Use the hash_list's get_size method to get the number of elements in the current bucket
        buckets[i] = _head[i].get_size();
    }
}

hash_map::~hash_map() {
    // Iterate over each bucket in the hash_map
    for (size_t i = 0; i < _capacity; ++i) {
        // Delete each hash_list object
        delete &_head[i];
    }

    // Free the memory allocated for the _head array
    delete[] _head;
}