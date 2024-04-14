#include <gtest/gtest.h>

#define WSL_DEFINITION
#include <wsl/wsl.h>

WS_VECTOR(int)

TEST(algorithm, vector_search)
{
    struct ws_vector_int vector = ws_vector_int_create(ws_vector_initialize(int, 69, 420, 720));
    EXPECT_NE(ws_search((ws_container_interface const*)&vector, ws_prvalue(int, 420)), nullptr);
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

    EXPECT_NE(ws_search((ws_container_interface const*)&vector, ws_prvalue(int, 420), nullptr, (ws_projection*)student_get_id), nullptr);
    EXPECT_EQ(ws_search((ws_container_interface const*)&vector, ws_prvalue(int, 720), nullptr, (ws_projection*)student_get_id), nullptr);

    ws_vector_destroy(student, &vector);
}

TEST(algorithm, c_array_search)
{
    int array[3] = { 69, 720, 420 };
    EXPECT_NE(ws_search_ex(array, 0, 3, sizeof(int), ws_prvalue(int, 420), nullptr, nullptr), nullptr);
}

