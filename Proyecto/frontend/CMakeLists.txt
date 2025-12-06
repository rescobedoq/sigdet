cmake_minimum_required(VERSION 3.16)

project(TO-Donaciones VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Svg Charts Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Svg Charts Sql)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    find_package(Qt6 REQUIRED COMPONENTS Widgets)

    qt_add_executable(TO-Donaciones
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        sidebarView.h sidebarView.cpp
        resources.qrc
        iconhelperController.h iconhelperController.cpp
        inventarioView.h inventarioView.cpp

        styles.qrc
        donacionesrecibidasView.h donacionesrecibidasView.cpp
        tablewidgetcardView.h tablewidgetcardView.cpp
        donacionesenviadasView.h donacionesenviadasView.cpp
        donantesView.h donantesView.cpp
        beneficiarioView.h beneficiarioView.cpp
        informesView.h informesView.cpp
        ayudaView.h ayudaView.cpp
        databasemanagerController.h databasemanagerController.cpp
        conexiondbhelperController.h conexiondbhelperController.cpp
        registromodalView.h registromodalView.cpp
        loginwindowView.h loginwindowView.cpp
        userModel.h userModel.cpp
        donanteModel.h donanteModel.cpp
        beneficiarioModel.h beneficiarioModel.cpp


    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET TO-Donaciones APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(TO-Donaciones SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(TO-Donaciones
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(TO-Donaciones PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Svg
    Qt${QT_VERSION_MAJOR}::Charts
    Qt${QT_VERSION_MAJOR}::Sql     # 👈 AGREGA ESTA LÍNEA
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.TO-Donaciones)
endif()
set_target_properties(TO-Donaciones PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS TO-Donaciones
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TO-Donaciones)
endif()

# --- Copiar DLLs de PostgreSQL automáticamente ---
if(WIN32)
    # Ruta local a las DLL de PostgreSQL (dentro del proyecto)
    set(POSTGRES_DLL_DIR "${CMAKE_SOURCE_DIR}/PostGreDll")

    message(STATUS "📦 Buscando DLLs de PostgreSQL en: ${POSTGRES_DLL_DIR}")

    # Lista de DLLs que deben copiarse
    set(POSTGRES_DLLS
        libpq.dll
        libssl-3-x64.dll
        libcrypto-3-x64.dll
        libiconv-2.dll
        libintl-9.dll
    )

    # Verifica si existen y copia las DLLs necesarias
    foreach(DLL_FILE IN LISTS POSTGRES_DLLS)
        if(EXISTS "${POSTGRES_DLL_DIR}/${DLL_FILE}")
            add_custom_command(TARGET TO-Donaciones POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "${POSTGRES_DLL_DIR}/${DLL_FILE}"
                    "$<TARGET_FILE_DIR:TO-Donaciones>/${DLL_FILE}"
            )
        else()
            message(WARNING "⚠️ No se encontró ${DLL_FILE} en ${POSTGRES_DLL_DIR}")
        endif()
    endforeach()

    message(STATUS "📦 Copiando librerías de PostgreSQL desde PostGreDll...")
endif()
