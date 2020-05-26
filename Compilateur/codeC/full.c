int main(){
	//test des différents types de déclarations
	int i, j,k,r;
	float a= 10e-1;
	float b= 1e2;
	float c= 1e+2;
	int z = 6;
	char abc='e';
	int uni;
	int
	zz
	=
	1;
	int const bob=2;
	const char lettre='a';
	i=5;
	//test des if seuls, if-else et imbrigation
	if(i==5){
		int w=99;
		if(lettre=='a'){
			w=999;
			if(bob > 5){
				w=w*2;
				int test=5;
			}
			else
			{
				w--;
				int omega=42;
				if(1 && (omega==42) || 0){
					w =w -omega;
				}
			}
		}
		else{
			w=1000;
		}
		//affiche : 956
		printf(w);
	}
	else{
		i++;
		i--;
	}
	//test des else simples et if vide
	if(i!=5){
		i=i*2/2;
	}
	else{
	printf(i);
	}
	if(lettre=='a'){}
	//test des conditions booléennes avancées (affiche 1 0 1)
	int boolean1=(-3)>(-4);
	int boolean2=30<=29;
	int boolean3=!(((((1<2)==1)<=10)-1)!=0);
	printf(boolean1);
	printf(boolean2);
	printf(boolean3);
	i =4;
	i++;i--;
	j=4;
	k=8;
	printf (i);
	//test des calculs avancés (r=-50)
	r=-(i+j)*(i+k/j)+-1-1;
	printf ( r );
	i=0;
	/*test des boucles (affiche 0 1 2 3 4 5 6 7 8 9)
	et des return
	*/
		do{
			printf(i);
			i++;
		}while(i<10);

	return 0;
}