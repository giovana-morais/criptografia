#include <stdio.h>
#include <stdlib.h>

unsigned int reverseBits(unsigned int num) 
{ 
    // sizeof é o tamanho em BYTESSSS
    unsigned int count = sizeof(num) * 8 - 1; 
    unsigned int reverse_num = num; 

    num >>= 1;  
    while(num) 
    { 
        reverse_num <<= 1;        
        reverse_num |= num & 1;     // 1 é o bit menos significativo
        num >>= 1; 
        count--; 
    } 
    reverse_num <<= count; 
    return reverse_num; 
} 

int main() 
{ 
    unsigned int x = 6; 
    printf("hexa %2x\n", x);
    printf("%u\n", reverseBits(x)); 
    getchar(); 
} 

