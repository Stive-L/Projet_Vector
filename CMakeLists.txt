cmake_minimum_required(VERSION 3.25)
project(Projet C)

set(CMAKE_C_STANDARD 11)


add_executable(Projet main.c shapes.c include/shapes.h area.c include/area.h commandes.c include/commandes.h)
