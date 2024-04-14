add_subdirectory(algorithm)
add_subdirectory(filesystem)

set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(wsl_HeaderFiles ${wsl_HeaderFiles}
    "${DIR}/ws_binary_tree.h"
    "${DIR}/ws_hash_map.h"
    "${DIR}/ws_linked_list.h"
    "${DIR}/ws_queue.h"
    "${DIR}/ws_stack.h"
    "${DIR}/ws_string_builder.h"
    "${DIR}/ws_string_view.h"
    "${DIR}/ws_vector.h"
    "${DIR}/wsl.h"

    PARENT_SCOPE
)

