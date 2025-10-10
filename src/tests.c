/**
 * Student Name: Sitong Zhang
 * Semester: 2025 Fall
 * 
 * 
 * This file is to test the functions in cpractice.h. You are to write at least *TWO* (maybe more) tests for every function. 
 * Some sample ones have been provided for you.
*/

#include <stdio.h>  // basic input and output
#include <stdlib.h> // standard library

#include "cpractice.h" // header file for cpractice.c


// this may help with some tests, as the array numbers match their index
int * create_simple_array(int size) {
    int * arr = malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }
    return arr;
}

/**
 * Tests a basic swap
*/
int test_swap_one() {
    printf("1. test_swap_one()\n");
    int a = 5;
    int b = 10;
    swap(&a, &b);
    if (a == 10 && b == 5) {
        return 1;
    }
    return 0;
}

/**
 * Tests swap with negative numbers
*/
int test_swap_negative() {
    printf("2. test_swap_negative()\n");
    int a = -15;
    int b = 25;
    swap(&a, &b);
    if (a == 25 && b == -15) {
        return 1;
    }
    return 0;
}

/**
 * Tests swap with same values
*/
int test_swap_same() {
    printf("3. test_swap_same()\n");
    int a = 7;
    int b = 7;
    swap(&a, &b);
    if (a == 7 && b == 7) {
        return 1;
    }
    return 0;
}

/**
 * Tests the create_array_of_ints_fib function
*/
int test_create_array_of_ints_fib() {
    printf("4. test_create_array_of_ints_fib()\n");
    int* arr = create_array_of_ints_fib(5);
    int expected[] = {1, 1, 2, 3, 5};
    for (int i = 0; i < 5; i++) {
        if (arr[i] != expected[i]) {
            free(arr);
            return 0;
        }
    }
    free(arr); // note expected does not need freed.. why is that?
    // everything matched
    return 1;
}

/**
 * Tests fibonacci with size 1 (edge case)
*/
int test_fib_size_one() {
    printf("5. test_fib_size_one()\n");
    int* arr = create_array_of_ints_fib(1);
    if (arr != NULL && arr[0] == 1) {
        free(arr);
        return 1;
    }
    if (arr != NULL) free(arr);
    return 0;
}

/**
 * Tests fibonacci with size 0 (should return NULL)
*/
int test_fib_size_zero() {
    printf("6. test_fib_size_zero()\n");
    int* arr = create_array_of_ints_fib(0);
    if (arr == NULL) {
        return 1;
    }
    free(arr);
    return 0;
}

/**
 * Tests fibonacci with negative size (should return NULL)
*/
int test_fib_negative_size() {
    printf("7. test_fib_negative_size()\n");
    int* arr = create_array_of_ints_fib(-5);
    if (arr == NULL) {
        return 1;
    }
    free(arr);
    return 0;
}

/**
 * Tests reverse_array with odd number of elements
*/
int test_reverse_odd() {
    printf("8. test_reverse_odd()\n");
    int arr[] = {1, 2, 3, 4, 5};
    reverse_array(arr, 5);
    int expected[] = {5, 4, 3, 2, 1};
    for (int i = 0; i < 5; i++) {
        if (arr[i] != expected[i]) {
            return 0;
        }
    }
    return 1;
}

/**
 * Tests reverse_array with even number of elements
*/
int test_reverse_even() {
    printf("9. test_reverse_even()\n");
    int arr[] = {1, 2, 3, 4};
    reverse_array(arr, 4);
    int expected[] = {4, 3, 2, 1};
    for (int i = 0; i < 4; i++) {
        if (arr[i] != expected[i]) {
            return 0;
        }
    }
    return 1;
}

/**
 * Tests reverse_array with size 1 (edge case)
*/
int test_reverse_single() {
    printf("10. test_reverse_single()\n");
    int arr[] = {42};
    reverse_array(arr, 1);
    if (arr[0] == 42) {
        return 1;
    }
    return 0;
}

/**
 * Tests double_array_size basic functionality
*/
int test_double_array() {
    printf("11. test_double_array()\n");
    int arr[] = {1, 2, 3};
    int* doubled = double_array_size(arr, 3);
    if (doubled == NULL) return 0;
    
    // Check first 3 elements are copied
    for (int i = 0; i < 3; i++) {
        if (doubled[i] != arr[i]) {
            free(doubled);
            return 0;
        }
    }
    // Check last 3 elements are 0
    for (int i = 3; i < 6; i++) {
        if (doubled[i] != 0) {
            free(doubled);
            return 0;
        }
    }
    free(doubled);
    return 1;
}

/**
 * Tests double_array_size with size 1
*/
int test_double_array_single() {
    printf("12. test_double_array_single()\n");
    int arr[] = {99};
    int* doubled = double_array_size(arr, 1);
    if (doubled == NULL) return 0;
    
    if (doubled[0] == 99 && doubled[1] == 0) {
        free(doubled);
        return 1;
    }
    free(doubled);
    return 0;
}

/**
 * Tests copy_array_start_end_loop normal case (start < end)
*/
int test_copy_array_normal() {
    printf("13. test_copy_array_normal()\n");
    int* arr = create_simple_array(5); // [0, 1, 2, 3, 4]
    int new_size;
    int* copied = copy_array_start_end_loop(arr, 5, 1, 3, &new_size);
    
    if (copied == NULL || new_size != 3) {
        free(arr);
        if (copied) free(copied);
        return 0;
    }
    
    // Should be [1, 2, 3]
    int expected[] = {1, 2, 3};
    for (int i = 0; i < 3; i++) {
        if (copied[i] != expected[i]) {
            free(arr);
            free(copied);
            return 0;
        }
    }
    free(arr);
    free(copied);
    return 1;
}

/**
 * Tests copy_array_start_end_loop wrap around case (start > end)
*/
int test_copy_array_wrap() {
    printf("14. test_copy_array_wrap()\n");
    int* arr = create_simple_array(5); // [0, 1, 2, 3, 4]
    int new_size;
    int* copied = copy_array_start_end_loop(arr, 5, 3, 1, &new_size);
    
    if (copied == NULL || new_size != 4) {
        free(arr);
        if (copied) free(copied);
        return 0;
    }
    
    // Should be [3, 4, 0, 1]
    int expected[] = {3, 4, 0, 1};
    for (int i = 0; i < 4; i++) {
        if (copied[i] != expected[i]) {
            free(arr);
            free(copied);
            return 0;
        }
    }
    free(arr);
    free(copied);
    return 1;
}

/**
 * Tests copy_array with invalid start (negative)
*/
int test_copy_array_invalid_start() {
    printf("15. test_copy_array_invalid_start()\n");
    int* arr = create_simple_array(5);
    int new_size;
    int* copied = copy_array_start_end_loop(arr, 5, -1, 2, &new_size);
    
    free(arr);
    if (copied == NULL) {
        return 1;
    }
    free(copied);
    return 0;
}

/**
 * Tests copy_array with invalid end (>= size)
*/
int test_copy_array_invalid_end() {
    printf("16. test_copy_array_invalid_end()\n");
    int* arr = create_simple_array(5);
    int new_size;
    int* copied = copy_array_start_end_loop(arr, 5, 0, 5, &new_size);
    
    free(arr);
    if (copied == NULL) {
        return 1;
    }
    free(copied);
    return 0;
}

/**
 * Tests copy_array with start == end (single element)
*/
int test_copy_array_single() {
    printf("17. test_copy_array_single()\n");
    int* arr = create_simple_array(5);
    int new_size;
    int* copied = copy_array_start_end_loop(arr, 5, 2, 2, &new_size);
    
    if (copied == NULL || new_size != 1) {
        free(arr);
        if (copied) free(copied);
        return 0;
    }
    
    if (copied[0] == 2) {
        free(arr);
        free(copied);
        return 1;
    }
    free(arr);
    free(copied);
    return 0;
}

/**
 * Tests create_point basic functionality
*/
int test_create_point() {
    printf("18. test_create_point()\n");
    Point* p = create_point(10, 20);
    if (p == NULL) return 0;
    
    if (p->x == 10 && p->y == 20) {
        free(p);
        return 1;
    }
    free(p);
    return 0;
}

/**
 * Tests create_point with negative values
*/
int test_create_point_negative() {
    printf("19. test_create_point_negative()\n");
    Point* p = create_point(-5, -10);
    if (p == NULL) return 0;
    
    if (p->x == -5 && p->y == -10) {
        free(p);
        return 1;
    }
    free(p);
    return 0;
}

/**
 * Tests create_polygon basic functionality
*/
int test_create_polygon() {
    printf("20. test_create_polygon()\n");
    Polygon* poly = create_polygon(4);
    if (poly == NULL) return 0;
    
    if (poly->size == 4 && poly->points != NULL) {
        free(poly->points);
        free(poly);
        return 1;
    }
    if (poly->points) free(poly->points);
    free(poly);
    return 0;
}

/**
 * Tests create_polygon with size 1
*/
int test_create_polygon_single() {
    printf("21. test_create_polygon_single()\n");
    Polygon* poly = create_polygon(1);
    if (poly == NULL) return 0;
    
    if (poly->size == 1 && poly->points != NULL) {
        free(poly->points);
        free(poly);
        return 1;
    }
    if (poly->points) free(poly->points);
    free(poly);
    return 0;
}

/**
 * Tests create_rectangle
*/
int test_create_rectangle() {
    printf("22. test_create_rectangle()\n");
    Polygon* rect = create_rectangle(5, 10);
    if (rect == NULL) return 0;
    
    // Check all 4 points
    if (rect->size == 4 &&
        rect->points[0]->x == 0 && rect->points[0]->y == 0 &&
        rect->points[1]->x == 5 && rect->points[1]->y == 0 &&
        rect->points[2]->x == 5 && rect->points[2]->y == 10 &&
        rect->points[3]->x == 0 && rect->points[3]->y == 10) {
        free_polygon(rect);
        return 1;
    }
    free_polygon(rect);
    return 0;
}

/**
 * Tests create_rectangle with different dimensions
*/
int test_create_rectangle_square() {
    printf("23. test_create_rectangle_square()\n");
    Polygon* rect = create_rectangle(7, 7);
    if (rect == NULL) return 0;
    
    if (rect->size == 4 &&
        rect->points[2]->x == 7 && rect->points[2]->y == 7) {
        free_polygon(rect);
        return 1;
    }
    free_polygon(rect);
    return 0;
}

/**
 * Tests create_triangle
*/
int test_create_triangle() {
    printf("24. test_create_triangle()\n");
    Polygon* tri = create_triangle(3, 4);
    if (tri == NULL) return 0;
    
    // Check all 3 points
    if (tri->size == 3 &&
        tri->points[0]->x == 0 && tri->points[0]->y == 0 &&
        tri->points[1]->x == 3 && tri->points[1]->y == 0 &&
        tri->points[2]->x == 3 && tri->points[2]->y == 4) {
        free_polygon(tri);
        return 1;
    }
    free_polygon(tri);
    return 0;
}

/**
 * Tests create_triangle with different dimensions
*/
int test_create_triangle_large() {
    printf("25. test_create_triangle_large()\n");
    Polygon* tri = create_triangle(10, 15);
    if (tri == NULL) return 0;
    
    if (tri->size == 3 &&
        tri->points[2]->x == 10 && tri->points[2]->y == 15) {
        free_polygon(tri);
        return 1;
    }
    free_polygon(tri);
    return 0;
}

/**
 * Tests calculate_polygon_area for rectangle
*/
int test_area_rectangle() {
    printf("26. test_area_rectangle()\n");
    Polygon* rect = create_rectangle(5, 10);
    if (rect == NULL) return 0;
    
    double area = calculate_polygon_area(rect);
    // Area should be 50 (5 * 10)
    if (area == 50.0) {
        free_polygon(rect);
        return 1;
    }
    free_polygon(rect);
    return 0;
}

/**
 * Tests calculate_polygon_area for triangle
*/
int test_area_triangle() {
    printf("27. test_area_triangle()\n");
    Polygon* tri = create_triangle(6, 8);
    if (tri == NULL) return 0;
    
    double area = calculate_polygon_area(tri);
    // Area should be 24 (6 * 8 / 2)
    if (area == 24.0) {
        free_polygon(tri);
        return 1;
    }
    free_polygon(tri);
    return 0;
}

/**
 * Tests calculate_polygon_area for square
*/
int test_area_square() {
    printf("28. test_area_square()\n");
    Polygon* square = create_rectangle(5, 5);
    if (square == NULL) return 0;
    
    double area = calculate_polygon_area(square);
    // Area should be 25 (5 * 5)
    if (area == 25.0) {
        free_polygon(square);
        return 1;
    }
    free_polygon(square);
    return 0;
}

// this is a list of all the unit tests
int (*unitTests[])() = {
        test_swap_one,
        test_swap_negative,
        test_swap_same,
        test_create_array_of_ints_fib,
        test_fib_size_one,
        test_fib_size_zero,
        test_fib_negative_size,
        test_reverse_odd,
        test_reverse_even,
        test_reverse_single,
        test_double_array,
        test_double_array_single,
        test_copy_array_normal,
        test_copy_array_wrap,
        test_copy_array_invalid_start,
        test_copy_array_invalid_end,
        test_copy_array_single,
        test_create_point,
        test_create_point_negative,
        test_create_polygon,
        test_create_polygon_single,
        test_create_rectangle,
        test_create_rectangle_square,
        test_create_triangle,
        test_create_triangle_large,
        test_area_rectangle,
        test_area_triangle,
        test_area_square
};

int main(int argc, char const *argv[])
{
    int numTests = sizeof(unitTests) / sizeof(unitTests[0]);
    int numPassed = 0;

    for (int i = 0; i < numTests; i++) {
        if (unitTests[i]()) {
            numPassed++;
        } else {
            printf("Test %d failed\n", i + 1);
        }
    }

    printf("Passed %d out of %d tests\n", numPassed, numTests);
    return 0;
}

