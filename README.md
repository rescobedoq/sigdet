<div align="center">

# **Sistema Integral de Gestión de Donaciones con Enfoque en Eficiencia y Transparencia**
## SIGDET
## Universidad Nacional de San Agustín de Arequipa
**Laboratorio:** Programación Orientada a Objetos

</div>

**Docente:** Richart Smith Escobedo Quispe (rescobedoq@unsa.edu.pe)

**Integrantes:**
- Carlos Ccamaqque Wilson Freddy (wcarlosc@unsa.edu.pe) 
- Companocca Checco Roni (rcompanocca@unsa.edu.pe)  
- Huamani Condori Jeanpiero Sixto (jhuamanicond@unsa.edu.pe)  
- Llacho Delgado Samir Jaren (sllachod@unsa.edu.pe)
- Mamani Quispe Adrian Issac (admamaniq@unsa.edu.pe)

**Fecha:** Diciembre 2025
<!-- Referencias principales del proyecto -->

## 🔗 Video explicativo del proyecto Semana 4

[![Video](https://img.shields.io/badge/YouTube-Video_explicativo_del_proyecto-FF0000?style=for-the-badge&logo=youtube&logoColor=white)](https://youtu.be/bp2yoYvOiJ0?si=RUZncQz5m35_8pbc)

## 🔗 Referencias y Recursos Utilizados

[![C++](https://img.shields.io/badge/C++-17/20-blue?style=for-the-badge&logo=cplusplus&logoColor=white)](https://en.cppreference.com/w/)
[![Qt](https://img.shields.io/badge/Qt-6-green?style=for-the-badge&logo=qt&logoColor=white)](https://www.qt.io/)
[![SQLite](https://img.shields.io/badge/SQLite-Database-07405E?style=for-the-badge&logo=sqlite&logoColor=white)](https://www.sqlite.org/index.html)
[![CMake](https://img.shields.io/badge/CMake-Build_System-064F8C?style=for-the-badge&logo=cmake&logoColor=white)](https://cmake.org/)
[![Git](https://img.shields.io/badge/Git-Version_Control-F05033?style=for-the-badge&logo=git&logoColor=white)](https://git-scm.com/)
[![GitHub](https://img.shields.io/badge/GitHub-Repository-121011?style=for-the-badge&logo=github&logoColor=white)](https://github.com/)
[![JSON](https://img.shields.io/badge/JSON-Data_Format-000000?style=for-the-badge&logo=json&logoColor=white)](https://www.json.org/)
[![GoogleTest](https://img.shields.io/badge/GoogleTest-Unit_Testing-4285F4?style=for-the-badge&logo=google&logoColor=white)](https://github.com/google/googletest)
[![Multithreading](https://img.shields.io/badge/Multithreading-Enabled-FF6F00?style=for-the-badge&logo=threadless&logoColor=white)](https://www.geeksforgeeks.org/multithreading-in-cpp/)
[![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)](LICENSE)

## Requisitos Generales del Proyecto

Este documento resume los principales requisitos y lineamientos técnicos del proyecto de **SIGDET**, desarrollado en **C++/Qt** bajo el patrón **MVC** y utilizando **GitHub** para control de versiones y colaboración en equipo.

**Control de Versiones (Git / GitHub)**
- Repositorio alojado en GitHub.  
- Uso de ramas para organización del trabajo:
- Commits **descriptivos y frecuentes**.
- Uso de **pull requests** y **merges controlados** para integrar cambios.

**Documentación**
El repositorio debe incluir:
- Archivo `README.md` con:
  - Descripción general del sistema.
  - Estructura del proyecto.
  - Diagrama de clases.
  - Diagrama de flujo del patrón MVC.
- Imágenes o GIFs de la interfaz (capturas Qt).

**Arquitectura del Sistema**
- Patrón principal: **MVC (Modelo–Vista–Controlador)** implementado en **C++/Qt**.
- Sin uso de frameworks externos (solo **bibliotecas estándar** de C++ y **Qt**).

**Requisitos Técnicos**
- Uso de **punteros inteligentes**: ejemplo
  ```cpp
  std::unique_ptr<Donacion> donacion = std::make_unique<Donacion>();

**¡¡NO USAR FRAMEWORK!!**

## Plan de Trabajo — Sistema Integral de Gestión de Donaciones (SIGDET)

**Objetivo General**
Desarrollar un sistema de gestión de donaciones en **C++** utilizando **arquitectura MVC** e **interfaz Qt**, aplicando principios de POO, patrones de diseño y control de versiones con **GitHub**, logrando una versión **ejecutable y funcional en 5 semanas**.

**Cronograma de Desarrollo**

### **Semana 1 – Análisis, Diseño y Base del Proyecto**
**Objetivo:** Establecer la estructura base del proyecto y definir el modelo de clases.  
**Tareas:**
- Configuración del entorno (Qt Creator / CMake / Git).  
- Creación del repositorio y estructura inicial (`src/`, `include/`, `data/`, `tests/`).  
- Definición de clases principales del **Modelo (Donante, Donación, Inventario, Reporte)**.  
- Elaboración de un **diagrama UML** inicial.  
- Configuración del archivo **CMakeLists.txt**.  
- Implementación de un **main básico** que compile correctamente.  
- Documentación inicial en el `README.md`.
**Entrega esperada:** Proyecto compila correctamente con estructura MVC vacía y modelos definidos.

### **Semana 2 – Implementación del Modelo (Lógica de Negocio)**
**Objetivo:** Desarrollar toda la lógica de negocio del sistema sin interfaz gráfica.  
**Tareas:**
- Implementación de las clases:
  - `Donante`, `Donacion`, `Inventario`, `Reporte`.  
- Aplicar **herencia y polimorfismo** (`DonacionAlimento`, `DonacionRopa`).  
- Implementar **Factory Method** para creación de objetos de donación.  
- Agregar **excepciones personalizadas** para control de errores.  
- Pruebas iniciales de CRUD desde consola.  
- Implementar **tests unitarios** básicos (GoogleTest o Catch2).
**Entrega esperada:** Lógica del sistema completamente funcional en modo consola.

### **Semana 3 – Interfaz Gráfica (Vista) y Controladores**
**Objetivo:** Implementar la interfaz Qt y conectar los controladores con el modelo.  
**Tareas:**
- Creación de ventanas con **Qt Widgets**:
  - Ventana principal.  
  - Formulario de Donantes y Donaciones.  
  - Tabla de Inventario.  
- Implementar controladores:
  - `ControladorDonante`, `ControladorDonacion`.  
- Conectar señales y slots (MVC).  
- Integrar validaciones visuales y mensajes de error (`QMessageBox`).  
- Prueba completa del CRUD desde la interfaz.
**Entrega esperada:** Aplicación Qt funcional con operaciones CRUD completas sobre estructuras en memoria.

### **Semana 4 – Persistencia y Funcionalidades Avanzadas**
**Objetivo:** Incorporar almacenamiento persistente y optimizar el rendimiento.  
**Tareas:**
- Implementar persistencia de datos:
  - **SQLite** (QSqlDatabase) o **JSON** (`QJsonDocument` / `nlohmann::json`).  
- Exportación de datos (Inventario / Reportes) a **CSV o PDF**.  
- Implementar **búsqueda y filtrado** de donaciones por tipo, fecha o cantidad.  
- Uso de **multithreading (QThread)** para carga masiva o procesos lentos.  
- Implementar **Observer** para actualizar la vista en tiempo real.  
- Mejoras visuales y pulido de interfaz.
**Entrega esperada:** Aplicación persistente, con reportes exportables y GUI estable.

### **Semana 5 – Pruebas, Optimización y Documentación Final**
**Objetivo:** Finalizar, probar y documentar completamente el proyecto.  
**Tareas:**
- Pruebas unitarias y de integración completas.  
- Revisión de excepciones, validaciones y manejo de errores.  
- Optimización de rendimiento y limpieza de código.  
- Documentación final en el `README.md`:  
  - Descripción general.  
  - Diagrama UML actualizado.  
  - Capturas o GIFs de la interfaz Qt.  
  - Guía de compilación y ejecución con **CMake**.  
- Presentación final y entrega del ejecutable.
**Entrega esperada:** Sistema completo, probado y documentado, listo para presentación.

[![C++](https://img.shields.io/badge/C++-17/20-blue?style=for-the-badge&logo=cplusplus&logoColor=white)](https://en.cppreference.com/w/)
[![Qt](https://img.shields.io/badge/Qt-6-green?style=for-the-badge&logo=qt&logoColor=white)](https://www.qt.io/)
[![SQLite](https://img.shields.io/badge/SQLite-Database-07405E?style=for-the-badge&logo=sqlite&logoColor=white)](https://www.sqlite.org/index.html)
[![CMake](https://img.shields.io/badge/CMake-Build_System-064F8C?style=for-the-badge&logo=cmake&logoColor=white)](https://cmake.org/)
[![Git](https://img.shields.io/badge/Git-Version_Control-F05033?style=for-the-badge&logo=git&logoColor=white)](https://git-scm.com/)
[![GitHub](https://img.shields.io/badge/GitHub-Repository-121011?style=for-the-badge&logo=github&logoColor=white)](https://github.com/)
[![JSON](https://img.shields.io/badge/JSON-Data_Format-000000?style=for-the-badge&logo=json&logoColor=white)](https://www.json.org/)
[![GoogleTest](https://img.shields.io/badge/GoogleTest-Unit_Testing-4285F4?style=for-the-badge&logo=google&logoColor=white)](https://github.com/google/googletest)
[![Multithreading](https://img.shields.io/badge/Multithreading-Enabled-FF6F00?style=for-the-badge&logo=threadless&logoColor=white)](https://www.geeksforgeeks.org/multithreading-in-cpp/)
[![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)](LICENSE)