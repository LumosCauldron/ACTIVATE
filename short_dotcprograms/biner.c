#include "../write.h"
#include <math.h>

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

char asciihexbyte_to_charbyte(Bytes* hexbyte)
{
	return (char)htoi(hexbyte->array, hexbyte->len);
}

int main(int argc, char** argv)
{
	if (argc < 2)
		THROW("No input file.");
	FILE* in = FOPEN(argv[1], "r");
	FILE* out = FOPEN("firmware.bin", "w+");
	Bytes* ptr = NULLPTR;
	register char bytetowrite = 0;
	do
	{
		ptr = readword(in, JUMPWHITE);
		if (!ptr)
			break;
		free_bytes(&ptr);
		
		ptr = readword(in, JUMPWHITE);
		if (!ptr)
			break;
		fputc((unsigned char)asciihexbyte_to_charbyte(ptr), out);
		free_bytes(&ptr);
		ptr = readword(in, JUMPWHITE);
		if (!ptr)
			break;
		fputc((unsigned char)asciihexbyte_to_charbyte(ptr), out);
		free_bytes(&ptr);
		ptr = readword(in, JUMPWHITE);
		if (!ptr)
			break;
		fputc((unsigned char)asciihexbyte_to_charbyte(ptr), out);
		free_bytes(&ptr);
		ptr = readword(in, JUMPWHITE);
		if (!ptr)
			break;
		fputc((unsigned char)asciihexbyte_to_charbyte(ptr), out);
		free_bytes(&ptr);
		ptr = readword(in, JUMPWHITE);
		if (!ptr)
			break;
		fputc((unsigned char)asciihexbyte_to_charbyte(ptr), out);
		free_bytes(&ptr);
		ptr = readword(in, JUMPWHITE);
		if (!ptr)
			break;
		fputc((unsigned char)asciihexbyte_to_charbyte(ptr), out);
		free_bytes(&ptr);
		ptr = readword(in, JUMPWHITE);
		if (!ptr)
			break;
		fputc((unsigned char)asciihexbyte_to_charbyte(ptr), out);
		free_bytes(&ptr);
		ptr = readword(in, JUMPWHITE);
		if (!ptr)
			break;
		fputc((unsigned char)asciihexbyte_to_charbyte(ptr), out);
		free_bytes(&ptr);
		ptr = readword(in, JUMPWHITE);
		if (!ptr)
			break;
		fputc((unsigned char)asciihexbyte_to_charbyte(ptr), out);
		free_bytes(&ptr);
		ptr = readword(in, JUMPWHITE);
		if (!ptr)
			break;
		fputc((unsigned char)asciihexbyte_to_charbyte(ptr), out);
		free_bytes(&ptr);
		ptr = readword(in, JUMPWHITE);
		if (!ptr)
			break;
		fputc((unsigned char)asciihexbyte_to_charbyte(ptr), out);
		free_bytes(&ptr);
		ptr = readword(in, JUMPWHITE);
		if (!ptr)
			break;
		fputc((unsigned char)asciihexbyte_to_charbyte(ptr), out);
		free_bytes(&ptr);
		ptr = readword(in, JUMPWHITE);
		if (!ptr)
			break;
		fputc((unsigned char)asciihexbyte_to_charbyte(ptr), out);
		free_bytes(&ptr);
		ptr = readword(in, JUMPWHITE);
		if (!ptr)
			break;
		fputc((unsigned char)asciihexbyte_to_charbyte(ptr), out);
		free_bytes(&ptr);
		ptr = readword(in, JUMPWHITE);
		if (!ptr)
			break;
		fputc((unsigned char)asciihexbyte_to_charbyte(ptr), out);
		free_bytes(&ptr);
		ptr = readword(in, JUMPWHITE);
		if (!ptr)
			break;
		fputc((unsigned char)asciihexbyte_to_charbyte(ptr), out);
		free_bytes(&ptr);
		
		set_to_nextline(in);
	} while (!feof(in));
	FCLOSE(in);
	FCLOSE(out);
}

