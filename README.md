# FlexController
Bluetooth Muscle Flex Controller for Games

The entailed project will have two bluetooth HM-10 Modules connected in a one-way connection. With this, the EMG sensor will placed on the transmitting microcontroller, which is an Arduino Uno R3, and then after determing whether the muscle is flexed or not, it shall send it to the receiver.

The receiving microcontroller contains an LCD panel to display the game and the muscle flex controls the character in the game. One optional feature is to have the score be displayed on a 4 digit led number display. 

As for how the game actually functions, it is a character that can move between two different paths in order to evade the spike coming along his path. The flex is what triggers him to switch paths and the score can either be determine by a timer using millis() or a counter for spikes evaded.
