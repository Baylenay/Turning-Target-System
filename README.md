# Turning-Target-System

For my A-Level Electronics project I built a turning target system in order to help me train for the pistol shooting element of Tetrathlon competitions. In competition, the shooter gets 10 shots from 10m. For each shot, a question: “Are you ready?”  and two commands: “watch…”, “…and shoot” are spoken by an officiator. There is then a 3 second delay before the target turns from a side position to a facing position, allowing the shooter to fire before the target returns to its side position 4 seconds later. The system has a controller, powered by an Arduino chip, with buttons to select competition mode or training mode and control the position of the target. A reset button halts any process. A buzzer seeks to mimic the question and 2 commands with a short buzzing noise whilst an LCD displays the words. Instructions are sent over a radio link to another Arduino chip which is in charge of controlling a stepper motor which can turn the target 90 degrees clockwise or anticlockwise.

![](Target%20box.jpg)
![](Controller.jpg)
