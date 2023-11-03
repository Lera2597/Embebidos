# Version Minima requerida de CMake
cmake_minimum_required(VERSION 3.12)

#Incluir funiones de sdk de pico
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

#Nombre del proyecto y estandares del lenguaje aceptados 
project(myblink C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
 
#Iicializacion de varios elementos del proyecto
pico_sdk_init()

#Indicarle a CMake los archivos de nuestro programa
add_executable(${PROJECT_NAME}
    main.c
)

# Crear archivos de salida
pico_add_extra_outputs(${PROJECT_NAME})

#Enlazar a las librerias requeridas
target_link_libraries(${PROJECT_NAME}
    pico_stdlib
)