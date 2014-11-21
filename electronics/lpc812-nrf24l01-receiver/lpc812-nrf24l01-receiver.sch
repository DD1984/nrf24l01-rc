EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:LPC810
LIBS:MCP1703
LIBS:lpc812-nrf24l01-receiver-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "21 nov 2014"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L LPC812M101JDH16_TSSOP16 U2
U 1 1 546ED16B
P 4600 2450
F 0 "U2" H 4600 2450 60  0001 C CNN
F 1 "LPC812M101JDH16_TSSOP16" H 4600 2450 60  0001 C CNN
F 2 "" H 4600 2450 60  0000 C CNN
F 3 "" H 4600 2450 60  0000 C CNN
	1    4600 2450
	1    0    0    -1  
$EndComp
$Comp
L MCP1703T-3302E/CB U1
U 1 1 546ED329
P 3000 6050
F 0 "U1" H 2846 6349 50  0000 L BNN
F 1 "MCP1703T-3302E/CB" H 2794 5462 50  0000 L BNN
F 2 "MCP1703-SOT95P300X145-3N" H 3000 6200 50  0001 C CNN
F 3 "" H 3000 6050 60  0000 C CNN
	1    3000 6050
	1    0    0    -1  
$EndComp
$Comp
L CONN_4X2 P1
U 1 1 546ED38F
P 7950 5600
F 0 "P1" H 7950 5850 50  0000 C CNN
F 1 "CONN_4X2" V 7950 5600 40  0000 C CNN
F 2 "" H 7950 5600 60  0000 C CNN
F 3 "" H 7950 5600 60  0000 C CNN
	1    7950 5600
	-1   0    0    1   
$EndComp
$Comp
L C C3
U 1 1 546ED3A6
P 3900 6250
F 0 "C3" H 3900 6350 40  0000 L CNN
F 1 "1u" H 3906 6165 40  0000 L CNN
F 2 "~" H 3938 6100 30  0000 C CNN
F 3 "~" H 3900 6250 60  0000 C CNN
	1    3900 6250
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 546ED3B5
P 2100 2250
F 0 "C1" H 2100 2350 40  0000 L CNN
F 1 "100n" H 2106 2165 40  0000 L CNN
F 2 "~" H 2138 2100 30  0000 C CNN
F 3 "~" H 2100 2250 60  0000 C CNN
	1    2100 2250
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 546ED3C4
P 2100 6250
F 0 "C2" H 2100 6350 40  0000 L CNN
F 1 "1u" H 2106 6165 40  0000 L CNN
F 2 "~" H 2138 6100 30  0000 C CNN
F 3 "~" H 2100 6250 60  0000 C CNN
	1    2100 6250
	1    0    0    -1  
$EndComp
$Comp
L CONN_3 K1
U 1 1 546ED52C
P 10200 1750
F 0 "K1" V 10150 1750 50  0000 C CNN
F 1 "CONN_3" V 10250 1750 40  0000 C CNN
F 2 "" H 10200 1750 60  0000 C CNN
F 3 "" H 10200 1750 60  0000 C CNN
	1    10200 1750
	1    0    0    -1  
$EndComp
$Comp
L CONN_3 K2
U 1 1 546EDCB1
P 10200 2250
F 0 "K2" V 10150 2250 50  0000 C CNN
F 1 "CONN_3" V 10250 2250 40  0000 C CNN
F 2 "" H 10200 2250 60  0000 C CNN
F 3 "" H 10200 2250 60  0000 C CNN
	1    10200 2250
	1    0    0    -1  
$EndComp
$Comp
L CONN_3 K3
U 1 1 546EDCC0
P 10200 2800
F 0 "K3" V 10150 2800 50  0000 C CNN
F 1 "CONN_3" V 10250 2800 40  0000 C CNN
F 2 "" H 10200 2800 60  0000 C CNN
F 3 "" H 10200 2800 60  0000 C CNN
	1    10200 2800
	1    0    0    -1  
$EndComp
$Comp
L CONN_3 K4
U 1 1 546EDCCF
P 10200 3350
F 0 "K4" V 10150 3350 50  0000 C CNN
F 1 "CONN_3" V 10250 3350 40  0000 C CNN
F 2 "" H 10200 3350 60  0000 C CNN
F 3 "" H 10200 3350 60  0000 C CNN
	1    10200 3350
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR01
U 1 1 546EDD7F
P 3900 5850
F 0 "#PWR01" H 3900 5810 30  0001 C CNN
F 1 "+3.3V" H 3900 5960 30  0000 C CNN
F 2 "" H 3900 5850 60  0000 C CNN
F 3 "" H 3900 5850 60  0000 C CNN
	1    3900 5850
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR02
U 1 1 546EDE14
P 2100 5850
F 0 "#PWR02" H 2100 5800 20  0001 C CNN
F 1 "+BATT" H 2100 5950 30  0000 C CNN
F 2 "" H 2100 5850 60  0000 C CNN
F 3 "" H 2100 5850 60  0000 C CNN
	1    2100 5850
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR03
U 1 1 546EDE3D
P 2100 1800
F 0 "#PWR03" H 2100 1760 30  0001 C CNN
F 1 "+3.3V" H 2100 1910 30  0000 C CNN
F 2 "" H 2100 1800 60  0000 C CNN
F 3 "" H 2100 1800 60  0000 C CNN
	1    2100 1800
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR04
U 1 1 546EE07C
P 9750 1350
F 0 "#PWR04" H 9750 1300 20  0001 C CNN
F 1 "+BATT" H 9750 1450 30  0000 C CNN
F 2 "" H 9750 1350 60  0000 C CNN
F 3 "" H 9750 1350 60  0000 C CNN
	1    9750 1350
	1    0    0    -1  
$EndComp
Text Label 8950 1650 0    60   ~ 0
Tx
Wire Wire Line
	2100 2050 3500 2050
Wire Wire Line
	2100 2450 2100 2600
Wire Wire Line
	2400 2150 3500 2150
Wire Wire Line
	2400 2150 2400 2250
Wire Wire Line
	2300 6050 2100 6050
Wire Wire Line
	3700 6050 3900 6050
Wire Wire Line
	2100 6450 2100 6600
Wire Wire Line
	2300 6250 2300 6600
Wire Wire Line
	3900 6050 3900 5850
Wire Wire Line
	2100 6050 2100 5850
Wire Wire Line
	2100 2050 2100 1800
Wire Wire Line
	9850 1850 9650 1850
Wire Wire Line
	9650 1850 9650 3650
Wire Wire Line
	9850 2350 9650 2350
Connection ~ 9650 2350
Wire Wire Line
	9850 2900 9650 2900
Connection ~ 9650 2900
Wire Wire Line
	9650 3450 9850 3450
Connection ~ 9650 3450
Wire Wire Line
	9750 3350 9850 3350
Wire Wire Line
	9750 1350 9750 3350
Wire Wire Line
	9750 1750 9850 1750
Connection ~ 9750 1750
Wire Wire Line
	9850 2250 9750 2250
Connection ~ 9750 2250
Wire Wire Line
	9850 2800 9750 2800
Connection ~ 9750 2800
Wire Wire Line
	8950 3250 9850 3250
Wire Wire Line
	8950 2700 9850 2700
Wire Wire Line
	8950 2150 9850 2150
Wire Wire Line
	8950 1650 9850 1650
Wire Wire Line
	3500 2250 2950 2250
Wire Wire Line
	3500 2450 2950 2450
Wire Wire Line
	3500 2550 2950 2550
Wire Wire Line
	2950 2650 3500 2650
Wire Wire Line
	3500 2750 2950 2750
Wire Wire Line
	3500 2850 2950 2850
Wire Wire Line
	3500 2950 2950 2950
Wire Wire Line
	5700 2550 6150 2550
Wire Wire Line
	8350 5750 8550 5750
Wire Wire Line
	8550 5750 8550 5950
$Comp
L +3.3V #PWR05
U 1 1 546EE5BB
P 7150 5250
F 0 "#PWR05" H 7150 5210 30  0001 C CNN
F 1 "+3.3V" H 7150 5360 30  0000 C CNN
F 2 "" H 7150 5250 60  0000 C CNN
F 3 "" H 7150 5250 60  0000 C CNN
	1    7150 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 5250 7150 5750
Wire Wire Line
	7150 5750 7550 5750
Wire Wire Line
	8350 5650 9100 5650
Wire Wire Line
	8350 5550 9100 5550
Wire Wire Line
	8350 5450 9100 5450
Wire Wire Line
	7550 5450 6750 5450
Wire Wire Line
	7550 5550 6750 5550
Wire Wire Line
	7550 5650 6750 5650
Wire Wire Line
	5700 2450 6150 2450
Wire Wire Line
	5700 2050 6150 2050
Wire Wire Line
	5700 2150 6150 2150
Wire Wire Line
	5700 2250 6150 2250
Text GLabel 6150 2050 2    39   Input ~ 0
ST
Text GLabel 6150 2150 2    39   Input ~ 0
TH
Text GLabel 6150 2250 2    39   Input ~ 0
IRQ
Text GLabel 8950 2150 0    39   Input ~ 0
CH3
Text GLabel 8950 2700 0    39   Input ~ 0
TH
Text GLabel 8950 3250 0    39   Input ~ 0
ST
Text GLabel 6150 2450 2    39   Input ~ 0
ISP
Text GLabel 6150 2550 2    39   Input ~ 0
CE
Wire Wire Line
	5700 2350 6150 2350
Text GLabel 6150 2350 2    39   Input ~ 0
MISO
Text GLabel 2950 2250 0    39   Input ~ 0
Rx
Text GLabel 2950 2450 0    39   Input ~ 0
CSN
Text GLabel 2950 2550 0    39   Input ~ 0
SCK
Text GLabel 2950 2650 0    39   Input ~ 0
Tx
Text GLabel 2950 2750 0    39   Input ~ 0
RESET
Text GLabel 2950 2950 0    39   Input ~ 0
MOSI
Text GLabel 2950 2850 0    39   Input ~ 0
CH3
Text GLabel 6750 5550 0    39   Input ~ 0
MOSI
Text GLabel 9100 5450 2    39   Input ~ 0
MISO
Text GLabel 9100 5550 2    39   Input ~ 0
SCK
Text GLabel 9100 5650 2    39   Input ~ 0
CE
Text GLabel 6750 5450 0    39   Input ~ 0
IRQ
Text GLabel 6750 5650 0    39   Input ~ 0
CSN
$Comp
L VSS #PWR06
U 1 1 546EE3D4
P 2100 6600
F 0 "#PWR06" H 2100 6600 30  0001 C CNN
F 1 "VSS" H 2100 6530 30  0000 C CNN
F 2 "" H 2100 6600 60  0000 C CNN
F 3 "" H 2100 6600 60  0000 C CNN
	1    2100 6600
	1    0    0    -1  
$EndComp
$Comp
L VSS #PWR07
U 1 1 546EE3EB
P 2300 6600
F 0 "#PWR07" H 2300 6600 30  0001 C CNN
F 1 "VSS" H 2300 6530 30  0000 C CNN
F 2 "" H 2300 6600 60  0000 C CNN
F 3 "" H 2300 6600 60  0000 C CNN
	1    2300 6600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 6600 3900 6450
$Comp
L VSS #PWR08
U 1 1 546EE3F1
P 3900 6600
F 0 "#PWR08" H 3900 6600 30  0001 C CNN
F 1 "VSS" H 3900 6530 30  0000 C CNN
F 2 "" H 3900 6600 60  0000 C CNN
F 3 "" H 3900 6600 60  0000 C CNN
	1    3900 6600
	1    0    0    -1  
$EndComp
$Comp
L VSS #PWR09
U 1 1 546EE3F9
P 8550 5950
F 0 "#PWR09" H 8550 5950 30  0001 C CNN
F 1 "VSS" H 8550 5880 30  0000 C CNN
F 2 "" H 8550 5950 60  0000 C CNN
F 3 "" H 8550 5950 60  0000 C CNN
	1    8550 5950
	1    0    0    -1  
$EndComp
$Comp
L VSS #PWR010
U 1 1 546EE412
P 9650 3650
F 0 "#PWR010" H 9650 3650 30  0001 C CNN
F 1 "VSS" H 9650 3580 30  0000 C CNN
F 2 "" H 9650 3650 60  0000 C CNN
F 3 "" H 9650 3650 60  0000 C CNN
	1    9650 3650
	1    0    0    -1  
$EndComp
$Comp
L VSS #PWR011
U 1 1 546EE42B
P 2100 2600
F 0 "#PWR011" H 2100 2600 30  0001 C CNN
F 1 "VSS" H 2100 2530 30  0000 C CNN
F 2 "" H 2100 2600 60  0000 C CNN
F 3 "" H 2100 2600 60  0000 C CNN
	1    2100 2600
	1    0    0    -1  
$EndComp
$Comp
L VSS #PWR012
U 1 1 546EE442
P 2400 2250
F 0 "#PWR012" H 2400 2250 30  0001 C CNN
F 1 "VSS" H 2400 2180 30  0000 C CNN
F 2 "" H 2400 2250 60  0000 C CNN
F 3 "" H 2400 2250 60  0000 C CNN
	1    2400 2250
	1    0    0    -1  
$EndComp
$EndSCHEMATC