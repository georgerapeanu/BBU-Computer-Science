#include <stdio.h>

int get_hundreds(unsigned int);

int main(){

    unsigned int last = 0;
    char v[101];
    unsigned int value;
    
    while(scanf("%u",&value) == 1){
        v[last++] = get_hundreds(value) + '0';
    }
    v[last++] = 0;
    
    printf("%s\n", v);

    return 0;
}