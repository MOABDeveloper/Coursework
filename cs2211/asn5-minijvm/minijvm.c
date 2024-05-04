#include <stdio.h>
#include <stdlib.h>
#include "./include/minijvm.h"
#include "./include/stack.h"
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>


char* jvm_read(const char* filename)
{
    // Allocate memory for the complete filename
    char* f_name = malloc(strlen(filename) + strlen(".mclass") + 1);
    //Make sure the allocation was sucessful.
    if (f_name == NULL)
    {
     	printf("Filename memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Connect the complete filename by appending ".mclass" to the given filename.
    strcpy(f_name, filename);
    strcat(f_name, ".mclass");

    // Use stat to check if the file exists
    struct stat statbuf;
    //If the file does not exists we exit with error, print message, and free the memory allocation. 
    if (stat(f_name, &statbuf) != 0)
    {
     	printf("File \'%s\' not found\n",f_name);
        free(f_name);
        exit(EXIT_FAILURE);
    }

    // Allocate memory for the bytecode.
    char* bytecode = malloc(MAX_CLASS_SIZE);
    //If there was an issue with memory allocation 
    if (bytecode == NULL)
    {
        //print and error and exit while freeing the memory for file name. 
     	printf("Memory allocation failed\n");
        free(f_name);
        exit(EXIT_FAILURE);
    }

    //Open the file
    FILE* file_ptr = fopen(f_name, "rb");
    //If the file fails to open
    if (file_ptr == NULL)
    {
        //print and error and exit while freeing the memory for file name and bytecode
     	printf("File opening failed\n");
        free(bytecode);
        free(f_name);
        exit(EXIT_FAILURE);
    }

    // Read the file's contents into the bytecode.
    size_t i = 0;
    while(i < MAX_CLASS_SIZE && fread(&bytecode[i], 1, 1, file_ptr) == 1)
    {
     	i++;
    }

    //Close the file and free the memory
    fclose(file_ptr);
    free(f_name);

    //return a pointer to the bytecode. 
    return bytecode;
}


minijvm* jvm_init(const char* filename)
{

    //Dynamically allocated the memory for a jvm
    minijvm* jvm = (minijvm*)malloc(sizeof(minijvm));
    //If there was an issue with memory allocation 
    if (jvm == NULL)
    {
        //We print an error and exit. 
     	printf("JVM Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    //set the bytecode the jvm to point to the code
    jvm->bytecode = jvm_read(filename);
    //Set the program count to the first item in bytecode
    jvm->pc = jvm->bytecode;
    //Initalize the stack for the jvm
    jvm->operands = stack_create();

    //If there is issues with creating the stack 
    if (jvm->operands == NULL)
    {
        //print an error message, free memory and exit with error. 
     	printf("Failed to create a stack\n");
        free(jvm->bytecode);
        free(jvm);
        exit(EXIT_FAILURE);
    }

    //Intialize the values of the local variables to zero.
    for (int i = 0; i < 10; i++)
    {
     	jvm->locals[i] = 0;
    }

    // Set the initial return value
    jvm->return_value = 0;

    return jvm;
}

void jvm_free(minijvm* jvm)
{
    //If the jvm exists 
    if (jvm != NULL)
    {
     	// Free the bytecode array if it has been allocated
        if (jvm->bytecode != NULL)
        {
            free(jvm->bytecode);
            jvm->bytecode = NULL; // Good practice to set the pointer to NULL after freeing
        }

	// Free the operand stack that has been allocated
        if (jvm->operands != NULL)
        {
            stack_free(jvm->operands);
            jvm->operands = NULL; // Set to NULL after freeing
        }

	//Free the struct itself
        free(jvm);
        jvm = NULL; // Set the original pointer to NULL
    }
}

/////////////////////////// Helper functions for bytecodes ///////////////////////////

void iadd(minijvm* jvm)
{
    int value1, value2;
    //If the stack is empty we print error message and exit with fault 1.
    if (!stack_pop(jvm->operands, &value2) || !stack_pop(jvm->operands, &value1))
    {
     	jvm->return_value =1;
        printf("Add Error, not enought values on stack\n");
        return;
    }
    //Push the result of the addition onto the stack
    stack_push(jvm->operands, value1 + value2);
}

void iprint(minijvm* jvm)
{
    int value;
    //If the stack is empty we print error message and exit with fault 1.
    if (!stack_peek(jvm->operands, &value))
    {
     	printf("Print Error, stack Empty\n");
        jvm->return_value =1;
        return;
    }
    //Print the top of the stack without popping
    printf("%d\n", value);
}

void imul(minijvm* jvm)
{
    int value1,value2;
    //If the stack is empty we print error message and exit with fault 1.
    if(!stack_pop(jvm->operands, &value1) || !stack_pop(jvm->operands, &value2))
    {
     	jvm->return_value =1;
        printf("Multiplication Error, not enought values on stack\n");
        return;
    }
    //Push the result of the multiplication onto the stack 
    stack_push(jvm->operands, value1 * value2);
}

void isub(minijvm* jvm)
{
    int value1, value2;
    //If the stack is empty we print error message and exit with fault 1.
    if(!stack_pop(jvm->operands, &value2) || !stack_pop(jvm->operands, &value1))
    {
     	jvm->return_value =1;
        printf("Sub Error, not enought values on stack\n");
        return;
    }
    //Push the result of the subatraction onto the stack 
    stack_push(jvm->operands, value1 - value2);
}

void idiv(minijvm* jvm)
{
    int value1, value2,ans;
    //If the stack is empty or divide by zero we print error message and exit with fault 1
    if(!stack_pop(jvm->operands, &value2) || !stack_pop(jvm->operands, &value1) || value2 == 0)
    {
     	jvm->return_value =1;
        printf("Divsion by Zero\n");
        return;
    }
    //Push the result of the multiplication onto the stack 
    stack_push(jvm->operands,value1 / value2);
}

void ipop(minijvm* jvm)
{
    int popped_value;
    //If the stack is empty we print error message and exit with fault 1.
    if(!stack_pop(jvm->operands,&popped_value))
    {
     	jvm->return_value =1;
        printf("Pop Error, not enough values on stack\n");
        return;
    }
}

//Push zero onto the stack 
void iconst_0(minijvm* jvm)
{
    stack_push(jvm->operands,0);
}

void idup(minijvm* jvm)
{
    int top;
    //If stack empty print and exit with error
    if(!stack_peek(jvm->operands,&top))
    {
     	jvm->return_value =1;
        printf("Duplicaton Error, not enough values on stack\n");
       	return;
    }
    //Push the duplicate onto the stack 
    stack_push(jvm->operands,top);
}

void irem(minijvm* jvm)
{
    int value1, value2,remainder;
    //If stack empty print and exit with error
    if(!stack_pop(jvm->operands, &value2) || !stack_pop(jvm->operands, &value1) || value2 ==0)
    {
     	jvm->return_value =1;
        printf("Division by Zero\n");
        return;
    }
    //Push the remainder of the integar divison onto the stack. 
    stack_push(jvm->operands, value1 % value2);
}

void ishr(minijvm* jvm)
{
    int value1, value2;
    //If stack empty print and exit with error or divsion by zero
    if(!stack_pop(jvm->operands, &value2) || !stack_pop(jvm->operands, &value1))
    {
     	jvm->return_value =1;
        printf("Shift Error, not enought values on stack\n");
        return;
    }
    stack_push(jvm->operands, value1 >> value2);
}

void bipush(minijvm* jvm)
{
    char value = *jvm->pc++; // Increment pc after getting the value
    stack_push(jvm->operands, (int)value); // Cast to int and push onto the stack
}

void iload(minijvm* jvm)
{
    //Get the next value in the bytecode
    int n = *jvm->pc++;
    //Push the jvm locals [at the bytecode value] onto the stack
    stack_push(jvm->operands, jvm->locals[n]);
}

void istore(minijvm* jvm)
{
    int value, location;
    //If stack empty print and exit with error
    if(!stack_pop(jvm->operands,&value))
    {
     	jvm->return_value =1;
        printf("Store Error\n");
        return;
    }
    //Get the local variable index from the bytecode
    location = *jvm->pc++;
    //Store the top of the stack at  locals index location.
    jvm->locals[location] = value;
}

void iinc(minijvm* jvm)
{
    int location, inc;
    //Get the next bytecode value
    location = *jvm->pc++;
    //Get increment value
    inc = *jvm->pc++;
    //If stack empty print and exit with error
    if(location>=10)
    {
     	printf("iinc Error\n");
        jvm->return_value = 1;
        return;
    }
    //increment the loaction in locals by specified amount
    jvm->locals[location] += inc;
}

void ifeq(minijvm* jvm) {
    int value;
    //If the stack is empty we print error message and return error 
    if (!stack_pop(jvm->operands, &value)) {
        fprintf(stderr, "Ifeq Error: Stack empty\n");
        jvm->return_value = 1;
        return;
    }

    //If the value on the top of the stack is 0
    if (value == 0) {
        //Get the next 2 bytecodes
        unsigned char offset1 = *jvm->pc++;
        unsigned char offset2 = *jvm->pc++;
        //Store them as 16-bit ints
        //Shift the first offset 8 to the left and combine the two offsets using the OR operator
        int16_t offset = (int16_t)((offset1 << 8) | offset2);

        // If the offset is larger tha the largest 2s compliment positive possible  number for 16bits
        //That means its negative
        if (offset > 0x7FFF) 
        {
            //Convert the offset if its negative 
            offset -= 0x10000;
        }

        // Branch by the offset accounting for the original pc, and the two increments above.
        jvm->pc += offset - 3;
    }
}

void go_to(minijvm* jvm) 
{
    //Get the next 2 bytecodes
    unsigned char offset1 = *jvm->pc++;
    unsigned char offset2 = *jvm->pc++;
    //Store them as 16-bit ints
    //Shift the first offset 8 to the left and combine the two offsets using the OR operator
    int16_t offset = (int16_t)((offset1 << 8) | offset2);

    // If the offset is larger tha the largest 2s compliment positive number for 16bits
    //That means its negative
    if (offset > 0x7FFF) 
    {
        //Convert the offset if its negative 
        offset -= 0x10000;
    }

    // Branch by the offset accounting for the original pc, and the two increments above.
    jvm->pc += offset - 3;
}

/////////////////////////// End of Helper functions ///////////////////////////

void jvm_run(minijvm* jvm)
{
    //specify our running condition
    bool running = true;
    while (running)
    {
     	unsigned char instruction = (unsigned char)*jvm->pc++; // Get next bytecode and increment pc
        //Based on the instruction we find and execute the corrisponding command
        switch (instruction)
        {
            case INST_BIPUSH:
                bipush(jvm);
                break;
            case INST_IADD:
                iadd(jvm);
                break;
            case INST_PRINT:
                iprint(jvm);
                break;
            case INST_RETURN:
                jvm->return_value =0;
                running = false;
                break;
            case INST_IMUL:
                imul(jvm);
                break;
            case INST_IDIV:
                idiv(jvm);
                break;
            case INST_ISUB:
                isub(jvm);
                break;
            case INST_POP:
                ipop(jvm);
                break;
            case INST_ICONST0:
                iconst_0(jvm);
                break;
            case INST_DUP:
                idup(jvm);
                break;
            case INST_IREM:
                irem(jvm);
                break;
            case INST_ISHR:
                ishr(jvm);
                break;
            case INST_ILOAD:
                iload(jvm);
                break;
            case INST_ISTORE:
                istore(jvm);
                break;
            case INST_IINC:
                iinc(jvm);
                break;
	    case INST_IFEQ:
		ifeq(jvm);
		break;
	    case 0xa7:
		go_to(jvm);
		break;
            default:
                break;
        }
         // Check for errors set by helper functions
        if (jvm->return_value != 0)
        {
            //End loop if we have an error.
            running = false;
        }

    }
}

int main(int argc, char** argv) {
    // Check for the correct number of arguments
    if (argc != 2) {
        printf("Usage: mjvm FILENAME\n");
        return 1; // Return an error code
    }

    // Initialize MiniJVM with the provided filename
    minijvm* jvm = jvm_init(argv[1]);
    if (jvm == NULL) {
        // jvm_init will handle its own errors and exit, so if we're here, it's an error
        return 1;
    }

    // Run the program
    jvm_run(jvm);

    // The return_value of the jvm structure indicates if the program finished correctly
    int returnValue = jvm->return_value;

    // Clean up
    jvm_free(jvm);

    // Return the return_value at the end of the program running. 
    return returnValue;
}
