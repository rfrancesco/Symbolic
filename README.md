# Symbolic
## A C++ Computer Algebra System

__Symbolic__ is a C++ library for symbolic mathematics.

Numerical expressions are implemented as ASTs (Abstract Syntax Trees), whose nodes are operations (+-*/^, exp...), values (1.2345) and symbols (x,y,...). Expressions can be evaluated on a given (x = ..., y = ..., ...).

The project is under active development and still missing unit tests - results could be wrong.

### Features
- `Expression` objects encapsulate the AST (symbolic representation) and a `NodeStorage` object, which manages the storage and ownership of the `Node`s of the tree. Non-owning raw pointers `Node*` are used internally for traversal.
- Supported operations: Arithmetics (addition `a+b+...`, subtraction through unary negation `a - b = a + (-b)`, multiplication `a*b*...`, division `a/b`, power `a^b`) and special functions (`exp`, `sin`, `cos`, `tan`).
- Numerical evaluation of the symbolic expression on a given `SymbolContext {x = ..., y = ..., etc.}`
- New operators and functions can be easily implemented by subclassing abstract `Node, UnaryNode, BinaryNode, NaryNode` objects.
- Unit tests with `GoogleTest` (WIP)

### Example

```
// Construct Expr(x,y) = sin(x) + y^2
Expression expr;
auto x = expr.makeSymbol("x");
auto y = expr.makeSymbol("y");

auto sum = expr.makeNode<Sum>({
    expr.makeNode<Sin>(x), 
    expr.makeNode<Power>(y, expr.makeNode<Value>(2.0))
});
expr.root = sum;

// Print expression
std::cout << expr << "\n";

// Evaluate the expression on (x, y) = (1.57, 3.0)
SymbolContext ctx = {{"x", 1.57}, {"y", 3.0}};
std::cout << ctx << "\n";
std::cout << expr.evaluate(ctx) << std::endl;
```

### To be implemented
- __Important!__ Unit tests 
- Rational arithmetics for exact symbolic computations (and switch to double for performance)
- Algebraic simplification and canonical forms
- Formula API with operator overloading (using current API as backend)
```
Formula x{"x"};
Formula y{"y"};
Formula f = 2*x+y;

double result = f(SymbolContext{{"x", 1.0},{"y", 0.75}});
```
- Symbolic substitution (`x + y` , ` <- y = 3/x`)
- Analytic differentiation
- String parser (`x^2 + 2*x - y + 3/2`)
- REPL

#### Possible ideas going forward
- Numerical algorithms for integration (Trapezoids, Monte Carlo...) and Root Finding

### Build
Examples are in `example` and built automatically.

```
cmake -B build && cmake --build build
./build/examples/01_basic_usage 
```