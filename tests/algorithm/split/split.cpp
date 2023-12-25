#include <gtest/gtest.h>

#define WS_ALGORITHM_DEFINITION
#include <wsl/algorithm/ws_algorithm.h>
#define WS_VECTOR_DEFINITION
#include <wsl/ws_vector.h>

WS_VECTOR(int)

TEST(algorithm, vector_split)
{
    struct ws_vector_int vector = ws_vector_int_create(ws_vector_initialize(int, 69, 720, 69, 420));

    int delimiter = 69;

    struct ws_vector_ws_generic_t result = ws_split(&vector, &delimiter);

    EXPECT_EQ(ws_vector_ws_generic_t_size(result), 2);

    EXPECT_EQ(*(int const*)(*ws_vector_ws_generic_t_at(result, 0)), 720);
    EXPECT_EQ(*(int const*)(*ws_vector_ws_generic_t_at(result, 1)), 420);

    ws_vector_destroy(ws_generic_t, &result, ws_generic_destroy);
    ws_vector_destroy(int, &vector);
}

TEST(algorithm, c_array_split)
{
    int array[4] = { 69, 720, 69, 420 };

    int delimiter = 69;

    struct ws_vector_ws_generic_t result = ws_split_ex(array, 0, 3, sizeof(int), &delimiter, nullptr, nullptr);

    EXPECT_EQ(ws_vector_ws_generic_t_size(result), 2);

    EXPECT_EQ(*(int const*)(*ws_vector_ws_generic_t_at(result, 0)), 720);
    EXPECT_EQ(*(int const*)(*ws_vector_ws_generic_t_at(result, 1)), 420);

    ws_vector_destroy(ws_generic_t, &result, ws_generic_destroy);
}

