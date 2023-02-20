
#include <math.h>
#include<iostream>
#include<fstream>
#include <string.h>
#include <time.h>
#include <divsufsort.h>
using namespace std;
ifstream myfile;
int max(int a ,int b){
int maximum = (a > b) ? a : b ;
return maximum;
}

int main(){
clock_t start, end;
string content;

//   FILE * fp;
//     char line[100];
//     int size=0;
//     char *content= (char*)malloc(sizeof(char)*size);
//     fp = fopen("chm13.chrX_v0.7.fasta", "r");
//       if (fp ==NULL) {
//         printf("file can't be opened \n");
//     }
//  while (fgets(line, 100, fp))
//     {
//         // printf("%s",line);
//         if((char)line[0]=='>'){
//           continue;
//         }
//         // printf("%s",line);
//         size += strlen(line);
//         content = (char*)realloc(content, size * sizeof(char)); 
  
//         strncat(content,line,strlen(line)-1);
//     }
//     fclose(fp);
myfile.open("chm13.chrX_v0.7.fasta");

 if (myfile.is_open()){ 
      string line;
      int i=0;
      while(getline(myfile,line )){ 
        if(line[0]!='>'){
        content.append(line);
        }
      }   
     
 }
myfile.close();

int len = content.length();
start = clock();
  int *SA = (int *)malloc(len * sizeof(int));
  int *LCP_arr = (int *)malloc(len * sizeof(int));
  int *inv_suf = (int *)malloc(len * sizeof(int));

  // sort
  divsufsort((unsigned char *)content.c_str(), SA, len);


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
int *myArray = (int *)malloc(sizeof(int)*arr_size); 

 for (int i=0;i<len;i++){
  if(LCP_arr[i]>long_repeat){
    long_repeat = LCP_arr[i];
    free(myArray);
    arr_size=2;
    int *myArray = (int *)malloc(sizeof(int)*arr_size);
     myArray[arr_size-2]=SA[i];
     myArray[arr_size-1]=SA[i-1];
  }
  else if(LCP_arr[i]==long_repeat){
    arr_size++;
    myArray = (int *)realloc(myArray, arr_size * sizeof(int)); 
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


  return 0;

}