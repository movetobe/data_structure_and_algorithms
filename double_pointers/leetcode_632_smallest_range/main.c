struct column {
    int index;
    int value;
};

int find_max_min_value(struct column *col, int *max_value, int *max_index,
                        int *min_value, int *min_index, int numsSize)
{
    int i = 0;

    *max_value = INT_MIN;
    *min_value = INT_MAX;
    for (i = 0; i < numsSize; i++) {
        if (col[i].value < *min_value) {
            *min_value = col[i].value;
            *min_index = i;
        }
        if (col[i].value > *max_value) {
            *max_value = col[i].value;
            *max_index = i;
        }
    }

    return 0;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* smallestRange(int** nums, int numsSize, int* numsColSize, int* returnSize){
    /* k-pointers point to each array
     * k_pointers[numsSize] records each pointers' position
     * k_array[numsSize] records each k-pointer's value
     */
    struct column *col = calloc(1, sizeof(struct column) * numsSize);
    int *range = calloc(1, sizeof(int) * 2);
    int i = 0;
    int max_value = INT_MIN;
    int min_value = INT_MAX;
    int max_index = 0;
    int min_index = 0;

    *returnSize = 2;
    for (i = 0; i < numsSize; i++) {
        col[i].index = 0;
        col[i].value = nums[i][0];
        if (nums[i][0] > max_value) {
            max_value = nums[i][0];
            max_index = i;
        }
        if (nums[i][0] < min_value) {
            min_value = nums[i][0];
            min_index = i;
        }
    }

    range[1] = INT_MAX;
    range[0] = 0;
    /* any array end would break from the loop */
    for (;;) {
        if ((range[1] - range[0]) > (max_value - min_value)) {
            range[1] = max_value;
            range[0] = min_value;
        }
        /* min value pointer move in */
        col[min_index].index++;
        if (col[min_index].index == numsColSize[min_index]) {
            break;
        }
        col[min_index].value = nums[min_index][col[min_index].index];
        /* find min value and its index */
        find_max_min_value(col, &max_value, &max_index, &min_value, &min_index, numsSize);
    }
    return range;
}
