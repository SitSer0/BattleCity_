cmake_minimum_required(VERSION 3.27)
project(BattleCity)

# Установите стандарт C++.
set(CMAKE_CXX_STANDARD 17)

# Добавьте путь к заголовочным файлам SDL2 и SDL2_image.
include_directories(/opt/homebrew/include/SDL2)

# Создайте исполняемый файл для вашего проекта.
add_executable(BattleCity main.cpp
        Objects/Object.cpp
        Objects/Object.h
        Objects/Tanks/Tank.cpp
        Objects/Tanks/Tank.h
        Objects/Bullets/Bullet.cpp
        Objects/Bullets/Bullet.h
        constatnti_itd.h
        GameProcess/Game.cpp
        GameProcess/Game.h
        Objects/Blocks/Block.cpp
        Objects/Blocks/Block.h
        Objects/Blocks/Stone/Stone.cpp
        Objects/Blocks/Stone/Stone.h
        Objects/Blocks/Bushes/Bushes.cpp
        Objects/Blocks/Bushes/Bushes.h
        Objects/Blocks/BrickWall/Brick.cpp
        Objects/Blocks/BrickWall/Brick.h
        levels/levels.h
        CreatingLevels/CreatingLevel.cpp
        CreatingLevels/CreatingLevel.h
        Objects/Tanks/Mouse/Mouse.cpp
        Objects/Tanks/Mouse/Mouse.h
        Objects/Tanks/Panther/Panther.cpp
        Objects/Tanks/Panther/Panther.h
        Objects/Tanks/Tiger/Tiger.cpp
        Objects/Tanks/Tiger/Tiger.h
        Objects/Tanks/T34/T34.cpp
        Objects/Tanks/T34/T34.h
        Player.cpp
        Player.h
        Objects/Base/Base.cpp
        Objects/Base/Base.h
        GameProcess/SoloGame.cpp
        GameProcess/SoloGame.h)

# Укажите полный путь к библиотекам SDL2 и SDL2_image.
find_library(SDL2_LIBRARY NAME SDL2 PATHS /opt/homebrew/lib)
find_library(SDL2_IMAGE_LIBRARY NAME SDL2_image PATHS /opt/homebrew/lib)

# Связывание вашего проекта с найденными библиотеками SDL2 и SDL2_image.
target_link_libraries(BattleCity ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})
