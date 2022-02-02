# Dioramas 

Código funciona en base a un timer general y maquinas de estado que verifican el estado de cada componente y ejecutan acción si corresponde 

tiempo actual 

## Archivos

- main.ino: contiene setup y loop principal
- config.h : configuracion de cada diorama
- globals.h : variables y objetos globales
- led_control
- servo_control
- stepper_lite
- serial_menu.h


## To Do

- [ ] Organizar código, (main, servo, led) usar funciones y clases para códigos que se repiten
  - [ ] funcion/clase que controle los led y luces
  - [ ] funcion/clase que controle los servos
  - [ ] funcion/clase que controle los steppers

- [ ] Configurar timmings para cada diorama (config.h)
- [ ] Diagrama y esquema de conexiones
- [ ] Armar prototipo

