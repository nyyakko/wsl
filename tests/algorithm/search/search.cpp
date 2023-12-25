#include <gtest/gtest.h>

#define WS_ALGORITHM_DEFINITION
#include <wsl/algorithm/ws_algorithm.h>

#define WS_VECTOR_DEFINITION
#include <wsl/ws_vector.h>

WS_VECTOR(int)

TEST(algorithm, vector_search)
{
    struct ws_vector_int vector = ws_vector_int_create(ws_vector_initialize(int, 69, 420, 720));

    int value = 420;
    EXPECT_NE(ws_search(&vector, &value), nullptr);

    ws_vector_destroy(int, &vector);
}

struct student
{
    int id;
};

typedef struct student student;

WS_VECTOR(student)

int const* student_get_id(struct student const* student)
{
    return &student->id;
}

TEST(algorithm, vector_search_with_projection)
{
    struct ws_vector_student vector = ws_vector_student_create(0);

    struct student student = { .id = 420 };
    ws_vector_student_push(&vector, student);

    int valueA = 420;
    EXPECT_NE(ws_search(&vector, &valueA, nullptr, (ws_projection*)student_get_id), nullptr);
    int valueB = 720;
    EXPECT_EQ(ws_search(&vector, &valueB, nullptr, (ws_projection*)student_get_id), nullptr);

    ws_vector_destroy(student, &vector);
}

TEST(algorithm, c_array_search)
{
    int array[3] = { 69, 720, 420 };

    int value = 420;
    EXPECT_NE(ws_search_ex(array, 0, 2, sizeof(int), &value, nullptr, nullptr), nullptr);
}

