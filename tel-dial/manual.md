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
This mode allows emulating any keypresses by specifying the ASCII codes. Some of the codes are left-padded with `0`s to disambiguate them.
Example keys, and the sequences of dialled digits to emulate a short press on the key:
| Key         | Code | Sequence |
|-------------|-----:|----------|
| (NUL)       |    0 | `000000` |
| (STX)       |    2 | `000002` |
| (ETX)       |    3 | `03`     |
| Bell        |    7 | `07`     |
| Backspace   |    8 | `08`     |
| Tab         |    9 | `09`     |
| Line Feed   |   10 | `010`    |
| C. Return   |   13 | `013`    |
| (EM)        |   25 | `025`    |
| (SUB)       |   26 | `26`     |
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
| F1          |  194 | `194`    |
| INSERT      |  209 | `209`    |
| DELETE      |  212 | `212`    |
| HOME        |  210 | `210`    |
| END         |  213 | `213`    |
| PAGE_UP     |  211 | `211`    |
| PAGE_DOWN   |  214 | `214`    |
| RIGHT_ARROW |  215 | `215`    |
| LEFT_ARROW  |  216 | `216`    |
| DOWN_ARROW  |  217 | `217`    |
| UP_ARROW    |  218 | `218`    |

### Holding down keys
To press and hold down a key, dial its sequence prefixed with `00`. Any key held down in this way will be released after any sequence not prefixed with `00`.
To hold a key permanently, prefix its sequence with `0000`. To release the key, dial its sequence (without the zeros prefix).
> Example: To execute the keys sequence _Ctrl+(Shift+a, a)_, dial: `0000128001299797128`.

> Note: Holding down is not available for keys with codes 0, 1 and 2.

Switching to ASCII mode (even from the same mode) also releases all keys.
