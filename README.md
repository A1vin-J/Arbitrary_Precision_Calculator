# Arbitrary Precision Calculator (APC)

## 📘 Overview

The **Arbitrary Precision Calculator (APC)** is a command-line based calculator written in **C** that performs arithmetic operations on integers of arbitrary length.

Unlike standard calculators limited by built-in data types, this project represents numbers using **doubly linked lists**, allowing accurate computation on very large values. The calculator supports both **positive and negative integers** and provides precise control over **decimal precision in division**.

---

## ⚙️ Features

* Perform arithmetic on integers of **unlimited length**
* Supports the following operations:

  * Addition (`+`)
  * Subtraction (`-`)
  * Multiplication (`x`)
  * Division (`/`) with user-defined decimal precision
  * Modulus (`%`)
* Correct handling of **positive and negative operands**
* Division implemented using **long division algorithm**
* Modular and layered code structure
* Input validation for operands and operators
* Graceful error handling for invalid inputs

---

## 🧩 Project Structure

```
APC/
|
├── apc.h              # Header file with structures and function prototypes
├── main.c             # Entry point, handles CLI validation and operation selection
├── addition.c         # Addition wrapper logic (sign handling)
├── subtraction.c      # Subtraction wrapper logic (sign handling)
├── multiplication.c   # Multiplication wrapper logic
├── division.c         # Division wrapper logic
├── modulus.c          # Modulus wrapper logic
├── cores.c            # Core arithmetic implementations
└── utils.c            # Helper and utility functions
```

---

## 🧱 Compilation

To compile the project:

```bash
gcc *.c
```

This will generate the executable file `a.out`.

---

## 🧠 Usage

```bash
./a.out <operand1> <operator> <operand2>
```

### Supported Operators

| Operator | Description    |
| -------- | -------------- |
| `+`      | Addition       |
| `-`      | Subtraction    |
| `x`      | Multiplication |
| `/`      | Division       |
| `%`      | Modulus        |

---

## ▶️ Sample Executions

### Addition

```bash
./a.out 1234567890 + 9876543223456780
```

**Output:**

```
9876544458024670
```

---

### Subtraction

```bash
./a.out -100 - -200
```

**Output:**

```
100
```

---

### Multiplication

```bash
./a.out -45678987654565667 x 87656789879876543345
```

**Output:**

```
-4004073422761737319861430987274336115
```

---

### Division (with Precision)

```bash
./a.out 987654321234567890 / 23456783456
```

**Input:**

```
Enter the number of decimal places : 10
```

**Output:**

```
42105275.1366017423
```

---

### Modulus

```bash
./a.out -1000 % 99
```

**Output:**

```
-10
```

---

## 🧩 Core Logic

* **Digit Representation**:
  Each digit of an operand is stored in a node of a doubly linked list (MSD at head, LSD at tail), enabling efficient carry and borrow propagation.

* **Centralized Sign Handling**:

  * Sign information is stored in a dedicated `Sign` structure (`sign1`, `sign2`, `res_sign`).
  * Wrapper functions decide the operation flow based on operand signs.
  * Core arithmetic functions operate purely on magnitudes.

* **Operation Reuse & Control Flow Optimization**:

  * **Subtraction is reused to perform addition** when operand signs differ.
  * **Addition is reused to perform subtraction** when subtracting a negative operand.
  * **Multiplication reuses addition logic** internally to accumulate partial products.
  * **Division core is reused for modulus**, returning either quotient or remainder based on mode.

* **Addition / Subtraction**:

  * Both operations are implemented using the same core logic with sign-based redirection.
  * Borrow handling is done via backward traversal of the linked list.

* **Multiplication**:

  * Implemented using the grade-school method.
  * Single-digit multiplication results are accumulated using the addition core.

* **Division**:

  * Implemented using long division.
  * Quotient digits are computed one-by-one (0–9) using repeated comparison.
  * Remainder is maintained as a linked list.
  * Decimal digits are generated iteratively up to user-defined precision.

* **Modulus**:

  * Implemented by reusing the division core in modulus mode.
  * Final result is the remainder.

---

## 🧠 Concepts Used

* Doubly Linked Lists
* Dynamic Memory Allocation
* Pointer Manipulation
* Long Division Algorithm
* Modular Programming in C
* Command-Line Argument Parsing

---

## 🚧 Limitations

* Division uses **truncation**, not rounding
* Modulus follows **C language semantics** (result sign follows dividend)
* Performance is not optimized for extremely large inputs
* No floating-point input support (decimals only in division output)

---

## 🚀 Future Improvements

* Implement rounding support for division
* Optimize division to reduce repeated list allocations
* Support floating-point input values
* Convert project into a reusable library

---

## 🧑‍💻 Author

**Alvin J**

[GitHub: A1vin-J](https://github.com/A1vin-J)

---

## 📄 License

This project is open-source and available under the MIT License. You are free to study, modify, and extend it.
