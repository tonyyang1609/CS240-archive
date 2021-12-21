/* Name, hw0.c, CS 24000, Fall 2018
 * Last updated August 16, 2018 
 */

/* Add any includes here */
#include <stdio.h>
#include "hw0.h"
/* Define compute_hailstone here */
int compute_hailstone(int startingNumber, int numberOfSteps) {
int bufferNumber=startingNumber;
int sum = 0;
if(startingNumber<=0) { 
return HAILSTONE_ERROR;
}
if(numberOfSteps<1) {
return HAILSTONE_ERROR;
}
g_hailstone_array[0]=startingNumber;
sum =sum+g_hailstone_array[0];
for(int i = 1; i < numberOfSteps; i++) {
  if(bufferNumber%2==0){
    bufferNumber=bufferNumber/2;
  }
  else{
    bufferNumber=bufferNumber*3+1;
  }
  g_hailstone_array [i]=bufferNumber;
  sum = sum + g_hailstone_array[i];
  } 
  return sum;
}
  
/* Define check_hailstone here */
int check_hailstone(int digit) {
  if(g_hailstone_array[0]<1){
    return HAILSTONE_ERROR;
  } 
  if(digit<1){
    return HAILSTONE_ERROR;
  }
  
  for(int i=1; i<digit; i++) {
    if(g_hailstone_array[i-1]%2==0) {
      if(g_hailstone_array[i]!=g_hailstone_array[i-1]/2) {
        return i;
      }
  } 
    else{
      if (g_hailstone_array[i]!=(g_hailstone_array[i-1]*3+1))
         return i;
        }
  }
return 0;
}
 
/* Remember, you don't need a main function!
 * it is provided by hw0_main.c or hw0_test.o
 */
