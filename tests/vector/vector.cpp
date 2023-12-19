#include <wsl/ws_vector.h>
#include <gtest/gtest.h>

#define WS_ASSERT(condition) if (!(condition)) exit(EXIT_FAILURE);

WS_VECTOR(int)

TEST(initialized_with_values, vector)
{
    struct ws_vector_int vector = ws_vector_int_create(ws_vector_initialize(int, 69, 420, 720));

    EXPECT_EQ(ws_vector_int_size(vector), 3);
    EXPECT_EQ(*ws_vector_int_at(vector, 0), 69);
    EXPECT_EQ(*ws_vector_int_at(vector, 1), 420);
    EXPECT_EQ(*ws_vector_int_at(vector, 2), 720);

    ws_vector_destroy(int, &vector);
}

TEST(push_values, vector)
{
    struct ws_vector_int vector = ws_vector_int_create(0);

    ws_vector_int_push(&vector, 69);
    EXPECT_EQ(*ws_vector_int_back(vector), 69);
    ws_vector_int_push(&vector, 420);
    EXPECT_EQ(*ws_vector_int_back(vector), 420);
    ws_vector_int_push(&vector, 720);
    EXPECT_EQ(*ws_vector_int_back(vector), 720);

    EXPECT_EQ(ws_vector_int_size(vector), 3);

    ws_vector_destroy(int, &vector);
}

TEST(pop_values, vector)
{
    struct ws_vector_int vector = ws_vector_int_create(ws_vector_initialize(int, 69, 420, 720));

    EXPECT_EQ(ws_vector_int_size(vector), 3);
    EXPECT_EQ(*ws_vector_int_pop(&vector), 720);
    EXPECT_EQ(ws_vector_int_size(vector), 2);
    EXPECT_EQ(*ws_vector_int_pop(&vector), 420);
    EXPECT_EQ(ws_vector_int_size(vector), 1);
    EXPECT_EQ(*ws_vector_int_pop(&vector), 69);
    EXPECT_EQ(ws_vector_int_size(vector), 0);

    ws_vector_destroy(int, &vector);
}

int test_sort_values_comparator(int const* lhs, int const* rhs)
{
    return *lhs > *rhs;
}

TEST(sort_values, vector)
{
    struct ws_vector_int vector = ws_vector_int_create(ws_vector_initialize(int, 720, 69, 420));

    ws_vector_sort(int, &vector, test_sort_values_comparator);

    EXPECT_EQ(*ws_vector_int_at(vector, 0) , 69);
    EXPECT_EQ(*ws_vector_int_at(vector, 1) , 420);
    EXPECT_EQ(*ws_vector_int_at(vector, 2) , 720);

    ws_vector_destroy(int, &vector);
}

TEST(copy_values, vector)
{
    struct ws_vector_int vectorA = ws_vector_int_create(ws_vector_initialize(int, 69, 420, 720));
    struct ws_vector_int vectorB = ws_vector_int_create(0);

    ws_vector_copy(int, &vectorB, &vectorA);

    EXPECT_EQ(ws_vector_int_size(vectorA), ws_vector_int_size(vectorB));

    EXPECT_EQ(*ws_vector_int_at(vectorA, 0), *ws_vector_int_at(vectorB, 0));
    EXPECT_EQ(*ws_vector_int_at(vectorA, 1), *ws_vector_int_at(vectorB, 1));
    EXPECT_EQ(*ws_vector_int_at(vectorA, 2), *ws_vector_int_at(vectorB, 2));

    ws_vector_destroy(int, &vectorA);

    EXPECT_EQ(ws_vector_int_is_empty(vectorB), false);

    ws_vector_destroy(int, &vectorB);
}

TEST(copy_values_non_empty, vector)
{
    struct ws_vector_int vectorA = ws_vector_int_create(ws_vector_initialize(int, 69, 420, 720));
    struct ws_vector_int vectorB = ws_vector_int_create(ws_vector_initialize(int, 69420));

    ws_vector_copy(int, &vectorB, &vectorA);

    EXPECT_EQ(ws_vector_int_size(vectorA), ws_vector_int_size(vectorB));

    EXPECT_EQ(*ws_vector_int_at(vectorA, 0), *ws_vector_int_at(vectorB, 0));
    EXPECT_EQ(*ws_vector_int_at(vectorA, 1), *ws_vector_int_at(vectorB, 1));
    EXPECT_EQ(*ws_vector_int_at(vectorA, 2), *ws_vector_int_at(vectorB, 2));

    ws_vector_destroy(int, &vectorA);

    EXPECT_EQ(ws_vector_int_is_empty(vectorB), false);

    ws_vector_destroy(int, &vectorB);
}

TEST(copy_empty, vector)
{
    struct ws_vector_int vectorA = ws_vector_int_create(0);
    struct ws_vector_int vectorB = ws_vector_int_create(0);

    ws_vector_copy(int, &vectorB, &vectorA);

    ws_vector_destroy(int, &vectorA);
    ws_vector_destroy(int, &vectorB);
}

