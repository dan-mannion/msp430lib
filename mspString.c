int getStrLen(char *str){
	int len = 0;
	for(len;*(str+len)!='\0';len++){;}
	return len;
}
void char2ascii(char *str, char num){
	//max value for char is 255 so only three characters need. 
	char values[3];

	values[0] = num/100;
	char remainder = num-values[0]*100;
	values[1] = remainder/10;
	values[2] = remainder-values[1]*10;
	
	char idx=0;
	for(idx=0;idx<3;idx++){
		*(str+idx)=values[idx]+'0';
	}
	*(str+3) = '\0';	
}
