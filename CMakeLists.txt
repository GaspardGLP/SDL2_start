cmake_minimum_required(VERSION 3.29)
project(SDL_start C)

set(CMAKE_C_STANDARD 11)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)

include_directories( ${SDL2_INCLUDE_DIR} )

add_executable(SDL_start
        main.c
        init.c
        events.c
        game_logic.c
        render.c
        menu.c
        button.c
        score.c
        utils.c
)

target_link_libraries(SDL_start
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)
target_link_libraries(SDL_start
        PRIVATE
        $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>
)
