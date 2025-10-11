# Homework - C Practice Report

Completely answer the report questions below. Make sure to double check the final version to make sure it is easily readable on your github repository. 




1. What is the difference between a standard numeric type (int, float, double) and a pointer?
A standard numeric type like int or float stores the actual value. So when I write int x = 5;, the variable x contains the value 5. But a pointer stores a memory address instead. If I write int* ptr = &x;, ptr contains the address where x lives in memory, not the value 5. To get the actual value from a pointer, I need to use * like *ptr.
2. In your test file, we had the following code:
    
    ```c
    int* arr = create_array_of_ints_fib(5);
    int expected[] = {1, 1, 2, 3, 5};
    ```
    Later in the code we only `free(arr)` but not expected. Why is this? What is the difference in where they are stored in memory?

We only free arr because it was created with malloc() on the heap, while expected is created on the stack. Stack memory gets cleaned up automatically when the function ends, but heap memory stays until we free it. If we don't free heap memory, we get memory leaks.

3. What is the difference between the heap and stack when related to memory allocation and management?
   
The stack is where local variables go. It's fast and cleans itself up when functions end, but it's small. The heap is bigger and we control it with malloc() and free(). Stack is like LIFO - last in, first out. Heap is more flexible but slower. We use the stack for regular variables and the heap when we need memory to stick around or don't know the size ahead of time.

4. Take the following code:
   ```c
   #include <stdio.h>
   #include <stdlib.h>

   typedef struct {
     int x, y;
   } Point;

   Point * new_point(int x, int y) {
     Point pt = {x, y};
     return &pt;
   }

   int main() {
      Point* point = new_point(10, 10);
      printf("x: %d, y: %d", point->x, point->y);
      return 0;
   }
   ```
   Would the code run correctly? Even if it does compile, what would be some potential runtime issues? After answering your thoughts, put the output of a run below (you may need to run it a few times).
   ```text
    x: 32764, y: -139656208
   ```

   Fix the code in the following block:
   ```c
   #include <stdio.h>
   #include <stdlib.h>

   typedef struct {
     int x, y;
   } Point;

   Point * new_point(int x, int y) {
     Point* pt = (Point*)malloc(sizeof(Point));
     pt->x = x;
     pt->y = y;
     return pt;
   }

   int main() {
      Point* point = new_point(10, 10);
      printf("x: %d, y: %d", point->x, point->y);
      free(point);  // Don't forget to free!
      return 0;
   }
   ```

5. When you use `malloc`, where are you storing the information?
When I use malloc, the memory is allocated on the heap. The heap is where dynamic memory goes - stuff that needs to last longer than the function that created it.

6. Speaking about `malloc` and `calloc`, what is the difference between the two (you may need to research it!)?

Malloc takes one parameter (total bytes) and gives you uninitialized memory with random garbage. calloc takes two parameters (number of items and size of each) and zeros out all the memory. So calloc is safer but slower. I use malloc for single things and calloc for arrays when I want them to start at 0.


7. What are some common built in libraries used for C, list at least 3 and explain each one in your own words. Name a few (at least 3) functions in those libraries (hint: we used two of the most common ones in this assignment. There are many resources online that tell you functions in each library - you need to include at least 1 reference, but ideally for every library, you should have a reference to it)?
   - Example: stdlib.h - provides functions for general-purpose operations including
              memory management and random numbers [1].
     - void * malloc(size_t) - allocates memory specified in size on the heap and returns a pointer to that location
     - void * calloc(size_t num_elements, size_t element_size) - contiguous allocation for allocating arrays with the default value of 0. Slower than malloc. 
     - int rand(void) - returns a random integer between 0 and RAND_MAX. Seed should be set before hand. 
   
   1. stdio.h - lets you do input and output, like printing to screen or reading files [2].
      * int printf(const char *format, ...) - prints stuff to the console
      * int scanf(const char *format, ...) - reads input from the user
      * FILE *fopen(const char *filename, const char *mode) - opens a file for reading or writing
   
   2. string.h - has functions for working with strings and character arrays [3].
      * size_t strlen(const char *str) - tells you how long a string is
      * char *strcpy(char *dest, const char *src) - copies one string to another
      * int strcmp(const char *str1, const char *str2) - compares two strings, returns 0 if they're the same
 
   3. math.h - does math calculations like square roots and trig [4].
      * double sqrt(double x) - gets the square root
      * double pow(double base, double exponent) - raises a number to a power
      * double sin(double x) - gets the sine of an angle
 

8. 

Looking at the struct Point and Polygon, we have a mix of values on the heap, and we make ample use of pointers. Take a moment to draw out how you think that looks after create_triangle(2,3) is called (see an example below). The important part of the drawing it to see that not everything is stored together in memory, but in different locations! Store the image file in your github repo and link it here. You can use any program to draw it such as drawIO, or even draw it by hand and take a picture of it.
Since I cannot include an actual image file, here's a text representation of the memory layout:

   Stack                         Heap
   -----                         ----
   
   [tri = @1000] ----------> [@1000: Polygon]
                              size: 3
                              points: @2000 ---------> [@2000: Point* array]
                                                       points[0] = @3000
                                                       points[1] = @3100  
                                                       points[2] = @3200
                                                              |
                                                              v
                                                       [@3000: Point]
                                                       x: 0
                                                       y: 0
                                                       
                                                       [@3100: Point]
                                                       x: 2
                                                       y: 0
                                                       
                                                       [@3200: Point]
                                                       x: 2
                                                       y: 3
The key observation is that after create_triangle(2,3) is called, the memory is scattered across different locations:

The stack contains the pointer variable tri that points to address @1000 on the heap
At @1000 on the heap: The Polygon struct containing size=3 and a pointer to @2000
At @2000 on the heap: An array of three Point pointers
At @3000, @3100, @3200 on the heap: Three separate Point structs with the triangle's coordinates

This scattered allocation is why free_polygon() must carefully free each Point individually, then the points array, and finally the Polygon struct itself to avoid memory leaks.


## Technical Interview Practice Questions
For both these questions, are you are free to use what you did as the last section on the team activities/answered as a group, or you can use a different question.

1. Select one technical interview question (this module or previous) from the [technical interview list](https://github.com/CS5008-khoury/Resources/blob/main/TechInterviewQuestions.md) below and answer it in a few sentences. You can use any resource you like to answer the question.

   **Question: What is a memory leak and how can you prevent it?**
   
   A memory leak happens when you malloc memory but forget to free it. The program keeps using more and more memory until it runs out. To prevent it, always match every malloc with a free, and be careful that you free even when there are errors. Tools like Valgrind can help find leaks.

2. Select one coding question (this module or previous) from the [coding practice repository](https://github.com/CS5008-khoury/Resources/blob/main/LeetCodePractice.md) and include a c file with that code with your submission. Make sure to add comments on what you learned, and if you compared your solution with others. 

   See two_sum.c file in the repository.

## Deeper Thinking
In Java and Python, do you think new objects are stored on the stack or the heap? Feel free to work through your thoughts as to why it would be better to store them on the stack or heap. You should consider pass by reference, and how that is similar to pointer in your answer. Feel free to use resources, but make sure to cite them, and include the citation below using ACM format. You will note LLMs are not valid references, but they can give you directions to valid references. Make sure to use your own words. 

Both Java and Python put all objects on the heap. When you make a new object in Java or create an instance in Python, the actual object goes on the heap and you just get a reference to it (like a pointer in C but safer). This makes sense because objects can be different sizes and need to live longer than the function that made them. It also means when you pass an object to a function, you're passing the reference, not copying the whole thing, which is faster. The downside is heap is slower than stack and needs garbage collection to clean up. But it's worth it because it's safer - you can't do pointer math or access freed memory like in C. The stack still gets used for method calls and primitive types in Java [5][6].

## References
Add any references you use here. Use ACM style formatting, adding to the numbers as you add the reference. 

1. cppreference.com Contributors. 2025. Standard library header <stdlib.h>. cppreference.com. Retrieved May 1, 2025 from https://en.cppreference.com/w/c/header/stdlib

2. cppreference.com Contributors. 2025. Standard library header <stdio.h>. cppreference.com. Retrieved October 10, 2025 from https://en.cppreference.com/w/c/header/stdio

3. cppreference.com Contributors. 2025. Standard library header <string.h>. cppreference.com. Retrieved October 10, 2025 from https://en.cppreference.com/w/c/header/string

4. cppreference.com Contributors. 2025. Standard library header <math.h>. cppreference.com. Retrieved October 10, 2025 from https://en.cppreference.com/w/c/header/math

5. Oracle Corporation. 2024. The Java Tutorials: Understanding Memory Management. Oracle. Retrieved October 10, 2025 from https://docs.oracle.com/javase/tutorial/java/nutsandbolts/datatypes.html

6. Python Software Foundation. 2024. Python Memory Management. Python Documentation. Retrieved October 10, 2025 from https://docs.python.org/3/c-api/memory.html

9. Looking at the struct Point and Polygon, we have a mix of values on the heap, and we make ample use of pointers. Take a moment to draw out how you think that looks after `create_triangle(2,3)` is called (see an example below). The important part of the drawing it to see that not everything is stored together in memory, but in different locations! Store the image file in your github repo and link it here. You can use any program to draw it such as [drawIO](https://app.diagrams.net/), or even draw it by hand and take a picture of it. 



## Resource/Help: Linking to images?
To link an image, you use the following code

```markdown
![alt text](path / link to image)
```
for example
```markdown
![my memory drawing](instructions/rectangle_points.png)
```


Here is a sample using: 
```c
void my_func() {
    Polygon* r = create_rectangle(5,5);
    printf("The area of the rectangle is %d\n", area(r));
}
```

![my memory drawing](instructions/rectangle_points.png)

Note: This is a simplified version. However, it helps illustrate why we need to use `free` on the pointers in the struct. If we do not, we will have memory leaks! (memory that is allocated, but not freed, and thus cannot be used by other programs). In the above example code, `r` is created, and then the variable is destroyed when the function ends. However, the memory allocated for the struct is not freed, and thus we have a memory leak.

When you work on your version for `create_triangle(2, 3)`, you do not have to be exact on the memory structure (the locations on the heap were randomly chosen). The idea is more to show how the memory is stored, and the pointers to different memory addresses. 

