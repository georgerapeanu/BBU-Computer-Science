#include <stdio.h>

void byte_to_base_8(char value, char* answer);

int main(){
    
    char base_8_representation[4];

    for(int i = 32;i <= 126;i++){
        byte_to_base_8(i, base_8_representation);
        printf("Value %d corresponds to char %c and is %s in base 8\n", i, i, base_8_representation);
    }
    
    return 0;
}