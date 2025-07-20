// Mohammed Abdulnabi - 251010251


//includes from slides
#include <stdio.h>     
#include <stdlib.h>     
#include <string.h>    
#include <pthread.h>    

//hardcoded bcz we know these wont change for this example
#define NUM_OF_THREADS 4

// structure to represent one transaction line from the CSV file
typedef struct {
    int atm_id;       // ID of the ATM/thread
    int account_id;   // ID of the account (1-based)
    int amount;       // amount to deposit (+) or withdraw (-)
} Transaction;

int accounts[NUM_OF_THREADS];     // array to store balances of 4 accounts
Transaction *transactions = NULL;   // dynamic array of transaction records
int transaction_count = 0;      // track the number of transactions read
pthread_mutex_t account_locks[NUM_OF_THREADS];    // mutexes for each account

// Function to read the input file and store account balances and transactions
// adapted and modified some code from : https://stackoverflow.com/questions/72259781/how-to-read-comma-separated-csv-file-with-sscanf
void read_transactions(const char *filename)
{
    // Try to open the file for reading
    FILE *file = fopen(filename, "r");
    if (!file) 
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[256];  // buffer to hold each line
    int line_num = 0;  // track how many lines we’ve read
    int tansaction_id = 0;  // index in the transactions array
    int tansaction_cap = 10;  // initial capacity for transactions array

    // allocate memory for the transactions
    transactions = malloc(tansaction_cap * sizeof(Transaction));
    if (!transactions) 
    {
        perror("Memory allocation failed");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // read and discard the header line 
    fgets(line, sizeof(line), file);

    // read the rest of the file
    while (fgets(line, sizeof(line), file)) 
    {
        // remove newline if it exists
        line[strcspn(line, "\n")] = '\0';

        // if we’re still in the first 4 lines, read account balances
        if (line_num < 4) 
        {
            char dash;
            int account;
            int balance;

            // read the line
            if (sscanf(line, " %c,%d,%d", &dash, &account, &balance) == 3) 
            {
                if (account >= 1 && account <= NUM_OF_THREADS) 
                {
                    // store balance into the appropriate array index
                    accounts[account - 1] = balance;
                }
            }
        } 
        else 
        {
            int atm;
            int account; 
            int amount;

            // read the line 
            if (sscanf(line, "%d,%d,%d", &atm, &account, &amount) == 3) 
            {

                // grow transaction array if needed by 2x
                if (tansaction_id >= tansaction_cap) 
                {
                    //double the capacity
                    tansaction_cap *= 2;
                    //re acllocatr the memeory 
                    transactions = realloc(transactions, tansaction_cap * sizeof(Transaction));

                    //check if the mem was allocated correcrtly 
                    if (!transactions) 
                    {
                        perror("Reallocation failed");
                        fclose(file);
                        exit(EXIT_FAILURE);
                    }
                }

                // store the transaction in the array
                transactions[tansaction_id].atm_id = atm;
                transactions[tansaction_id].account_id = account;
                transactions[tansaction_id].amount = amount;
                tansaction_id++;
            }
        }

        // move to next line
        line_num++;
    }

    // record the total number of valid transactions read
    transaction_count = tansaction_id;

    // close file
    fclose(file);
}

// helper function to print the balances 
void print_balances(const char *label) 
{
    printf("\n%s\n", label);
    for (int i = 0; i < NUM_OF_THREADS; i++) 
    {
        printf("Account %d: $%d\n", i + 1, accounts[i]);
    }
    printf("\n%s\n", label);
}


//  process transactions 
void *process_transactions(void *args) 
{
    //makes the input argument an int to get which trhead
    int thread_id = *(int *)args;

    // go through each transaction in the list
    for (int i = 0; i < transaction_count; i++) 
    {
        // skip if this transaction isn't for the current thread
        if (transactions[i].atm_id != thread_id) 
        {
            continue;
        }

        //get the account from the transactions array
        int acc = transactions[i].account_id - 1;

        // get the transaction amount
        int amt = transactions[i].amount;

        //lock so no one else can touch it
        pthread_mutex_lock(&account_locks[acc]);

        //check if the withdrawal would cause an overdraft
        if (amt < 0 && accounts[acc] + amt < 0) 
        {
            //if they do print this and would exit
            printf("Thread %d: Withdraw $%d from Account %d - INSUFFICIENT FUNDS\n", thread_id, -amt, acc + 1);
        } 
        //if the withdrawal wont or isnt a withdraw at all 
        else 
        {
            //apply the transaction
            accounts[acc] += amt;

            //strings we will use the print depending on the aciton
            const char *action;
            const char *direction;

            //to print the value being used to debit or credit 
            int abs_amt = abs(amt);

            //if its a deposit
            if (amt >= 0) 
            {
                //set the strings accordingly
                action = "Deposit";
                direction = "into";
      
            } 
            //if its a withdraw
            else 
            {
                //set the strings accordingly
                action = "Withdraw";
                direction = "from";
            }

            //print statement from requiremnts 
            printf("Thread %d: %s $%d %s Account %d\n", thread_id, action, abs_amt, direction, acc + 1);
        }

        // unloack the account
        pthread_mutex_unlock(&account_locks[acc]);
    }

    return NULL;
}

int main(int argc, char *argv[]) 
{
    // check if filename was provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <inputfile>\n", argv[0]);
        return EXIT_FAILURE;
    }

    read_transactions(argv[1]);

    print_balances("Starting Balances:");

    pthread_t threads[NUM_OF_THREADS];    //hold thread IDs
    int thread_ids[NUM_OF_THREADS];   // One ID per thread

    // initalize a mutex for each account
    for (int i = 0; i < NUM_OF_THREADS; i++) 
    {
        pthread_mutex_init(&account_locks[i], NULL);
    }

    // create the threads 
    for (int i = 0; i < NUM_OF_THREADS; i++) 
    {
        thread_ids[i] = i + 1; 
        pthread_create(&threads[i], NULL, process_transactions, &thread_ids[i]);
    }

    // waiting for threads
    for (int i = 0; i < NUM_OF_THREADS; i++) 
    {
        pthread_join(threads[i], NULL);
    }


    print_balances("Final Balances:");
    free(transactions);
    return 0;
}
