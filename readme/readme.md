# CP386 Assignment 4
## Sanchit Gogia & Nicholas Sam

# Makefile
### Question 1
make runq1

runs Q1 with the arguments 10 5 7 8
### Question 2
make runq2

runs Q1 with the argument 1000000

# Screenshots
<a href="https://github.com/SanchitGogia/CP386-A4/blob/master/readme/Q1.PNG">
	<img src="https://github.com/SanchitGogia/CP386-A4/blob/master/readme/Q1.PNG" />
</a>

Example input & output of Question 1

<a href="https://github.com/SanchitGogia/CP386-A4/blob/master/readme/Q2.PNG">
	<img src="https://github.com/SanchitGogia/CP386-A4/blob/master/readme/Q2.PNG" />
</a>

Example input & output of Question 2

# Contribution
### Sanchit Gogia
Question 1
- main
- safeCheck
- safeSequence
- display
### Nicholas Sam
Question 1
- runthread

Question 2
- main
- comparesize/comparestart
- allocate
- release
- status

# Features
### Question 1
Question 1 is an implementation of the banker's algorithm.
The banker’s algorithm is a resource allocation and deadlock avoidance algorithm 
that tests for safety by simulating the allocation for predetermined maximum possible 
amounts of all resources, then makes an “s-state” check to test for possible activities, 
before deciding whether allocation should be allowed to continue.
Maximum resources are passed as command line arguments to the program.
### Question 2
Question 2 is an implementation of the best-fit algorithm for contiguous
memory allocation. The best-fit algorithm involves managing a contiguous region
of memory of size memory_size ehere addresses may range from 0 ... memory_size-1.
Memory size is passed as a command line argument to the program.

## Test Cases & Use Examples
See [Screenshots](https://github.com/SanchitGogia/CP386-A4/blob/master/readme/readme.md#screenshots)

## About Developers
Two Wilfrid Laurier University students 

## License
For use only by Wilfrid Laurier University