include(FetchContent)

set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

# Getting googletest sources from GitHub repository
FetchContent_Declare(
    magic_enum
    GIT_REPOSITORY https://github.com/Neargye/magic_enum.git
    GIT_TAG        e55b9b54d5cf61f8e117cafb17846d7d742dd3b4 # v0.9.5
)

# Compiling googletest library
FetchContent_MakeAvailable(magic_enum)
