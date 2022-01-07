#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countingValleys(int steps, char* path) {
    int count = 0, valleys = 0;
    bool enable;
    for (int i =0; i < steps; i++) {
        if(count == 0)
            enable = true;
        if(path[i] == 'U')
            count ++;
        if(path[i] == 'D')
            count --;
        if(count < 0 && enable == true){
            valleys ++;
        }
        enable = false;
    }
    return valleys;
}

int main()
{
   printf("%d", countingValleys(5, "UDDUUDDDUDUUU")); //sample input
   return 0;
}
