{\rtf1\ansi\ansicpg1252\cocoartf2865
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\paperw11900\paperh16840\margl1440\margr1440\vieww11520\viewh8400\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 # Parallel Prefix Sum Implementation in C/MPI\
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
\
## Report\
See [report.pdf](./report.pdf) for detailed steps, testing results, and conclusions.\
\
## Limitations and Upgrades\
- Assumes n is divisible by processes; could add padding for arbitrary n.\
- For larger n, optimize with more efficient MPI collectives or GPU acceleration.\
\
Based on the Hillis-Steele prefix scan concept, adapted for MPI.}