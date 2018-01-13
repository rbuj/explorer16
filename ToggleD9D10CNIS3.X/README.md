# D10OnOffS3
## Description
Toggle switch on/off the D9/D10 LEDs using the Change Notification Interrupt on S3 switch button.

## Usage
- Set up the Developmnent Board:
    - Unplug the 9V power supply and the programmer from the development board.
    - Plug PIM to the development board.
    - Set switch S2 to PIM position.
    - Install the jumper JP2 to enable the LEDs.
    - Plug the 9V power supply and the programmer to the development board.
- Set up the project:
    - Open MPLAB X IDE.
    - Select "File -> Open Project..." from the MPLAB X IDE menu.
    - Select the project and click on "Open Project"
    - Right click on project name, select "Set configuration" and select the installed PIM.
- Run the project:
    - Right click on project name, select "Run"

## Pinout
###### Indicator LEDs
| LED | dsPIC33FJ256GP710A | PIC24FJ128GA010 | Overlaps with |
| --- | :----------------: | :-------------: | :-----------: |
| D3  | RA0                | RA0             |               |
| D4  | RA1                | RA1             |               |
| D5  | RA2                | RA2             |               |
| D6  | RA3                | RA3             |               |
| D7  | RA4                | RA4             |               |
| D8  | RA5                | RA5             |               |
| D9  | RA6                | RA6             |               |
| D10 | RA7                | RA7             | S5            |

###### Push button switches
| Push button switch    | dsPIC33FJ256GP710A | PIC24FJ128GA010 | Overlaps with |
| --------------------- | :----------------: | :-------------: | :-----------: |
| S3: Active-low switch | CN15/RD6           | CN15/RD6        |               |
| S4: Active-low switch | CN19/RD13          | CN19/RD13       |               |
| S5: Active-low switch | CN23/RA7           | CN23/RA7        | D10           |
| S6: Active-low switch | CN16/RD7           | CN16/RD7        |               |

###### 16x2 LCD Display
| LCD | dsPIC33FJ256GP710A | PIC24FJ128GA010 | Overlaps with |
| --- | :----------------: | :-------------: | :-----------: |
| E   | RD4                | PMWR            |               |
| R/W | RD5                | PMRD            |               |
| RS  | RB15               | PMAO            |               |
| DB0 | RE0                | PMD0            |               |
| DB1 | RE1                | PMD1            |               |
| DB2 | RE2                | PMD2            |               |
| DB3 | RE3                | PMD3            |               |
| DB4 | RE4                | PMD4            |               |
| DB5 | RE5                | PMD5            |               |
| DB6 | RE6                | PMD6            |               |
| DB7 | RE7                | PMD7            |               |

###### ADC
| Analog Input       | dsPIC33FJ256GP710A | PIC24FJ128GA010 | Overlaps with |
| ------------------ | :----------------: | :-------------: | :-----------: |
| Potentiometer      | AN5/RB5            | AN5/RB5         |               |
| Temperature sensor | AN4/RB4            | AN4/RB4         |               |

###### Oscillators
| Oscillator                  | dsPIC33FJ256GP710A | PIC24FJ128GA010 | Overlaps with |
| --------------------------- | :----------------: | :-------------: | :-----------: |
| Primary: 8 MHz crystal (Y3) | OSC1/RC12          | OSC1/RC12       |               |
| Primary: 8 MHz crystal (Y3) | OSC2/RC15          | OSC2/RC15       |               |

###### MPLAB ICD programmer/debugger module
| ICD Pin   | dsPIC33FJ256GP710A | PIC24FJ128GA010 | Overlaps with |
| --------- | :----------------: | :-------------: | :-----------: |
| Vpp/!MCLR | !MCLR              | !MCLR           |               |
| PGD       | PGED1/RB7          | PGED1/RB7       |               |
| PGC       | PGEC1/RB6          | PGEC1/RB6       |               |
