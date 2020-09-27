# Cómo usar la plantilla

La plantilla se usa para poder compilar archivos del *Qt Designer*.

Para poder usar la plantilla, es necesario guardar el archivo .ui del Designer como `Form.ui`, y cambiar el objectName del QWidget base a `MyForm`:

![Save objectName as MyForm](https://i.imgur.com/pWt3lZd.png)

Después sólo hay que copiar los archivos de la plantilla en la misma carpeta, y ya se puede compilar.

## Compilar

Para compilar, simplemente hay que acceder a la carpeta desde la consola y ejecutar dos comandos:
- `qmake-qt5` para crear el Makefile
- `make` para ejecutar el Makefile y compilar el código.

Ahora simplemente para abrirlo sólo hay que ejecutar `./myform` en la consola.
