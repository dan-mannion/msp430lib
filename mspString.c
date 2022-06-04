int getStrLen(char *str){
	int len = 0;
	for(len;*(str+len)!='\0';len++){;}
	return len;
}