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

long repeatedString(char* s, long n) {
    long aOcurr = 0, count=0;
    long a = n / strlen(s);
    long b = n % strlen(s);
    
    for (int i = 0; i < strlen(s); i++) {
        if(s[i] == 'a'){
            count++;
            if(i < b){
                aOcurr++;
            }
        }
    }
        aOcurr += a * count;
   
    return aOcurr;
}

int main(){
   long res = repeatedString("abc", 20); //sample input
   printf("%ld", res);
}