//I got the includes from the slides.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

//Helper function to check if a number is prime.
int check_if_prime(int num) 
{
    if (num <= 1) 
    {
        return 0;
    }
    for (int i = 2; i * i <= num; i++) 
    {
        if (num % i == 0) 
        {
            return 0;
        }
    }

    return 1;
}

int main(int argc, char* argv[])
{
    int run_type = atoi(argv[1]);
    int min = atoi(argv[2]);
    int max = atoi(argv[3]);

    int range = (max - min + 1) / 4;
    int ranges[5] = {min, min + range, min + 2 * range, min + 3 * range, max};

    if (run_type == 0) 
    {
        for (int i = 0; i < 4; i++) 
        {
            int bottom_range = ranges[i];
            int top_range = ranges[i + 1];
            int number_of_primes = 0;
            long sum_of_primes = 0;

            for (int current_number_in_range = bottom_range; current_number_in_range <= top_range; current_number_in_range++) 
            {
                if (check_if_prime(current_number_in_range)) 
                {
                    number_of_primes++;
                    sum_of_primes += current_number_in_range;
                }
            }
            printf("pid: %d, ppid: %d - Count and sum of prime numbers between %d and %d are %d and %ld\n",
                    getpid(), getppid(), bottom_range, top_range, number_of_primes, sum_of_primes);
        }
    } 
    else 
    {
        for(int i=0;i<4;i++) 
        {
            if(fork() == 0)
            {
                int bottom_range = ranges[i];
                int top_range = ranges[i + 1];
                int number_of_primes;
                long sum_of_primes;

                for(int current_number_in_range = bottom_range; current_number_in_range<=top_range; current_number_in_range++)
                {
                    if(check_if_prime(current_number_in_range))
                    {
                        number_of_primes++;
                        sum_of_primes += current_number_in_range;
                    }
                }
                printf("pid: %d, ppid %d - Count and sum of prime numbers between %d and %d are %d and %ld\n",
                getpid(),getppid(),bottom_range,top_range,number_of_primes,sum_of_primes);

                exit(0);
            }
        }
        for(int i=0;i<4;i++)
        wait(NULL);
    }
}

