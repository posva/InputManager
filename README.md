#InputManager
by Eduardo San Martin Morote aka [posva](https://github.com/posva)
Simple Input and Actions linking and managing using [SFML2](https://github.com/LaurentGomila/SFML).

##Description
You can manage Actions and link some inputs to them. Then when the input is detected a signal is send to the related actions which will check if the event match any activation method with that input. If it's the case the binded function to that action will be launched.

##Modules
- [x] Input: base class for different inputs such as Mouse, Keyboard and Joystick
- [x] Keyboard: class for keybard keys
- [ ] Mouse: class for mouse events
- [ ] Joystick: class for Joystick events
- [x] Action: class for managing actions and its related inputs and activation methods
- [x] ActivatedInput: link between and input and its activation method such as keyPress or keyRelease
- [x] InputManager: user interaction class for managing all the classes above

##License
This is distributed under the [LGPL license](http://www.gnu.org/licenses/lgpl.html)
