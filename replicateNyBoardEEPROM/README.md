# replicateNyBoardEEPROM

This sketch will allow you to read the EEPROM data from one NyBoard and replicate it in another board.

I wrote this because I released the magic blue smoke from a NyBoard, but the Atemel 328p and external EEPROM still worked, so I wanted to replicate the calibrations in a second board to avoid needing to go through the calibration process again... I'll probably still need to tweak it, but since the servos are the same, hopefully it will be pretty close.  We'll see...

*Update after using*

Nope, probably would have taken just as long to start fram scratch with `WriteInstinct.ino`.

While the servos *were* close on the new board with the replicated EEPROM data, I still had to recalibrate all of them at least a little bit; two were so bad that I had to remove the gear arm and rotate it by a tooth because the correction would have had an adjustment with an absolute value greater than 18. Still, it was an instructive experiment and interesting to see what's actually being stored in the EEPROM data.

### Prerequisites

This sketch requires the `Streaming` library located at http://arduiniana.org/libraries/streaming/. This library provides a simple and elegant way to specify text/data to classes which inherit fromt the `Print` class (like `Serial`, most tft libraries I've come across, etc.).

### Usage

The initial contents of `eepromData.h` contains placeholder data from a stock NyBoard; you need to populate it with the EEPROM contents of the NyBoard you wish to replicate.

1. Open this sketch in the Arduino IDE and upload it to the device you wish to copy the EEPROM data from.
2. Make sure that the I2C switch is in the `Ar` position (not the `Pi` position).
3. Open up the Serial Monitor in the Arduino IDE. Make sure that the baud rate is set to 57600; line endings don't matter.
4. The sketch will restart and you will see `Y to update onboard EEPROM:`. Enter anything *except* `Y` into the input field and click on `Send`.
5. You will see `Y to update I2C EEPROM:`. Again, enter anything *except* `Y` into the input field and click on `Send`.
6. The contents of the current onboard and external EEPROMs will be dumped to the Serial Monitor. This will take a few seconds to complete.
7. When no more data is being sent to the Serial Monitor, select and copy everything in the window after the line which reads `Copy and paste the following into eepromData.h, then recompile`.
8. Open `eepromData.h` in the text editor of your choice (or use the Arduino IDE editor and click on the `eepromData.h` tab).
9. Paste the copied data into this file, replacing everything that is currently in the file.
10. Save the changed file.

Now, close the Serial Monitor and disconnect the originating NyBoard.

Now, attach the destination NyBoard.

1. Upload the sketch with the changed `eepromData.h` file to the second NyBoard.
2. Make sure that the I2C switch is in the `Ar` position (not the `Pi` position).
3. Open up the Serial Monitor in the Arduino IDE. Make sure that the baud rate is set to 57600; line endings don't matter.
4. The sketch will restart and you will see `Y to update onboard EEPROM:`. Enter `Y` into the input field and click on `Send`. You will see some lines with periods as data is written to the onboard EEPROM.
5. You will see `Y to update I2C EEPROM:`. Again, enter `Y` into the input field and click on `Send`. You will see some lines with periods as data is written to the external EEPROM.
6. After a short delay, the contents of the changed onboard and external EEPROMs will be dumped to the Serial Monitor. This will take a few seconds to complete.
7. If you wish, you can copy the output in the Serial Monitor to compare against `eepromData.h` for confirmation.
8. Close the Serial Monitor

Replication is now complete!

### License

> The MIT License (MIT)
>
> Copyright (c) 2019 Aaron Magill
>
> Permission is hereby granted, free of charge, to any person obtaining a copy
> of this software and associated documentation files (the "Software"), to deal
> in the Software without restriction, including without limitation the rights
> to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
> copies of the Software, and to permit persons to whom the Software is
> furnished to do so, subject to the following conditions:
>
> The above copyright notice and this permission notice shall be included in
> all copies or substantial portions of the Software.
>
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
> IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
> FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
> AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
> LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
> OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
> THE SOFTWARE.

