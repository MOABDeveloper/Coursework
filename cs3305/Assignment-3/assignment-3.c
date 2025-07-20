#include "stdio.h"
#include "stdlib.h"
#include <stdbool.h>
#include <pthread.h>

#define SIZE 9

int complete_result = 0;

//Define a struct to help us pass in more parameters to the threads.
typedef struct {
    // Row, Column, or Subgrid index
    int index;      
    // ThreadID
    int thread_num; 
    // Pointer to the grid 
    int (*grid)[SIZE]; 
} ThreadData;

//Define the funtions
void *check_row(void *threaddata);
void *check_subgrid(void *arg);
void *check_column(void *arg);

//TO be able to use a mutex lock to keep track of the final result.
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


int main(int argc, char const *argv[])
{
    //Read the file 
    FILE *sudoku = fopen(argv[1],"r");
 
    //Defines for 2d array to store the puzzle
    int ROW = 9;
    int COL = 9;
    int grid[ROW][COL];    

    //Store all the values int he 2d array. 
    for(int i = 0; i < ROW; i++)
    {
        for(int j = 0; j < COL; j++)
        {
            fscanf(sudoku, "%d", &grid[i][j]);
        }
    }
    //Close the file we opened.
    fclose(sudoku);

    pthread_t threads[27];
    int thread_count = 0;

    // Create subgrid threads
    for (int i = 0; i < SIZE; i++) {
        ThreadData *data = malloc(sizeof(ThreadData));
        data->index = i;
        data->thread_num =1 + i;
        data->grid = grid;
        pthread_create(&threads[thread_count++], NULL, check_subgrid, (void *)data);
    }

    // Create row threads
    for (int i = 0; i < SIZE; i++) {
        ThreadData *data = malloc(sizeof(ThreadData));
        data->index = i;
        data->thread_num = 10 + i;
        data->grid = grid;
        pthread_create(&threads[thread_count++], NULL, check_row, (void *)data);
    }

    // Create column threads
    for (int i = 0; i < SIZE; i++) {
        ThreadData *data = malloc(sizeof(ThreadData));
        data->index = i;
        data->thread_num = 19 + i;
        data->grid = grid;
        pthread_create(&threads[thread_count++], NULL, check_column, (void *)data);
    }

    // Wait for all threads to complete
    for (int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }

    //Print if the overall grid was valid.
    if(complete_result == 27)
    {
        printf("%s contains a valid sudoku\n",argv[1]);
    }
    else
    {
        printf("%s contains an INVALID sudoku\n",argv[1]);       
    }
    return 0;
}



void *check_subgrid(void *arg) 
{
    //Extract the struct values locally
    ThreadData *data = (ThreadData *)arg;
    int subgrid_index = data->index;
    int thread_num = data->thread_num;
    int (*grid)[SIZE] = data->grid;

    //Divide the gird into subgrids, I got the method on HOW to divide them from stack overflow.
    //https://stackoverflow.com/questions/22289144/how-to-get-the-sudoku-2d-array-index-given-its-sub-grid-and-cell-in-the-sub
    int row_start = (subgrid_index / 3) * 3;
    int col_start = (subgrid_index % 3) * 3;

    //Set the base line that we havent seen anything yet. 
    bool seen[10] = {false};

    //Each subgrid is a 3x3 so loop through it. 
    for (int i = 0; i < 3; i++) 
    {
        for (int j = 0; j < 3; j++) 
        {
            //Assign a temp int the value in each grid slot
            int val = grid[row_start + i][col_start + j];

            //Check the validity of that grid slot and then print
            if (val < 1 || val > 9 || seen[val]) 
            {
                //Print that it is invalid and decalloate the struct memory
                printf("Thread # %d (subgrid %d) is invalid\n", thread_num, subgrid_index + 1);
                free(arg);
                return (void *)false;
            }
            //Set that we have seen that value in the grid. 
            seen[val] = true;
        }
    }

    //Increment the OVERALL result counter using a mutex lock
    pthread_mutex_lock(&mutex);
    complete_result += 1;
    pthread_mutex_unlock(&mutex);

    //Print that this thread is valid and deallocate. 
    printf("Thread # %d (subgrid %d) is valid\n", thread_num, subgrid_index + 1);
    free(arg);
    return (void *)true;
}

void *check_column(void *arg) 
{
    //Extract the struct values locally
    ThreadData *data = (ThreadData *)arg;
    int col_index = data->index;
    int thread_num = data->thread_num;
    int (*grid)[SIZE] = data->grid;

    //Set the base line that we havent seen anything yet. 
    bool seen[10] = {false};

    //Loop through the whole col and check each index. 
    for (int i = 0; i < SIZE; i++) 
    {
        //Assign a temp int the value in each col slot
        int val = grid[i][col_index];
        if (val < 1 || val > 9 || seen[val]) 
        {
            //print that it is invalid and free mem
            printf("Thread # %d (column %d) is invalid\n", thread_num, col_index + 1);
            free(arg);
            return (void *)false;
        }
        //save that we have seen current index number
        seen[val] = true;
    }

    //Increment the OVERALL result counter using a mutex lock
    pthread_mutex_lock(&mutex);
    complete_result += 1;
    pthread_mutex_unlock(&mutex);

    //Print that this thread is valid and deallocate. 
    printf("Thread # %d (column %d) is valid\n", thread_num, col_index + 1);
    free(arg);
    return (void *)true;
}

void *check_row(void *arg) 
{
    //Extract the struct values locally
    ThreadData *data = (ThreadData *)arg;
    int row_index = data->index;
    int thread_num = data->thread_num;
    int (*grid)[SIZE] = data->grid; 

    //Set the base line that we havent seen anything yet. 
    bool seen[10] = {false}; // Track digits 1-9

    //Loop through the whole col and check each index.
    for (int i = 0; i < SIZE; i++) 
    {
        //Assign a temp int the value in each col slot
        int val = grid[row_index][i];
        if (val < 1 || val > 9 || seen[val]) 
        {
            printf("Thread # %d (row %d) is invalid\n", thread_num, row_index + 1);
            free(arg);
            return (void *)false;
        }
        //save that we have seen current index number
        seen[val] = true;
    }

    //Increment the OVERALL result counter using a mutex lock
    pthread_mutex_lock(&mutex);
    complete_result += 1;
    pthread_mutex_unlock(&mutex);

    //Print that this thread is valid and deallocate. 
    printf("Thread # %d (row %d) is valid\n", thread_num, row_index + 1);
    free(arg);
    return (void *)true;
}
