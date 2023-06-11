#[[ Library creation details - use this to create libraries which can break project up into manageable 
    pieces instead of compiling all through add_executable function.
    add_library(<library name> <library type> <source files with relative path>)
    STATIC is the default and does not need declaring - all code compiled and linked into executable, 
    meaning only executable file needs to be shared (SHARED can be set for smaller executable but other
    files will be created which the executable will rely on)
    e.g: ]]
add_library(container STATIC
            container/container.cpp
            container/container.h
            container/chest.cpp
            container/chest.h)

#[[ ]]
add_library(placeholders STATIC
            container/placeholder_creature_classes.cpp
            container/placeholder_item_classes.cpp)

# add_library(display STATIC
#             display/window.cpp
#             display/appWindow.cpp)

add_library(display STATIC
            display/console.cpp
            display/intro.cpp
            display/menu.cpp
            display/quitMenu.cpp
            display/window.cpp
            display/mainMenu.cpp)

# configure_file(display/intro_background.bmp intro_background.bmp COPYONLY)

#[[ Not needed if library directories are nested within target's directory, but will be needed if target
    is moved parallel. "${CMAKE_CURRENT_SOURCE_DIRECTORY}" is the directory of the current CMakeLists.txt file.
target_include_directories(CMake_target PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/containers") ]]