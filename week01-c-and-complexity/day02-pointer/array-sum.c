#include<stdio.h>

int sum_array(int *,int);

int main(){
	int n;
	int s[20];
	scanf("%d",&n);
	for(int i = 0; i < n; i++){
		scanf("%d",&s[i]);
	}
	printf("%d",sum_array(s,n));
	return 0;
} 

int sum_array(int *a,int n){
	int sum = 0;
	for(int *p = a;p < a+n; p++){
		sum += *p;
	}
	return sum;
}
