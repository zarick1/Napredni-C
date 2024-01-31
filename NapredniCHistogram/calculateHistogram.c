#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

void calculateHistogram(int_least16_t* values, uint_least16_t n, int_least16_t* histogram, int_least16_t maxValue, int_least16_t minValue)
{
    for (uint_fast16_t i = 0; i < (maxValue - minValue + 1); i++)
    {
        histogram[i] = 0;
    }

    for (uint_fast16_t i = 0; i < n; i++)
    {
        if (values[i] >= minValue && values[i] < (maxValue + 1))
        {
            histogram[values[i] - minValue]++;
        }
    }
}