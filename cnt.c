#include<stdio.h>
#include<string.h>
int main() {
	char buff[1024];
	memset(buff, 0, 1024);
	char c;
	int cnt = 0;
	while ((c=getchar())!=EOF) {
		if(c=='\n')cnt += 1;
	}
	printf("%d\n", cnt);
	return 0;
}
