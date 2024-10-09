#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This is an array of register mnemonics in y86
const char *register_names[] =
    {
        "%eax",
        "%ecx",
        "%edx",
        "%ebx",
        "%esp",
        "%ebp",
        "%esi",
        "%edi",
        "UNKNOWN_REGISTER"};

// Array that stores the hexadecimal code for each instruction
const int opCodesHex[27] = {0x00,0x10,0x90,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x60,
    0x61,0x62,0x63,0xA0, 0xB0, 0x30,0x40,0x50,0x70,0x71,0x72, 0x73, 0x74, 0x75,
    0x76,0x80};

// Array that stores instruction name for each instruction
const char *opCodesString[27] = {"halt","nop","ret","rrmovl", "cmovle", "cmovl", "cmove", "cmovne", "cmovge", "cmovg", "addl", "subl", "andl", "xorl", "pushl", "popl", "irmovl", "rmmovl", "mrmovl", "jmp", "jle", "jl", "je", "jne", "jge", "jg", "call"};


int convertStrToByteCode(const char *str, unsigned char inst[], int size);

int main(int argc, char **argv)
{
  FILE *pFile = NULL;

  char buffer[15];

  if (argc < 2)
  {
    pFile = fopen("./test1.txt", "r");
  }
  else
  {
    pFile = fopen(argv[1], "r");
  }

  if (pFile == NULL)
  {
    printf("Error open test file, please make sure they exist.\n");

    return 0;
  }

  while (fgets(buffer, 15, pFile) && strlen(buffer) > 1)
  {
    //This unsigned char array stores an instruction read from the file
    //As the largest y86 instruction is 6 bytes, there are 6 unsigned char in the array where
    //each represents a byte.
    unsigned char instruction[6] = {0, 0, 0, 0, 0, 0};
    convertStrToByteCode(buffer, instruction, 6);
    
    int i = 0;
    int found = 0;
    int firstReg, secReg;
    while (instruction[0] != opCodesHex[i]) {
      i++;
    }
    if (instruction[0] == opCodesHex[i]) {
      printf("%s ", opCodesString[i]);
      found = i;
    }
    else {
      printf("TODO: undisassembled opcode. The first byte of the instruction "
      "is 0x%X\n",instruction[0]);
      }
    
    // Checking for instruction type and printing accordingly
    
    if (found >= 3 && found <= 13) {
      // Selecting the lower 4 bits and shifting by 4
       int firstReg = (instruction[1] >> 4);
       int secReg = instruction[1] & 0xF;
       printf("%s %s ", register_names[firstReg], register_names[secReg]);
    }
    else if (found == 14 || found == 15) {
       int firstReg = (instruction[1] >> 4);
       printf("%s ", register_names[firstReg]);
    }
    else if (found == 16) {
      int secReg = instruction[1] & 0xF;
      printf("$%d, %s ",*(int*)&instruction[2] ,register_names[secReg]);
    }
    else if (found == 17) {
      int firstReg = (instruction[1] >> 4);
      int secReg = instruction[1] & 0xF;
      printf("%s, %d(%s) ",register_names[firstReg] ,*(int*)&instruction[2] ,register_names[secReg]);
    }
    else if (found == 18) {
      int firstReg = (instruction[1] >> 4);
      int secReg = instruction[1] & 0xF;
      printf("%d(%s), %s ",*(int*)&instruction[2] ,register_names[secReg] ,register_names[firstReg]);
    }
    else if (found >= 19 && found <= 27) {
      printf("%d",*(int*)&instruction[1]);
    }
    
    printf("\n");
}
    // 
    fclose(pFile);

    return 0;
}

int convertStrToByteCode(const char *str, unsigned char inst[], int size)
{
  int numHexDigits = 0;
  char *endstr;
  //Each instruction should consist of at most 12 hex digits
  numHexDigits = strlen(str) - 1;
  //Convert the string to integer, N.B. this integer is in decimal
  long long value = strtol(str, &endstr, 16);

  int numBytes = numHexDigits >> 1;
  int byteCount = numHexDigits >> 1;

  while (byteCount > 0)
  {
    unsigned long long mask = 0xFF;
    unsigned long shift = (numBytes - byteCount) << 3;

    inst[byteCount - 1] = (value & (mask << shift)) >> shift;
    byteCount--;
  }

  //Return the size of the instruction in bytes
  return numHexDigits >> 1;
}