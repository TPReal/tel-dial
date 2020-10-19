# TelDial keyboard
TelDial is a keyboard that uses for input exclusively an old telephone rotary dial.
It works in two modes: digits mode and ASCII mode, see description of the modes below. The default after plugging in the keyboard is digits mode.

## Switching modes
Each mode has a number (see sections below). To switch to mode _`n`_, follow these steps:
1. Pull the `0` hole to the finger stop, and hold it there.
2. Slowly go back, until the finger stop is placed in the middle of the _`n`_ hole.
3. Pull the `0` hole to the finger stop again.
4. Let the dial return to the home position.

## Digits mode (mode 1)
This mode only allows inputting digits, simply by dialling them.

## ASCII mode (mode 2)
This mode allows emulating any keypresses by specifying the ASCII codes. Codes are left-padded with `0`s to disambiguate.
Example keys, and the sequences of dialled digits to emulate a press and release on the key:
| Key         | Code | Sequence |
|-------------|-----:|----------|
| NUL         |    0 | `0000`   |
| STX         |    2 | `0002`   |
| ETX         |    3 | `03`     |
| Bell        |    7 | `07`     |
| Backspace   |    8 | `08`     |
| Tab         |    9 | `09`     |
| Line Feed   |   10 | `010`    |
| C. Return   |   13 | `013`    |
| Space       |   32 | `32`     |
| 0           |   48 | `48`     |
| A           |   65 | `65`     |
| a           |   97 | `97`     |
| LEFT_CTRL   |  128 | `128`    |
| LEFT_SHIFT  |  129 | `129`    |
| LEFT_ALT    |  130 | `130`    |
| RIGHT_ALT   |  134 | `134`    |
| RETURN      |  176 | `176`    |
| ESC         |  177 | `177`    |
| BACKSPACE   |  178 | `178`    |
| TAB         |  179 | `179`    |
| RIGHT_ARROW |  215 | `215`    |
| LEFT_ARROW  |  216 | `216`    |
| DOWN_ARROW  |  217 | `217`    |
| UP_ARROW    |  218 | `218`    |
| INSERT      |  209 | `209`    |
| DELETE      |  212 | `212`    |
| HOME        |  210 | `210`    |
| END         |  213 | `213`    |
| PAGE_UP     |  211 | `211`    |
| PAGE_DOWN   |  214 | `214`    |
| F1          |  194 | `194`    |

It is also possible to emulate keystrokes. Specifying the key code prefixed with `00` emulates pressing and holding the key. Then specifying any non-`00` sequence of a key sends a keypress for that last key, and then releases all the previously held keys. For example, to emulate LEFT_SHIFT+RIGHT_ALT+a, dial the sequence `001290013497`.
