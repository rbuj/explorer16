# Pinout
* Set switch S2 to PIM position.
* Install the jumper JP2 to enable the LEDs

## Indicator LEDs
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

## 16x2 LCD Display
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

## ADC
| Analog Input       | dsPIC33FJ256GP710A | PIC24FJ128GA010 | Overlaps with |
| ------------------ | :----------------: | :-------------: | :-----------: |
| Potentiometer      | RB5/AN5            | RB5/AN5         |               |
| Temperature sensor | RB4/AN4            | RB4/AN4         |               |