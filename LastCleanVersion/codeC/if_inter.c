int main(){
	int a=0;
	int b=2;
	if(a==0){
		int c=3;
		printf(a);
		if(a >= 0){
			c=5;
			b= b+2;
			if(c==5){
				printf(b);
			}
		}else{
			b= b-2;
		}
		printf(c);
	}else{
		printf(b);
	}

}