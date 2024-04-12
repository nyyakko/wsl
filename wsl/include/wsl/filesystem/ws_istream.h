#ifndef WS_ISTREAM
#define WS_ISTREAM

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

struct ws_istream_state
{
    bool ignoreWhiteSpace : 1;
};

struct ws_istream
{
    FILE* handle;
    struct ws_istream_state state;
};

typedef void(strategy_t)(void*, char);

[[nodiscard]] bool ws_istream_eof(struct ws_istream* stream);
void ws_istream_ignore_whitespaces(struct ws_istream* stream, bool should);
[[nodiscard]] char ws_istream_peek(struct ws_istream* stream);
void ws_istream_unread_char(struct ws_istream* stream, char byte);
[[nodiscard]] char ws_istream_read_char(struct ws_istream* stream);
void ws_istream_read_to_buffer(struct ws_istream* stream, char* destination, size_t destinationSize);
void ws_istream_read_to_container(struct ws_istream* stream, void* destination, strategy_t* strategy);
void ws_istream_read_line_to_buffer(struct ws_istream* stream, char* destination, size_t destinationSize);
void ws_istream_read_line_to_container(struct ws_istream* stream, void* destination, strategy_t* strategy);
[[nodiscard]] struct ws_istream ws_istream_open(char const* file);
void ws_istream_close(struct ws_istream* stream);

#ifdef WS_FILE_ISTREAM_DEFINITION

bool ws_istream_eof(struct ws_istream* stream)
{
    assert(stream != nullptr && "STREAM POINTER WAS NULL");
    assert(stream->handle != nullptr && "FILE HANDLE WAS NULL");
    return ws_istream_peek(stream) == EOF;
}

void ws_istream_ignore_whitespaces(struct ws_istream* stream, bool should)
{
    assert(stream != nullptr && "STREAM POINTER WAS NULL");
    stream->state.ignoreWhiteSpace = should;
}

char ws_istream_peek(struct ws_istream* stream)
{
    assert(stream != nullptr && "STREAM POINTER WAS NULL");
    char peeked = ws_istream_read_char(stream);
    ws_istream_unread_char(stream, peeked);
    return peeked;
}

void ws_istream_unread_char(struct ws_istream* stream, char byte)
{
    assert(stream != nullptr && "STREAM POINTER WAS NULL");
    (void)ungetc(byte, stream->handle);
}

char ws_istream_read_char(struct ws_istream* stream)
{
    assert(stream != nullptr && "STREAM POINTER WAS NULL");
    return (char)fgetc(stream->handle);
}

void ws_istream_read_to_buffer(struct ws_istream* stream, char* destination, size_t destinationSize)
{
    assert(stream != nullptr && "STREAM POINTER WAS NULL");
    assert(destination != nullptr && "DESTINATION POINTER WAS NULL");

    for (size_t index = 0; index != destinationSize && !ws_istream_eof(stream); index += 1)
    {
        if ((stream->state.ignoreWhiteSpace
                && isspace(ws_istream_peek(stream))) || ws_istream_peek(stream) == '\n')
        {
            (void)ws_istream_read_char(stream);
            break;
        }

        destination[index] = ws_istream_read_char(stream);
    }
}

void ws_istream_read_to_container(struct ws_istream* stream, void* destination, strategy_t* strategy)
{
    assert(stream != nullptr && "STREAM POINTER WAS NULL");
    assert(destination != nullptr && "DESTINATION POINTER WAS NULL");

    while (!ws_istream_eof(stream))
    {
        if ((stream->state.ignoreWhiteSpace
                && isspace(ws_istream_peek(stream))) || ws_istream_peek(stream) == '\n')
        {
            (void)ws_istream_read_char(stream);
            break;
        }

        strategy(destination, ws_istream_read_char(stream));
    }
}

void ws_istream_read_line_to_buffer(struct ws_istream* stream, char* destination, size_t destinationSize)
{
    assert(stream != nullptr && "STREAM POINTER WAS NULL");
    assert(destination != nullptr && "DESTINATION POINTER WAS NULL");

    for (size_t index = 0; index != destinationSize && !ws_istream_eof(stream); index += 1)
    {
        if (ws_istream_peek(stream) == '\n')
        {
            (void)ws_istream_read_char(stream);
            break;
        }

        destination[index] = ws_istream_read_char(stream);
    }
}

void ws_istream_read_line_to_container(struct ws_istream* stream, void* destination, strategy_t* strategy)
{
    assert(stream != nullptr && "STREAM POINTER WAS NULL");
    assert(destination != nullptr && "DESTINATION POINTER WAS NULL");
    assert(strategy != nullptr && "STRATEGY POINTER WAS NULL");

    while (!ws_istream_eof(stream))
    {
        if (ws_istream_peek(stream) == '\n')
        {
            (void)ws_istream_read_char(stream);
            break;
        }

        strategy(destination, ws_istream_read_char(stream));
    }
}

struct ws_istream ws_istream_open(char const* file)
{
    struct ws_istream stream =
    {
#if !(defined(_WIN32) && defined(_WIN64))
        .handle = fopen(file, "r"),
#else
        .handle = nullptr,
#endif
        .state  = {
            .ignoreWhiteSpace = true
        }
    };

#if defined(_WIN32) || defined(_WIN64)
    (void)fopen_s(&stream.handle, file, "r");
#endif

    return stream;
}

void ws_istream_close(struct ws_istream* stream)
{
    (void)fclose(stream->handle);
    stream->handle = nullptr;
    stream->state  = (struct ws_istream_state){};
}

#endif

#endif

