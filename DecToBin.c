
// TESTING DECIMAL TO BINARY CONVERSION


#include <stdio.h>


int main()
{
	int TOTAL [6];
	int score = 28;
	int one = score % 10;
	int ten = score / 10;
	int ones[4];
	int tens[4];
	
	if(score==0){printf("0");}
	else{
	
	int i = 0;
	int q = 0;
	
	for (i=0;i<4;i++){
		ones[i] = one % 2;
		one /= 2;
	}
	
	for (q=0;q<4;q++){
		tens[q] = ten % 2;
		ten /= 2;
	}
	
	
		TOTAL[5] = ones[0];
		TOTAL[4] = ones[1];
		TOTAL[3] = ones[2];
		TOTAL[2] = ones[3];
		TOTAL[1] = tens[0];
		TOTAL[0] = tens[1];
		
	for (int j = 0; j <= 5; j++)
		printf("%d",TOTAL[j]);
		
	}
		
	return 0;
}



