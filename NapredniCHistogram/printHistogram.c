#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

void printHistogram(int_least16_t* histogram, int_least16_t maxValue, int_least16_t minValue)
{
    printf("Histogram:\n");

    for (uint_fast16_t i = 0; i < (maxValue - minValue + 1); i++)
    {

        printf("%4ld: [%d]", i + minValue, histogram[i]);

        for (uint_fast16_t j = 0; j < histogram[i]; j++)
        {
            printf("#");
        }

        printf("\n");
    }

}