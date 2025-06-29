set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
  GIT_SHALLOW TRUE)

if(NOT CMAKE_HOST_SYSTEM_NAME MATCHES "Windows" AND MSVC)
  set(gtest_disable_pthreads
      OFF ON
      CACHE BOOL "" FORCE)
endif()
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
  subprocess
  GIT_REPOSITORY https://github.com/shediao/subprocess.hpp
  GIT_TAG v0.0.5)
FetchContent_MakeAvailable(subprocess)

FetchContent_Declare(
  environment
  GIT_REPOSITORY https://github.com/shediao/environment.hpp
  GIT_TAG v0.0.4)
FetchContent_MakeAvailable(environment)

function(add_md5_test test_name test_files)
  add_executable(${test_name} ${test_files})
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU"
     OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang"
     OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    if(NOT MSVC)
      target_compile_options(${test_name} PRIVATE -Wall -Wextra -Werror)
    endif()
  endif()
  if(MSVC)
    target_compile_options(${test_name} PRIVATE /utf-8 /EHsc /W4)
  endif()

  target_link_libraries(
    ${test_name}
    PRIVATE md5::md5 subprocess::subprocess environment::environment
            GTest::gtest GTest::gtest_main)
  add_test(NAME ${test_name} COMMAND ${test_name})
endfunction()

file(GLOB test_files "*.cc")

foreach(test_file ${test_files})
  get_filename_component(test_name ${test_file} NAME_WE)
  add_md5_test(${test_name} ${test_file})
endforeach()

add_md5_test(all_test "${test_files}")
