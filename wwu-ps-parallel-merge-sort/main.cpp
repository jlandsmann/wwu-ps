#include <iostream>
#include <thread>
#include <random>

// Here you can configure the size of the random number array
const auto sampleSize = 100000;
// This condition points out if the array should be printed
const auto print = sampleSize <= 100;
// This calculates the max thread count relative to the number of cores
const auto maxThreadCount = 2 * std::thread::hardware_concurrency();
// This states the minimum count of items to create a new thread,
// This limits the count of threads to maxThreadCount.
const auto minThreadSize = sampleSize / maxThreadCount;

// Just printing the array as oneliner
void print_int_arr(int* arr, int size) {
    for (int i = 0; i < size; ++i) {
        if (i != 0) printf(", ");
        printf("%4d", arr[i]);
    }
    printf("\n");
}

// Merging a list inplace, where start and start2 are the idx of both parts
void merge(int* arr, int start, int start2, int size) {
    // If the greatest element of the first half
    // is smaller than the smallest of the second half,
    // there is nothing to do
    if (arr[start2 - 1] <= arr[start2]) {
        return;
    }
    // counting up until one end of the lists is reached
    while (start < start2 && start2 < size) {
        // if the smaller element is in the first half
        // just go forward
        if (arr[start] <= arr[start2]) {
            start++;
        }
        // if not shift all elements on to the right
        // and insert the smallest element
        else {
            int value = arr[start2];
            int index = start2;
            while (index != start) {
                arr[index] = arr[index - 1];
                index--;
            }
            arr[start] = value;
            start++;
            start2++;
        }
    }
}

// the merge sort itself
void parallel_merge_sort(int* arr, int size) {
    if (size <= 1) {
        return;
    }
    int divider = ceil(size / 2);
    // this condition checks if we should create a thread or not
    if (divider > minThreadSize) {
        // start thread first, because async
        std::thread helper (parallel_merge_sort, arr+divider, size-divider);
        // this is blocking, so do it afterward
        parallel_merge_sort(arr, divider);
        // wait for helper to complete
        helper.join();
    } else {
        // if not just sort both sequentially
        parallel_merge_sort(arr, divider);
        parallel_merge_sort(arr+divider, size-divider);
    }
    // merge sorted parts
    merge(arr, 0, divider, size);
}

// this generates <count> random numbers from 1 to 10*<count>
// uses uniform distribution
int* generate_random_numbers(int count) {
    std::random_device rd;
    std::mt19937  gen(rd());
    std::uniform_int_distribution<> distrib(1, 10*count);
    int* random = new int[count];
    for (int i = 0; i < count; ++i) {
        random[i] = distrib(gen);
    }
    return random;
}

int main() {
    std::cout << "Generating " << sampleSize << " random numbers" << std::endl;
    int* random = generate_random_numbers(sampleSize);
    if (print) print_int_arr(random, sampleSize);

    std::cout << "Starting to sort parallel" << std::endl;
    std::cout << "MaxThreadCount: " << maxThreadCount << std::endl;
    std::cout << "MinThreadSize: " << minThreadSize << std::endl;
    auto begin = std::chrono::high_resolution_clock::now();
    parallel_merge_sort(random, sampleSize);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count();
    std::cout << "Sorting took " << duration << "ms" << std::endl;

    if (print) print_int_arr(random, sampleSize);

    return 0;
}