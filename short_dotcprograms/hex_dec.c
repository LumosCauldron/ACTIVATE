#include <stdio.h>
#include <math.h>
#include <string.h>

int htoi(char hex[], int length) {
  int result = 0;
  char conversion;
  if (hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X')) {
    hex += 2;
    length -= 2;
  }

  if (length > 1) result += htoi(hex+1, length-1);

  switch (hex[0]) {
    case '0' ... '9' : conversion = '0'; break;
    case 'a' ... 'f' : conversion = 'a'-10; break;
    case 'A' ... 'F' : conversion = 'A'-10; break;
    default: break;
  }   

  return (result += (hex[0]-conversion)*(pow(16, length-1)));
}

int main(int argc, char* argv[]) {
  if (argc > 1) printf("Result is: %d\n", htoi(argv[1], strlen(argv[1])));
  else return -1;
  return 0;
}

