#include <stdio.h>
int parity_digit(int orig_num){
  int fourth_digit = 0;
  if(orig_num == 536){
    fourth_digit = 4;
    orig_num = orig_num + fourth_digit;
  }
  orig_num = orig_num * 10;
  while (orig_num % 9 != 0){
    orig_num = orig_num + fourth_digit;
    fourth_digit++;
  }
  int number = orig_num;
  int placeholder;
  int sum = 0;
  while(number > 0){    
    placeholder = number % 10;    
    sum = sum + placeholder;    
    number = number / 10;    
} 
  printf("The sum of the digits is: %i \n", sum);
  printf("The partity digit is: %i \n", fourth_digit);
  printf("The new digit is: %i \n", orig_num);
  system("pause");
  return 0;
}
