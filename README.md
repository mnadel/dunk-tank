# Dunk Tank

An Arduino sketch that:

1. Reads a number sequence from a [DFRobot IR remote](https://www.robotshop.com/en/dfrobot-ir-remote-kit-arduino.html)
1. If the value is followed by the `EQ` button, stores that number as the secret code
1. If the value is equal to the secret code, engages a servo for 750ms

![img](https://user-images.githubusercontent.com/1819618/53690805-2d0f8c00-3d37-11e9-81e3-c9ab864f57d4.jpg)

# Dunk?

This is an engineering (electrical, mechanical, CS) demo for grade school students.

First, affix the servo to a spray bottle:

![img](https://user-images.githubusercontent.com/1819618/53690906-e02cb500-3d38-11e9-8cdd-c452e97a0b04.png)

Next, set an answer by entering a value then pressing the `EQ` button.

Now, ask for two volunteers. Give one the remote, and put the other in front of the spray bottle.

Finally, ask the remote-holder a math problem whose answer is the value you just entered.

If they key in the right answer, they get to squirt their friend!
