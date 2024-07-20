//script to solve a linear equation 
main(){
	
	int a = 2;
	int b = -4;
	
	if(a != 0){
		float x = -b/a;
		print('The solution to the equation ax + b = 0 is x =  ' x);
	} else {
		print('Coefficient "a" cannot be zero in a linear equation.');
	}
}
