Sobald man aus dem TrueSTUDIO oder STM32CubeIDE ein Embedded/MCU.. irgendwas mit STM32 anklickt,
hat man die HAL Lib mit drin hängen und bekommt sie schier nicht mehr aus den Einstellungen.
Ich habe schon versucht aus so einem Project die HAL herauszutrennen und sie SPL einzubinden,
hab aber dann aufgegeben.

Hier der Versuch ein "empty" Projekt anzulegen (das hat auch geklappt):

In Atollic TrueSTUDIO
  File - New - C Project -  Executable - Empty Project - Atollic ARM Tools

Dann wie hier beschrieben weiter mit Pfad einbinden usw.

Als Vorlage hat mir https://www.mikrocontroller.net/articles/STM32F4-Discovery#Beispiel-Projekte
gedient.

C/C++ Build - Settings -> Target Settings -> STM32F469NI
sobald man in TrueSTUDIO an dem Target dreht, wird das Linker file neu erzeugt (welches sich dann vom
Original kopierten STM32F479NI_FLASH.ld unterscheidet)

Bei stm32f4xx_fsmc.c bekomme ich den Fehler:
Description	Resource	Path	Location	Type
'FSMC_Bank1' undeclared (first use in this function)	stm32f4xx_fsmc.c	/disko5/Libraries/STM32F4xx_StdPeriph_Driver/src	line 137	C/C++ Problem

Wenn ich nach stm32f4xx.h schaue, wird für STM32F469_479xx
zwar FMC_Bank1 definiert, aber kein FSMC_Bank1

Jetzt weiß ich nicht, ob die lib fehlerhaft ist oder ob ich stm32_fsmc.c vom compilieren ausschließen sollte (habe ich jetzt mal probiert)

--------------
Debug Configurations - Embedded C/C++ Application doppelklick
Debug probe ST-LINK
