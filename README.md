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
