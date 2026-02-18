cmake_minimum_required(VERSION 3.16)

project(inventory LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(inventory main.cpp
    item.h item.cpp
    inventory.h inventory.cpp
    player.h player.cpp
    game.h game.cpp
    charCheck.h
    random.h random.cpp
    menu.h menu.cpp
    shop.h shop.cpp
    store.h store.cpp
    gridbase.h gridbase.cpp
    equipment.h equipment.cpp


)

include(GNUInstallDirs)
install(TARGETS inventory
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
