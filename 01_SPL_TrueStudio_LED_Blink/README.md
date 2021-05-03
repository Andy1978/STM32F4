Sobald man aus dem TrueSTUDIO oder STM32CubeIDE ein Embedded/MCU.. irgendwas mit STM32 anklickt,
hat man die HAL Lib mit drin hängen und bekommt sie schier nicht mehr aus den Einstellungen.
Ich habe schon versucht aus so einem Project die HAL herauszutrennen und sie SPL einzubinden,
hab aber dann aufgegeben.

Hier der Versuch ein "empty" Projekt anzulegen und dann erst die SPL einzubinden (das hat auch geklappt):

Der Versuch basiert auf https://www.mikrocontroller.net/articles/STM32F4-Discovery#Beispiel-Projekte
Die Atollic Version hat sich zwischenzeitlich geändert, daher stimmt nicht mehr alles.
Ich habe hier alle wichtigen Schritte für Atollic TrueSTUDIO Version 9.3.0, Build id: 20190212-0734
erwähnt, so dass man den Link oben nur noch als Referenz braucht.

In Atollic TrueSTUDIO
File - New - C Project -  Executable - Empty Project - Atollic ARM Tools

  Project name "blink1" -> Next
  Debug und Release gewählt -> Finish

Project - Build Settings...
  kommt ne Warnung "No target settings could be found" -> OK
  Unter C/C++ Build - Settings -> Target Settings -> STM32F469NI
  (die MCU ist auf dem STMF469 Discovery kit verbaut)
  -> Apply
  Sobald man in TrueSTUDIO an dem Target dreht, wird das Linker file neu erzeugt (welches sich dann vom
  Original STM32F479NI_FLASH.ld in der SPL Lib leicht unterscheidet)

  "Changes made probably requires modification to the linker script file..." -> OK
  Dann kommt der "Create linker script" wizard. -> Finish
  Jetzt wurde ...Atollic_TrueSTUDIO/STM32_workspace_9.3/blink1/Debug_STM32F469NI_FLASH.ld erzeugt

Jetzt die SPL (en.stm32f4_dsp_stdperiph_lib.zip) irgendwo in ein Temporäres dir entpacken.
Dann daraus das directory Libraries komplett in das workspace STM32_workspace_9.3/blink1/ kopieren

Nun werden die Include Pfade für die Header hinzugefügt:
  Project - Properties - C/C++ General - Paths and Symbols
  Configuration [All configurations] auswählen
  dann Tab Includes - Languages GNU C - Add

  ./Libraries/CMSIS/Include/
  ./Libraries/CMSIS/Device/ST/STM32F4xx/Include/
  ./Libraries/STM32F4xx_StdPeriph_Driver/inc/
  ./inc

  Das meckert dann "Using relative paths is ambiguous..." aber ich will es so haben

Dann der Pfad zum Quellcode:
  Wie oben, dann Tab "Source Location" -> "Add Folder"
  Libraries/STM32F4xx_StdPeriph_Driver/src

  Per default ist auch /blink in "Source Location" enthalten und wird recursiv durchsucht.
  Dies führt dann zu Problemen, weil auch
  Libraries/CMSIS/Device/ST/STM32F4xx/Source/Templates/iar/* usw. mit eingebunden werden.

  Entweder packen wir unseren Sourcecode (main.c) in ein getrenntes dir (und binden das ein), oder
  machen einen "Exclude Filter" auf ./Libraries.

  Ich habe mich hier für ersteres Entschieden.
  Also ein "src" dir anlegen und das hinzufügen, das /blink1 löschen.

Jetzt noch die Symbole (für [All configurations]) anlegen:

  USE_STDPERIPH_DRIVER
  STM32F469_479xx

Jetzt benötigen wir noch den startup und system code un kopieren
  ./Libraries/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c
  ./Libraries/CMSIS/Device/ST/STM32F4xx/Source/Templates/TrueSTUDIO/startup_stm32f469_479xx.s

  nach ./src

  ./src/main.c und ./inc/stm32f4xx_conf.h
  Die einzigen beiden Dateien mit UserCode sind Teil dieses Repos

Jetzt steht dem kompilieren eigentlich nichts mehr im Weg aber bei stm32f4xx_fsmc.c bekomme ich den Fehler:
  Description	Resource	Path	Location	Type
  'FSMC_Bank1' undeclared (first use in this function)	stm32f4xx_fsmc.c	/disko5/Libraries/STM32F4xx_StdPeriph_Driver/src	line 137	C/C++ Problem

  Wenn ich nach stm32f4xx.h schaue, wird für STM32F469_479xx
  zwar FMC_Bank1 definiert, aber kein FSMC_Bank1

  Jetzt weiß ich nicht, ob die lib fehlerhaft ist oder ob ich stm32_fsmc.c vom compilieren ausschließen sollte (habe ich jetzt mal probiert)
  Da kann man im Project Explorer auf die Datei stm32f4xx_fsmc.c (da ist ein rotes x davor um anzuzeigen, dass es in der Datei ein Problem gibt)
  und dann rechte Maustaste "Resource Configuration" - "Exclude from build"
  Die Datei wird dann ausgegraut am unteren Ende der Liste dargestellt

Nun noch ST-LINK als Programmiertool und Debugger einrichten.
Run - Debug Configurations - Embedded C/C++ Application doppelklick
Debug probe ST-LINK, Rest so lassen

Wenn man jetzt "Run - Debug As - Embedded C/C++ Application" klick, lädt das Programm hoch und man steht am Anfang von main
Nun steppen oder F8 resume. Led sollte dann orange/rot blinken.
