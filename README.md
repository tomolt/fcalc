# fcalc
**a basic calculator, fully contained within a single function, released into the public domain.**

## Features
- Contained in a single C function
- Less than 100 lines long!
- Fully C89 compliant
- Absolutely NO dependency on the standard library
- No use of static or global variables (trivial to use in multithreaded programs)
- No allocations
- Public domain (go nuts with it)
- Floating-point math
- Supported operations:
 - addition (+)
 - subtraction (-)
 - multiplication (*)
 - division (/)
 - negation (-)
- Easy to extend
- Has a builtin 'pi' constant

## Usage
Using fcalc in your own program is trivial. Just copy the `fcalc` function into a source file and call it like this:
```
char *input = ...;
double result = fcalc(&input, NULL, 0);
```
Or, if you want to handle errors:
```
char *input = ...;
int err;
double result = fcalc(&input, &err, 0);
```
Where `err` will return one of three possible values:
 `0`: success
 `1`: success with errors
`-1`: error

## A common use case
An extremely common use case for something like fcalc would be almost any time you want the user of your program to input a number.
This way, they can input small mathematical terms instead of plain numbers, so they don't have compute it in their own heads (or use some desktop calculator). Many programs like GIMP or Blender already offer this feature, and fcalc is mainly intended to be a simple and easy prebaked solution for any other user-interfacing program wanting to follow suit.

## Crediting
Even though fcalc is released to the public domain and you are free to do anything you want with it, I would really appreciate it if you keep the small header comment crediting me as the original author of fcalc in your code.
