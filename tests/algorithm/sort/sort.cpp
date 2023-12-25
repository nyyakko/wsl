#include <gtest/gtest.h>

#define WS_ALGORITHM_DEFINITION
#include <wsl/algorithm/ws_algorithm.h>

#define WS_VECTOR_DEFINITION
#include <wsl/ws_vector.h>

WS_VECTOR(int)

int predicate(void const* lhs, void const* rhs)
{
    return *(int const*)lhs > *(int const*)rhs;
}

TEST(algorithm, vector_sort)
{
    struct ws_vector_int vector = ws_vector_int_create(ws_vector_initialize(int, 69, 720, 420));

    ws_sort(&vector, predicate);

    EXPECT_EQ(*ws_vector_int_at(vector, 0), 720);
    EXPECT_EQ(*ws_vector_int_at(vector, 1), 420);
    EXPECT_EQ(*ws_vector_int_at(vector, 2), 69);

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

TEST(algorithm, vector_sort_with_projection)
{
    struct ws_vector_student vector = ws_vector_student_create(0);

    struct student studentA = { .id = 420 };
    ws_vector_student_push(&vector, studentA);
    struct student studentB = { .id = 69  };
    ws_vector_student_push(&vector, studentB);
    struct student studentC = { .id = 720 };
    ws_vector_student_push(&vector, studentC);

    ws_sort(&vector, predicate, (ws_projection*)student_get_id);

    EXPECT_EQ(ws_vector_student_at(vector, 0)->id, 720);
    EXPECT_EQ(ws_vector_student_at(vector, 1)->id, 420);
    EXPECT_EQ(ws_vector_student_at(vector, 2)->id, 69);

    ws_vector_destroy(student, &vector);
}


TEST(algorithm, c_array_sort)
{
    int array[3] = { 69, 720, 420 };

    ws_sort_ex(array, 0, 2, sizeof(int), predicate, nullptr);

    EXPECT_EQ(array[0], 720);
    EXPECT_EQ(array[1], 420);
    EXPECT_EQ(array[2], 69);
}

