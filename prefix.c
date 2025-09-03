#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to print arrays
void print_array(int arr[], int n, const char* msg) {
    printf("%s: ", msg);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Parallel Prefix Scan Function (involving up phase and down phase)
int main(int argc, char** argv) {
    int rank, size, n;
    int* data = NULL;  // Array to store random integers (in process 0)
    int* local_data = NULL;  // Local portion for each process
    int local_n;  // Size of local array

    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Step 1: Process 0 generates the random data
    if (rank == 0) {
        // Get the number of elements to generate
        printf("Enter the number of elements to generate: ");
        scanf("%d", &n);

        // Ensure n is divisible by the number of processes
        if (n % size != 0) {
            printf("Number of elements must be divisible by the number of processes.\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        // Allocate memory for n integers
        data = (int*)malloc(n * sizeof(int));

        // Seed the random number generator and generate n random numbers
        srand(time(0));
        for (int i = 0; i < n; i++) {
            data[i] = rand() % 100;  // Random integers between 0 and 99
        }

        // Print the generated array
        print_array(data, n, "Array generated");
    }

    // Step 2: Broadcast the value of n to all processes
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Step 3: Calculate the number of elements each process will handle
    local_n = n / size;

    // Allocate memory for the local array in each process
    local_data = (int*)malloc(local_n * sizeof(int));

    // Step 4: Scatter the data to all processes
    MPI_Scatter(data, local_n, MPI_INT, local_data, local_n, MPI_INT, 0, MPI_COMM_WORLD);

    // Step 5: Each process computes the prefix sum of its local portion (up phase)
    for (int i = 1; i < local_n; i++) {
        local_data[i] += local_data[i - 1];  // Add previous element to current
    }

    // Print the up phase result
    printf("Process %d up phase result: ", rank);
    for (int i = 0; i < local_n; i++) {
        printf("%d ", local_data[i]);
    }
    printf("\n");

    // Step 6: Gather the local prefix sums back to process 0
    MPI_Gather(local_data, local_n, MPI_INT, data, local_n, MPI_INT, 0, MPI_COMM_WORLD);

    // Step 7: Process 0 combines the results into a global prefix sum (down phase)
    if (rank == 0) {
        // Print the up phase gathered results
        printf("\nUp phase gathered results:\n");
        print_array(data, n, "Up phase gathered");

        // Combine the prefix sums from all processes (down phase)
        for (int i = 1; i < size; i++) {
            for (int j = 0; j < local_n; j++) {
                data[i * local_n + j] += data[(i - 1) * local_n + (local_n - 1)];
            }

            // Print the down phase result at each step
            printf("Down phase after process %d: ", i);
            print_array(data, n, "Down phase");
        }

        // Print the final global prefix sum
        printf("\nFinal global prefix sum:\n");
        print_array(data, n, "Global prefix sum");
    }

    // Free allocated memory
    free(data);
    free(local_data);

    // Finalize MPI
    MPI_Finalize();
    return 0;
}

