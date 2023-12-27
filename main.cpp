#include "header.h"
/*
int
main()
{
    time_t czas;
    time(&czas);
#pragma warning(suppress : 4996)
    printf("Czas lokalny: %s", asctime(localtime(&czas)));
#pragma warning(suppress : 4996)
    printf("Czas UTC: %s", asctime(gmtime(&czas)));
    czas += 604800;
#pragma warning(suppress : 4996)
    printf("Czas lokalny: %s", asctime(localtime(&czas)));
#pragma warning(suppress : 4996)
    printf("Czas UTC: %s", asctime(gmtime(&czas)));
    return 0;
}*/
int main()
{
    makeing make;
    Builder2000_2001 zdarzenie;
    make.makePizza(zdarzenie);
    U_Zdarzenie a = zdarzenie.getZD();
    a.pokaz_zd();
    return 0;
}