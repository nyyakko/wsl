set(wsl_TestsCompilerOptions ${wsl_TestsCompilerOptions}
    -Wno-unused-function
    -Wno-c99-extensions
    -Wno-vla-extension
    -Wno-gnu-statement-expression-from-macro-expansion
)

add_subdirectory(algorithm)
add_subdirectory(filesystem)

add_subdirectory(vector)
add_subdirectory(stack)
add_subdirectory(queue)
add_subdirectory(string_view)
add_subdirectory(string_builder)
add_subdirectory(linked_list)
add_subdirectory(binary_tree)
add_subdirectory(hash_map)

