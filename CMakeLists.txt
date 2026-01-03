
# SET CMAKE TARGET NAME HERE:
set(APP_TARGET Template)

cmake_minimum_required(VERSION 3.16)
project(${APP_TARGET})


option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

#---- Fetch SFML, only works if you have git installed on your machine ----#

include(FetchContent)   # Allows fetching content remotely at configure time
FetchContent_Declare(   # Fetches SFML from github and puts it in the build directory
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 69ea0cd863aed1d4092b970b676924a716ff718b    # Makes sure to fetch SFML version 2.6.1
)

FetchContent_MakeAvailable(SFML)    # Makes sure SFML and its dependencies are available for the project

#---- File management & .exe creation ----#

file(GLOB_RECURSE LIBRARY_FILES "Libraries/*.cpp" "Libraries/*.h" "Libraries/*.hpp")
file(GLOB_RECURSE GAME_OBJECTS "src/GameObjects/*.cpp" "src/GameObjects/*.h" "src/GameObjects/*.hpp")
file(GLOB_RECURSE SCENES "src/Scenes/*.cpp" "src/Scenes/*.h" "src/Scenes/*.hpp")
file(GLOB_RECURSE SCRIPTS "src/Scripts/*.cpp" "src/Scripts/*.h" "src/Scripts/*.hpp")
set(SOURCE_FILES "src/main.cpp" )  # Sets variable SOURCE_FILES to hold names & locations of files that need to be compiled into the application

set (ALL_FILES  ${LIBRARY_FILES} ${SOURCE_FILES} ${GAME_OBJECTS} ${SCENES} ${SCRIPTS})
add_executable(${APP_TARGET} ${ALL_FILES} )  # Names the application and tells compiler which source files to use

target_link_libraries(${APP_TARGET} PRIVATE sfml-graphics sfml-window sfml-system sfml-network sfml-audio) # Links the SFML libraries we need to our application
target_compile_features(${APP_TARGET} PRIVATE cxx_std_20)  # Defines which standard of C++ the compiler should use

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Data/)  # Copies data from source directory to build directory (so the executable can access it)

if(WIN32)
    add_custom_command(
        TARGET ${APP_TARGET}
        COMMENT "Copy OpenAL DLL to build directory so app can have sound"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${APP_TARGET}>
        VERBATIM)
    add_custom_command(
            TARGET ${APP_TARGET}
            COMMENT "Delete and Re-Copy Data Folder so app has most up to-date asset folders"
            PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E rm -rf $<TARGET_FILE_DIR:${APP_TARGET}>/data
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/data
            $<TARGET_FILE_DIR:${APP_TARGET}>/data
    )
endif()
