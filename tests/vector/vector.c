#include "wsl/ws_vector.h"

#include <string.h>

#define WS_ASSERT(condition) if (!(condition)) exit(EXIT_FAILURE);

WS_VECTOR(int)

void test_initialized_with_values()
{
    struct ws_vector_int vector = ws_vector_int_create(ws_vector_initialize(int, 69, 420, 720));

    WS_ASSERT(ws_vector_int_size(vector)   == 3);
    WS_ASSERT(*ws_vector_int_at(vector, 0) == 69);
    WS_ASSERT(*ws_vector_int_at(vector, 1) == 420);
    WS_ASSERT(*ws_vector_int_at(vector, 2) == 720);

    ws_vector_destroy(int, &vector);
}

void test_push_values()
{
    struct ws_vector_int vector = ws_vector_int_create(0);

    ws_vector_int_push(&vector, 69);
    WS_ASSERT(*ws_vector_int_back(vector) == 69);
    ws_vector_int_push(&vector, 420);
    WS_ASSERT(*ws_vector_int_back(vector) == 420);
    ws_vector_int_push(&vector, 720);
    WS_ASSERT(*ws_vector_int_back(vector) == 720);

    WS_ASSERT(ws_vector_int_size(vector)  == 3);

    ws_vector_destroy(int, &vector);
}

void test_pop_values()
{
    struct ws_vector_int vector = ws_vector_int_create(ws_vector_initialize(int, 69, 420, 720));

    WS_ASSERT(ws_vector_int_size(vector)  == 3);
    WS_ASSERT(*ws_vector_int_pop(&vector) == 720);
    WS_ASSERT(ws_vector_int_size(vector)  == 2);
    WS_ASSERT(*ws_vector_int_pop(&vector) == 420);
    WS_ASSERT(ws_vector_int_size(vector)  == 1);
    WS_ASSERT(*ws_vector_int_pop(&vector) == 69);
    WS_ASSERT(ws_vector_int_size(vector)  == 0);

    ws_vector_destroy(int, &vector);
}

int test_sort_values_comparator(int const* lhs, int const* rhs)
{
    return *lhs > *rhs;
}

void test_sort_values()
{
    struct ws_vector_int vector = ws_vector_int_create(ws_vector_initialize(int, 720, 69, 420));

    ws_vector_sort(int, &vector, test_sort_values_comparator);

    WS_ASSERT(*ws_vector_int_at(vector, 0) == 69);
    WS_ASSERT(*ws_vector_int_at(vector, 1) == 420);
    WS_ASSERT(*ws_vector_int_at(vector, 2) == 720);

    ws_vector_destroy(int, &vector);
}

void test_copy_values()
{
    struct ws_vector_int vectorA = ws_vector_int_create(ws_vector_initialize(int, 69, 420, 720));
    struct ws_vector_int vectorB = ws_vector_int_create(0);

    ws_vector_copy(int, &vectorB, &vectorA);

    WS_ASSERT(ws_vector_int_size(vectorA) == ws_vector_int_size(vectorB));

    WS_ASSERT(*ws_vector_int_at(vectorA, 0) == *ws_vector_int_at(vectorB, 0));
    WS_ASSERT(*ws_vector_int_at(vectorA, 1) == *ws_vector_int_at(vectorB, 1));
    WS_ASSERT(*ws_vector_int_at(vectorA, 2) == *ws_vector_int_at(vectorB, 2));

    ws_vector_destroy(int, &vectorA);

    WS_ASSERT(!ws_vector_int_is_empty(vectorB));

    ws_vector_destroy(int, &vectorB);
}

void test_copy_values_non_empty()
{
    struct ws_vector_int vectorA = ws_vector_int_create(ws_vector_initialize(int, 69, 420, 720));
    struct ws_vector_int vectorB = ws_vector_int_create(ws_vector_initialize(int, 69420));

    ws_vector_copy(int, &vectorB, &vectorA);

    WS_ASSERT(ws_vector_int_size(vectorA) == ws_vector_int_size(vectorB));

    WS_ASSERT(*ws_vector_int_at(vectorA, 0) == *ws_vector_int_at(vectorB, 0));
    WS_ASSERT(*ws_vector_int_at(vectorA, 1) == *ws_vector_int_at(vectorB, 1));
    WS_ASSERT(*ws_vector_int_at(vectorA, 2) == *ws_vector_int_at(vectorB, 2));

    ws_vector_destroy(int, &vectorA);

    WS_ASSERT(!ws_vector_int_is_empty(vectorB));

    ws_vector_destroy(int, &vectorB);
}

void test_copy_empty()
{
    struct ws_vector_int vectorA = ws_vector_int_create(0);
    struct ws_vector_int vectorB = ws_vector_int_create(0);

    ws_vector_copy(int, &vectorB, &vectorA);

    ws_vector_destroy(int, &vectorA);
    ws_vector_destroy(int, &vectorB);
}

int main(int argumentCount, char const** argumentValues)
{
    assert(argumentCount == 2);

    if (!strcmp(argumentValues[1], "initialized_with_values"))
    {
        test_initialized_with_values();
    }
    else if (!strcmp(argumentValues[1], "push_values"))
    {
        test_push_values();
    }
    else if (!strcmp(argumentValues[1], "pop_values"))
    {
        test_pop_values();
    }
    else if (!strcmp(argumentValues[1], "sort_values"))
    {
        test_sort_values();
    }
    else if (!strcmp(argumentValues[1], "copy_values"))
    {
        test_copy_values();
    }
    else if (!strcmp(argumentValues[1], "copy_values_non_empty"))
    {
        test_copy_values_non_empty();
    }
    else if (!strcmp(argumentValues[1], "copy_empty"))
    {
        test_copy_empty();
    }

    return EXIT_SUCCESS;
}
