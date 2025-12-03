cmake_minimum_required(VERSION 3.5)

project(SIGDET VERSION 1.0 LANGUAGES CXX)

# Usar C++17 (suficiente para tu curso y Qt)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Detectar Qt automáticamente (funciona para Qt 5 y Qt 6)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
# Para Qt6, descomenta:
# find_package(Qt6 COMPONENTS Widgets REQUIRED)

# Archivos fuente
set(SOURCES
    Sources/main.cpp
    Sources/donacion.cpp
)

# Archivos de header
set(HEADERS
    Headers/donacion.h
)

# Formularios .ui
set(FORMS
    Forms/donacion.ui
)

# Generar código de UI, MOC y recursos
qt5_wrap_ui(UI_HEADERS ${FORMS})
qt5_wrap_cpp(MOC_SOURCES ${HEADERS})

# Crear el ejecutable final
add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${UI_HEADERS}
    ${MOC_SOURCES}
)

# Vincular librerías Qt
target_link_libraries(${PROJECT_NAME}
    Qt5::Widgets
)

# Para Qt6:
# target_link_libraries(${PROJECT_NAME}
#     Qt6::Widgets
# )

