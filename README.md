<div align="center">

# **Sistema Integral de Gestión de Donaciones con Enfoque en Eficiencia y Transparencia**
## SIGDET
## Universidad Nacional de San Agustín de Arequipa
**Laboratorio:** Programación Orientada a Objetos

</div>

**Docente:** Richart Smith Escobedo Quispe

**Integrantes:**
- Carlos Ccamaqque Wilson Freddy (wcarlosc@unsa.edu.pe) 
- Companocca Checco Roni (rcompanocca@unsa.edu.pe)  
- Huamani Condori Jeanpiero Sixto (jhuamanicond@unsa.edu.pe)  
- Llacho Delgado Samir Jaren (sllachod@unsa.edu.pe)
- Mamani Quispe Adrian Issac (admamaniq@unsa.edu.pe)

**Fecha:** Noviembre 2025
<!-- Referencias principales del proyecto -->
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

# Requisitos Generales del Proyecto

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

## Requisitos Técnicos
- Uso de **punteros inteligentes**: ejemplo
  ```cpp
  std::unique_ptr<Donacion> donacion = std::make_unique<Donacion>();


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