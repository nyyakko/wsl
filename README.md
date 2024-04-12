# ads library.

because c ain't got anything. lol.

# installation

you may copy the files under wsl/include into your project, install it with [CPM](https://github.com/cpm-cmake/CPM.cmake) or install directly into your system with the following: 

* ``py install.py``

and then include it with cmake into your project

```cmake
cmake_minimum_required_version(VERSION 3.25)

project(CoolProject LANGUAGES C)

find_package(wsl CONFIG REQUIRED)
add_executable(CoolProject source.c)
target_link_libraries(CoolProject PRIVATE wsl::wsl)
```

# examples
```c++
#include <wsl/ws_vector.h>

#include <stdio.h>

WS_VECTOR(int)

int main()
{
    struct ws_vector_int numbers = ws_vector_create(ws_vector_initialize(int, 1, 2, 3));

    for (size_t index = 0; index != ws_vector_size(numbers); index += 1)
    {
        printf("%s ", *ws_vector_at(numbers, index));
    }

    ws_vector_destroy(int, &numbers);
}
```

```c++
#include <wsl/ws_string_builder.h>

#include <stdio.h>

int main()
{
    struct ws_string_builder stringA = ws_string_builder_create("What a beautiful world");
    struct ws_string_builder stringB = ws_string_builder_create("Hello, ");

    ws_string_builder_chop_until_last(&stringA, ' ');
    ws_string_builder_append_string_while(&stringB, stringA.data, isalpha);

    printf("%s\n", stringB.data); // output: Hello, World

    ws_string_builder_destroy(&stringB);
    ws_string_builder_destroy(&stringA);
}
```

i recommend you to simply explore the code and see what you can do with it. seriously. do it.
