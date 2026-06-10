# Little Fermat: 16-bit Wieferich Prime Hunter

A hyper-optimized, **zero-allocation** ANSI C application designed to exhaustively search the 16-bit integer space to identify all **Wieferich Primes**.

## Mathematical Background

**Fermat's Little Theorem** states that if $p$ is a prime number, then for any integer $a$ not divisible by $p$:
$$ a^{p-1} \equiv 1 \pmod p $$

A **Wieferich Prime** is a rare prime number $p$ that satisfies a much stricter condition. Specifically, it must satisfy the congruence using the *square* of the prime as the modulus:
$$ 2^{p-1} \equiv 1 \pmod{p^2} $$

These primes are incredibly rare. In the entire 16-bit integer space (up to $65,535$), only two primes satisfy this condition: **1093** and **3511**.

## Algorithms & Architecture

To achieve absolute simplicity and zero memory footprint, the program relies on two core design pillars:

### 1. On-The-Fly Trial Division
The program evaluates the primality of every odd number on-the-fly. 
Because the maximum number in 16-bit space is $65,535$, the maximum factor we ever need to check is $\sqrt{65535} \approx 255$. A standard modern CPU or microcontroller can execute trial division up to 255 in CPU registers faster than accessing an array stored in RAM. This drops the program's memory requirement to absolutely nothing.

### 2. Native 64-bit Modular Exponentiation
For each prime $p$, the program must evaluate $2^{p-1} \pmod{p^2}$.
Because the maximum $p \le 65521$, the mathematical bounds are extremely well-defined:
- The modulus $p^2 \le 4,293,001,441$, perfectly fitting inside a standard `uint32_t`.
- The intermediate multiplications $(a \times b) \pmod{p^2}$ will never exceed $(p^2)^2 = p^4$.
- The maximum $p^4 \approx 1.842 \times 10^{19}$. The absolute limit of a standard 64-bit integer (`uint64_t`) is $1.844 \times 10^{19}$.

## Project Structure

* `source/main.c`: The core C application containing the trial division and the native modular math.
* `Makefile`: A minimal, multi-platform build system configuration for compiling and formatting.
* `.clang-format`: The LLVM configuration file ensuring consistent C code style.

## How to Build & Run

### Desktop Compilation
* **Build and Run:**
  ```bash
  make run
  ```
  This will compile `source/main.c` into a native executable and run it immediately.

* **Format the code:**
  ```bash
  make format
  ```

* **Clean:**
  ```bash
  make clean
  ```
