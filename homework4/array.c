#include "array.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct array* array_create()
{
	struct array* a = (struct array*)malloc(sizeof(struct array));
        assert(0 != a);
        memset(a, 0, sizeof(struct array));
	a->size = 0;
	a->capacity = 2;
	a->start = (element_type*)malloc(a->capacity * sizeof(element_type));
	return a;
}

void array_push_back(struct array* a, element_type e)
{
	assert(a != NULL);

	// if array is fu;;, double the capacity
	if (a->size == a->capacity)
       	{
		a->capacity *= 2;
       		a->start = realloc(a->start, a->capacity * sizeof(element_type));
		assert(a->start != NULL); // ensuring reallocation is successful
	}

	// adding element to the end and incrementing the sieze
	a->start[a->size++]=e;
}


void array_pop_back(struct array* a)
{
	assert(a != NULL);
	assert(a->size > 0); // prevent underflow on empty array
	
	// only decrementing the sieze since the element is logically removed
	a->size--;

}

void array_insert(struct array* a, size_type index, element_type e)
{
	assert(a != NULL);
	assert(index <= a->size); // allowing o insert at the end
	
	// if array is full, we have to double the capacity
	if (a->size == a->capacity)
       	{
		a->capacity *= 2;
		a->start = realloc(a->start, a->capacity * sizeof(element_type));
		assert(a->start != NULL); // ensuring that the reallocation was successful	
	}

	//shifting elements a position to the right from index  
	for (size_type i = a->size; i > index; --i  )
       	{
		a->start[i] = a->start[i - 1];
	}

	// finally, inserting the new element and updating
	a->start[index] = e;
	a->size++;
}


size_type array_size(struct array* a)
{
	assert(0 != a);
	return a->size;
}

size_type array_capacity(struct array* a)
{
	assert(0 != a);
	return a->capacity;
}

void array_print(struct array* a)
{
	assert(0 != a);
	for (size_type i = 0; i < a->size; ++i) {
		printf("%d ", a->start[i]);
	}
	printf("\nsize = %d", a->size);
	printf("\ncapacity = %d\n\n", a->capacity);
}

int array_empty(struct array* a)
{
	assert(0 != a);
	return a->size == 0;
}
