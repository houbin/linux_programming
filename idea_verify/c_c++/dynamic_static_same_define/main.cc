#include <stdio.h>   
#include <stdlib.h>   
#include "mylib.h"   
   
extern "C" void foo() {   
        printf("foo in main\n");   
}   
   
int main() 
{   
        bar();   
        return 0;   
}
