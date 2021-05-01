# STM32F4
Hier versuche ich meine ersten Schritte mit dem STM32F4 zu dokumentieren.

## Atollic TrueSTUDIO

https://www.st.com/en/development-tools/truestudio.html

Die Firma mit dem M verwendet die IDE auch für das neue Projekt.
Keine Updates mehr seit 2017 aber der Download ist auf 2019 datiert.

  $ tar xzvf en.TrueSTUDIO_V9.3_lin.gz
  $ cd Atollic_TrueSTUDIO_for_STM32_9.3.0_installer/
  $ sudo ./install.sh
  ST-Link udev rules ja, Segger nein

TODO: noch lesen (gleich am Samstag)
https://www.mikrocontroller.net/articles/STM32_LEDBlinken_AtollicTrueStudio

## STM32CubeMX

Tool um sich die Hardwarekonfiguration (Clocks, GPIO, Middleware usw.) zusammen zu klicken und ein
Projekt mit startup code usw. zu erzeugen. Als Zielplatform konnte man
dieverse IDEs (wie auch TrueSTUDIO oder Makefiles) angeben.
Der erzeugte Coderumpf konnte man dann mit seinem eigenen Code füllen und kompilieren.

Als Library wird die HAL verwendet. So wie ich es sehe gibt es keine Möglichkeit die SPL zu verwenden.

## STM32CubeIDE

STM32CubeIDE vereint nun die Atollic TrueSTUDIO mit STM32CubeMX
Download von https://www.st.com/en/development-tools/stm32cubeide.html

Ich habe die .deb version gezogen: st-stm32cubeide_1.6.1_9958_20210326_1446_amd64.deb_bundle.sh
$ sudo sh st-stm32cubeide_1.6.1_9958_20210326_1446_amd64.deb_bundle.sh
  Segger J-Link haben wir nicht, daher udev rules -> no
  wenn fertig, wurde die IDE nach /opt/st/stm32cubeide_1.6.1 installiert

  Ein Link findet sich im Menü unter "Entwicklung"
  Beim ersten Start will es ein Workspace anlegen, ich habe den default
  /home/andy/STM32CubeIDE/workspace_1.6.1 gelassen
  und [x] "... do not ask again"

## STM32 Standard Peripheral Libraries

Eine Peripherie-Bibliothek, die auf CMSIS aufsetzt. Wurde 2012 von HAL (siehe unten) abgelöst.

Kann man aber immer noch für viele MCUs herunterladen:
https://www.st.com/en/embedded-software/stm32-standard-peripheral-libraries.html
Für STM32F4 wäre das "STSW-STM32065 v 1.8.0"

aktuelle MCUs werden nicht mehr unterstützt.

Hier wird die SPL für STM32F10x beschrieben: https://www.mikrocontroller.net/articles/STM32F10x_Standard_Peripherals_Library
Hier für STM32F4-Discovery: https://www.mikrocontroller.net/articles/STM32F4-Discovery

## HAL / STM32Cube MCU & MPU Packages

Seit 2012 der neue Standard. TrueStudio, STM32CubeMX und STM32CubeIDE verwenden diese automatisch bei Projekterzeugung.

https://www.st.com/en/embedded-software/stm32cube-mcu-mpu-packages.html

## externe Links
https://www.mikrocontroller.net/articles/STM32
