#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#define side 30
int x[side][side];
char y[side][side],z[100];
int count,sum;
int seed[8] = {1,2,3,4,6,7,8,9};
FILE *fp/*指向待写入文件*/,*fps/*指向待读取文件*/;

void swap(int i, int begin);/*交换seed数组中的两个数*/ 
void input();/*命令行输入-s时从指定文件中读取待求解数独，嵌套put(),dfs()函数*/ 
void put();/*将生成的数独和求解出来的数独写回文件sudoku.txt*/
void Permutation(int begin);/*递归生成seed数组的一个全排列数后，将seed数组所有数和x[0][0]合并为a数组第一行,嵌套sudoku()函数*/ 
void dfs(int row, int col);/*回溯求解数独*/ 

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
		return 0;
	else if(c == 'c' && flag == 0)
		printf("wrong input.\n");	
	else if(c == 's'){ 
		if( (fps = fopen(argv[2], "r")) ==NULL)
		{
    		printf("Can not open this file.\n");
    		exit(0);
		}
		input();	
	}	
	return 0;			
} 

void input()
{
	int i,j,k;
	char ch;
	
	count = 0;
	while(!feof(fps)){
		
		for(i = 0; i < 9; i++)
			fgets(y[i], 30, (FILE*)fps);
		ch = fgetc(fps);	
		for(i = 0; i < 9; i++)
			y[i][17] = 0;
				
		for(i = 0; i < 9; i++)
		{
			k = 0;
			for(j = 0; j < 17; j++)
			{
				if(y[i][j] != ' ')
					x[i][k++] = y[i][j] - '0';
			}
		}
		dfs(0, 0);
		
		count ++;				
	} 
		
	fclose(fps);
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

void dfs(int row, int col)
{
	int i,j,k;
 	int count = 0;
 	int d[50]; 
 
 	for(i = 0; i < 9; i++)
 		d[i] = 0;
 	if (row == 9 && col == 9)
	 {
 		put();
 		return;
	 }
		
 	if(x[row][col] == 0)
	 {
  		for (i = 0; i < 9; i++)
   			if (x[row][i] != 0)
    			d[x[row][i] - 1] = 1;		
  		for(i = 0; i < 9; i++)
  			if(x[i][col] != 0)
  				d[ x[i][col] - 1 ] = 1;

  		for (i = int(row / 3) * 3; i < int(row / 3) * 3 + 3; i++)
		  {
   			for (j = int(col / 3) * 3; j < int(col / 3) * 3 + 3; j++)
			   {
    			if (x[i][j] != 0)
     				d[x[i][j] - 1] = 1;
   			}
  		}
  		for (i = 0; i < 9; i++)
   			if (d[i] == 0) 
			   count++;
   			
  		if (count == 0)
   			return;
  		else{
   			for (i = 0; i < 9; i++)
			   {
    			if (d[i] == 0){

    			x[row][col] = i + 1;
     			d[i] = 1;	

     			if (col == 8)
				 {
     				if(row == 8)
					 {
     					col++;
      					row++;
					}
      				if(row < 8){
      					col = 0;
      					row++;
					}
     			}
     			else if(col < 8 && row <= 8)
      				col++;
     			    		
     			dfs(row, col); 

     			if (col == 0){
      				col = 8;
      				row--;
    			}
     			else
      				col--;
     			x[row][col] = 0;
     			d[i] = 0;
    			}
   			}
  		}
 	}
 	else{
 		
 		if (col == 8){
     		if(row == 8){
     			col++;
      			row++;
			}
      		if(row < 8){
      			col = 0;
      			row++;
			}
     	}
     	else if(col < 8 && row <= 8)
      		col++;
  		dfs(row, col); 
 	}
}
