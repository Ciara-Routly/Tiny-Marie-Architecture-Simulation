// Ciara Routly

// *** My program runs and compiles from the command line with one input file parameter. Use programname.c filename

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct inStruct{
    int opCode;
    int address;
}instructions;

int main(int argc, char* argv[]){
    
    int MAR = 0;
    int MDR = 0;
    // Program counter initialized to begin at 10
    int PC = 10;
    // Accumulator is empty = NULL
    int A = 0;
  
    instructions IR;
    instructions IM[100];

    // Data memory is empty to begin
    int mem[10] = {0,0,0,0,0,0,0,0,0};
    
    // Two arguments into command/terminal
    // 1 = programName.c 2 = fileName.txt
    FILE* FP1 = fopen(argv[1], "r");
 
    if (FP1 == NULL){
        // File could not be found
        printf("Couldn't open file. Exiting...\n");
        exit(0);
    }
    else {
        // File found successfully
        printf("\nOpening file.\n\n");
    }

    printf("Assembling Program... \n");
    printf("Program Assembled. \n\n");
    printf("Running: \n\n");
    
    int address2;
    
    // While loop to run as long as opCode is not end (7)
    while (IR.opCode != 7){
        int i = 0;
        // Scan in opCode and address of every line in file
        fscanf(FP1, "%d", &IM[i].opCode);
        
        fscanf(FP1, "%d", &IM[i].address);
        
        // If statement to handle instruction end
        if (IM[i].opCode == 7){
            
            printf("Instruction end has been requested \n\n");
            
            printf("Ending...\n\n");
            
            break;
        }
        
        // Will print after execution to detail the workings of the simulator
        printf("PC = %d | A = %d | MEM = [%d, %d, %d, %d, %d, %d, %d, %d, %d]\n\n", PC, A, mem[0],mem[1], mem[2], mem[3], mem[4], mem[5], mem[6], mem[7], mem[8]);
        
        // Some bookkeeping
        IR.opCode = IM[i].opCode;
        
        IR.address = IM[i].address;
        
        address2 = IM[i].address;
        
        // Fetch instruction begins here
        // Memory address register recieves the program counter
        MAR = PC;
        
        // Program counter/register is increased by one at each execution
        PC = PC + 1;
        
        // Memory data register recieves data content of memory location
        MDR = mem[MAR];
        
        // Init instruction by storing data in memory data register to the instruction register.address
        IR.address = MDR;
        
        // Counter variable to run through every line in file
        i++;
        
        switch (IR.opCode){
            case 1: // Load
                
                printf("Loading value stored in memory location %d to accumulator\n\n", address2);
                
                // Memory address register gets the instruction register.address value
                MAR = address2;
                
                // Memory data register recieves data content of memory location
                MDR = mem[MAR];
                
                // Accumulator register gets content of memory data register
                A = MDR;
                
                break;
                
            case 2: // Add
                
                printf("Adding value in memory location %d to accumulator\n\n", address2);
                
                // Memory address register receives data in instruction register.address
                MAR = address2;
                
                // Memory data register gets data content of memory location
                MDR = mem[MAR];
                
                // Value stored in accumulator + value stored into MDR goes into accumulator
                A = A + MDR;
                
                break;
                
            case 3: // Store
                
                printf("Storing accumulator to memory location %d\n\n", address2);
                
                // Memory address register gets data stored in instruction register.address
                MAR = address2;
                
                // Memory data register gets contents of A
                MDR = A;
                
                // Specific memory location gets contents of the memory data register
                mem[MAR] = MDR;
                
                break;
                
            case 4: // Subtract
                
                printf("Subtracting value in memory location %d from accumulator\n\n", address2);
                
                // Memory address register gets data from instruction register.address
                MAR = address2;
                
                // Memory data register gets data from specific memory location
                MDR = mem[MAR];
                
                // Value stored in memory data register is subtracted from the val in A, then stored in A
                A = A - MDR;
                
                break;
                
            case 5: // In
                
                // Prompts user to enter value. Value is stored in the accumulator
                printf("Input your value:\n");
                scanf("%d", &A);
                printf("\n");
                
                break;
                
            case 6: // Out
                
                // Accumulator is simply printed out to the screen
                printf("Outputting accumulator to screen \n");
                
                printf("%d\n\n", A);
                
                break;
                
            case 7: // End
                
                break;
                
            case 8: // Jump
                
                printf("Instruction jump has been requested. Processing...\n\n");
                
                // Program counter is set back to whatever data is in instruction register.address
                PC = address2;

                break;
                
            case 9: // Skipz
                
                printf("Instruction skip z has been requested. Processing...\n\n");
                
                // If the accumulator is 0, jump does not need to be executed.
                if (A==0){
                    
                    printf("The accumulator is 0. Not continuing to instruction jump.\n\n");
                    
                    PC = PC + 1;
                    
                }
                // If the accumulator is not 0, program must cont. and jump will be executed
                else {
                    
                    printf("The accumulator is not 0. Continuing to instruction jump.\n\n");
                    
                }
                
                break;
        }
    }
    // Final print statement to alert that program is finished running
    printf("Program Complete.\n\n");
    return 0;
}
