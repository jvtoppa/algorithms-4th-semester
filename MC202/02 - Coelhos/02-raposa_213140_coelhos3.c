#include <stdio.h>
#include <math.h>

int main(void)
{
    //Qtd Buracos
    int n;
    
    //Raposa
    double xRaposa;
    double yRaposa;
    
    //Coelho
    double xCoelho;
    double yCoelho;

    //Buraco
    double xBuraco;
    double yBuraco;

    //Flags
    int flag = 0;
    int increment2 = 0;
    
    
        
        while(30){
        increment2 = 0;
        if(scanf("%d %lf %lf %lf %lf", &n, &xCoelho, &yCoelho, &xRaposa, &yRaposa) == 5){
        getchar();
        if (n == 0){
            break;
        }

        for (int i = 0; i < n; i++)
        {
            if(scanf("%lf %lf", &xBuraco, &yBuraco) != 2){
                break;
            }
            getchar();

            double dRaposaBuraco = pow(xBuraco - xRaposa, 2) + pow(yBuraco - yRaposa, 2); 
            double dCoelhoBuraco = pow(xBuraco - (xCoelho), 2) + pow(yBuraco - (yCoelho), 2); 
            
            if(dRaposaBuraco > 4*dCoelhoBuraco) //Verificar por Pitagoras
            
            {
                if (flag == 0)
                {
                    printf("O coelho pode escapar pelo buraco (%.3lf,%.3lf).\n", xBuraco, yBuraco);
                    flag = 1;
                }
                
            } 

            if(flag == 0)
            
            {
                increment2++;
            }

            if(increment2 == n)
            {
                printf("O coelho nao pode escapar.\n");
            }

            
            
        }
        }
        else
        {
            break;
        }
        flag = 0;
        


}
}