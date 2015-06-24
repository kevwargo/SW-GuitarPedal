#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int maxCounter = 128;
    if (argc > 1)
        maxCounter = atoi(argv[1]);
    /* for (int l = 0; l < 5; l++) */
    {
        for (int counter = 0; counter < maxCounter; counter++)
        {
            float res = sinf(2 * 3.141593 * (float)counter / (float)maxCounter);
            uint32_t i = res * 0x7ff + 0x7ff;
            printf("%d ", i);
        }
    }
    printf("\n");
}
