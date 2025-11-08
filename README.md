<div align="center" style="background-color:#0A192F; color:#E6F1FF; padding:40px; border-radius:20px;">

  <h1 style="color:#64FFDA; font-size:2em; margin:0 0 8px;">Sistema Integral de Gestión de Donaciones con Enfoque en Eficiencia y Transparencia</h1>
  <h3 style="color:#A8B2D1; margin:0 0 16px;">SIGDET</h3>

  <hr style="width:80%; border:1px solid #64FFDA;">

  <div style="font-size:1.05em; line-height:1.6; text-align:left; max-width:700px; margin:20px auto; color:#E6F1FF;">
    <p style="margin:0;"><strong>Institución:</strong> Universidad Nacional de San Agustín de Arequipa</p>
    <p style="margin:8px 0 0;"><strong>Docente:</strong> Richart Smith Escobedo Quispe</p>

    <p style="margin:12px 0 4px;"><strong>Integrantes:</strong></p>
    <ul style="margin:0 0 8px 20px; padding:0;">
      <li>Carlos Ccamaqque Wilson Freddy</li>
      <li>Companocca Checco Roni (rcompanocca@unsa.edu.pe)</li>
      <li>Huamani Condori Jeanpiero Sixto</li>
      <li>Llacho Delgado Samir Jaren</li>
      <li>Mamani Quispe Adrian Issac</li>
    </ul>

    <p style="margin:8px 0 0;"><strong>Fecha:</strong> Noviembre 2025</p>
  </div>

  <hr style="width:80%; border:1px solid #64FFDA;">

  <p style="font-size:0.95em; color:#8892B0; margin:12px 0 0;">Proyecto: Programación Orientada a Objetos</p>
</div>

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



<tr>
  <td colspan="6">
    <strong>Referencias y Recursos Utilizados</strong>
    <ul>
      <li><a href="https://www.w3schools.com/python/python_reference.asp" target="_blank">W3Schools – Python Reference</a></li>
      <li><a href="https://docs.python.org/3/tutorial/" target="_blank">Documentación oficial de Python</a></li>
      <li><a href="https://developer.mozilla.org/es/docs/Learn/Server-side/Django/Models" target="_blank">MDN – Django (Modelos)</a></li>
      <li><a href="https://tutorial.djangogirls.org/es/django_models/" target="_blank">Django Girls – Tutorial de Modelos</a></li>
      <li><a href="https://pear.php.net/manual/en/standards.php" target="_blank">PEAR – PHP Coding Standards</a></li>
      <li><a href="https://docs.djangoproject.com/en/4.0/" target="_blank">Documentación oficial de Django 4.0</a></li>
      <li><a href="https://www.youtube.com/watch?v=M4NIs4BM1dk" target="_blank">Video: Django Course (YouTube)</a></li>
      <li><a href="https://pypi.org/" target="_blank">PyPI – Python Package Index</a></li>
      <li><a href="https://pip.pypa.io/en/latest/user_guide/" target="_blank">Guía de usuario de pip</a></li>
      <li><a href="https://packaging.python.org/en/latest/tutorials/installing-packages/" target="_blank">Instalación de paquetes en Python</a></li>
    </ul>
  </td>
</tr>

<tr>
  <td colspan="6">
    <strong>DOCENTE:</strong>
    <ul>
      <li>Nombre del docente: [Escribe aquí el nombre del profesor]</li>
      <li>Curso: [Nombre del curso o asignatura]</li>
      <li>Institución: [Nombre de la institución educativa]</li>
    </ul>
  </td>
</tr>

# 🧩 Requisitos Generales del Proyecto

Este documento resume los principales requisitos y lineamientos técnicos del proyecto de **Gestión de Donaciones**, desarrollado en **C++/Qt** bajo el patrón **MVC** y utilizando **GitHub** para control de versiones y colaboración en equipo.

---

## 🧱 Control de Versiones (Git / GitHub)

- Repositorio alojado en GitHub.  
- Uso de ramas para organización del trabajo:
  - `main` → Rama principal (versión estable).
  - `roni` → Desarrollo de lógica de negocio.
  - `jeanpiero` → Desarrollo de interfaz gráfica.
  - `feature/*` → Nuevas funcionalidades temporales.
- Commits **descriptivos y frecuentes**.
- Uso de **pull requests** y **merges controlados** para integrar cambios.

---

## 📄 Documentación

El repositorio debe incluir:

- Archivo `README.md` con:
  - Descripción general del sistema.
  - Instrucciones para compilar y ejecutar el programa usando **CMake**.
  - Estructura del proyecto.
  - Créditos del equipo y roles.
- Diagramas UML:
  - Diagrama de clases.
  - Diagrama de flujo del patrón MVC.
- Imágenes o GIFs de la interfaz (capturas Qt).

---

## 🏗️ Arquitectura del Sistema

- Patrón principal: **MVC (Modelo–Vista–Controlador)** implementado en **C++/Qt**.
- Sin uso de frameworks externos (solo **bibliotecas estándar** de C++ y **Qt**).
- Separación clara de responsabilidades:
  - **Modelo:** Clases `Donante`, `Donacion`, `Inventario`, `Reporte`.
  - **Vista:** Formularios Qt (QWidgets/QML).
  - **Controlador:** Comunicación entre modelo y vista.

---

## ⚙️ Requisitos Técnicos

- Uso de **punteros inteligentes**:
  ```cpp
  std::unique_ptr<Donacion> donacion = std::make_unique<Donacion>();
