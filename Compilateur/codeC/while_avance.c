int main(){
	int i=0;
	int j;
	do{
		printf(i);
		j=5;
		do{
				printf(j);
				j--;
		}while(j>0);
		i++;
	}while(i<5);
	return 0;
}