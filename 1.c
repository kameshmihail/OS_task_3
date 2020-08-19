
#include<stdio.h>                                                                             
#include <stdlib.h>
#include<omp.h>

void ascendingSwap(int index1 , int index2 , int *ar) {
  if(ar[index2] < ar[index1])
  {
      int temp = ar[index2];
      ar[index2] = ar[index1];
      ar[index1] = temp;
  }
}
void decendingSwap(int index1 , int index2 , int *ar)                                           
{
  if(ar[index1] < ar[index2])
  {
      int temp = ar[index2];
      ar[index2] = ar[index1];
      ar[index1] = temp;
  }
}
    void bitonicSortFromBitonicSequence( int startIndex ,int lastIndex, int dir , int *ar )     
    {
        if(dir == 1)
        {
            int counter = 0;                                                                  
            int noOfElements = lastIndex - startIndex + 1;
            for(int j = noOfElements/2;j>0;j = j/2)
            {   counter =0;
                for(int i = startIndex ; i +j <= lastIndex ; i++)
                {
                        if(counter < j)
                        {
                            ascendingSwap(i,i+j,ar);
                            counter++;

                        }
                        else
                        {
                            counter =0;
                            i = i+ j-1;

                        }
                }
            }
        }
        else                                                                          
        {
            int counter = 0;
            int noOfElements = lastIndex - startIndex + 1;
            for(int j = noOfElements/2;j>0;j = j/2)
            {   counter =0;
                for(int i = startIndex ; i <= (lastIndex-j) ; i++)
                {
                        if(counter < j)
                        {
                            decendingSwap(i,i+j,ar);
                            counter++;

                        }
                        else
                        {
                            counter =0;
                            i = i+ j-1;

                        }
                }
            }
        }

    }
void bitonicSequenceGenerator(int startIndex , int lastIndex , int *ar)               
{
    int noOfElements = lastIndex - startIndex +1;
      for(int j = 2;j<=noOfElements;j = j*2)
            {
                #pragma omp parallel for                                                
                for(int i=0;i<noOfElements;i=i+j)
                {
                 if(((i/j)%2) ==0)                                                     
                 {
                     bitonicSortFromBitonicSequence(i,i+j-1,1,ar);
                 }
                 else
                 {
                     bitonicSortFromBitonicSequence(i,i+j-1,0,ar);
                 }
                }
            }
}
int main()                                                                                        
{
    omp_set_dynamic(0);                                                                          
    int maxNumberOfThreads = omp_get_num_procs();                                                
    omp_set_num_threads(maxNumberOfThreads);                                                     
    int n;
    printf("enter the number of elements to be sorted (number should be in the order of 2^n\n");  
    scanf("%d", &n);
    int *ar = (int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++)
    {
        scanf("%d", &ar[i]);
    }
    bitonicSequenceGenerator(0,n-1,ar);
    for(int i=0;i<n;i++)
    {
        printf("%d \n", ar[i] );
    }

}

