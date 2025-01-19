# Define the executable

add_executable(${PROJECT_NAME}
    mainwin.cpp)


target_link_libraries(${PROJECT_NAME} PRIVATE Crow::Crow)

