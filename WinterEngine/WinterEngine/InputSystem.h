#pragma once

//handles all components that wants to make use of inputs
//idea how it works: a inputComponent wants some sort of input, specified in the component, the component registers to the inputsystem
//which will register the value it wants( lets say key W ,the input will add it if it doesn't already exist, and create a list for that key and add the component in it)
//preferebly using a map to vector?

class InputSystem
{
public:
	InputSystem();
	~InputSystem();
};

