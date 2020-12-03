#include <time.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))
#define getmax(x, y) (((x) > (y)) ? (x) : (y))
#define getmin(x, y) (((x) < (y)) ? (x) : (y))
#define R 1000 
#define C 1000
static int M[R][C];
  
void Task1_ALG1(int M[R][C], int m, int n, int h) 
{ 
	static int S[R][C]; 
	int max_of_s, max_i, max_j;  
	  
	/* Construct other entries of S[][]*/
	max_of_s = 0; max_i = 0; max_j = 0; 
	int i, j;
	for(i = 0; i < m; ++i) 
	{ 
	  for(j = 0; j < n; ++j) 
	  { 
	    if(M[i][j] >= h){ 
	      if (i > 0 && j > 0){
	        S[i][j] = min(min(S[i][j-1], S[i-1][j]), S[i-1][j-1]) + 1;
        } else if(i == 0 || j == 0) {
          S[i][j] = 1;
        } 
      } else {
	        S[i][j] = 0; 
	    }  
	    if(max_of_s < S[i][j]) 
	    { 
	        max_of_s = S[i][j]; 
	        max_i = i+1;  
	        max_j = j+1; 
	    }
    }
	}
	printf("%d %d %d %d\n", max_i-max_of_s+1, max_j-max_of_s+1, max_i, max_j);
}
  
void Task2_ALG1(int M[R][C], int m, int n, int h) 
{ 
  int buffer[n], tmpBuf[n];
  int maxSquare[2];
  maxSquare[0] = -1;
  maxSquare[1] = -1;
  int currentMax = -1;

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      int current = M[i][j];
      if (current >= h) {
          if (i == 0 || j == 0) {
              tmpBuf[j] = 1;
          } else {
              int min = getmin(getmin(buffer[j], buffer[j - 1]), tmpBuf[j - 1]);
              tmpBuf[j] = min + 1;
          }
      } else {
          tmpBuf[j] = 0;
      }

      if (tmpBuf[j] > currentMax) {
          currentMax = tmpBuf[j];
          maxSquare[0] = j;
          maxSquare[1] = i;
      }
    }
    memcpy(buffer, tmpBuf, sizeof(tmpBuf));
    memset(tmpBuf, 0, sizeof(tmpBuf));
  }
  int dif = currentMax - 1;
  printf("%d %d %d %d\n", maxSquare[1] - dif + 1, maxSquare[0] - dif + 1, maxSquare[1] + 1, maxSquare[0] + 1);
}	 

void Task3_ALG2(int M[][C], int m, int n, int h)
{
  int sum = 0, topLeft_x = 0, topLeft_y = 0, bottomRight_x = m, bottomRight_y = n;
  int max_sum = INT_MIN;
  for(int i=0;i < m; ++i)
  {
    for(int j=0;j < n; ++j)
    {
      for(int i1=0; i1 < m; ++i1)
      {
        for(int j1=0; j1 < n; ++j1)
        {

          sum = 0;
          for (int k=i; k <= i1; ++k)
          {
            for(int l=j; l <= j1; ++l)
            {
              if(M[k][l] >= h){
                sum = sum+1;
              } else {
                sum = 0;
                break;
              }
            }
          }
          if(sum >= max_sum){
            max_sum = sum;
            topLeft_x = i;
            topLeft_y = j;
            bottomRight_x = i1;
            bottomRight_y = j1;
          }
        }
      }
    }
  }
  printf("%d %d %d %d\n", topLeft_x+1, topLeft_y+1, bottomRight_x+1, bottomRight_y+1);
}

void Task4_ALG3(int M[R][C], int m, int n, int h) 
{ 
  int max_x[R][C];
  int area = 0;
  int x1=0, x2=0, y1=0, y2=0;
  for (int i=0; i < m; ++i){
    for (int j=0; j < n; ++j){
      if(M[i][j] >= h){
        if(j == 0) max_x[i][j] = 1;
        else max_x[i][j] = max_x[i][j-1] + 1;
        int y=1;
        int x=m;
        while((i-y+1 >= 0) && (M[i][j] >= h)){
          x=min(x, max_x[i-y+1][j]);
          if(x*y > area) {
            x2 = i+1;
            y2 = j+1;
            x1 = x2-y+1;
            y1 = y2-x+1;
            area = x*y;
          }
          y++;
        }
      }
    }
  }
  printf("%d %d %d %d\n", x1, y1, x2, y2);
}
  
int kadane(int* arr, int* start, 
           int* finish, int n)
{
    int sum = 0, maxSum = INT_MIN, i;
 
    *finish = -1;
 
    int local_start = 0;
 
    for (i = 0; i < n; ++i) 
    {
        sum += arr[i];
        if (sum < 0) {
            sum = 0;
            local_start = i + 1;
        }
        else if (sum > maxSum) 
        {
            maxSum = sum;
            *start = local_start;
            *finish = i;
        }
    }
 
    for (i = 1; i < n; i++) 
    {
        if (arr[i] > maxSum) 
        {
            maxSum = arr[i];
            *start = *finish = i;
        }
    }
    return maxSum;
}
 
void Task5_bonus(int M[][C], int m, int n, int h)
{
    int maxSum = INT_MIN, 
                 topleft_y, 
                 bottomRight_y, 
                 topleft_x,
                 bottomRight_x;
 
    int left, right, i;
    int temp[R], sum, start, finish;
     
    /*for(int i=0; i < m; ++i){
      for(int j=0; j < n; ++j){
        if(M[i][j] >= h){
          M[i][j] = M[i][j];
        } else {
          M[i][j] = -100;
        }
      }
    }*/
    for (left = 0; left < C; ++left) 
    {
        memset(temp, 0, sizeof(temp));
         
        for (right = left; right < C; ++right) {
            for (i = 0; i < R; ++i){
                
                if(M[i][right] >= h){
                  M[i][right] = M[i][right];
                } else {
                  M[i][right] = -100;
                }
                temp[i] += M[i][right];
            }
            sum = kadane(temp, &start, &finish, R);
            if (sum > maxSum) 
            {
                maxSum = sum;
                topleft_y = left;
                bottomRight_y = right;
                topleft_x = start;
                bottomRight_x = finish;
            }
        }
    }
 
    // Print final values
    printf("%d %d %d %d\n", topleft_x+1, topleft_y+1, bottomRight_x+1, bottomRight_y+1);
}

// Driver Code
int main(int argc, char *argv[])
{
  int m, n, h;
  printf("Executing Task %d\n",atoi(argv[1]));
  printf("Enter number of Rows, Columns, and height limit:");
  scanf("%d %d %d",&m,&n,&h);
  printf("\nEnter M elements :\n");
  for(int i=0;i< m;i++)
  {
    for(int j=0;j< n;j++)
    {
      scanf("%d",&M[i][j]);
    }
  }
  clock_t begin = clock();

  if (argc == 1)
    printf("\nNo Extra command line argument passed. Please run with argument 1 for Task1, 2 for Task2, 3 for Task3, 4 for Task4, and 5 for bonus Task\n");
  if (atoi(argv[1]) == 1) {

    Task1_ALG1(M, m, n, h);

  } else if (atoi(argv[1]) == 2){

    Task2_ALG1(M, m, n, h);
  
  } else if (atoi(argv[1]) == 3) {

    Task3_ALG2(M, m, n, h);
  
  } else if (atoi(argv[1]) == 4) {

    Task4_ALG3(M, m, n, h);
  
  } else if (atoi(argv[1]) == 5) {

    Task5_bonus(M, m, n, h);
  
  }
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  return 0;
}

