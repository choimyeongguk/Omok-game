#include <stdio.h>

int main()
{
    int a ;
    scanf("%x", &a) ;

    printf("%x\n", a) ;
    printf("%d\n", a) ;
    printf("%d\n", a-(int)a) ;
    printf("%lf\n", a) ;

    if(a<0)
    {
        printf("hahaha") ;
    }
}
