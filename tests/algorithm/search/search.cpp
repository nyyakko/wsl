#include <gtest/gtest.h>

#include <wsl/algorithm/ws_algorithm.h>

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

typedef void const*(projection_t)(void const*);

TEST(algorithm, vector_search_with_projection)
{
    struct ws_vector_student vector = ws_vector_student_create(0);

    struct student student = { .id = 420 };
    ws_vector_student_push(&vector, student);

    int valueA = 420;
    EXPECT_NE(ws_search(&vector, &valueA, (projection_t*)student_get_id), nullptr);
    int valueB = 720;
    EXPECT_EQ(ws_search(&vector, &valueB, (projection_t*)student_get_id), nullptr);

    ws_vector_destroy(student, &vector);
}

TEST(algorithm, c_array_search)
{
    int array[3] = { 69, 720, 420 };

    int value = 420;
    EXPECT_NE(ws_search_ex(array, 0, 2, sizeof(int), &value, nullptr, nullptr), nullptr);
}

