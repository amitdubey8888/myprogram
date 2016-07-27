#include<stdio.h>
#define tabsize 8
#define IN 0
#define OUT 1
void err(int e);
int main(int argc, char *argv[])
{
	FILE *in, *out;
	int tab,i;
	char ch;
	if(argc!=3)
	{
		printf("Usage:detab<in <out>\n");
		exit(1);
	}
	if((in=fopen(argv[1],"rb"))==NULL)
	{
		printf("Can not open file %s.\n",argv[1]);
		exit(1);
	}
	tab=0;
	do
	{
		ch=getc(in);
		if(ferror(in)) err(IN);
		if(ch=='\t')
		{
			for(i=tab;i<8;i++)
			{
				putc(' ',out);
				if(ferror(out)) err(OUT);
			}
			tab=0;
		}
		else
		{
			putc(ch,out);
			if(ferror(out)) err(OUT);
			tab++;
			if(tab==tabsize) tab=0;
			if(ch=='\n' || ch=='\r') tab=0;
		}
	}while(!feof(in));
	fclose(in);
	fclose(out);
	return 0;
}
void err(int e)
{
	if(e==IN) printf("Error on input.\n");
	else printf("Error on output.\n");
	exit(1);
}

