## Descripción del directorio libs/board/ en el repositorio basic-firmware-educiaa

En board tenemos varios subdirectorios y el archivo module.mk de documentación.
Los directorios son los siguientes:

- edu_ciaa_nxp: en este directorio tenemos código especifico de la EDU-CIAA, dentro se sub-divide en inc y src, para headers y source
    - inc/board.h: define posiciones de pines, baudrate y otras constantes importantes para el uso de la placa.
    - inc/board_api.h: define los prototipos para la API de la placa.
    - src/board.c: define las funciones de board.h para inicializar la placa.
    - src/board_sysinit.c: define funciones de inicialización, como la multiplexación de pines.
- lib: en este directorio se encuentran cuatro archivos que son para el linker de GCC. Estos archivos son flat.ld, libs.ld, link.ld y mem.ld.
- lpc_chip_43xx: este directorio posee los headers y la implementación de una gran cantidad de funcionalidades para los chips 18xx y 43xx. Está separada en inc, src y usbd_rom, y además posee el archivo "Software Content Register.txt".
- lpc_startup: este directorio posee unicamente el subdirectorio src. En src tenemos funciones para inicializar la placa.
