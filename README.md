# seat-viz-control
Software to control microcontroller as part of seat viz project

## Introduction

The software controls pressure sensors used in bicycle seat model. Companion software to [Seat-viz](https://github.com/KZM26/seat-viz/edit/master/README.md)

### System 

The software implements the display unit component of the overall system

![image](https://user-images.githubusercontent.com/23017771/134786162-1b123157-407c-4b7f-b23e-290eb1d75cb7.png)

### Function

The system controls a 6x6 grid of sensors via the GPIO lines. Power is selectivly provided to a sensor using a demux system.

