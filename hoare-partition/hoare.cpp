#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <cstdlib>



using namespace std;

unordered_map<int, int> counts;	// Value, nTimes
int countsSize;
vector<int> unique;

int partition (int left, int right, int pivot_index)
{
    int pivot_frequency = counts[unique[pivot_index]];

    // Move pivot to the end
    swap(unique[pivot_index], unique[right]);

    // Move all less frequent items to the left of the pivot
    int store_index = left;
    for (int i = left; i <= right; i++)
    {
        if(counts[unique[i]] < pivot_frequency)
        {
            swap(unique[store_index++], unique[i]);
        }
    }

    // Move pivot to its final place
    swap(unique[store_index], unique[right]);

    return store_index;
}

void quickSelect (int left, int right, int kSmallest)
{
    // Base case
    if (left >= right)
    {
        return;
    }

    // Select a random pivot index
    int pivot_index = left + (rand() % (right - left));

    // Find its correct position
    pivot_index = partition(left, right, pivot_index);


    if (pivot_index == kSmallest)
    {
        return;
    }
    else if (pivot_index > kSmallest)
    {
        quickSelect(left, pivot_index - 1, kSmallest);
    }
    else
    {
        quickSelect(pivot_index + 1, right, kSmallest);
    }

}

vector<int> kMostFrequent (vector<int> &nums, int k)
{

    // Count how many times an element appears
    for (int n : nums)
    {
        counts[n]++;
    }


    // Create vector of unique elements
    countsSize = counts.size();
    unique.resize(countsSize);
    int i = 0;
    printf("Value -> nTimes\n");
    for (pair<int, int> p : counts)
    {
        unique[i++] = p.first;
        printf("%d -> %d\n", p.first, p.second);
    }

    // Partial sort using Hoare partition
    quickSelect(0, countsSize - 1, countsSize - k);

    // Return k most frequent elements
    return vector<int>(unique.begin() + countsSize - k, unique.end());
}



int main (int arg, char *argv[])
{
    srand (time(NULL));

    vector<int> nums {1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 3, 7, 7, 6, 6, 5, 2, 5, 4, 4, 5, 6, 3, 3, 3, 2, 2, 2, 2, 2, 3, 3};
    int k = 2;
    vector<int> freq = kMostFrequent(nums, 2);

    printf("\n%d most frequent elements:\n", k);
    for (int n : freq)
    {
        printf("%d ", n);
    }
    printf("\n");
    return 0;
}