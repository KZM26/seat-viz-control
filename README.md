# seat-viz-control
Software to control microcontroller as part of seat viz project

## Introduction

The software controls pressure sensors used in bicycle seat model. Companion software to [Seat-viz](https://github.com/KZM26/seat-viz/edit/master/README.md)

### System 

The software implements the display unit component of the overall system

![image](https://user-images.githubusercontent.com/23017771/134786162-1b123157-407c-4b7f-b23e-290eb1d75cb7.png)

### Function

The system controls a 6x6 grid of sensors via the GPIO lines.

Each sensor consists of a infrared (IR) LED and IR photodiode. Power is provide from the outputs of a demultiplexer whose inputs come from the microcontroller. Outputs are read to a multiplexer whose inputs again from the microcontroller.

![image](https://user-images.githubusercontent.com/23017771/134787935-3552c210-9311-4a2e-a1d2-575a182d206a.png)

Outputs are then sent to a computer connected via USB running the [Seat-viz](https://github.com/KZM26/seat-viz/edit/master/README.md) software. The communication library is based on the work of [Tilen Majerle](https://github.com/MaJerle). 
