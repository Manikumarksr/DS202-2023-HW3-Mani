
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <divsufsort.h>
int max(int a ,int b){
int maximum = (a > b) ? a : b ;
return maximum;
}

int main(){
clock_t start, end;

// // read file
    FILE * fp;
    char * line =NULL;
    int size=0;
    char *content= (char*)malloc(sizeof(char)*size);
    size_t leng = 0;
    ssize_t read;
    fp = fopen("../chm13.chrX_v0.7.fasta", "r");

    int i=0;
    while ((read = getline(&line, &leng, fp)) != -1) {
      int temp =60;
        if(i==0){
          i++;
          continue;
        }
        size += read;

    content = (char*)realloc(content, size * sizeof(char)); 
        if(read<60){
          temp = read;
        }
        strncat(content,line,temp);
        // content = &content[strlen(content)];
        i++;
    }
    fclose(fp);


int len = strlen(content);
start = clock();
  int *SA = (int *)malloc(len * sizeof(int));
  int *LCP_arr = (int *)malloc(len * sizeof(int));
  int *inv_suf = (int *)malloc(len * sizeof(int));

  // sort
  divsufsort((unsigned char *)content, SA, len);


  // Compute insverve suffix array
for(int i = 0; i < len; ++i) {
inv_suf[SA[i]] =i;
}

// compute LCP Array

int a =0;
for(int i = 0; i < len; i++) {
  a = max(a-1,0);
  if (inv_suf[i]== 0){a= 0; continue;}
  int temp=SA[inv_suf[i]-1];
  while (i+a< len && temp+a < len && content[i+a] ==content[temp+a])a++;
  LCP_arr[inv_suf[i]] = a;

}

end = clock();
double duration = ((double)end - start)/CLOCKS_PER_SEC;

// for(int i = 0; i < len; i++) {
//     printf("SA[%2d] = %2d: ", i, SA[i]);
//     for(int j = SA[i]; j < len; ++j) {
//       printf("%c", content[j]);
//     }
//     printf("$\n");
//   }

// Finding the longest repeat and its positions
int long_repeat = 0;
int arr_size=2;
int *myArray = malloc(sizeof(int)*arr_size); 

 for (int i=0;i<len;i++){
  if(LCP_arr[i]>long_repeat){
    long_repeat = LCP_arr[i];
    free(myArray);
    arr_size=2;
    int *myArray = malloc(sizeof(int)*arr_size);
     myArray[arr_size-2]=SA[i];
     myArray[arr_size-1]=SA[i-1];
  }
  else if(LCP_arr[i]==long_repeat){
    arr_size++;
    myArray = realloc(myArray, arr_size * sizeof(int)); 
    myArray[arr_size-1]=SA[i];
  }
 }


printf("Length of the longest repeat is: %d\n",long_repeat);
printf("The positions of the longest repeat is:");
for(int i =0;i<arr_size;i++){
  printf("%d,",myArray[i]);
}
printf("\nThe time used for construction of SA and LCP array is : %fs\n",duration);

// deallocate
  free(SA);
  free(LCP_arr);
  free(inv_suf);
  free(myArray);
  free(content);

  return 0;

}
