#define WS_ISTREAM_DEFINITION

#include <gtest/gtest.h>
#include <wsl/filesystem/ws_istream.h>

TEST(istream, open_empty)
{
    struct ws_istream stream = ws_istream_open(CWD"/files/empty.txt");
    EXPECT_EQ(ws_istream_eof(&stream), true);
    ws_istream_close(&stream);
}

TEST(istream, open_non_empty)
{
    {
        struct ws_istream stream = ws_istream_open(CWD"/files/single_line.txt");
        EXPECT_EQ(ws_istream_eof(&stream), false);
        ws_istream_close(&stream);
    }
    {
        struct ws_istream stream = ws_istream_open(CWD"/files/multi_line.txt");
        EXPECT_EQ(ws_istream_eof(&stream), false);
        ws_istream_close(&stream);
    }
}

TEST(istream, single_line_file_read_to_buffer_ignore_whitespaces)
{
    struct ws_istream stream = ws_istream_open(CWD"/files/single_line.txt");

    char buffer[1024] = {};
    ws_istream_read_to_buffer(&stream, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "hello");
    EXPECT_EQ(ws_istream_eof(&stream), false);

    ws_istream_close(&stream);
}

TEST(istream, single_line_file_read_to_buffer_no_ignore_whitespaces)
{
    struct ws_istream stream = ws_istream_open(CWD"/files/single_line.txt");

    ws_istream_ignore_whitespaces(&stream, false);

    char buffer[1024] = {};
    ws_istream_read_to_buffer(&stream, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "hello world!");
    EXPECT_EQ(ws_istream_eof(&stream), true);

    ws_istream_close(&stream);
}

TEST(istream, single_line_file_read_line_to_buffer)
{
    struct ws_istream stream = ws_istream_open(CWD"/files/single_line.txt");

    char buffer[1024] = {};
    ws_istream_read_line_to_buffer(&stream, buffer, sizeof(buffer));
    EXPECT_STREQ(buffer, "hello world!");
    EXPECT_EQ(ws_istream_eof(&stream), true);

    ws_istream_close(&stream);
}

TEST(istream, multi_line_file_read_to_buffer_ignore_whitespaces)
{
    struct ws_istream stream = ws_istream_open(CWD"/files/multi_line.txt");

    {
        char buffer[1024] = {};
        ws_istream_read_to_buffer(&stream, buffer, sizeof(buffer));
        EXPECT_STREQ(buffer, "how");
        EXPECT_EQ(ws_istream_eof(&stream), false);
    }
    {
        char buffer[1024] = {};
        ws_istream_read_to_buffer(&stream, buffer, sizeof(buffer));
        EXPECT_STREQ(buffer, "are");
        EXPECT_EQ(ws_istream_eof(&stream), false);
    }

    ws_istream_close(&stream);
}

TEST(istream, multi_line_file_read_to_buffer_no_ignore_whitespaces)
{
    struct ws_istream stream = ws_istream_open(CWD"/files/multi_line.txt");

    ws_istream_ignore_whitespaces(&stream, false);

    {
        char buffer[1024] = {};
        ws_istream_read_to_buffer(&stream, buffer, sizeof(buffer));
        EXPECT_STREQ(buffer, "how are you?");
        EXPECT_EQ(ws_istream_eof(&stream), false);
    }
    {
        char buffer[1024] = {};
        ws_istream_read_to_buffer(&stream, buffer, sizeof(buffer));
        EXPECT_STREQ(buffer, "fine thank you!");
        EXPECT_EQ(ws_istream_eof(&stream), true);
    }

    ws_istream_close(&stream);
}

TEST(istream, multi_line_file_read_line_to_buffer)
{
    struct ws_istream stream = ws_istream_open(CWD"/files/multi_line.txt");

    ws_istream_ignore_whitespaces(&stream, false);

    {
        char buffer[1024] = {};
        ws_istream_read_line_to_buffer(&stream, buffer, sizeof(buffer));
        EXPECT_STREQ(buffer, "how are you?");
        EXPECT_EQ(ws_istream_eof(&stream), false);
    }
    {
        char buffer[1024] = {};
        ws_istream_read_line_to_buffer(&stream, buffer, sizeof(buffer));
        EXPECT_STREQ(buffer, "fine thank you!");
        EXPECT_EQ(ws_istream_eof(&stream), true);
    }

    ws_istream_close(&stream);
}

