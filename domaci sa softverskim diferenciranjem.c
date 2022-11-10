/***********************************
 MOGUCE JE DA IMA NEKA SINTAKSNA GRESKA JER
 NISAM USPEO SA PLOCICE DA PUSHUJEM NA GIT NEGO
 SAM IZ VIMA MANUELNO PREKUCAVAO U NOTEPAD++
 KOJI SAM ONDA OKACIO NA GIT IZ WINDOWSA.
 SOFTVERSKO DIFERENCIRANJE NISAM PROBAO NA
 PLOCICI ALI TREBALO BI DA RADI
 Petar Ubavic EE156/2019
 Jovan Ikic EE195/2019
 10.nov.2022 11:50
 ***********************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main ()
{
	FILE *fl;
	FILE *fb;
	char *str;
	char *str3;
	char tval1,tval2,tval3,tval4, sval1, sval2, sval3, sval4, prom, staroSt, novoSt;
	size_t num_of_bytes = 6;
	char operacija, operand;
	
	prom=0;
	
	while(1)
	{

		//Citanje vrednosti tastera
		fb = fopen ("/dev/button", "r");
		
		if(fb==NULL)
		{
			puts("Problem pri otvaranju /dev/button");
			return -1;
		}
		
		str = (char *)malloc(num_of_bytes+1);
		getline(&str, &num_of_bytes, fb);
		
		if(fclose(fb))
		{
			puts("Problem pri zatvaranju /dev/button");
			return -1;
		}
		
		tval4 = str[5] - 48;
		free(str);
		
		//puts("Broj");
		//printf("%d", tval4);

		novoSt = tval4;
        if(staroSt!=novoSt)
        {
            staroSt=novoSt;
            if(tval4 == 1)
            {///////////////////

                //Citanje vrednosti switcha
                fs = fopen ("/dev/switch", "r");
                if(fs==NULL)
                {
                    puts("Problem pri otvaranju /dev/switch");
                    return -1;
                }


                str = (char *)malloc(num_of_bytes+1); 
                getline(&str, &num_of_bytes, fs); 

                if(fclose(fs))
                {
                    puts("Problem pri zatvaranju /dev/switch");
                    return -1;
                }


                sval1 = str[2] - 48;
                sval2 = str[3] - 48;
                sval3 = str[4] - 48;
                sval4 = str[5] - 48;
                free(str3);
                
                if(sval3 == 0)
                    if(sval4 == 0)
                        operacija = 1; //plus 
                    else
                        operacija = 2; //minus
                    
                else
                    if(sval4 == 0)
                        operacija = 3; //puta
                    else
                        operacija = 4; //podeljeno
                    
                if(sval1 == 0)
                    if(sval2 == 0)
                        operand = 0;
                    else
                        operand = 1;
                else
                    if(sval2 == 0)
                        operand = 2;
                    else
                        operand = 3;
                
                
                if(operacija == 1)
                    prom=prom+operand;
                else if(operacija == 2)
                    prom=prom-operand;
                else if(operacija == 3)
                    prom=prom*operand;
                else if(operacija == 4)
                    prom=prom/operand;
                
                fl = fopen("/dev/led", "w");
                if(fl==NULL)
                {
                    puts("Problem pri otvaranju /dev/led");
                    return -1;
                }
                //fprintf(fl, "%d\n", prom);
                if(fclose(fl))
                {
                    puts("Problem pri zatvaranju /dev/led");
                    return -1;
                }
            sleep(1);	
            }////////////////*/
        }
	}
}