# Taller OpenMP

En este taller se da una introducción de la herramienta de OpenMP para realizar cálculos paralelos en C. El objetivo principal
fue el realizar ciertos algoritmos para el cálculo de pi, la constante e y DAXPY.

## Requisitos

- Build Tools: sudo apt-get install build-essential
- OpenMp Library: sudo apt-get install libomp-dev
- Plotly Library: pip install plotly --upgrade
- GCC Compiler.
- Python3.

## Compilación

Para la compilación de todos los programas, abra su terminal de consola o la terminal de algún editor de código como VSC y ejecute el siguiente comandos
dentro de la carpeta princiapl:

- 'make': Esto compilará todos los arcihvos necesarios para la creación de los ejecutables de los programas de pi, e_taylor y daxpy.
- 'make clean': Esto eliminará todos los ejecutables de todos los directorios para limpiar.

## Ejecución

Para poder ejectuar los programas y generar los reportes, puede hacer desde la terminal siguiendo los siguientes pasos:

- './pi_loopB': Esto ejecutará el programa de pi para multi-threading una sola vez y desplegará su resultados en consola.
- './pi_loopC n': Esto ejecutará una versión midificada que permite ejecutar por lotes el programa y generar 'n' reportes que se guardarán la carpeta results.
- './e_taylor n': Este comando ejecuta el programa del cálculo de e con serie de taylor.
- './daxpy_single': Para ejecutar versión single-thread the daxpy.
- './daxpy_muilti n': Para ejecutar versión multi-thread the daxpy.

**Para cada uno de los pasos anteriores, sustituir 'n' con el número de veces a ejecutar el programa.**
**Cada uno de los ejecutables generará n reportes que se guardarán en el direcotrio correspondiente.**

## Visualización

- Correr el script plotter.py para poder generar las gráficas y visualizarlas en su navegador.
- Cada plotter grafica un programa en específico. Plotter en program_a ejecutará el de la serie de Taylor. plotter en programa_b ejecutará DAXPY.