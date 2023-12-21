#include <gtest/gtest.h>
#include <wsl/ws_linked_list.h>

WS_LINKED_LIST(int)

TEST(linked_list, initialized_with_values)
{
    struct ws_linked_list_int list = ws_linked_list_int_create(ws_linked_list_initialize(int, 69, 420, 720));

    EXPECT_EQ(list.head->value, 69);
    EXPECT_EQ(list.head->next->value, 420);
    EXPECT_EQ(list.head->next->next->value, 720);

    ws_linked_list_destroy(int, &list);
}

TEST(linked_list, push_front_values)
{
    struct ws_linked_list_int list = ws_linked_list_int_create(0);

    ws_linked_list_int_push_front(&list, 69);
    ws_linked_list_int_push_front(&list, 420);
    ws_linked_list_int_push_front(&list, 720);

    EXPECT_EQ(list.head->value, 720);
    EXPECT_EQ(list.head->next->value, 420);
    EXPECT_EQ(list.head->next->next->value, 69);

    ws_linked_list_destroy(int, &list);
}

TEST(linked_list, pop_front_values)
{
    struct ws_linked_list_int list = ws_linked_list_int_create(ws_linked_list_initialize(int, 69, 420, 720));

    EXPECT_EQ(ws_linked_list_int_pop_front(&list), 69);
    EXPECT_EQ(ws_linked_list_int_pop_front(&list), 420);
    EXPECT_EQ(ws_linked_list_int_pop_front(&list), 720);

    EXPECT_EQ(ws_linked_list_int_size(list), 0);

    ws_linked_list_destroy(int, &list);
}

TEST(linked_list, push_back_values)
{
    struct ws_linked_list_int list = ws_linked_list_int_create(0);

    ws_linked_list_int_push_back(&list, 69);
    ws_linked_list_int_push_back(&list, 420);
    ws_linked_list_int_push_back(&list, 720);

    EXPECT_EQ(list.head->value, 69);
    EXPECT_EQ(list.head->next->value, 420);
    EXPECT_EQ(list.head->next->next->value, 720);

    ws_linked_list_destroy(int, &list);
}

TEST(linked_list, pop_back_values)
{
    struct ws_linked_list_int list = ws_linked_list_int_create(ws_linked_list_initialize(int, 69, 420, 720));

    EXPECT_EQ(ws_linked_list_int_pop_back(&list), 720);
    EXPECT_EQ(ws_linked_list_int_pop_back(&list), 420);
    EXPECT_EQ(ws_linked_list_int_pop_back(&list), 69);

    EXPECT_EQ(ws_linked_list_int_size(list), 0);

    ws_linked_list_destroy(int, &list);
}

