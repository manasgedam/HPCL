#include <stdio.h>
#include <omp.h>

#define SIZE 5
#define NUM_ITEMS 10

int buffer[SIZE];
int count = 0; // items in buffer

int main() {
    omp_set_num_threads(2); // one producer, one consumer

    #pragma omp parallel sections
    {
        // Producer Thread
        #pragma omp section
        {
            int items_produced = 0;
            while (items_produced < NUM_ITEMS) {
                #pragma omp critical
                {
                    // Wait until there is space in the buffer
                    if (count < SIZE) {
                        int item_to_produce = items_produced + 1;
                        buffer[count] = item_to_produce;
                        count++;
                        printf("Producer produced: %d (buffer count = %d)\n", item_to_produce, count);
                        items_produced++;
                    }
                }
                // No barrier here! Allows producer to work independently.
            }
        }

        // Consumer Thread
        #pragma omp section
        {
            int items_consumed = 0;
            while (items_consumed < NUM_ITEMS) {
                #pragma omp critical
                {
                    // Wait until there is an item in the buffer
                    if (count > 0) {
                        count--;
                        int item = buffer[count];
                        printf("Consumer consumed: %d (buffer count = %d)\n", item, count);
                        items_consumed++;
                    }
                }
                // No barrier here! Allows consumer to work independently.
            }
        }
    }
    return 0;
}