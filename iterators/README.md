# Iterators 
Iterators in C++ are objects that allow you to access each element of a container (e.g., std::vector, std::map). They are especially useful when iterating through data structures that aren't stored contiguously in memory, for example, Linked Lists (which you will see later in CPSC 131).

<br/>

<div align="center">
   <div style="overflow: hidden;">
      <img src="https://scaler.com/topics/images/array-of-5-elements.gif" style="width: auto; height: 250px; margin-top: -15px; margin-bottom: -50px">
   </div>
</div>

<br/>

## Instructions
1. Download the project files:

   ```bash
   mkdir iterators && cd iterators && curl --remote-name-all https://raw.githubusercontent.com/Ashleyc417/si/main/cpsc121/iterators/{main.cpp,run.sh,README.md} 
   ```


2. Complete the TODOs in `main.cpp`


3. Run the testing suite script:
   > Note: You will only have to run `chmod +x run.sh` once!
   ```bash
   chmod +x run.sh
   ./run.sh
   ```
   > This script will compile the `main.cpp` file using either `clang++` or `g++` (depending on availability). If compilation is successful, it will run the testing suite to verify the functionality.


4. Review the test results:

<br/>

## Expected Output
```
Words in the vector: I just woke up from a dream and I feel alive 
The word 'dream' appears 1 time(s).

Words with frequency greater than 1:
I: 2

Modified vector: 1 2 10 4 5 
```