# Video transmitter SPI programmer

Simple Arduino VTX channel programmer.

Work in progress. Currently using a Nano and FX758.

Basic setup:

    Nano                          FX758
    8 -> S1 -> 3V
    9 -> LED -> R330 -> gnd
    10                            6
    11 MOSI (out)                 5
    13 SCK (serial clock)         7
