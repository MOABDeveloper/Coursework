#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
    //Define the variables to store the user input.
    int input1,input2,a1,a2,b1,b2;

    //Store the first and second value of user input. 
    input1 = atoi((argv[1]));
    input2 = atoi((argv[2]));

    //Check if the inputs are within range. 
    if ((input1 < 1000 || input1 > 9999) || (input2 < 1000 || input2 > 9999))
    {
        printf("Input not 4 valid digits, try again!\n");
        return 1;
    }

    printf("Your integers are %d and %d\n",input1,input2);


    //Use integar division/modulo to split the fist two numbers off asuming 4 digits
    a1 = input1 / 100;
    a2 = input1 % 100;

    //Use integar division/modulo to split the fist two numbers off of input 2 (asuming 4 digits)
    b1 = input2 / 100;
    b2 = input2 % 100;

    //Establish two pipes (Parent -> Child and Child -> Parent)
    int child_to_parent[2];
    int parent_to_child[2];

    //Check if making pipes was successful
    if (pipe(child_to_parent) == -1 || pipe(parent_to_child) == -1) 
    {
        perror("Pipe creation failed");
        return 1;
    }


//////////////////////////////////Forking//////////////////////////////////////

    //Reminder;
    //array[0] - read
    //array[1] - write
    int id = fork();
    if (id < 0) {
        perror("Fork failed");
        return 1;
    }

    printf("Parent (PID %d): created child (PID %d)\n\n",getpid(),id);
//////////////////////////////////Forking Done///////////////////////////////


    //Within the parent process
    if (id != 0)
    {
        //Close as a precaution because we are not using it 
        close(child_to_parent[1]);

//////////////////////////////////Calculating X////////////////////////////////
        printf("###\n# Calculating X\n###\n");
        int X;

        //Write both a1 and b1 to the pipe and close it.
        write(parent_to_child[1],&a1,sizeof(int));
        write(parent_to_child[1],&b1,sizeof(int));

        //Required print statements
        printf("Parent (PID %d): Sending %d to child\n",getpid(),a1);
        printf("Parent (PID %d): Sending %d to child\n",getpid(),b1);
        
        //Read the result from the child, leave pipe open beceause we need it.
        read(child_to_parent[0],&X, sizeof(int));

        //Required print statements
        printf("Parent (PID %d): Received %d from child\n",getpid(),X);


        //We can hard code 10,000 since we are assuming n=4
        //I know this is bad coding practice. 
        X = X * 10000;
        
///////////////////////////Finished Calculating X//////////////////////////
printf("\n");
//////////////////////////////////Calculating Y////////////////////////////////
        printf("###\n# Calculating Y\n###\n");
        int Y,tempC;

        //Write both a2 and b1 to the pipe and close it.
        write(parent_to_child[1],&a2,sizeof(int));
        write(parent_to_child[1],&b1,sizeof(int));

        //Required print statements
        printf("Parent (PID %d): Sending %d to child\n",getpid(),a2);
        printf("Parent (PID %d): Sending %d to child\n",getpid(),b1);

        //Read the result from the child,leave pipe open beceause we need it.
        read(child_to_parent[0],&Y, sizeof(int));

        //Required print statements
        printf("Parent (PID %d): Received %d from child\n",getpid(),Y);

        //Write both a1 and b2 to the pipe, leave it open we need it.
        write(parent_to_child[1],&a1,sizeof(int));
        write(parent_to_child[1],&b2,sizeof(int));

        //Required print statements
        printf("Parent (PID %d): Sending %d to child\n",getpid(),a1);
        printf("Parent (PID %d): Sending %d to child\n",getpid(),b2);

        //Read the result from the child.
        read(child_to_parent[0],&tempC, sizeof(int));

        //Required print statements
        printf("Parent (PID %d): Received %d from child\n",getpid(),tempC);

        Y += tempC;
        Y *= 100;
///////////////////////////Finished Calculating Y/////////////////////////////
printf("\n");
//////////////////////////////////Calculating Z////////////////////////////////
        printf("###\n# Calculating Z\n###\n");
        int Z;

        //Write both a2 and b2 to the pipe and close it.
        write(parent_to_child[1],&a2,sizeof(int));
        write(parent_to_child[1],&b2,sizeof(int));
        close(parent_to_child[1]); 

        //Required print statements
        printf("Parent (PID %d): Sending %d to child\n",getpid(),a2);
        printf("Parent (PID %d): Sending %d to child\n",getpid(),b2);

        //Read the result from the child.
        read(child_to_parent[0],&Z, sizeof(int));

        //Required print statements
        printf("Parent (PID %d): Received %d from child\n",getpid(),Z);
        close(child_to_parent[0]);

        //Z is already calculated since 10^0  = 1
/////////////////////////////Finished Calculating Z////////////////////////////////
printf("\n");
//////////////////////////////////Final Result////////////////////////////////////
        int final_sum = X + Y + Z;
        printf("%d * %d == %d + %d + %d == %d\n",input1,input2,X,Y,Z,final_sum);



    }
    else if (id == 0)
    {
        //Within the child process
        //Close as a precaution because we are not using it 
        close(parent_to_child[1]);

        //Define some temp variables to pass information
        int tempa1, tempb1, tempa2, tempb2, A, B, C, D;

//////////////////////////////////Calculating A////////////////////////////////

        //Read a1 and b1 from the parent process and close the pipe.
        read(parent_to_child[0],&tempa1, sizeof(int));
        read(parent_to_child[0],&tempb1, sizeof(int));
        //close(parent_to_child[0]);

        //Required print statements
        printf("Child (PID %d): Received %d from parent\n",getpid(),tempa1);
        printf("Child (PID %d): Received %d from parent\n",getpid(),tempb1);


        //Calculate the multiple of a and b 1 and pass it back up to the parent.
        A = tempa1 * tempb1;
        write(child_to_parent[1],&A, sizeof(int));

        //Required print statement
        printf("Child (PID %d): Sending %d to parent\n",getpid(),A);

/////////////////////////////Finished Calculating A////////////////////////////

//////////////////////////////////Calculating B+C////////////////////////////////

        //Read a2 and b1 from the parent process and close the pipe.
        read(parent_to_child[0],&tempa2, sizeof(int));
        read(parent_to_child[0],&tempb1, sizeof(int));

        //Required print statements
        printf("Child (PID %d): Received %d from parent\n",getpid(),tempa2);
        printf("Child (PID %d): Received %d from parent\n",getpid(),tempb1);

        //Calculate the multiple of a2 and b1 and pass it back up to the parent.
        B = tempa2 * tempb1;
        write(child_to_parent[1],&B, sizeof(int));

        //Required print statement
        printf("Child (PID %d): Sending %d to parent\n",getpid(),B);


        read(parent_to_child[0],&tempa1, sizeof(int));
        read(parent_to_child[0],&tempb2, sizeof(int));


        //Required print statements
        printf("Child (PID %d): Received %d from parent\n",getpid(),tempa1);
        printf("Child (PID %d): Received %d from parent\n",getpid(),tempb2);

        //Calculate the multiple of a1 and b2 and pass it back up to the parent.
        C = tempa1 * tempb2;
        write(child_to_parent[1],&C, sizeof(int));
        

        //Required print statement
        printf("Child (PID %d): Sending %d to parent\n",getpid(),C);
///////////////////////////Finished Calculating B+C//////////////////////////

//////////////////////////////////Calculating D////////////////////////////////

        // Read a2 and b2 from the parent process.
        read(parent_to_child[0],&tempa2, sizeof(int));
        read(parent_to_child[0],&tempb2, sizeof(int));

        //Close the pipe now that we are done reading.
        close(parent_to_child[0]);

        //Required print statements
        printf("Child (PID %d): Received %d from parent\n",getpid(),tempa2);
        printf("Child (PID %d): Received %d from parent\n",getpid(),tempb2);

        //Calculate the multiple of a2 and b2 and pass it back up to the parent.
        D = tempa2 * tempb2;
        write(child_to_parent[1],&D, sizeof(int));

        //Required print statement
        printf("Child (PID %d): Sending %d to parent\n",getpid(),D);
        
        //Close the pipe now that we are done writing.
        close(child_to_parent[1]);
/////////////////////////////Finished Calculating D////////////////////////////
        exit(0);
    }
    else 
    {
        printf("Yeah, you should not be here!, something has gone terribly wrong\n");
        return -1;
    }

    return 0;
}