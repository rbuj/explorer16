# explorer16
Samples for Explorer 16 Development Board of Microchip

###### Project List
| Project Name     | Short description | [1] | [2] |
| ---------------- | ----------------- | :-: | :-: |
| [ChronometerTimer1SOSC](ChronometerTimer1SOSC/) | Display a chronometer in LCD by using Timer1 Interrupt and SOSC as clock source, change notification interrupt on S3 to start/reset the chronometer. Precision 1/32s. | x | x |
| [ClockTimer1SOSC](ClockTimer1SOSC.X/) | Display a Clock in LCD by using Timer1 Interrupt and SOSC as clock source, change notification interrupt on S3 to start/reset the clock. | x | x |
| [D10OnOffS3](D10OnOffS3.X/) | Switch on D10 LED by pressing and holding S3 switch button, LED is switched off when it's not pressed. | x | x |
| [D10ToggleTimer1](D10ToggleTimer1.X/) | Toggle switch on/off the D10 LED @ 1 Hz using Timer1 Interrupt and SOSC as clock source. | x | x |
| [D10FlashDelay](D10FlashDelay.X/) | Flash LED D10 using __delay_ms(d) macro. | x | x |
| [LCDHelloWorld4MIPS](LCDHelloWorld4MIPS.X/) | Print a message in the LCD Display @ 4 MIPS. | x | x |
| [LCDHelloWorld8MIPS](LCDHelloWorld8MIPS.X/) | Print a message in the LCD Display @ 8 MIPS. | x | x |
| [LCDHelloWorld16MIPS](LCDHelloWorld16MIPS.X/) | Print a message in the LCD Display @ 16 MIPS. | x | x |
| [LEDsOnOffS3](LEDsOnOffS3.X/) | Switch on D3:D10 LEDs by pressing and holding S3 switch button, LED is switched off when it's not pressed. | x | x |
| [LEDsToggleTimer1](LEDsToggleTimer1.X/) | Toggle switch on/off the D3:D10 LEDs @ 1 Hz using Timer1 Interrupt and SOSC as clock source. | x | x |
| [ToggleD9D10CNIS3](ToggleD9D10CNIS3.X/) | Toggle switch on/off the D9/D10 LEDs using the Change Notification Interrupt on S3 switch button. | x | x |

[1] PIC24FJ128GA010, [2] dsPIC33FJ256GP710A

###### Module List

| Module Name      | Project Name | [1] | [2] |
| ---------------- | ------------ | :-: | :-: |
| Write to output pin / D10 | [D10FlashDelay](D10FlashDelay.X/) | x | x |
| Use delay macro | [D10FlashDelay](D10FlashDelay.X/) | x | x |
| Read from input pin / S3 | [D10OnOffS3](D10OnOffS3.X/) | x | x |
| Write to LCD using Parallel Master Port (PMP) | [LCDHelloWorld4MIPS](LCDHelloWorld4MIPS.X/) | x |  |
| Write to LCD (w/ PMP) | [LCDHelloWorld](LCDHelloWorld.X/) | x | x |
| Parallel write to output pins / D3:10 | [LEDsOnOffS3](LEDsOnOffS3.X/) | x | x |
| Change Notification Interrupt / S3 | [ToggleD9D10CNIS3](ToggleD9D10CNIS3.X/) | x | x |
| Low-Power Secondary Oscillator (SOSC) / Timer 1 | [D10ToggleTimer1](D10ToggleTimer1.X/) | x | x |

[1] PIC24FJ128GA010, [2] dsPIC33FJ256GP710A

###### Ascending Order of Difficulty
| # | Project Name     | Modules       |
| - | ---------------- | ------------- |
| 1 | [D10FlashDelay](D10FlashDelay.X/) | Write to output pin / D10; Use delay macro; |
| 2 | [D10OnOffS3](D10OnOffS3.X/) | Write to output pin / D10; Read from input pin / S3; |
| 3 | [LCDHelloWorld4MIPS](LCDHelloWorld4MIPS.X/) | Write to LCD @ 4 MIPS (Busy flag check) |
| 4 | [LCDHelloWorld8MIPS](LCDHelloWorld8MIPS.X/) | Write to LCD @ 8 MIPS (Busy flag check) |
| 5 | [LCDHelloWorld16MIPS](LCDHelloWorld16MIPS.X/) | Write to LCD @ 16 MIPS (Busy flag check) |
| 6 | [LEDsOnOffS3](LEDsOnOffS3.X/) | Parallel write to output pins / D3:10; Read from input pin / S3; Write to LCD; |
| 7 | [ToggleD9D10CNIS3](ToggleD9D10CNIS3.X/) | Change Notification Interrupt / S3; Write to output pin / D10; Write to LCD; |
| 8 | [D10ToggleTimer1](D10ToggleTimer1.X/) | Low-Power Secondary Oscillator (SOSC) / Timer 1; Write to output pin / D10; Write to LCD; |
| 9 | [LEDsToggleTimer1](LEDsToggleTimer1.X/) | Low-Power Secondary Oscillator (SOSC) / Timer 1; Write to output pins / D3:10; Write to LCD; |
| 10 | [ClockTimer1SOSC](ClockTimer1SOSC.X/) | Low-Power Secondary Oscillator (SOSC) / Timer 1; Change Notification Interrupt / S3; Write to LCD; |
| 11 | [ChronometerTimer1SOSC](ChronometerTimer1SOSC/) | Low-Power Secondary Oscillator (SOSC) / Timer 1; Change Notification Interrupt / S3; Write to LCD; |

## Requirements

###### Software
- [MPLAB X IDE](http://www.microchip.com/mplab/mplab-x-ide) is a software program that runs on a PC (Windows®, Mac OS®, Linux®), supports project management, code editing, debugging and programming of Microchip microcontrollers.
- [MPLAB XC16](http://www.microchip.com/mplab/compilers) is a C compiler for 16-bit PIC devices.

###### Hardware
- Explorer 16 Development Board with ICD3 Bundle, [Part Number: DV164037](http://www.microchip.com/developmenttools/ProductDetails.aspx?PartNO=DV164037)

<img src="http://www.microchip.com/_ImagedCopy/DV164037.jpg" width="640">

or

- Development Board:
    - Explorer 16 Development Board with 100-pin PIM, [Part Number: DM240001](http://www.microchip.com/Developmenttools/ProductDetails.aspx?PartNO=DM240001) or
    - Explorer 16/32 Development Board, [Part Number: DM240001-2](http://www.microchip.com/DevelopmentTools/ProductDetails.aspx?PartNO=DM240001-2)
- Supported Processor Plug-In Modules (PIMs):
    - dsPIC33FJ256GP710A Plug-In-Module [Part Number: MA330011](http://www.microchip.com/DevelopmentTools/ProductDetails.aspx?PartNO=MA330011)
    - PIC24FJ128GA010 Plug-In-Module [Part Number: MA240011](http://www.microchip.com/DevelopmentTools/ProductDetails.aspx?PartNO=MA240011)
- 9V power supply, Part Number: AC162039, AC002014
- Hardware debugger/programmer: MPLAB REAL ICE, MPLAB ICD or PICkit
