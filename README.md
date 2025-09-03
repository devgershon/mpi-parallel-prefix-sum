
Parallel Prefix Sum Implementation in C/MPI
\
This project implements a parallel prefix sum algorithm using MPI, as part of concurrent programming coursework. It distributes data across processes, computes local prefix sums, gathers results, and combines them into a global prefix sum without using `MPI_Scan`.\
\
## Key Features\
- **Input**: Keyboard input for number of elements (`n`), must be divisible by number of processes.\
- **Data Generation**: Process 0 generates random integers.\
- **Parallelization**: Uses `MPI_Scatter` for distribution, local serial prefix computation (up phase), `MPI_Gather` for collection, and offset addition (down phase).\
- **Output**: Process 0 prints input and final global prefix sum.\
\
## Compilation and Running\
- Compile: `mpicc -o prefix prefix.c`\
- Run: `mpirun -np <num_processes> ./prefix` (e.g., `-np 4`)\
- Example: For n=4, input [0, 4, 27, 53] \uc0\u8594  output [0, 4, 31, 84]\
