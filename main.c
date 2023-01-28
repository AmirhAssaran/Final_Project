#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LSIZ 128 
#define RSIZ 10 
#define MAX 100
 
int top = -1, stack[MAX];
int statusRegistersArray[8];

void parityChecker (int *array, unsigned int num) {
    int oneCounter = 1;
    while (num > 1) {
        if (num % 2 == 1) {
            oneCounter++;
        }
        num /= 2;
    }

    if (oneCounter % 2 == 1) {
        *(array + 0) =  1;
    }
    else {
        *(array + 0) = 0;
    }  
}

void zeroChecker (int *array, int num) {
    if (num == 0) {
        *(array + 1) = 1;
    }
    else {
        *(array + 1) = 0;
    }  
}

void signChecker (int *array, int num) {
    if (num < 0) {
        *(array + 2) = 1;
    }
    else {
        *(array + 2) = 0;
    }  
}

void overflowChecker (int *array, int num1, int num2) {
    int res = num1 + num2;
    if (num1 < 0 && num2 < 0 && res > 0) {
        *(array + 5) = 1;
    }
    else if (num1 > 0 && num2 > 0 && res < 0) {
        *(array + 5) = 1;
    }
    else {
       *(array + 5) = 0;
    }  
}

int sFinder(char str[1000]) {
    int n = strlen(str);
    int con = 0;
    for (int i = 0; i < n; i++) {
        if (str[i] == 'S') {
            con++;
        }
    }

    if (con > 1) {
        return 1; 
    }
    return 0;
}

void MOVBIT(int *array, int res, int num) {
   int intVal = *(array + num);
   *(array + res) = intVal; 
}

void MOVIMM(int *array, int res, int num) {
   *(array + res) = num; 
}

void ADD (int *array, int res, int reg1, int reg2) {
    *(array + res) = *(array + reg1) + *(array + reg2);
    parityChecker(statusRegistersArray, *(array + res));
    zeroChecker(statusRegistersArray, *(array + res));
    signChecker(statusRegistersArray, *(array + res));
    overflowChecker(statusRegistersArray, *(array + reg1), (array + reg2));
}

void ADDI (int *array, int res, int reg1, int num) {
    *(array + res) = *(array + reg1) + num;
    parityChecker(statusRegistersArray, *(array + res));
    zeroChecker(statusRegistersArray, *(array + res));
    signChecker(statusRegistersArray, *(array + res));
    overflowChecker(statusRegistersArray, *(array + reg1), num);
}

void SUB (int *array, int res, int reg1, int reg2) {
    *(array + res) = *(array + reg2) - *(array + reg1);
    parityChecker(statusRegistersArray, *(array + res));
    zeroChecker(statusRegistersArray, *(array + res));
    signChecker(statusRegistersArray, *(array + res));
    overflowChecker(statusRegistersArray, *(array + reg1), (array + reg2));
}

void SUBI (int *array, int res, int reg1, int num) {
    *(array + res) = *(array + reg1) - num;
    parityChecker(statusRegistersArray, *(array + res));
    zeroChecker(statusRegistersArray, *(array + res));
    signChecker(statusRegistersArray, *(array + res));
    overflowChecker(statusRegistersArray, *(array + reg1), num);
}

void AND (int *array, int res, int reg1, int reg2) {
    *(array + res) = *(array + reg1) & *(array + reg2);
    parityChecker(statusRegistersArray, *(array + res));
    zeroChecker(statusRegistersArray, *(array + res));
    signChecker(statusRegistersArray, *(array + res));
}

void ANDI (int *array, int res, int reg1, int num) {
    *(array + res) = *(array + reg1) & num;
    parityChecker(statusRegistersArray, *(array + res));
    zeroChecker(statusRegistersArray, *(array + res));
    signChecker(statusRegistersArray, *(array + res));
}

void OR (int *array, int res, int reg1, int reg2) {
    *(array + res) = *(array + reg1) | *(array + reg2);
    parityChecker(statusRegistersArray, *(array + res));
    zeroChecker(statusRegistersArray, *(array + res));
    signChecker(statusRegistersArray, *(array + res));
}

void ORI (int *array, int res, int reg1, int num) {
    *(array + res) = *(array + reg1) | num;
    parityChecker(statusRegistersArray, *(array + res));
    zeroChecker(statusRegistersArray, *(array + res));
    signChecker(statusRegistersArray, *(array + res));
}

void XOR (int *array, int res, int reg1, int reg2) {
    *(array + res) = *(array + reg1) ^ *(array + reg2);
    parityChecker(statusRegistersArray, *(array + res));
    zeroChecker(statusRegistersArray, *(array + res));
    signChecker(statusRegistersArray, *(array + res));
}

void XORI (int *array, int res, int reg1, int num) {
    *(array + res) = *(array + reg1) ^ num;
    parityChecker(statusRegistersArray, *(array + res));
    zeroChecker(statusRegistersArray, *(array + res));
    signChecker(statusRegistersArray, *(array + res));
}

void SWP (int *array, int num1, int num2) {
    int temp = *(array + num1);
    *(array + num1) = *(array + num2);
    *(array + num2) = temp;
}

void DUMP_REGS (int *array1, int *array2) {
    printf("\nRegisters are:\n");
    for (int i = 0; i < 32; i++) {
        printf("register['%2d'] => %d\n", i, *(array1 + i));
    }
    printf("\nStatus registers are:\n");
    for (int i = 0; i < 8; i++) {
        printf("Status Register['%2d'] => %d\n", i, *(array2 + i));
    }
}

void INPUT (int *array, int number) {
    *(array + 0) = number;
}

void MULL (int *array, int num1, int num2) {
    int res = *(array + num1) * *(array + num2);
    *(array + num1) = res / 16;
    *(array + num2) = res % 16;
    parityChecker(statusRegistersArray, *(array + num1));
    zeroChecker(statusRegistersArray, *(array + num1));
    signChecker(statusRegistersArray, *(array + num1));
    parityChecker(statusRegistersArray, *(array + num2));
    zeroChecker(statusRegistersArray, *(array + num2));
    signChecker(statusRegistersArray, *(array + num2));
    overflowChecker(statusRegistersArray, *(array + num1), (array + num2));
}

void DIV (int *array, int num1, int num2) {
    int khrjG = *(array + num1) / *(array + num2);
    int baghm = *(array + num1) % *(array + num2);
    *(array + num1) = khrjG;
    *(array + num2) = baghm;
    parityChecker(statusRegistersArray, *(array + num1));
    zeroChecker(statusRegistersArray, *(array + num1));
    signChecker(statusRegistersArray, *(array + num1));
    parityChecker(statusRegistersArray, *(array + num2));
    zeroChecker(statusRegistersArray, *(array + num2));
    signChecker(statusRegistersArray, *(array + num2));
}

int SKIE (int *array, int num1, int num2) {
    if (*(array + num1) == *(array + num2)) {
        return 1;
    }
    return 0;
}

void PUSH (int *array, int num) {
    int val = *(array + num);
    if(top == MAX - 1) {
        printf("\nStack is full!!\n");
    }
    else {
        top = top  +1;
        *(stack + top) = val;
    }
}

void POP (int *array, int num) {
    if(top == -1) {
        printf("\nStack is empty!!\n");
    }
    else {
        *(array + num) = *(stack + top);
        top = top - 1;
    }
}

int indxValidator(int num) {
    if (num < 0 || num > 31) {
        return 1;
    }
    return 0;
}

int main() {

   char fileArray[RSIZ][LSIZ];
   char fname[20];
   int i = 0, tot = 0;
   int file_exsit = 0;
   FILE *fptr = NULL; 
   printf("Input the filename to be opened : ");
   scanf("%s",fname);
   fptr = fopen(fname, "r");
   if (fptr == NULL) {
    printf("No file were found with the given name!\n");
   }
   else {
    while(fgets(fileArray[i], LSIZ, fptr)) {
        fileArray[i][strlen(fileArray[i])] = '\0';
        i++;
    }
    file_exsit = 1;
   }
   tot = i;

   char MovFuncName[20] = "MOV", swpFuncName[20] = "SWP", dmpFuncName[20] = "DUMP_REGS", inptFuncName[20] = "INPUT", outpFuncName[20] = "OUTPUT";
   char AddFuncName[20] = "ADD", AddiFuncName[20] = "ADDI", SubFuncName[20] = "SUB", SubiFuncName[20] = "SUBI", AndFuncName[20] = "AND", AndiFuncName[20] = "ANDI";
   char OrFuncName[20] = "OR",   OriFuncName[20] = "ORI", XorFuncName[20] = "XOR", XoriFuncName[20] = "XORI", extFuncName[20] = "EXIT";
   char JmpFuncName[20] = "JMP", fdmpFuncName[20] = "DUMP_REGS_F", mullFuncName[20] = "MULL", divFuncName[20] = "DIV", skieFuncName[20] = "SKIE";
   char pushFuncName[20] = "PUSH", popFuncName[20] = "POP";

   char funcName[100];
   int indx1, indx2, indx3;
   char extraArg[10000];
   int sscanfVal;

   int inptNum;
   int inpt_check = 0, outpt_check = 0;

   int registersArray[32];

   for (i = 0; i < tot; i++) {

    sscanf(fileArray[i], "%s", funcName);

    if (strcasecmp(funcName, AddFuncName) == 0) {
        sscanfVal = sscanf(fileArray[i], "%s S%d, S%d, S%d %s", funcName, &indx1, &indx2, &indx3, extraArg);
        if (sscanfVal != 4) {
            printf("(Add) Failed to execute the command: Invalid prefix, Not using a comma or too many arguments\n");
        }
        else if (indxValidator(indx1) || indxValidator(indx2) || indxValidator(indx3))  {
            printf("(Add) Failed to execute the command => Invalid register index. the index must be between 0 & 31\n");
        }
        else {
            ADD(registersArray, indx1, indx2, indx3);  
        } 
    }

    else if (strcasecmp(funcName, SubFuncName) == 0) {
        sscanfVal = sscanf(fileArray[i], "%s S%d, S%d, S%d %s", funcName, &indx1, &indx2, &indx3, extraArg);
        if (sscanfVal != 4) {
            printf("(Sub) Failed to execute the command: Invalid prefix, Not using a comma or too many arguments\n");
        }
        else if (indxValidator(indx1) || indxValidator(indx2) || indxValidator(indx3))  {
            printf("(Sub) Failed to execute the command => Invalid register index. the index must be between 0 & 31\n");
        }
        else {
            SUB(registersArray, indx1, indx2, indx3);  
        } 
    }

    else if (strcasecmp(funcName, AndFuncName) == 0) {
        sscanfVal = sscanf(fileArray[i], "%s S%d, S%d, S%d %s", funcName, &indx1, &indx2, &indx3, extraArg);
        if (sscanfVal != 4) {
            printf("(And) Failed to execute the command: Invalid prefix, Not using a comma or too many arguments\n");
        }
        else if (indxValidator(indx1) || indxValidator(indx2) || indxValidator(indx3))  {
            printf("(And) Failed to execute the command => Invalid register index. the index must be between 0 & 31\n");
        }
        else {
            AND(registersArray, indx1, indx2, indx3);  
        } 
    }

    else if (strcasecmp(funcName, OrFuncName) == 0) {
        sscanfVal = sscanf(fileArray[i], "%s S%d, S%d, S%d %s", funcName, &indx1, &indx2, &indx3, extraArg);
        if (sscanfVal != 4) {
            printf("(Or) Failed to execute the command: Invalid prefix, Not using a comma or too many arguments\n");
        }
        else if (indxValidator(indx1) || indxValidator(indx2) || indxValidator(indx3))  {
            printf("(Or) Failed to execute the command => Invalid register index. the index must be between 0 & 31\n");
        }
        else {
            OR(registersArray, indx1, indx2, indx3);  
        } 
    }

    else if (strcasecmp(funcName, XorFuncName) == 0) {
        sscanfVal = sscanf(fileArray[i], "%s S%d, S%d, S%d %s", funcName, &indx1, &indx2, &indx3, extraArg);
        if (sscanfVal != 4) {
            printf("(Xor) Failed to execute the command: Invalid prefix, Not using a comma or too many arguments\n");
        }
        else if (indxValidator(indx1) || indxValidator(indx2) || indxValidator(indx3))  {
            printf("(Xor) Failed to execute the command => Invalid register index. the index must be between 0 & 31\n");
        }
        else {
            XOR(registersArray, indx1, indx2, indx3);  
        } 
    }

    else if (strcasecmp(funcName, AddiFuncName) == 0) {
        sscanfVal = sscanf(fileArray[i], "%s S%d, S%d, %d %s", funcName, &indx1, &indx2, &indx3, extraArg);
        if (sscanfVal != 4) {
            printf("(Addi) Failed to execute the command: Invalid prefix, Not using a comma or too many arguments\n");
        }
        else if (indxValidator(indx1) || indxValidator(indx2))  {
            printf("(Addi) Failed to execute the command => Invalid register index. the index must be between 0 & 31\n");
        }
        else {
            ADDI(registersArray, indx1, indx2, indx3);  
        } 
    }

    else if (strcasecmp(funcName, SubiFuncName) == 0) {
        sscanfVal = sscanf(fileArray[i], "%s S%d, S%d, %d %s", funcName, &indx1, &indx2, &indx3, extraArg);
        if (sscanfVal != 4) {
            printf("(Subi) Failed to execute the command: Invalid prefix, Not using a comma or too many arguments\n");
        }
        else if (indxValidator(indx1) || indxValidator(indx2))  {
            printf("(Subi) Failed to execute the command => Invalid register index. the index must be between 0 & 31\n");
        }
        else {
            SUBI(registersArray, indx1, indx2, indx3);  
        } 
    }

    else if (strcasecmp(funcName, AndiFuncName) == 0) {
        sscanfVal = sscanf(fileArray[i], "%s S%d, S%d, %d %s", funcName, &indx1, &indx2, &indx3, extraArg);
        if (sscanfVal != 4) {
            printf("(Andi) Failed to execute the command: Invalid prefix, Not using a comma or too many arguments\n");
        }
        else if (indxValidator(indx1) || indxValidator(indx2))  {
            printf("(Andi) Failed to execute the command => Invalid register index. the index must be between 0 & 31\n");
        }
        else {
            ANDI(registersArray, indx1, indx2, indx3);  
        } 
    }

    else if (strcasecmp(funcName, OriFuncName) == 0) {
        sscanfVal = sscanf(fileArray[i], "%s S%d, S%d, %d %s", funcName, &indx1, &indx2, &indx3, extraArg);
        if (sscanfVal != 4) {
            printf("(Ori) Failed to execute the command: Invalid prefix, Not using a comma or too many arguments\n");
        }
        else if (indxValidator(indx1) || indxValidator(indx2))  {
            printf("(Ori) Failed to execute the command => Invalid register index. the index must be between 0 & 31\n");
        }
        else {
            ORI(registersArray, indx1, indx2, indx3);  
        } 
    }

    else if (strcasecmp(funcName, XoriFuncName) == 0) {
        sscanfVal = sscanf(fileArray[i], "%s S%d, S%d, %d %s", funcName, &indx1, &indx2, &indx3, extraArg);
        if (sscanfVal != 4) {
            printf("(Xori) Failed to execute the command: Invalid prefix, Not using a comma or too many arguments\n");
        }
        else if (indxValidator(indx1) || indxValidator(indx2))  {
            printf("(Xori) Failed to execute the command => Invalid register index. the index must be between 0 & 31\n");
        }
        else {
            XORI(registersArray, indx1, indx2, indx3);  
        } 
    }

    else if (strcasecmp(funcName, MovFuncName) == 0) {

        if ( sFinder(fileArray[i])) {
            sscanfVal = sscanf(fileArray[i], "%s S%d, S%d %s", funcName, &indx1, &indx2, extraArg);
            if (sscanfVal != 3) {
                printf("(Mov) Failed to execute the command: Invalid prefix, Not using a comma or too many arguments\n");
            }
            else if (indxValidator(indx1) || indxValidator(indx2))  {
                printf("(Mov) Failed to execute the command => Invalid register index. the index must be between 0 & 31\n");
            }
            else {
                MOVBIT(registersArray, indx1, indx2);  
            }    
        }

        else {
            sscanfVal = sscanf(fileArray[i], "%s S%d, %d %s", funcName, &indx1, &indx2, extraArg);
            if (sscanfVal != 3) {
            printf("(Mov) Failed to execute the command: Invalid prefix, Not using a comma or too many arguments\n");
            }
            else if (indxValidator(indx1))  {
                printf("(Mov) Failed to execute the command => Invalid register index. the index must be between 0 & 31\n");
            }
            else {
                MOVIMM(registersArray, indx1, indx2);  
            }
        }
    }

    else if (strcasecmp(funcName, swpFuncName) == 0) {
        sscanfVal = sscanf(fileArray[i], "%s S%d, S%d %s", funcName, &indx1, &indx2, extraArg);
        if (sscanfVal != 3) {
            printf("(Swp) Failed to execute the command: Invalid prefix, Not using a comma or too many arguments\n");
        }
        else if (indxValidator(indx1) || indxValidator(indx2))  {
            printf("(Swp) Failed to execute the command => Invalid register index. the index must be between 0 & 31\n");
        }
        else {
            SWP(registersArray, indx1, indx2);  
        } 
    }

    else if (strcasecmp(funcName, mullFuncName) == 0) {
        sscanfVal = sscanf(fileArray[i], "%s S%d, S%d %s", funcName, &indx1, &indx2, extraArg);
        if (sscanfVal != 3) {
            printf("(Mull) Failed to execute the command: Invalid prefix, Not using a comma or too many arguments\n");
        }
        else if (indxValidator(indx1) || indxValidator(indx2))  {
            printf("(Mull) Failed to execute the command => Invalid register index. the index must be between 0 & 31\n");
        }
        else {
            MULL(registersArray, indx1, indx2);  
        } 
    }

    else if (strcasecmp(funcName, divFuncName) == 0) {
        sscanfVal = sscanf(fileArray[i], "%s S%d, S%d %s", funcName, &indx1, &indx2, extraArg);
        if (sscanfVal != 3) {
            printf("(Div) Failed to execute the command: Invalid prefix, Not using a comma or too many arguments\n");
        }
        else if (indxValidator(indx1) || indxValidator(indx2))  {
            printf("(Div) Failed to execute the command => Invalid register index. the index must be between 0 & 31\n");
        }
        else {
            DIV(registersArray, indx1, indx2);  
        } 
    }

    else if (strcasecmp(funcName, skieFuncName) == 0) {
        sscanfVal = sscanf(fileArray[i], "%s S%d, S%d %s", funcName, &indx1, &indx2, extraArg);
        if (sscanfVal != 3) {
            printf("(Skie) Failed to execute the command: Invalid prefix, Not using a comma or too many arguments\n");
        }
        else if (indxValidator(indx1) || indxValidator(indx2))  {
            printf("(Skie) Failed to execute the command => Invalid register index. the index must be between 0 & 31\n");
        }
        else {
            if (SKIE(registersArray, indx1, indx2)) {
                i += 1;
            }  
        } 
    }

    else if (strcasecmp(funcName, JmpFuncName) == 0) {
        sscanfVal = sscanf(fileArray[i], "%s %d %s", funcName, &indx1, extraArg);
        if (indx1 > tot || indx1 < 1) {
            printf("(Jmp) Failed to execute the command: Invalid line number or too many arguments\n");
        }
        else if (sscanfVal != 2) {
            printf("(Jmp) Failed to execute the command => Invalid Command: Correct form => JMP n\n");  
        }
        else {
            i = indx1 - 2;  
        } 
    }

    else if (strcasecmp(funcName, inptFuncName) == 0) {
        printf("Please enter an integer to fill the 0 register: ");
        scanf("%d", &inptNum);
        INPUT (registersArray, inptNum);
    }

    else if (strcasecmp(funcName, outpFuncName) == 0) {
        outpt_check = 1;
    }

    else if (strcasecmp(funcName, dmpFuncName) == 0) {
        DUMP_REGS(registersArray, statusRegistersArray);
    }

    else if (strcasecmp(funcName, fdmpFuncName) == 0) {
        FILE *fp;
        fp = fopen ("regs.txt", "w");
        for (int i = 0; i < 32; i++) {
            fprintf(fp, "register bit[%2d] => %d\n", i, registersArray[i]);
        }
        for (int j = 0; j < 8; j++) {
            fprintf(fp, "register bit[%2d] => %d\n", i, statusRegistersArray[i]);
        }
        fclose (fp);
    }

    else if (strcasecmp(funcName, extFuncName) == 0) {
        break;
    }

    else if (strcasecmp(funcName, pushFuncName) == 0) {
        sscanfVal = sscanf(fileArray[i], "%s S%d %s", funcName, &indx1, extraArg);
        if (sscanfVal != 2) {
            printf("(Push) Failed to execute the command: Invalid prefix, Not using a comma or too many arguments\n");
        }
        else if (indxValidator(indx1))  {
            printf("(Push) Failed to execute the command => Invalid register index. the index must be between 0 & 31\n");
        }
        else {
            PUSH (registersArray, indx1);
        }
    }

    else if (strcasecmp(funcName, popFuncName) == 0) {
        sscanfVal = sscanf(fileArray[i], "%s S%d %s", funcName, &indx1, extraArg);
        if (sscanfVal != 2) {
            printf("(Pop) Failed to execute the command: Invalid prefix, Not using a comma or too many arguments\n");
        }
        else if (indxValidator(indx1))  {
            printf("(Pop) Failed to execute the command => Invalid register index. the index must be between 0 & 31\n");
        }
        else {
            POP (registersArray, indx1);
        }
    } 

    else {
        printf("Failed to execute the command: Invalid Command Name on line %d\n", i + 1);
    }

  }

  if (outpt_check == 1) {
    printf("The value of 0 register is: %d\n", *(registersArray + 0));
  }

  if (file_exsit == 1) {
    DUMP_REGS(registersArray, statusRegistersArray);
  } 
  
}

