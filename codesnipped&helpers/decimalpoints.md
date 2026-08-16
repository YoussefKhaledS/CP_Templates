# Floating Point Cheat Sheet (C++)

## Types
```cpp
float       // ~7 digits
double      // ~15 digits (use this)
long double // ~18-21 digits (when extra precision is needed)
```

## Constants
```cpp
const double EPS = 1e-9;
const long double PI = acosl(-1.0L);
```

## Comparing doubles (NEVER use ==)
```cpp
bool equal(double a, double b) {
    return fabs(a - b) < EPS;
}

bool lessThan(double a, double b) {
    return a < b - EPS;
}

bool greaterThan(double a, double b) {
    return a > b + EPS;
}

bool lessOrEqual(double a, double b) {
    return a < b + EPS;
}

bool greaterOrEqual(double a, double b) {
    return a > b - EPS;
}
```

## Rounding
```cpp
round(x);   // nearest
floor(x);   // down
ceil(x);    // up
trunc(x);   // toward zero
```

## Absolute value
```cpp
fabs(x);    // double
abs(x);     // int
```

## Printing
```cpp
cout << fixed << setprecision(10) << x;
```

## Binary Search on Answer
```cpp
for (int i = 0; i < 100; i++) {
    double mid = (l + r) / 2;
    if (check(mid))
        l = mid;
    else
        r = mid;
}
```

## Useful Math
```cpp
sqrt(x);
cbrt(x);
pow(a, b);
hypot(x, y);     // sqrt(x*x + y*y)
```

## Angle Conversion
```cpp
double rad = deg * PI / 180.0;
double deg = rad * 180.0 / PI;
```

## Infinity
```cpp
const double INF = 1e100;
```

## Output with Specific Decimal Places

```cpp
#include <iomanip>

// Exactly 2 digits after decimal point
cout << fixed << setprecision(2) << x;

// Exactly 6 digits after decimal point
cout << fixed << setprecision(6) << x;

// Exactly 10 digits after decimal point
cout << fixed << setprecision(10) << x;
```

### Difference
```cpp
cout << setprecision(6) << x;          // 6 significant digits
cout << fixed << setprecision(6) << x; // 6 digits after decimal point
```

### Examples
```cpp
double x = 3.1415926535;

cout << fixed << setprecision(2) << x;   // 3.14
cout << fixed << setprecision(4) << x;   // 3.1416
cout << fixed << setprecision(10) << x;  // 3.1415926535
```

## Common Mistakes
- ❌ Never compare doubles with `==`
- ✅ Always compare using `EPS`
- ✅ Use `double` unless the problem requires higher precision
- ✅ Print with enough precision (`setprecision(10)` or more)
- ✅ In binary search on doubles, iterate ~100 times instead of `while`