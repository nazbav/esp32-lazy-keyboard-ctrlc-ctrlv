# BLE Keyboard Project Documentation on ESP32 (Description and Code by ChatGPT)

![Welcome](https://github.com/nazbav/esp32-lazy-keyboard-ctrlc-ctrlv/blob/master/photo_2024-09-09_00-18-58.jpg?raw=true "Welcome")

## About the Project

This project allows you to control your computer using an ESP32, emulating keyboard keystrokes via Bluetooth. The program uses the [ESP32-BLE-Keyboard](https://github.com/T-vK/ESP32-BLE-Keyboard) library to create a BLE keyboard that responds to button presses. It is ideal for automating frequently used actions such as copying, pasting, and selecting text.

## Required Hardware

- **ESP32** (recommended board version 2.0.13) — a microcontroller supporting Bluetooth Low Energy (BLE).
- **Two buttons** — regular buttons with pull-up resistors can be used.
- **No external pull-up resistors needed** — using built-in pull-ups of the ESP32.

## How the Program Works

The program monitors presses on two buttons and performs corresponding actions by emulating keyboard inputs. The control works as follows:

1. **First button** (`buttonPin`, GPIO 23):
   - **Short press**: Sends the `Ctrl + C` combination, used for copying text.
   - **Long press** (press duration over 300 ms): Sends the `Ctrl + A` combination, which selects all text on the screen.
   - **Double press**: Detected but not used in the current code version.

2. **Second button** (`buttonPin1`, GPIO 19):
   - **Short press**: Sends the `Ctrl + V` combination, which pastes copied text.
   - **Long press**: Sends the `Ctrl + Shift + Left Arrow` combination, used for selecting text to the left of the cursor.
   - **Double press**: Detected but not processed.

3. **Simultaneous press of both buttons**:
   - Resets text selection by sending `Ctrl + X`, then the cursor moves right and back left to clear the selection.

## Button Connections

- Connect the first button to GPIO 23 using the built-in pull-up resistor (`INPUT_PULLUP`).
- Connect the second button to GPIO 19 with the same setup.

## Important Notes

1. **ESP32 Board Version**: Ensure version 2.0.13 is installed, as other versions may have incompatible changes in BLE functionality.

2. **Button Connections**: Built-in pull-up resistors (`INPUT_PULLUP`) on the ESP32 eliminate the need for external resistors.

3. **Bug on First Connection**: The program has a known issue — on the first connection, the BLE keyboard might not reconnect automatically. If this occurs, you need to remove and re-add the device in Windows.

4. **Reconnection**: The current version of the program does not automatically reconnect the keyboard upon losing the connection, which should be considered during use.

## Conclusion

This project allows you to automate simple tasks on your computer using an ESP32 functioning as a BLE keyboard. The program is perfect for enhancing workflow and reducing repetitive actions. Use this code to control text and other operations effortlessly!

![Welcome](https://github.com/nazbav/esp32-lazy-keyboard-ctrlc-ctrlv/blob/master/photo_2024-09-09_00-18-51.jpg?raw=true "Welcome")


# Документация проекта BLE-клавиатуры на ESP32 (Описание и код от ChatGPT)

![Welcome](https://github.com/nazbav/esp32-lazy-keyboard-ctrlc-ctrlv/blob/master/photo_2024-09-09_00-18-58.jpg?raw=true "Welcome")

## О проекте

Этот проект позволяет управлять вашим компьютером с помощью ESP32, имитируя нажатия клавиш клавиатуры через Bluetooth. Программа использует библиотеку [ESP32-BLE-Keyboard](https://github.com/T-vK/ESP32-BLE-Keyboard) для создания BLE-клавиатуры, реагирующей на нажатие кнопок. Идеально подходит для автоматизации часто используемых действий, таких как копирование, вставка и выделение текста.

## Необходимое оборудование

- **ESP32** (рекомендуемая версия платы 2.0.13) — микроконтроллер, поддерживающий Bluetooth Low Energy (BLE).
- **Две кнопки** — можно использовать обычные кнопки с подтягивающими резисторами.
- **Подтягивающие резисторы не нужны** — используем встроенные пуллапы ESP32.

## Принцип работы программы

Программа отслеживает нажатия на две кнопки и выполняет соответствующие действия, имитируя клавиатуру. Управление происходит следующим образом:

1. **Первая кнопка** (`buttonPin`, GPIO 23):
   - **Короткое нажатие**: отправляется комбинация `Ctrl + C`, используется для копирования текста.
   - **Длинное нажатие** (длительность нажатия более 300 мс): отправляется комбинация `Ctrl + A`, выделяет весь текст на экране.
   - **Двойное нажатие**: детектируется, но в текущей версии кода не используется.

2. **Вторая кнопка** (`buttonPin1`, GPIO 19):
   - **Короткое нажатие**: отправляется комбинация `Ctrl + V`, вставляет скопированный текст.
   - **Длинное нажатие**: отправляется комбинация `Ctrl + Shift + Left Arrow`, используется для выделения текста слева от курсора.
   - **Двойное нажатие**: детектируется, но не обрабатывается.

3. **Одновременное нажатие обеих кнопок**:
   - Выполняется сброс выделения текста путем имитации `Ctrl + X`, затем курсор смещается вправо и обратно влево, чтобы снять выделение.

## Подключение кнопок

- Подключите первую кнопку к GPIO 23 с использованием встроенного подтягивающего резистора (`INPUT_PULLUP`).
- Подключите вторую кнопку к GPIO 19 с аналогичным подключением.

## Важные замечания

1. **Версия платы ESP32**: Убедитесь, что установлена версия 2.0.13, так как другие версии могут содержать несовместимые изменения в работе BLE.

2. **Подключение кнопок**: Встроенные подтягивающие резисторы (`INPUT_PULLUP`) на ESP32 позволяют избежать необходимости внешних резисторов.

3. **Баг при первом подключении**: Программа имеет известный баг — при первом подключении BLE-клавиатуры может возникнуть проблема, при которой клавиатура не подключается повторно автоматически. Если это произошло, требуется удалить устройство и добавить его заново в Windows.

4. **Переподключение**: В текущей версии программы нет автоматического переподключения клавиатуры при потере связи, что необходимо учитывать в использовании.

## Заключение

Этот проект позволяет автоматизировать простые задачи на вашем компьютере с помощью ESP32, работающего как BLE-клавиатура. Программа идеально подходит для улучшения рабочего процесса и снижения количества рутинных действий. Используйте данный код для управления текстом и другими операциями без лишних усилий!

![Welcome](https://github.com/nazbav/esp32-lazy-keyboard-ctrlc-ctrlv/blob/master/photo_2024-09-09_00-18-51.jpg?raw=true "Welcome")
