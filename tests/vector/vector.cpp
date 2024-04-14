#include <gtest/gtest.h>

#define WSL_DEFINITION
#include <wsl/wsl.h>

WS_VECTOR(int)

TEST(vector, initialized_with_values)
{
    struct ws_vector_int vector = ws_vector_int_create(ws_vector_initialize(int, 69, 420, 720));

    EXPECT_EQ(vector.end, vector.size);
    EXPECT_EQ(ws_vector_int_size(vector), 3);
    EXPECT_EQ(*ws_vector_int_at(vector, 0), 69);
    EXPECT_EQ(*ws_vector_int_at(vector, 1), 420);
    EXPECT_EQ(*ws_vector_int_at(vector, 2), 720);

    ws_vector_destroy(int, &vector);
}

TEST(vector, push_values)
{
    struct ws_vector_int vector = ws_vector_int_create(0);

    ws_vector_int_push(&vector, 69);
    EXPECT_EQ(*ws_vector_int_back(vector), 69);
    ws_vector_int_push(&vector, 420);
    EXPECT_EQ(*ws_vector_int_back(vector), 420);
    ws_vector_int_push(&vector, 720);
    EXPECT_EQ(*ws_vector_int_back(vector), 720);

    EXPECT_EQ(vector.end, vector.size);
    EXPECT_EQ(ws_vector_int_size(vector), 3);

    ws_vector_destroy(int, &vector);
}

TEST(vector, pop_values)
{
    struct ws_vector_int vector = ws_vector_int_create(ws_vector_initialize(int, 69, 420, 720));

    EXPECT_EQ(ws_vector_int_size(vector), 3);
    EXPECT_EQ(ws_vector_int_pop(&vector), 720);
    EXPECT_EQ(ws_vector_int_size(vector), 2);
    EXPECT_EQ(ws_vector_int_pop(&vector), 420);
    EXPECT_EQ(ws_vector_int_size(vector), 1);
    EXPECT_EQ(ws_vector_int_pop(&vector), 69);
    EXPECT_EQ(ws_vector_int_size(vector), 0);

    EXPECT_EQ(vector.end, vector.size);

    ws_vector_destroy(int, &vector);
}

TEST(vector, pop_and_push_values)
{
    struct ws_vector_int vector = ws_vector_int_create(ws_vector_initialize(int, 69, 420, 720));

    EXPECT_EQ(ws_vector_int_size(vector), 3);

    EXPECT_EQ(ws_vector_int_pop(&vector), 720);
    EXPECT_EQ(ws_vector_int_size(vector), 2);

    {
        ws_vector_int_push(&vector, 360);
        EXPECT_EQ(ws_vector_int_size(vector), 3);
        EXPECT_EQ(ws_vector_int_pop(&vector), 360);
    }

    EXPECT_EQ(ws_vector_int_size(vector), 2);
    EXPECT_EQ(ws_vector_int_pop(&vector), 420);
    EXPECT_EQ(ws_vector_int_size(vector), 1);
    EXPECT_EQ(ws_vector_int_pop(&vector), 69);

    EXPECT_EQ(ws_vector_int_size(vector), 0);

    EXPECT_EQ(vector.end, vector.size);

    ws_vector_destroy(int, &vector);
}

int predicate(int const* lhs, int const* rhs)
{
    return *lhs > *rhs;
}

TEST(vector, clear_values)
{
    struct ws_vector_int vector = ws_vector_int_create(ws_vector_initialize(int, 69, 420, 720));

    ws_vector_clear(int, &vector);

    EXPECT_EQ(vector.data[0], 0);
    EXPECT_EQ(vector.data[1], 0);
    EXPECT_EQ(vector.data[2], 0);

    EXPECT_EQ(vector.end, vector.size);
    EXPECT_EQ(ws_vector_int_size(vector), 0);

    ws_vector_destroy(int, &vector);
}

TEST(vector, copy_values_empty)
{
    struct ws_vector_int vectorA = ws_vector_int_create(ws_vector_initialize(int, 69, 420, 720));
    struct ws_vector_int vectorB = ws_vector_int_create(0);

    ws_vector_copy(int, &vectorB, &vectorA);

    EXPECT_EQ(ws_vector_int_size(vectorA), ws_vector_int_size(vectorB));

    EXPECT_EQ(vectorB.data[0], vectorA.data[0]);
    EXPECT_EQ(vectorB.data[1], vectorA.data[1]);
    EXPECT_EQ(vectorB.data[2], vectorA.data[2]);

    EXPECT_EQ(vectorB.begin, vectorA.begin);
    EXPECT_EQ(vectorB.end, vectorA.end);
    EXPECT_EQ(vectorB.size, vectorA.size);
    EXPECT_EQ(vectorB.capacity, vectorA.capacity);

    ws_vector_destroy(int, &vectorA);

    EXPECT_EQ(ws_vector_int_is_empty(vectorB), false);

    ws_vector_destroy(int, &vectorB);
}

TEST(vector, copy_values_non_empty)
{
    struct ws_vector_int vectorA = ws_vector_int_create(ws_vector_initialize(int, 69, 420, 720));
    struct ws_vector_int vectorB = ws_vector_int_create(ws_vector_initialize(int, 69420));

    ws_vector_copy(int, &vectorB, &vectorA);

    EXPECT_EQ(ws_vector_int_size(vectorA), ws_vector_int_size(vectorB));

    EXPECT_EQ(vectorB.data[0], vectorA.data[0]);
    EXPECT_EQ(vectorB.data[1], vectorA.data[1]);
    EXPECT_EQ(vectorB.data[2], vectorA.data[2]);

    EXPECT_EQ(vectorB.begin, vectorA.begin);
    EXPECT_EQ(vectorB.end, vectorA.end);
    EXPECT_EQ(vectorB.size, vectorA.size);
    EXPECT_EQ(vectorB.capacity, vectorA.capacity);

    ws_vector_destroy(int, &vectorA);

    EXPECT_EQ(ws_vector_int_is_empty(vectorB), false);

    ws_vector_destroy(int, &vectorB);
}

TEST(vector, copy_empty)
{
    struct ws_vector_int vectorA = ws_vector_int_create(0);
    struct ws_vector_int vectorB = ws_vector_int_create(0);

    ws_vector_copy(int, &vectorB, &vectorA);

    EXPECT_EQ(vectorB.begin, vectorA.begin);
    EXPECT_EQ(vectorB.end, vectorA.end);
    EXPECT_EQ(vectorB.size, vectorA.size);
    EXPECT_EQ(vectorB.capacity, vectorA.capacity);

    ws_vector_destroy(int, &vectorA);
    ws_vector_destroy(int, &vectorB);
}

