/**
 * Student Name: Sitong Zhang
 * Semester: 2025 Fall
 * 
 * LeetCode Problem: Two Sum
 * Problem #1 - Easy
 * 
 * Given an array of integers and a target sum, return indices of the two numbers 
 * such that they add up to the target.
 * 
 * What I learned:
 * - The brute force approach with nested loops is simple but O(n^2) time
 * - I could use a hash table for O(n) solution but that's more complex in C
 * - Need to be careful with array bounds and returning dynamically allocated memory
 * - Important to handle the case where no solution exists
 * 
 * I compared with other solutions and found that most C solutions use the 
 * brute force approach since implementing a hash table in C is complex.
 * In languages like Python or Java, hash table solutions are preferred.
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 * 
 * This function finds two numbers in the array that add up to target.
 * Returns an array of size 2 containing the indices.
 * 
 * Time Complexity: O(n^2) - nested loops checking all pairs
 * Space Complexity: O(1) - only using constant extra space
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    // Allocate memory for result array (2 integers)
    int* result = (int*)malloc(2 * sizeof(int));
    
    // Set return size to 2 (we're returning 2 indices)
    *returnSize = 2;
    
    // Check every pair of numbers
    for (int i = 0; i < numsSize - 1; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            // If we found the pair that adds up to target
            if (nums[i] + nums[j] == target) {
                result[0] = i;
                result[1] = j;
                return result;
            }
        }
    }
    
    // If no solution found (shouldn't happen based on problem constraints)
    *returnSize = 0;
    free(result);
    return NULL;
}

/**
 * Test function to verify our solution works
 */
void test_twoSum() {
    printf("Testing Two Sum Solution\n");
    printf("========================\n\n");
    
    // Test case 1: nums = [2,7,11,15], target = 9
    printf("Test 1: nums = [2,7,11,15], target = 9\n");
    int nums1[] = {2, 7, 11, 15};
    int target1 = 9;
    int returnSize1;
    int* result1 = twoSum(nums1, 4, target1, &returnSize1);
    if (result1 != NULL) {
        printf("Output: [%d, %d]\n", result1[0], result1[1]);
        printf("Verification: %d + %d = %d\n", 
               nums1[result1[0]], nums1[result1[1]], 
               nums1[result1[0]] + nums1[result1[1]]);
        free(result1);
    }
    printf("\n");
    
    // Test case 2: nums = [3,2,4], target = 6
    printf("Test 2: nums = [3,2,4], target = 6\n");
    int nums2[] = {3, 2, 4};
    int target2 = 6;
    int returnSize2;
    int* result2 = twoSum(nums2, 3, target2, &returnSize2);
    if (result2 != NULL) {
        printf("Output: [%d, %d]\n", result2[0], result2[1]);
        printf("Verification: %d + %d = %d\n", 
               nums2[result2[0]], nums2[result2[1]], 
               nums2[result2[0]] + nums2[result2[1]]);
        free(result2);
    }
    printf("\n");
    
    // Test case 3: nums = [3,3], target = 6
    printf("Test 3: nums = [3,3], target = 6\n");
    int nums3[] = {3, 3};
    int target3 = 6;
    int returnSize3;
    int* result3 = twoSum(nums3, 2, target3, &returnSize3);
    if (result3 != NULL) {
        printf("Output: [%d, %d]\n", result3[0], result3[1]);
        printf("Verification: %d + %d = %d\n", 
               nums3[result3[0]], nums3[result3[1]], 
               nums3[result3[0]] + nums3[result3[1]]);
        free(result3);
    }
    printf("\n");
    
    // Test case 4: negative numbers
    printf("Test 4: nums = [-1,-2,-3,-4,-5], target = -8\n");
    int nums4[] = {-1, -2, -3, -4, -5};
    int target4 = -8;
    int returnSize4;
    int* result4 = twoSum(nums4, 5, target4, &returnSize4);
    if (result4 != NULL) {
        printf("Output: [%d, %d]\n", result4[0], result4[1]);
        printf("Verification: %d + %d = %d\n", 
               nums4[result4[0]], nums4[result4[1]], 
               nums4[result4[0]] + nums4[result4[1]]);
        free(result4);
    }
    printf("\n");
}

/**
 * Alternative O(n) solution using sorting (for learning purposes)
 * This modifies the original array so it's not ideal, but shows
 * a different approach between brute force and hash table
 */
typedef struct {
    int value;
    int original_index;
} IndexedValue;

int compare(const void* a, const void* b) {
    return ((IndexedValue*)a)->value - ((IndexedValue*)b)->value;
}

int* twoSumOptimized(int* nums, int numsSize, int target, int* returnSize) {
    // Create array of value-index pairs
    IndexedValue* indexed = (IndexedValue*)malloc(numsSize * sizeof(IndexedValue));
    for (int i = 0; i < numsSize; i++) {
        indexed[i].value = nums[i];
        indexed[i].original_index = i;
    }
    
    // Sort by value
    qsort(indexed, numsSize, sizeof(IndexedValue), compare);
    
    // Use two pointers
    int left = 0;
    int right = numsSize - 1;
    int* result = (int*)malloc(2 * sizeof(int));
    
    while (left < right) {
        int sum = indexed[left].value + indexed[right].value;
        if (sum == target) {
            result[0] = indexed[left].original_index;
            result[1] = indexed[right].original_index;
            *returnSize = 2;
            free(indexed);
            return result;
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }
    
    // No solution found
    *returnSize = 0;
    free(result);
    free(indexed);
    return NULL;
}

int main() {
    test_twoSum();
    
    printf("Comparing with optimized solution:\n");
    printf("==================================\n");
    int nums[] = {2, 7, 11, 15};
    int target = 9;
    int returnSize;
    int* result = twoSumOptimized(nums, 4, target, &returnSize);
    if (result != NULL) {
        printf("Optimized solution: [%d, %d]\n", result[0], result[1]);
        free(result);
    }
    
    return 0;
}
