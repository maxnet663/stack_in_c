#include <stdio.h>
#include <stdlib.h>

/* As you know, elements on the stack are added to the beginning and 
   removed from there. In this stack, the array of values is constantly 
   pressed to the right edge, and the stack itself imitates growth to the left
*/

struct stackdbl {
    int capacity;
    int size;
    double *head; /* points to the head of the stack */
    double *data; /* points to the beginning of the occupied memory */
};

void stackdbl_init(struct stackdbl *sod) {
    sod->capacity = 0;
    sod->size = 0;
    sod->head = NULL; 
    sod->data = NULL; 
}

void stackdbl_destroy(struct stackdbl *sod) {
    if (sod->data)
        free(sod->data);
    sod->capacity = 0;
    sod->size = 0;
    sod->head = NULL;
    sod->data = NULL;
}

/* copy src to dest */
void arr_copy(double *dest, double *src, int size) {
   int i;
   for (i = 0; i < size; i++)
       dest[i] = src[i];
}

/* change size of stack to min or x2 */
void resize_stack(struct stackdbl *sod) {
    if (!sod->capacity)
        sod->capacity = 2;
    else
        sod->capacity *= 2;
    double *new_arr = malloc(sod->capacity * sizeof(double));
    if (sod->head) {
        /*copy to the right part of data */
        arr_copy(new_arr + sod->capacity / 2, sod->head, sod->size);
        free(sod->data);
    }
    sod->data = new_arr;
    /* new head, to the left we had free space to push */
    sod->head = new_arr + sod->capacity / 2; 
}

void stackdbl_push(struct stackdbl *sod, double d) {
    sod->size++;
    if (sod->size > sod->capacity)
        resize_stack(sod);
    sod->head = sod->data + (sod->capacity - sod->size);
    *(sod->head) = d;
}

double stackdbl_pop(struct stackdbl *sod) {
    double d;
    if (sod->head)
        d = sod->head[0];
    else 
        d = 0;
    sod->size--;
    if (sod->size)
        sod->head++;
    else
        sod->head = NULL;
    return d;
}

int stackdbl_empty(struct stackdbl *sod) {
    return !sod->size;
}

int main(int argc, char **argv) {
    struct stackdbl sod;
    stackdbl_init(&sod);
    for (int i = 0; i < 10; i++) {
        stackdbl_push(&sod, i);
    }
    while(!stackdbl_empty(&sod))
        printf("%lf ", stackdbl_pop(&sod));
    printf("\n");
    stackdbl_destroy(&sod);
    return 0;
}
