#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#define side 30
int x[side][side];
char y[side][side],z[100];
int count,sum;
int seed[8] = {1,2,3,4,6,7,8,9};
FILE *fp/*ָ���д���ļ�*/,*fps/*ָ�����ȡ�ļ�*/;

void swap(int i, int begin);/*����seed�����е�������*/ 
void put();/*�����ɵ�������������������д���ļ�sudoku.txt*/ 
void swap_x(int a,int b);/*Ϊ�˶Դ��������վֵ�x��������б任���γ��µĸ���������վ֣�����x�����������*/ 
void sudoku();/*x�����һ���γ�һ��ȫ�������󣬸��ݵ�һ������һ�������վֲ������б任���ɸ��������վ�Ƕ��swap(),swap_x(int x,int y),put()��������*/ 
void Permutation(int begin);/*�ݹ�����seed�����һ��ȫ�������󣬽�seed������������x[0][0]�ϲ�Ϊa�����һ��,Ƕ��sudoku()����*/ 

int main(int argc, char *argv[])
{
	int i,j,k,n,flag;
	char c;
	
	sum = 0;
	n = strlen(argv[2]);
			
	flag = 1;
	if(argv[2][0] <= '0' || argv[2][0] >= '9')
		flag = 0;
	for(i = 0; i < n; i++){
		sum *= 10;
		sum += argv[2][i] - '0';		
	}
		
	c = argv[1][1];
	
	count = 0;
	x[0][0] = 5;
	if(c == 'c' && flag == 1)
		Permutation(0);
	else if(c == 'c' && flag == 0)
		printf("wrong input.\n");	
	else if(c == 's'){ 
		if( (fps = fopen(argv[2], "r")) ==NULL)
		{
    		printf("Can not open this file.\n");
    		exit(0);
		}	
	}	
	return 0;			
} 


void put()
{
	int i,j,k;
	
	for(i = 0; i < 9; i++){
		k = 0;
		for(j = 0; j < 17; j++){
			if(j % 2 == 0)
				y[i][j] = x[i][k++] + '0';
			else if(j % 2 == 1)	
				y[i][j] = ' ';
		}
		y[i][j] = '\n';
	}
	
	if(count == 0)
		fp = fopen(".\\sudoku.txt", "w+");
	else
		fp = fopen(".\\sudoku.txt", "a");	
	
	for(j = 0; j < 9; j++)
		fprintf(fp, y[j]);
	fprintf(fp, "\n");	
	fclose(fp);	
}

void swap(int i, int begin)
{
	int temp;
	temp = seed[i];
	seed[i] = seed[begin];
	seed[begin] = temp;
}

void swap_x(int a,int b)
{
	int i,j;
	int m1[10],m2[10];
	
	if(a == 0 && b == 0)
		return;	
	for(i = 0; i < 9; i ++){
		m1[i] = x[a][i];
		m2[i] = y[b][i];
	}
	for(i = 0; i < 9; i++){
		x[a][i] = m2[i];
		y[b][i] = m1[i];
	}
}

void sudoku()
{
	int i,j;
	int vary[9] = {0,3,6,1,4,7,2,5,8};
	
	for(i = 1; i < 9; i++)
	{
		for(j = 0; j < 9; j++)
		{
			x[i][ (j + vary[i]) % 9 ] = x[0][j];
		}		
	}
	
	for(i = 0; i < 6; i++)
	{
		switch(i)
		{
			case 0: swap_x(0,0);break;
			case 1: swap_x(4,5);break;
			case 2: swap_x(3,4);break;
			case 3: swap_x(3,4);swap_x(4,5);break;
			case 4: swap_x(3,5);swap_x(4,5);break;
			case 5: swap_x(3,5);break;
		}
		
		for(j = 0; j < 6; j++)
		{
			switch(j)
			{
				case 0: swap_x(0,0);break;
				case 1: swap_x(7,8);break;
				case 2: swap_x(6,7);break;
				case 3: swap_x(6,7);swap_x(7,8);break;
				case 4: swap_x(6,8);swap_x(7,8);break;
				case 5: swap_x(6,8);break;
			}
			if(count < sum)
			{
				put();
				count++;
			}
			else break;
			switch(j)
			{
				case 0: swap_x(0,0);break;
				case 1: swap_x(7,8);break;
				case 2: swap_x(6,7);break;
				case 3: swap_x(7,8);swap_x(6,7);break;
				case 4: swap_x(7,8);swap_x(6,8);break;
				case 5: swap_x(6,8);break;
			}
		}		
		switch(i)
		{
			case 0: swap_x(0,0);break;
			case 1: swap_x(4,5);break;
			case 2: swap_x(3,4);break;
			case 3: swap_x(4,5);swap_x(3,4);break;
			case 4: swap_x(4,5);swap_x(3,5);break;
			case 5: swap_x(3,5);break;
		}		
		if(count >= sum)
			break;		
	}	
}

void Permutation(int begin)
{
	int i;
	
	if(begin == 7 && count < sum)
	{
		for(i = 1; i < 9; i++)
			x[0][i] = seed[i - 1];
		sudoku();
		return;	
	}else if(count < sum)
	{
		for(i = begin; i < 8; i++)
		{
			swap(i, begin);
			Permutation(begin + 1);
			swap(i, begin);
		}
	}
}


