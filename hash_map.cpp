#include "hash_map.h"
#include "hash_list.h"

hash_map::hash_map(const hash_map &other) : _capacity(other._capacity) {
    _head = new hash_list[_capacity];
    for (size_t i = 0; i < _capacity; ++i) {
        _head[i] = other._head[i];
    }
}

hash_map& hash_map::operator=(const hash_map &other) {
    if (this != &other) {  // Self-assignment check
        // Free existing memory
        delete[] _head;

        // Copy over capacity
        _capacity = other._capacity;

        // Allocate new memory for the _head array
        _head = new hash_list[_capacity];

        // Copy each hash_list from the other hash_map
        for (size_t i = 0; i < _capacity; ++i) {
            _head[i] = other._head[i];
        }
    }
    return *this;
}


hash_map::hash_map(size_t capacity) : _capacity(capacity) {
    _head = new hash_list[capacity];  // Allocate array of hash_list
}

void hash_map::insert(int key, float value) {
    // Compute the index for the bucket using a hash function and then use insert function from hash_list
    size_t index = key % _capacity;
    _head[index].insert(key, value);
}

std::optional<float> hash_map::get_value(int key) const {
    // Compute the index for the bucket using a hash function and then use get_value function from hash_list
    size_t index = key % _capacity;
    return _head[index].get_value(key);
}

bool hash_map::remove(int key) {
    // Compute the index for the bucket using a hash function and then use remove function from hash_list
    size_t index = key % _capacity;
    return _head[index].remove(key);
}

size_t hash_map::get_size() const {
    size_t total_size = 0;

    // loop through and increment size variable
    for (size_t i = 0; i < _capacity; i++) {
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
    for (size_t i = 0; i < _capacity; i++) {
        hash_list &list = _head[i];

        // Reset iterator to the start of the current hash_list
        list.reset_iter();

        // Iterate over each element in the list using the iterator functions
        while (!list.iter_at_end()) {
            // Get the current key-value pair
            std::optional<std::pair<const int*, float*>> current_value = list.get_iter_value();
            keys[index++] = *(current_value->first);
            // Move the iterator to the next element
            list.increment_iter();
        }
    }
}


void hash_map::get_bucket_sizes(size_t *buckets) {
    // Iterate over each bucket in the hash_map
    for (size_t i = 0; i < _capacity; i++) {
        // Use the hash_list's get_size method to get the number of elements in the current bucket
        buckets[i] = _head[i].get_size();
    }
}

// hash_map::~hash_map() {
//     // Iterate over each bucket in the hash_map
//     for (size_t i = 0; i < _capacity; i++) {
//         // Delete each hash_list object
//         delete &_head[i];
//     }

//     // Free the memory allocated for the _head array
//     delete[] _head;
// }

hash_map::~hash_map() {
    delete[] _head;
}