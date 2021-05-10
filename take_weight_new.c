#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	
	float nums[96][3][11][11] = {0};
	float kontrol[1] = {0};
    int i = 0;
    int j = 0;
    int k = 0;  
    int l = 0;
    int count = 0;
    int temp = 0;
    int temp2 = 0;
    FILE * fp;
 	char ch;
 	int sayac = 0;
 	
    if(fp = fopen("weight_0_yuvarlama.txt", "r")) {
        while ((ch = fgetc(fp)) != EOF ) {
        //printf("%f\n", ch);	
		fscanf(fp, "%f", &kontrol[0]) != EOF;     // kontrol e atama yapýldý
        	//printf("%d \n",ch);
		if(kontrol[0] != 0){                      // kontrol deðeri 0 dan farklý ise
            nums[i][j][k][l] = kontrol[0];
			++count;                // nums deðerine aktarýlýr sayý
			++i;
			if(i == 96){
				i = 0;
				j = j +1 ;
				if(j == 3){
					j = 0;
					k = k+1;
					if(k == 11){
						k = 0;
						l = l+1;
					}
				}
			}
            kontrol[0] = 0;
        }
        else            // txt dosyasýnda 0 sayýsý olduðunda hata olmamasý için
        {
        	if(ch == 32){            			// sayý 0 ise ve "[" karakterine eþit deðilse
        		nums[i][j][k][l] = kontrol[0];	// içeri girer ve 0 sayýsýný atama yapar
        		++count;                // nums deðerine aktarýlýr sayý
			++i;
			if(i == 96){
				i = 0;
				j = j +1 ;
				if(j == 3){
					j = 0;
					k = k+1;
					if(k == 11){
						k = 0;
						l = l+1;
					}
				}
			}
            kontrol[0] = 0;
			}		
		}
}
        fclose(fp);
    }
    
	temp = j;
	temp2 = k;
	printf("k = %d && j = %d  &&  count = %d\n", k,j,count);

for(l = 0; l <= 10; l++){
	for(k = 0; k <= 10 ; k++){
    	for(j = 0; j <= 2 ; j++){
    		for (i = 0; i <=95 ; i++){
        		printf("num[%d][%d][%d][%d] = %f     ", i,j,k,l, nums[i][j][k][l]);
        		sayac++;
        		if(sayac == 3){
        			sayac = 0;
        			printf("\n");
				}
			}
		}
	}
}

	
}

