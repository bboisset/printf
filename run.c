//#include "printf.h"
#include "printf.h"

int main(void){// d|i|u => -1
    int res =  printf("test %-12i et %--2.4s %24s !\n", 0, NULL, "coco");
    int res2 = ft_printf("test %-12i et %--2.4s %24s !\n", 0, NULL, "coco");
    printf("\n%i|%i\n", res, res2);
    return (0);
}
