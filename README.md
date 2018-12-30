# myGradientLib
simple C++ auto-differentiation library being implemented for exercise

### Automatic Differentiation

Every computer program uses primitive operations (e.g. add, subtract, multiply, divide) and functions (e.g. log, sin, cos) that have simple derivatives. Knowing their derivatives, the chain rule can be used to compute the gradient of any function composed of these primitives.

---

[*tape.h*](https://github.com/Btsan/myGradientLib/blob/master/tape.h) defines the following classes:

- __Var__:

   a class that represents a floating point value. It contains a reference to its containing dependency graph. Additionally, its operators (+, -, *, /, ^) have been overloaded to update a dependency graph with a new node.
   
- __Node__: 

   this object stores the resulting partial derivatives of a primitive operation/function on Var objects and references to those Var objects.
   
- __Tape__:

   A dependency graph of Node objects. This gets traversed during gradient calculation, called from a Var object.
   
- __Grad__:

   Container that stores a calculated gradient. It has a function for returning the derivative w.r.t. a Var object.
   
### [test.cpp](https://github.com/Btsan/myGradientLib/blob/master/test.cpp) output:
###### Note that floating point error is noticeable
```
./test
a = 2
b = 3
c = (ab + a + sin(b)a)/b
c += log(a)

calculating gradient of c:
dc/da = 1.88037 	correct answer: 1.88037...
dc/db = -0.913577 	correct answer: -0.9135...

e = c - a
f = c + ab

calculating gradient of e:
de/da = 0.880373 	correct answer: 0.88037...
de/db = -0.913577 	correct answer: -0.9135...

calculating gradient of f:
df/da = 4.88037 	correct answer: 4.88037...
df/db = 1.08642 	correct answer: 1.086...

g = sin(a) + cos(a) + tan(a) + sec(a) + csc(a) + cot(a) + sinh(a) + cosh(a) + tanh(a) + sech(a) + csch(a) + coth(a)

calculating gradient of g:
dg/da = 16.0349 	correct answer: 15.8348...
dg/db = 0 	correct answer: 0

h = (e^log10(b))^2 + a

calculating gradient of h:
dh/da = 1 	correct answer: 1
dh/db = 0.751823 	correct answer: 0.7518...

i = sinc(a) + sigmoid(b)

calculating gradient of i:
di/da = -0.435398 	correct answer: -0.43539...
di/db = -0.0451767 	correct answer: -0.04517...
a = 0
b = 1
m = asin(b) + acos(a) + atan(a)

calculating gradient of m:
dm/da = 0 	correct answer: 0
dm/db = inf 	correct answer: 1/0
```

### Usage

```c
#include "tape.h"
```
compile with C++11 and build with tape.cpp

```make
g++ example.cpp tape.cpp -std=c++11 -o example
```

### Example

[example.cpp](https://github.com/Btsan/myGradientLib/blob/master/example.cpp) demonstrates using this library to train a multilayer perceptron neural network to model XOR.

```make
make example
g++ example.cpp tape.cpp -O2 -std=c++11 -o example
./example
iteration 0/100 	mean_squared_loss = 0.223089
iteration 1/100 	mean_squared_loss = 0.220401
iteration 2/100 	mean_squared_loss = 0.218163
iteration 3/100 	mean_squared_loss = 0.216287
iteration 4/100 	mean_squared_loss = 0.214705
iteration 5/100 	mean_squared_loss = 0.213361
iteration 6/100 	mean_squared_loss = 0.212213
iteration 7/100 	mean_squared_loss = 0.211225
iteration 8/100 	mean_squared_loss = 0.210369
iteration 9/100 	mean_squared_loss = 0.209623
iteration 10/100 	mean_squared_loss = 0.208969
iteration 11/100 	mean_squared_loss = 0.208391
iteration 12/100 	mean_squared_loss = 0.207879
iteration 13/100 	mean_squared_loss = 0.207421
...
iteration 83/100 	mean_squared_loss = 0.198765
iteration 84/100 	mean_squared_loss = 0.198701
iteration 85/100 	mean_squared_loss = 0.198638
iteration 86/100 	mean_squared_loss = 0.198575
iteration 87/100 	mean_squared_loss = 0.198512
iteration 88/100 	mean_squared_loss = 0.198451
iteration 89/100 	mean_squared_loss = 0.198389
iteration 90/100 	mean_squared_loss = 0.198329
iteration 91/100 	mean_squared_loss = 0.198268
iteration 92/100 	mean_squared_loss = 0.198209
iteration 93/100 	mean_squared_loss = 0.19815
iteration 94/100 	mean_squared_loss = 0.198091
iteration 95/100 	mean_squared_loss = 0.198033
iteration 96/100 	mean_squared_loss = 0.197975
iteration 97/100 	mean_squared_loss = 0.197918
iteration 98/100 	mean_squared_loss = 0.197861
iteration 99/100 	mean_squared_loss = 0.197805
rm example
```

---

I referenced these webpages on auto-differentiation:
- <https://stats.stackexchange.com/questions/224140/step-by-step-example-of-reverse-mode-automatic-differentiation>

   A concise example of how reverse-accumulation of derivatives can compute gradients.
- <https://rufflewind.com/2016-12-30/reverse-mode-automatic-differentiation>

   More technical example of implementing auto-differentiation in the Python and Rust languages.
