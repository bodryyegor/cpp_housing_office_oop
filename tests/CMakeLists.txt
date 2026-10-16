file(GLOB TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/test_*.cpp
)

foreach(TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)

    add_executable(${TEST_NAME} ${TEST_SOURCE})

    target_link_libraries(${TEST_NAME}
        PRIVATE
            HousingManagementSystem_lib
            Catch2::Catch2WithMain
    )

    target_include_directories(${TEST_NAME}
        PRIVATE
            ${CMAKE_SOURCE_DIR}/include
    )

    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()
