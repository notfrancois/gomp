file(GLOB_RECURSE SOURCES "src/*.cpp" "src/api/*.cpp" "src/extensions/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp" "include/**/*.hpp" "src/*.hpp")

add_library(Gomp SHARED ${SOURCES} ${HEADERS})

target_include_directories(Gomp
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(Gomp PRIVATE OMP-SDK OMP-Network samp-streamer-plugin)
set_target_properties(Gomp PROPERTIES PREFIX "")

if(TARGET_BUILD_ARCH MATCHES "(i[3-6]86|x86)" AND NOT TARGET_BUILD_ARCH MATCHES "(x64|x86_64|amd64)")
    set(CMAKE_C_FLAGS "-m32 ${CMAKE_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "-m32 ${CMAKE_CXX_FLAGS}")
    set(CMAKE_SIZEOF_VOID_P 4)
endif()