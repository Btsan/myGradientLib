# myGradientLib
simple C++ auto-differentiation library being implemented for exercise

### Automatic Differentiation

Every computer program uses primitive operations (e.g. add, subtract, multiply, divide) and functions (e.g. log, sin, cos) that have simple derivatives. Knowing their derivatives, the chain rule can be used to compute the gradient of any function composed of these primitives.

---

*tape.h* defines the following classes:

- __Var__:

   a class that represents a floating point value. It contains a reference to its containing dependency graph. Additionally, its operators (+, -, *, /, ^) have been overloaded to update a dependency graph with a new node.
   
- __Node__: 

   this object stores the resulting partial derivatives of a primitive operation/function on Var objects and references to those Var objects.
   
- __Tape__:

   A dependency graph of Node objects. This gets traversed during gradident calculation, called from a Var object.
   
- __Grad__:

   Container that stores a calculated gradient. It has a function for returning the derivative w.r.t. a Var object.
   
### [test.cpp](https://github.com/Btsan/myGradientLib/blob/master/test.cpp) output:

```
./test
a = 2
b = 3
c = (ab + a + sin(b))/b
c += log(a)

calculating gradient of c
a = 2, b = 3
c = (ab + a + sin(b))/b + log(a)
dc/da = 1.88037 	correct answer: 1.88037...

e = c - a

calculating gradient of e
e = c - a
e = (ab + a + sin(b))/b + log(a) - a
dc/da = 0.880373 	correct answer: 0.88037...
```

### Usage

```c
#include "tape.h"
```
compile with C++11

---

I referenced these webpages:
- <https://stats.stackexchange.com/questions/224140/step-by-step-example-of-reverse-mode-automatic-differentiation>

   A concise example of how reverse-accumulation of derivatives can compute gradients.
- <https://rufflewind.com/2016-12-30/reverse-mode-automatic-differentiation>

   More technical example of implementing auto-differentiation in the Python and Rust languages.
