#include <stdio.h>
#include <math.h>
#include <stdlib.h>


double func_call(double x)
{
    double f = 2*x + 1;

    return f;
}


double bisseccao(double extremo_a, double extremo_b, double tolerancia, int iteracoes_max)
{

double func_value;

for(int iter = 0; iter <= iteracoes_max; iter++)
{
 func_value = (extremo_a + extremo_b)/ 2;
 
 if(func_call(func_value) == 0 || (extremo_b - extremo_a)/2 <= tolerancia)
 {
    return func_value;
 }
 if((func_call(func_value) > 0 && func_call(extremo_a) > 0) || (func_call(func_value) < 0 && func_call(extremo_a) < 0))
 {
    extremo_a = func_value;
 }
 else
 {
    extremo_b = func_value;
 }
 
}
printf("Falhou.");
return 0;
}



int main(void)
{
    double x; 
    double extremo_a = -1;
    double extremo_b = 2;
    double tolerancia = 0.003;
    int iteracoesmax = 10;

    printf("%f", bisseccao(extremo_a, extremo_b, tolerancia, iteracoesmax));
}