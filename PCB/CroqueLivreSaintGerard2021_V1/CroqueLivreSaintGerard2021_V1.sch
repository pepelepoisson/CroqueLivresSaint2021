EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 1 1
Title "Croque-livres Saint-Gérard 2021"
Date "2021-03-10"
Rev "V1"
Comp "Papas Inventeurs"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Module:WeMos_D1_mini U2
U 1 1 6035D94E
P 5900 4800
F 0 "U2" H 5900 3400 50  0000 C CNN
F 1 "WeMos_D1_mini" H 5900 3300 50  0000 C CNN
F 2 "Module:WEMOS_D1_mini_light" H 5900 3650 50  0001 C CNN
F 3 "https://wiki.wemos.cc/products:d1:d1_mini#documentation" H 4050 3650 50  0001 C CNN
	1    5900 4800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 6035FABC
P 4300 4150
F 0 "R4" H 4370 4196 50  0000 L CNN
F 1 "1k" H 4370 4105 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4230 4150 50  0001 C CNN
F 3 "~" H 4300 4150 50  0001 C CNN
	1    4300 4150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 6035FEDE
P 3500 5900
F 0 "R1" H 3570 5946 50  0000 L CNN
F 1 "560" H 3570 5855 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3430 5900 50  0001 C CNN
F 3 "~" H 3500 5900 50  0001 C CNN
	1    3500 5900
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR04
U 1 1 60362B49
P 4300 3700
F 0 "#PWR04" H 4300 3550 50  0001 C CNN
F 1 "+5V" H 4315 3873 50  0000 C CNN
F 2 "" H 4300 3700 50  0001 C CNN
F 3 "" H 4300 3700 50  0001 C CNN
	1    4300 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 3700 4300 4000
$Comp
L power:GND #PWR05
U 1 1 6036389B
P 4300 6450
F 0 "#PWR05" H 4300 6200 50  0001 C CNN
F 1 "GND" H 4305 6277 50  0000 C CNN
F 2 "" H 4300 6450 50  0001 C CNN
F 3 "" H 4300 6450 50  0001 C CNN
	1    4300 6450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 5350 4300 6100
Wire Wire Line
	3500 5150 3500 5250
$Comp
L power:GND #PWR01
U 1 1 603661C6
P 3500 6500
F 0 "#PWR01" H 3500 6250 50  0001 C CNN
F 1 "GND" H 3505 6327 50  0000 C CNN
F 2 "" H 3500 6500 50  0001 C CNN
F 3 "" H 3500 6500 50  0001 C CNN
	1    3500 6500
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x08_Male J7
U 1 1 603EFD3C
P 9500 5750
F 0 "J7" H 9472 5632 50  0000 R CNN
F 1 "ePaper_connector" H 9472 5723 50  0000 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Horizontal" H 9500 5750 50  0001 C CNN
F 3 "~" H 9500 5750 50  0001 C CNN
	1    9500 5750
	-1   0    0    1   
$EndComp
Wire Wire Line
	9300 5350 8700 5350
Text Label 8700 5350 0    50   ~ 0
BUSY
Wire Wire Line
	9300 5450 8700 5450
Wire Wire Line
	9300 5550 8700 5550
Wire Wire Line
	9300 5650 8700 5650
Wire Wire Line
	9300 5750 8700 5750
Wire Wire Line
	9300 5850 8700 5850
Wire Wire Line
	9300 5950 8700 5950
Wire Wire Line
	9300 6050 8700 6050
Text Label 8700 5450 0    50   ~ 0
RST
Text Label 8700 5550 0    50   ~ 0
DC
Text Label 8700 5650 0    50   ~ 0
CS
Text Label 8700 5850 0    50   ~ 0
DIN
Text Label 8700 5950 0    50   ~ 0
GND
Text Label 8700 6050 0    50   ~ 0
3.3V
Wire Wire Line
	6300 4600 6700 4600
Wire Wire Line
	6300 4800 6700 4800
Wire Wire Line
	6300 4500 6700 4500
Wire Wire Line
	6300 5200 6700 5200
Wire Wire Line
	6300 4900 6700 4900
Wire Wire Line
	6300 5100 6700 5100
Wire Wire Line
	5900 5600 5900 5900
Wire Wire Line
	6000 4000 6000 3900
Wire Wire Line
	6000 3900 6550 3900
Text Label 6150 3900 0    50   ~ 0
3.3V
$Comp
L pspice:DIODE D1
U 1 1 603FAFB8
P 7750 4400
F 0 "D1" H 7750 4135 50  0000 C CNN
F 1 "DIODE" H 7750 4226 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 7750 4400 50  0001 C CNN
F 3 "~" H 7750 4400 50  0001 C CNN
	1    7750 4400
	-1   0    0    1   
$EndComp
Wire Wire Line
	6300 4700 6700 4700
Wire Wire Line
	6300 5000 6700 5000
Text Label 4950 4400 0    50   ~ 0
WEMOS_RESET
Wire Wire Line
	7950 4400 8450 4400
Text Label 8450 4400 0    50   ~ 0
WEMOS_RESET
$Comp
L Device:R R5
U 1 1 60414FA8
P 6500 2400
F 0 "R5" V 6293 2400 50  0000 C CNN
F 1 "10k" V 6384 2400 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 6430 2400 50  0001 C CNN
F 3 "~" H 6500 2400 50  0001 C CNN
	1    6500 2400
	0    1    1    0   
$EndComp
$Comp
L Device:R R6
U 1 1 60415464
P 7800 2350
F 0 "R6" H 7870 2396 50  0000 L CNN
F 1 "10k" H 7870 2305 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 7730 2350 50  0001 C CNN
F 3 "~" H 7800 2350 50  0001 C CNN
	1    7800 2350
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_PMOS_GDS Q3
U 1 1 604179A3
P 8300 2200
F 0 "Q3" H 8505 2246 50  0000 L CNN
F 1 "NPD6020P" H 8505 2155 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Horizontal_TabDown" H 8500 2300 50  0001 C CNN
F 3 "~" H 8300 2200 50  0001 C CNN
	1    8300 2200
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR09
U 1 1 6041FF9D
P 9150 2350
F 0 "#PWR09" H 9150 2200 50  0001 C CNN
F 1 "+5V" H 9165 2523 50  0000 C CNN
F 2 "" H 9150 2350 50  0001 C CNN
F 3 "" H 9150 2350 50  0001 C CNN
	1    9150 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 2200 7800 2200
Wire Wire Line
	7800 2200 8100 2200
Connection ~ 7800 2200
Wire Wire Line
	8400 2400 8400 2500
Wire Wire Line
	7800 2500 8400 2500
Wire Wire Line
	8400 2500 9150 2500
Connection ~ 8400 2500
Wire Wire Line
	9150 2500 9150 2350
$Comp
L power:GND #PWR08
U 1 1 604251F3
P 7200 2850
F 0 "#PWR08" H 7200 2600 50  0001 C CNN
F 1 "GND" H 7205 2677 50  0000 C CNN
F 2 "" H 7200 2850 50  0001 C CNN
F 3 "" H 7200 2850 50  0001 C CNN
	1    7200 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 2850 7200 2600
Wire Wire Line
	6650 2400 6900 2400
Wire Wire Line
	6350 2400 5750 2400
Text Label 5850 2400 0    50   ~ 0
MOSFET_CTRL
$Comp
L Connector:Conn_01x03_Male J6
U 1 1 6042C68D
P 8500 1450
F 0 "J6" V 8562 1594 50  0000 L CNN
F 1 "WS2812B_LEDs_3" V 8653 1594 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 8500 1450 50  0001 C CNN
F 3 "~" H 8500 1450 50  0001 C CNN
	1    8500 1450
	0    1    1    0   
$EndComp
Text Label 8400 1950 1    50   ~ 0
LED_VIN
$Comp
L power:GND #PWR010
U 1 1 60431545
P 9150 3000
F 0 "#PWR010" H 9150 2750 50  0001 C CNN
F 1 "GND" H 9155 2827 50  0000 C CNN
F 2 "" H 9150 3000 50  0001 C CNN
F 3 "" H 9150 3000 50  0001 C CNN
	1    9150 3000
	1    0    0    -1  
$EndComp
$Comp
L Device:R R7
U 1 1 60433010
P 9150 1900
F 0 "R7" V 8943 1900 50  0000 C CNN
F 1 "470" V 9034 1900 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 9080 1900 50  0001 C CNN
F 3 "~" H 9150 1900 50  0001 C CNN
	1    9150 1900
	0    1    1    0   
$EndComp
Wire Wire Line
	9000 1900 8600 1900
Wire Wire Line
	8600 1900 8600 1650
Text Label 9700 1900 0    50   ~ 0
WS2812B_DATA_IN
$Comp
L Device:R R2
U 1 1 604949F0
P 3500 6300
F 0 "R2" H 3570 6346 50  0000 L CNN
F 1 "560" H 3570 6255 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3430 6300 50  0001 C CNN
F 3 "~" H 3500 6300 50  0001 C CNN
	1    3500 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 6500 3500 6450
Wire Wire Line
	3500 6150 3500 6100
Wire Wire Line
	3500 6100 3150 6100
Connection ~ 3500 6100
Wire Wire Line
	3500 6100 3500 6050
Wire Wire Line
	6300 4300 6700 4300
Wire Wire Line
	6300 4400 7550 4400
Text Label 6750 4400 0    50   ~ 0
D0
$Comp
L Device:CP C1
U 1 1 604ACDC7
P 3500 5400
F 0 "C1" H 3850 5350 50  0000 R CNN
F 1 "1microF" H 3900 5450 50  0000 R CNN
F 2 "Capacitor_THT:CP_Radial_D6.3mm_P2.50mm" H 3538 5250 50  0001 C CNN
F 3 "~" H 3500 5400 50  0001 C CNN
	1    3500 5400
	-1   0    0    1   
$EndComp
Text Label 3150 6100 0    50   ~ 0
A0
$Comp
L power:PWR_FLAG #FLG01
U 1 1 604B8B50
P 1100 1000
F 0 "#FLG01" H 1100 1075 50  0001 C CNN
F 1 "PWR_FLAG" H 1100 1173 50  0000 C CNN
F 2 "" H 1100 1000 50  0001 C CNN
F 3 "~" H 1100 1000 50  0001 C CNN
	1    1100 1000
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG02
U 1 1 604B9302
P 1750 1000
F 0 "#FLG02" H 1750 1075 50  0001 C CNN
F 1 "PWR_FLAG" H 1750 1173 50  0000 C CNN
F 2 "" H 1750 1000 50  0001 C CNN
F 3 "~" H 1750 1000 50  0001 C CNN
	1    1750 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 1000 1100 1650
Wire Wire Line
	1750 1000 1750 1650
Text Label 1750 1650 0    50   ~ 0
LIPO-
$Comp
L Device:CP C2
U 1 1 604FA0D7
P 9150 2750
F 0 "C2" H 8800 2800 50  0000 L CNN
F 1 "1000microF" H 8600 2700 50  0000 L CNN
F 2 "lib_fp:Edge_CP_Radial_D12.5mm_P5.00mm" H 9188 2600 50  0001 C CNN
F 3 "~" H 9150 2750 50  0001 C CNN
	1    9150 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	9150 2600 9150 2500
Connection ~ 9150 2500
Wire Wire Line
	9150 2900 9150 2950
Wire Wire Line
	9150 2950 9550 2950
Wire Wire Line
	9550 2950 9550 2000
Wire Wire Line
	9550 2000 8500 2000
Connection ~ 9150 2950
Wire Wire Line
	9150 2950 9150 3000
Wire Wire Line
	3500 5150 3900 5150
$Comp
L Device:R R3
U 1 1 6050F431
P 3900 5950
F 0 "R3" H 3970 5996 50  0000 L CNN
F 1 "1k" H 3970 5905 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3830 5950 50  0001 C CNN
F 3 "~" H 3900 5950 50  0001 C CNN
	1    3900 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 5800 3900 5150
Connection ~ 3900 5150
Wire Wire Line
	3900 5150 4000 5150
Wire Wire Line
	3900 6100 4300 6100
Connection ~ 4300 6100
Wire Wire Line
	4300 6100 4300 6450
$Comp
L Connector:Conn_01x02_Male J1
U 1 1 60516B7C
P 1500 2950
F 0 "J1" H 1150 3000 50  0000 C CNN
F 1 "Solar pannel" H 1150 2900 50  0000 C CNN
F 2 "Connector_JST:JST_EH_S2B-EH_1x02_P2.50mm_Horizontal" H 1500 2950 50  0001 C CNN
F 3 "~" H 1500 2950 50  0001 C CNN
	1    1500 2950
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male J3
U 1 1 6051F83C
P 1500 3600
F 0 "J3" H 1150 3650 50  0000 R CNN
F 1 "Lipo_Battery" H 1350 3550 50  0000 R CNN
F 2 "Connector_JST:JST_EH_S2B-EH_1x02_P2.50mm_Horizontal" H 1500 3600 50  0001 C CNN
F 3 "~" H 1500 3600 50  0001 C CNN
	1    1500 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 3100 3000 3250
Wire Wire Line
	3650 2450 4200 2450
Wire Wire Line
	3650 2600 4200 2600
Text Label 2550 2600 2    50   ~ 0
SOLAR-
Text Label 1100 1650 0    50   ~ 0
LIPO+
Text Label 3950 2450 0    50   ~ 0
+5V
Text Label 3950 2600 0    50   ~ 0
GND
Wire Wire Line
	4300 4300 4300 4400
Wire Wire Line
	4300 4400 5500 4400
Connection ~ 4300 4400
Wire Wire Line
	4300 4400 4300 4950
$Comp
L power:GND #PWR07
U 1 1 6056B9AF
P 5900 5900
F 0 "#PWR07" H 5900 5650 50  0001 C CNN
F 1 "GND" H 5905 5727 50  0000 C CNN
F 2 "" H 5900 5900 50  0001 C CNN
F 3 "" H 5900 5900 50  0001 C CNN
	1    5900 5900
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR06
U 1 1 6056D58A
P 5800 3700
F 0 "#PWR06" H 5800 3550 50  0001 C CNN
F 1 "+5V" H 5815 3873 50  0000 C CNN
F 2 "" H 5800 3700 50  0001 C CNN
F 3 "" H 5800 3700 50  0001 C CNN
	1    5800 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 3700 5800 4000
$Comp
L power:+5V #PWR02
U 1 1 605793E3
P 4200 2450
F 0 "#PWR02" H 4200 2300 50  0001 C CNN
F 1 "+5V" H 4215 2623 50  0000 C CNN
F 2 "" H 4200 2450 50  0001 C CNN
F 3 "" H 4200 2450 50  0001 C CNN
	1    4200 2450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 6057A62A
P 4200 2600
F 0 "#PWR03" H 4200 2350 50  0001 C CNN
F 1 "GND" H 4205 2427 50  0000 C CNN
F 2 "" H 4200 2600 50  0001 C CNN
F 3 "" H 4200 2600 50  0001 C CNN
	1    4200 2600
	1    0    0    -1  
$EndComp
Text Label 8500 1950 1    50   ~ 0
LED_GND
Text Label 8600 1900 1    50   ~ 0
LED_DIN
$Comp
L Connector:Conn_01x03_Male J5
U 1 1 6059F876
P 7500 1450
F 0 "J5" V 7562 1594 50  0000 L CNN
F 1 "WS2812B_LEDS_2" V 7653 1594 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 7500 1450 50  0001 C CNN
F 3 "~" H 7500 1450 50  0001 C CNN
	1    7500 1450
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x03_Male J4
U 1 1 605A0FF2
P 6500 1450
F 0 "J4" V 6562 1594 50  0000 L CNN
F 1 "WS2812B_LEDs_1" V 6653 1594 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 6500 1450 50  0001 C CNN
F 3 "~" H 6500 1450 50  0001 C CNN
	1    6500 1450
	0    1    1    0   
$EndComp
Wire Wire Line
	8500 1650 8500 2000
Wire Wire Line
	8400 1650 8400 2000
Wire Wire Line
	8400 2000 7400 2000
Wire Wire Line
	7400 2000 7400 1650
Connection ~ 8400 2000
Wire Wire Line
	7400 2000 6400 2000
Wire Wire Line
	6400 2000 6400 1650
Connection ~ 7400 2000
Wire Wire Line
	6500 1650 6500 1900
Wire Wire Line
	6600 1650 6600 1900
Wire Wire Line
	7500 1650 7500 1900
Wire Wire Line
	7600 1650 7600 1900
Text Label 6500 1900 1    50   ~ 0
LED_GND
Text Label 7500 1900 1    50   ~ 0
LED_GND
Text Label 6600 1900 1    50   ~ 0
LED_DIN
Text Label 7600 1900 1    50   ~ 0
LED_DIN
Text Label 7400 1950 1    50   ~ 0
LED_VIN
Text Label 6400 1950 1    50   ~ 0
LED_VIN
$Comp
L Connector:Conn_01x02_Male J2
U 1 1 605D460F
P 2100 5500
F 0 "J2" H 2208 5681 50  0000 C CNN
F 1 "TO_REED_SWICH" H 2208 5590 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Horizontal" H 2100 5500 50  0001 C CNN
F 3 "~" H 2100 5500 50  0001 C CNN
	1    2100 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 5550 3500 5600
Wire Wire Line
	3000 3250 3000 5500
Wire Wire Line
	3000 5500 2300 5500
Connection ~ 3000 3250
Wire Wire Line
	2300 5600 3500 5600
Connection ~ 3500 5600
Wire Wire Line
	3500 5600 3500 5750
Text Label 8700 5750 0    50   ~ 0
CLK
Text Label 6700 4900 0    50   ~ 0
CLK
Text Label 6700 5200 0    50   ~ 0
CS
Text Label 6700 5100 0    50   ~ 0
DIN
Text Label 6700 5000 0    50   ~ 0
MOSFET_CTRL
Text Label 6700 4800 0    50   ~ 0
RST
Text Label 6700 4700 0    50   ~ 0
DC
Text Label 6700 4600 0    50   ~ 0
BUSY
Text Label 6700 4500 0    50   ~ 0
WS2812B_DATA_IN
Text Label 6700 4300 0    50   ~ 0
A0
$Comp
L Project_Library:Lithium_solar_mngt_board U1
U 1 1 60515009
P 3100 2400
F 0 "U1" H 3100 2715 50  0000 C CNN
F 1 "Lithium_solar_mngt_board" H 3100 2624 50  0000 C CNN
F 2 "Lib_fp:Lithium_solar_mngt_board" H 3150 2450 50  0001 C CNN
F 3 "" H 3150 2450 50  0001 C CNN
	1    3100 2400
	1    0    0    -1  
$EndComp
Text Label 3250 3100 3    50   ~ 0
LIPO-
Text Label 3100 3250 1    50   ~ 0
LIPO+
Wire Wire Line
	9300 1900 9700 1900
$Comp
L Switch:SW_DPST_x2 SW1
U 1 1 6061E2D6
P 2600 3250
F 0 "SW1" H 2600 3025 50  0000 C CNN
F 1 "Battery_switch" H 2600 3116 50  0000 C CNN
F 2 "Button_Switch_THT:SW_Slide_1P2T_CK_OS102011MS2Q" H 2600 3250 50  0001 C CNN
F 3 "~" H 2600 3250 50  0001 C CNN
	1    2600 3250
	-1   0    0    1   
$EndComp
Wire Wire Line
	3150 3800 3150 4000
Text Label 2550 2450 2    50   ~ 0
SOLAR+
Text Label 1700 2950 0    50   ~ 0
SOLAR-
Text Label 1700 3050 0    50   ~ 0
SOLAR+
Text Label 1700 3600 0    50   ~ 0
LIPO-
Wire Wire Line
	2800 3250 3000 3250
Text Label 2400 3250 2    50   ~ 0
LIPO+SWITCH
Text Label 1700 3700 0    50   ~ 0
LIPO+SWITCH
$Comp
L Device:Q_NPN_CBE Q1
U 1 1 604EEAAD
P 4200 5150
F 0 "Q1" H 4390 5196 50  0000 L CNN
F 1 "2N3904" H 4390 5105 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92L_Inline_Wide" H 4400 5250 50  0001 C CNN
F 3 "~" H 4200 5150 50  0001 C CNN
	1    4200 5150
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_NPN_CBE Q2
U 1 1 604F2723
P 7100 2400
F 0 "Q2" H 7290 2446 50  0000 L CNN
F 1 "2N3904" H 7290 2355 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92L_Inline_Wide" H 7300 2500 50  0001 C CNN
F 3 "~" H 7100 2400 50  0001 C CNN
	1    7100 2400
	1    0    0    -1  
$EndComp
$EndSCHEMATC
