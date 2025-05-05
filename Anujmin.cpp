#include <omp.h>
#include <iostream>
#include <chrono>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
using namespace std::chrono;
using namespace std;

// Display Array
void displayArray(int nums[], int length)
{
    cout << "Nums: [";
    for (int i = 0; i < length; i++) {
        cout << nums[i];
        if (i != length - 1)
            cout << ", ";
    }
    cout << "]" << endl;
}

// Parallel Min Operation
void minOperation(int nums[], int length)
{
    int minValue = nums[0];
#pragma omp parallel for reduction(min : minValue)
    for (int i = 0; i < length; i++) {
        minValue = (nums[i] < minValue) ? nums[i] : minValue;
    }
    cout << "Min value: " << minValue << endl;
}

// Parallel Max Operation
void maxOperation(int nums[], int length)
{
    int maxValue = nums[0];
#pragma omp parallel for reduction(max : maxValue)
    for (int i = 0; i < length; i++) {
        maxValue = (nums[i] > maxValue) ? nums[i] : maxValue;
    }
    cout << "Max value: " << maxValue << endl;
}

// Parallel Sum Operation
void sumOperation(int nums[], int length)
{
    int sum = 0;
#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < length; i++) {
        sum += nums[i];
    }
    cout << "Sum: " << sum << endl;
}

// Parallel Average Operation
void avgOperation(int nums[], int length)
{
    float sum = 0;
#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < length; i++) {
        sum += nums[i];
    }
    cout << "Average: " << (sum / length) << endl;
}

// Main Function
int main()
{
    int length;
    cout << "Enter the number of elements in the array: ";
    cin >> length;

    if (length <= 0) {
        cout << "Length must be a positive number." << endl;
        return 1;
    }

    int* nums = new int[length]; // Dynamic allocation for user-defined size

    srand(time(0)); // Seed for random number generator

    for (int i = 0; i < length; i++)
    {
        nums[i] = rand() % 10000; // Random number between 0 and 9999
    }

    // Uncomment to display the array (only for small lengths)
    // displayArray(nums, length);

    auto start = high_resolution_clock::now();

    minOperation(nums, length);
    maxOperation(nums, length);
    sumOperation(nums, length);
    avgOperation(nums, length);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nExecution time: " << duration.count() << " microseconds" << endl;

    delete[] nums; // Free dynamically allocated memory
    return 0;
}
