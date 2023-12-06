cmake_minimum_required(VERSION 3.8)

project(opengl_learning VERSION 1.0)

# Version c++
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Creamos la variable y le asignamos el valor "src/main.cpp" que es la ubicación de nuestro archivo.
# Por defecto las variables son listas o arrays
# Si tenemos dos archivos sería SET(<NOMBRE_VARIABLE> "src/main.cpp" "src/segundo.cpp")
# Se permite multilínea
set(opengl_learning_src "./main.cpp")

# ----- OTHER CONFIGS ----- #

set(BUILD_PATH ${CMAKE_SOURCE_DIR}/bin/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BUILD_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BUILD_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${BUILD_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${BUILD_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${BUILD_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${BUILD_PATH})

# ----- END OTHER CONFIGS ----- #

# ----- LIBRERIAS EXTERNAS ----- #

# Una de las características más interesantes de CMake es que es capaz de encontrar librerías externas 
# que necesite nuestro programa. Esta característica se implementa con plugins de CMake

# Windows graphics
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
# JSON LIBRARY
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
# SQLITE3
find_package(SQLite3 REQUIRED)
# ASSIMP
find_package(assimp REQUIRED)
# FREETYPE
find_package(Freetype REQUIRED)

# En grandes librerías, podemos pedir solo ciertos componentes
# con el comando COMPONENTS
# find_package(wxWidgets COMPONENTS core gl html base net)
# Si todo va bien, tenemos las variables wxWidgets_FOUND, wxWidgets_LIBRARIES y wxWidgets_INCLUDE_DIR

include_directories(${OPENGL_INCLUDE_DIR} 
    ${GLEW_INCLUDE_DIR} 
    ${SQLite3_INCLUDE_DIRS}
    ${FREETYPE_INCLUDE_DIRS})

# ----- FIN LIBRERIAS EXTERNAS ----- #

# ----- CONDICIONALES ----- #

# option(NOMBRE_VARIABLE DESCRIPCION_LEGIBLE VALOR_POR_DEFECTO)
# on/off es la pareja de valores booleanos en CMake. TRUE/FALSE también es correcto
option(EXPERIMENTAL_FEATURE "Activar característica experimental" off)

# El condicional más básico
if(EXPERIMENTAL_FEATURE)
# Añadimos un elemento a la lista
list(APPEND opengl_learning_src "experimental_feature.cpp")
# También se puede hacer con SET
# SET(opts_src ${opts_src} "experimental_feature.cpp")
ENDIF()

# ----- FIN CONDICIONALES ----- #

# ----- FILES ----- #

# that's just quick and dirty folder cleanup, actually CMake would detect what has changed
# file(REMOVE_RECURSE ${BUILD_PATH})
# file(MAKE_DIRECTORY  ${BUILD_PATH})

# FILE GLOB selecciona todos los archivos que cumplan la característica y los almacena en libs_src
# GLOB no es recursivo. Si lo necesitas, usa GLOB_RECURSE
file(GLOB_RECURSE libs_src 
    "libs/*.h" "libs/*.hpp" "libs/*.cpp"
    "src/*.h" "src/*.cpp"
)

file(GLOB shaders 
    "shaders/*"
)
file(COPY ${shaders} DESTINATION ${BUILD_PATH}/shaders)

file(GLOB assets
    "assets/*")
file(COPY ${assets} DESTINATION ${BUILD_PATH}/assets)

# ----- FIN FILES ----- #

# Se creará un ejecutable llamado opts en Linux o opts.exe en Windows
# Se hace referencia a las variables con ${NOMBRE_VARIABLE}
add_executable(opengl_learning ${opengl_learning_src} ${libs_src})
target_link_libraries(opengl_learning 
    ${OPENGL_gl_LIBRARY} 
    ${GLEW_LIBRARIES} 
    glfw 
    ${JSONCPP_LIBRARIES} 
    ${SQLite3_LIBRARIES}
    assimp
    ${FREETYPE_LIBRARIES})