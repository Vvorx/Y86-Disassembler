# Y86 Disassembler

This project is a disassembler for Y86 assembly code. It takes a file containing Y86 machine code as input and outputs the corresponding Y86 assembly instructions.

## What is Y86?

The Y86 instruction set architecture (ISA) is a simplified version of the x86 architecture, commonly used in computer architecture courses to illustrate key concepts. It features a smaller set of instructions, registers, and addressing modes than x86, making it easier to learn and understand. For more information on Y86, please refer to the textbook "Computer Systems: A Programmer's Perspective" by Randal E. Bryant and David R. O'Hallaron, which is the original source for the Y86 ISA.

## Usage

To disassemble a Y86 machine code file, use the following command:

```bash
./y86-disassembler <input_file>
```

Replace `<input_file>` with the path to your Y86 machine code file.

## Building

To compile the Y86 disassembler, you will need a C compiler such as `gcc`. Navigate to the directory containing the source code file `y86disassembler.c` and run the following command:

```bash
gcc -o y86-disassembler y86disassembler.c
```

This will create an executable file named `y86-disassembler` in the current directory.

## Features

The Y86 Disassembler supports a wide range of Y86 instructions, including:

*   **Data Transfer:** `rrmovl`, `irmovl`, `rmmovl`, `mrmovl`, `pushl`, `popl`
*   **Conditional Moves:** `cmovle`, `cmovl`, `cmove`, `cmovne`, `cmovge`, `cmovg`
*   **Arithmetic/Logical Operations:** `addl`, `subl`, `andl`, `xorl`
*   **Control Flow:** `jmp`, `jle`, `jl`, `je`, `jne`, `jge`, `jg`, `call`, `ret`
*   **Miscellaneous:** `halt`, `nop`

The disassembler correctly decodes register operands and immediate values, including displacements for memory operations.

## Example

Here's an example of Y86 machine code and its corresponding disassembled output:

**Input (e.g., in a file named `example.yo`):**

```
30F234120000
2001
00
```

**Command:**

```bash
./y86-disassembler example.yo
```

**Output:**

```
irmovl $4660, %edx
rrmovl %eax, %ecx
halt
```
(Note: The immediate value `$4660` is the decimal representation of `0x1234`.)
