#include <iostream>
#include <vector>


/**
 * Helper function for selectionSort to swap location of two numbers in a vector.
 * @param numbers vector of numbers over which the operation takes place.
 * @param i location of larger number to be swapped.
 * @param min location of minimum value to be swapped.
 */
void swap(std::vector<int> &numbers, int i, int min) {
    int old = numbers[i];           //save value of number to be swapped
    numbers[i] = numbers[min];      //set value of element at given location to the smallest value in list
    numbers[min] = old;             //set value of min to old
}

/**
 * Implementation of selection sort for a vector of numbers.
 * @param numbers vector to be sorted.
 * @return sorted version of numbers vector.
 */
std::vector<int> selectionSort(std::vector<int> numbers) {
    for (int i = 0; i < numbers.size(); ++i) {              //loop over vector
        int min = i;                                        //set i as the current minimum value in min

        for (int j = i + 1; j < numbers.size(); ++j) {      //loop over elements starting from unsorted elements
            if (numbers[j] < numbers[min]) {                //check if new value larger than current minimum value
                min = j;                                    //set min to new minimum value's location
            }
        }
        if (min  != i) {                                    //check if minimum value is already sorted
            swap(numbers, i, min);                      //function call to swap unsorted value with min value
        }
    }
    return numbers;                                         //return sorted vector
}


int main() {
    std::vector<int> sorted = selectionSort({2, 22, 22, 9, 14, 14, 67, 2, 9});
    for (int i : sorted) {
        if (i != *(sorted.end() - 1)) {
            std::cout << i << ", ";
        } else {
            std::cout << i << std::endl;
        }
    }
    return 0;
}
