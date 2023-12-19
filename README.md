# wellington standard library (WSL)

funny library i use to do some C stuff. ***i do not recommend*** it to anyone but myself or people who just want to have some fun, if you're looking for production ready code ... what the hell are you doing in here?

## examples:

* ### vector
```c
#include <wsl/ws_vector.h>

#include <stdio.h>

WS_VECTOR(int)

int main(void)
{
    struct ws_vector_int vector = ws_vector_int_create(ws_vector_initialize(int, 69, 420));

    ws_vector_int_push(&vector, 720);

    // output: 69 420 720
    for (size_t index = 0; index != vector.size; vector += 1)
    {
        printf("%d ", *ws_vector_int_at(vector, index));
    }

    ws_vector_destroy(int, &vector);
}
```
* ### string_builder
```c
#include <wsl/ws_string_builder.h>

#include <stdio.h>

int main(void)
{
    struct ws_string_builder string = ws_string_builder_create("Hello, ");

    ws_string_builder_append_string(&string, "world!");
    printf("%s\n", string.data); // output: Hello, world!

    ws_string_builder_chop_until_last(&string, ' ');
    printf("%s\n", string.data); // output: world!

    ws_string_builder_destroy(&string);
}
```

if you need more examples, you're out of luck, i am not giving more examples to you. i am not your babysitter. go read the code.
