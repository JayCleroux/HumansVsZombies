cmake_minimum_required(VERSION 3.21)
project(HumansVsZombies)

set(CMAKE_CXX_STANDARD 23)

add_executable(HumansVsZombies src/main.cpp src/City.cpp src/Organism.cpp src/Human.cpp src/Zombie.cpp)
