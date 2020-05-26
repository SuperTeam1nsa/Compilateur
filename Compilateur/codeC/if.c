int main(){
	int const bob=2;
	const char lettre='a';
	int i=5;
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
	int z=42;
	return 0;
}
