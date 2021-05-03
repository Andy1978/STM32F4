30.04.2021

WIP: es kompiliert und flashed aber die LEDs blinken nicht....

ich versuche hier einmal ein kleines Beispielprojekt ohne eine IDE zu erzeugen.
Die IDEs machen mir zu viel im Hintergrund und wenn es dann schief geht, verstehe ich nicht warum.

Die SPL ist seit Jahren durch die HAL abgelöst (die wird auch von den
Atollic TrueStudio und dem Nachfolger STM32CubeIDE unterstützt).
Da die Firmwa mit M in ihrem "neuen" Projekt aber immer noch auf die SPL aufsetzt,
muss ich mich damit beschäftigen.

Von hier aus https://www.st.com/en/embedded-software/stm32-standard-peripheral-libraries.html
wähle ich F4 (weil das Disco Board einen STM31F469 MCU hat).
Das führt "STSW-STM32065 	STM32F4 DSP and standard peripherals library 	1.8.0"
en.stm32f4_dsp_stdperiph_lib.zip

Die CHM Hilfe darin sieht recht gut strukturiert aus.
Darin gibt es auch ein "How to use the Standard Peripherals Library" chapter.
Unter Project gibt es Beispiele, die ich mir auch einmal genauer anschauen will
(z.B. auch SDIO)

--- http://cms.seng.de/service-support/downloads/
    http://www.downloads.seng.de/HowTo_ToolChain_STM32_Ubuntu.pdf

https://hackaday.com/2016/03/22/embed-with-elliot-arm-makefile-madness/

In dem Artikel heißt es zur memory map "...but you can find the right memory map for your project in the development libraries that you’re using."
Ich habe in STM32F4xx_DSP_StdPeriph_Lib_V1.8.0 gesucht
  find . -name "*.ld" | grep F469 | xargs md5sum

und mich dann für diese hier entschieden:
./STM32F4xx_DSP_StdPeriph_Lib_V1.8.0/Project/STM32F4xx_StdPeriph_Templates/SW4STM32/STM32F469_479xx/STM32F479NIHx_FLASH.ld

Wo bekomme ich den startup code her?
  $ find . -name "startup*" | grep 469
ich habe jetzt den aus TrueSTUDIO genommen ohne genau zu wissen, was es damit auf sich hat


