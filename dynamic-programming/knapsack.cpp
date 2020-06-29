#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

class Jewel
{
public:
    unsigned int profit;
    unsigned int weight;

    Jewel(unsigned int _profit = 0, unsigned int _weight = 0)
    {
        profit = _profit;
        weight = _weight;
    }
};

/*
	In this case we have:
		* Limited types of objects
		* Unlimited amounts of each object
		* Indivisible objects
*/
unsigned int maxProfit_LUI (const vector<Jewel> &jewels, unsigned int capacity)
{
    unsigned int maxProfitAtCapacities [capacity + 1] = {0};

    for (unsigned int curCapacity = 0; curCapacity < capacity + 1; curCapacity++)
    {

        unsigned int maxProfitAtCurCapacity = 0;

        for (Jewel curJewel : jewels)
        {

            if (curJewel.weight <= curCapacity)
            {
                unsigned int maxProfitUsingCurJewel = curJewel.profit + maxProfitAtCapacities[curCapacity - curJewel.weight];

                maxProfitAtCurCapacity = max(maxProfitAtCurCapacity, maxProfitUsingCurJewel);
            }

        }

        //printf("Max profit = %u with capacity = %u\n", maxProfitAtCurCapacity, curCapacity);
        maxProfitAtCapacities[curCapacity] = maxProfitAtCurCapacity;


    }


    return maxProfitAtCapacities[capacity];
}

int main (int argc, char *argv [])
{
    const vector<Jewel> jewels =
    {
        Jewel(3, 65),
        Jewel(45, 5),
        Jewel(6, 46),
        Jewel(345, 638),
        Jewel(87, 145),
        Jewel(890, 66),
        Jewel(23, 27),
        Jewel(9, 30),
        //Jewel(43, 1),
        Jewel(67, 324),
        Jewel(993, 453),
        Jewel(4, 68),
        Jewel(233, 145)
    };

    unsigned int capacity = 150;


    printf("Max profit is %u with capacity of %u\n\n", maxProfit_LUI(jewels, capacity), capacity);
}

