# Symbolic
## A C++ library for symbolic computation

__Symbolic__ is a C++ library for symbolic computation.

Symbolic expressions (e.g. `2x + x*y - 3`) are implemented as immutable objects represented interally as ASTs (abstract syntax trees), whose (immutable) nodes are operations (+-*/^, exp...), values (1.2345) and symbols (x,y,...). 

Expressions can be evaluated on a given (x = ..., y = ..., ...).

### Features
- `Expression` objects encapsulate the AST and handle the storage (Encapsulated `vector<unique_ptr>` is used for ownership, while raw `const Node*` are used for tree wiring and traversal).
- Supported operations: Arithmetics (addition `a+b+...`, subtraction through unary negation `a - b = a + (-b)`, multiplication `a*b*...`, division `a/b`, power `a^b`) and function calls (either built-in or user-defined)
- `Expression`s can be turned into callable functions using an `Evaluator` (visitor):
```
Evaluator eval(expr);  // transforms an expression into a callable!
double result = eval(SymbolContext{...});
```
- Values are rational numbers (`boost::rational`, necessary for exact cancellations), expression evaluation on `double`.
- Unit tests with `GoogleTest`

### Build
Requirements:
- C++20
- CMake 3.20+
- GCC 16.1.1 
- Boost 1.90 (`boost::rational`, to be installed by your package manager)
- GoogleTest (fetched by CMake, no need to do anything)

Examples are in `example` and built automatically.

```
cmake -B build && cmake --build build
./build/examples/01_basic_usage 

To enable sanitizers (debug):
cmake -B build -DENABLE_SANITIZERS=ON -DCMAKE_BUILD_TYPE=Debug

To run test suite:
ctest --test-dir build --output-on-failure
```

### Example

```
using namespace Symbolic::Core;
namespace Functions = Symbolic::Core::Functions;

// Construct Expr(x,y) = -x + y^(1/2) + sin(z)
Expression expr;
auto x = expr.makeSymbol("x");
auto y = expr.makeSymbol("y");
auto z = expr.makeSymbol("z");

// Define the expression using inbuilt operators, values and functions...
auto sum = expr.makeNode<Sum>({                                         // use N-ary operators (Sum, Product)
        expr.makeNode<Negative>(x),                                     // unary operators (x -> -x)
        expr.makeNode<Power>(y, expr.makeNode<Value>(Rational{1,2})),   // binary ops and rational constants
        expr.makeFunctionNode(Functions::Sin,{z})                     // or use inbuilt functions!
        });
expr.root = sum;

// Print expression
std::cout << expr << "\n";

// Evaluate the expression on (x, y) = (1.57, 3.0)
Evaluator eval{expr};
SymbolContext ctx = {{"x", 1.57}, {"y", 3.0}, {"z", 1.0}};
std::cout << ctx << "\n";
std::cout << eval(ctx) << "\n";

// or define your own functions (in place of Functions::Sin())
Function func = Function{
            "my_function", [](std::span<const double> s)                // arguments are {s[0], s[1], ...}
            {
                return std::sin(s[0])/s[1]; 
            },
            2};                                                         // number of arguments goes here (checked at runtime)
```

### To be implemented
- Move printing outside of AST, just like Evaluation! (Visitor pattern)
- Algebraic simplification and canonical forms
- Formula API with operator overloading (using current API as backend) OR a string parser
```
Formula x{"x"};
Formula y{"y"};
Formula f = 2*x+y;

double result = f(SymbolContext{{"x", 1.0},{"y", 0.75}});
```
- Symbolic substitution (`x + y` , ` <- y = 3/x`)
- Analytic differentiation
- REPL

#### Possible ideas going forward
- Numerical algorithms for integration (Trapezoids, Monte Carlo...) and Root Finding
