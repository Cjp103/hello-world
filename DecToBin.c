#include <stdio.h>

void decToBinary(int score){
	
	int one = score % 10;
	int ten = score / 10;
	int ones[4];
	int tens[4];
	
	if(score==0){printf("0"); return;}
	
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
	
		printf("ones = ");
	
	for (int j = 3; j >= 0; j--)
		printf("%d", ones[j]);
		
		printf("\ntens = ");
		
	for (int p = q - 1; p >= 0; p--)
		printf("%d", tens[p]);
}


int main()
{
	int score = 25;
	decToBinary(score);
	return 0;
}



