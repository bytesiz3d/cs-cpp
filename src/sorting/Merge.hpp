#pragma once
#include <vector>
#include "SortingAlgorithm.hpp"

class Merge : public SortingAlgorithm {
    template <class T>
    static void merge(T *data, index_t START, index_t MID, index_t END, predicate_t<T> predicate, std::vector<T> &merge_array) {
        std::copy(data + START, data + END, merge_array.begin() + START);
        index_t left_index = START;
        index_t right_index = MID;

        for (index_t i = START; i < END; i++) {
            if (predicate(merge_array[left_index], merge_array[right_index])) {
                data[i] = merge_array[left_index++];
                if (left_index == MID) {
                    std::copy(merge_array.begin() + right_index, merge_array.begin() + END, data + i + 1);
                    break;
                }
            }

            else {
                data[i] = merge_array[right_index++];
                if (right_index == END) {
                    std::copy(merge_array.begin() + left_index, merge_array.begin() + MID, data + i + 1);
                    break;
                }
            }
        }
    }

    template <class T>
    static void split(T *data, index_t START, index_t END, predicate_t<T> predicate, std::vector<T> &merge_array) {
        if (END - START <= 1) return;

        const index_t MID = START + (END - START) / 2;
        split(data, START, MID, predicate, merge_array);
        split(data, MID, END, predicate, merge_array);

        merge(data, START, MID, END, predicate, merge_array);
    }

public:
    // Out-of-place
    template <class T>
    static void sort(T *data, size_t SIZE, predicate_t<T> predicate = predicate_lt<T>) {
        std::vector<T> merge_array(SIZE);
        split(data, 0, SIZE, predicate, merge_array);
    }
};
