set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(wsl_HeaderFiles ${wsl_HeaderFiles}
    "${DIR}/ws_clear.h"
    "${DIR}/ws_count.h"
    "${DIR}/ws_search.h"
    "${DIR}/ws_sort.h"

    PARENT_SCOPE
)
