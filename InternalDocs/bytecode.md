# NSN Bytecode Specification

The NSN compiler translates the abstract syntax tree (AST) into a compact, stack‑based **bytecode** format that the virtual machine (`ceval.c`) executes.  The format is deliberately simple to keep the interpreter lightweight while still allowing powerful optimisations.

---

## 1. Bytecode Layout

A compiled module is represented by a contiguous memory buffer (`unsigned char *code`).  The buffer consists of a **header** followed by a sequence of **instructions**.

| Offset | Size (bytes) | Meaning |
|--------|--------------|---------|
| 0      | 4            | Magic number `0x4E534E42` (`"NSNB"`) – identifies a valid NSN bytecode file. |
| 4      | 2            | Version (major/minor). Current version: `0x0100`. |
| 6      | 2            | Constant‑pool size (number of entries). |
| 8      | *            | Constant‑pool entries (see §2). |
| …      | *            | Instruction stream (see §3). |

The **constant pool** stores immutable values referenced by the bytecode: strings, numbers, and object references (e.g., built‑in functions).  Each entry begins with a 1‑byte type tag followed by the payload.

---

## 2. Constant‑Pool Entry Types

| Tag | Name | Payload |
|-----|------|---------|
| `0x01` | `CONST_INT` | 8‑byte signed integer (little‑endian). |
| `0x02` | `CONST_FLOAT` | 8‑byte IEEE‑754 double. |
| `0x03` | `CONST_STRING` | 4‑byte length `N` + `N` UTF‑8 bytes. |
| `0x04` | `CONST_OBJECT` | 4‑byte index of another constant‑pool entry (used for built‑ins). |

The compiler emits the pool first, then references entries by their zero‑based index using the `LOAD_CONST idx` opcode.

---

## 3. Instruction Set

Each instruction is a 1‑byte opcode followed by zero or more operand bytes.  Operands are always little‑endian.

| Opcode | Mnemonic | Operands | Description |
|--------|----------|----------|-------------|
| `0x00` | `NOP` | – | No operation (used for alignment). |
| `0x01` | `LOAD_CONST` | `uint16 idx` | Push constant‑pool entry `idx` onto the value stack. |
| `0x02` | `LOAD_GLOBAL` | `uint16 name_idx` | Push global variable referenced by constant‑pool string `name_idx`. |
| `0x03` | `STORE_GLOBAL` | `uint16 name_idx` | Pop value and store in global `name_idx`. |
| `0x04` | `LOAD_FAST` | `uint16 local_idx` | Load a local variable from the current frame. |
| `0x05` | `STORE_FAST` | `uint16 local_idx` | Store top of stack into a local slot. |
| `0x06` | `CALL_FUNCTION` | `uint8 argc` | Call callable object with `argc` arguments (popped from stack). |
| `0x07` | `RETURN_VALUE` | – | Return the top of stack as the function result. |
| `0x08` | `POP_TOP` | – | Discard the top of stack. |
| `0x09` | `JUMP_FORWARD` | `uint16 offset` | Unconditional jump forward by `offset` bytes. |
| `0x0A` | `JUMP_IF_FALSE` | `uint16 offset` | Pop a boolean; if false, jump forward. |
| `0x0B` | `BUILD_LIST` | `uint16 count` | Pop `count` items and build a list object. |
| `0x0C` | `BUILD_DICT` | `uint16 count` | Pop `2*count` items (key/value) and build a dict. |
| `0x0D` | `GET_ITER` | – | Convert top of stack to an iterator. |
| `0x0E` | `FOR_ITER` | `uint16 offset` | Iterate; if exhausted, jump forward. |
| `0x0F` | `SETUP_EXCEPT` | `uint16 offset` | Set up an exception handler block. |
| `0x10` | `RAISE_EXCEPTION` | – | Raise the exception object on top of stack. |
| `0x11` | `END_FINALLY` | – | End a `try/finally` block. |
| `0xFF` | `HALT` | – | Stop execution (used for compiled scripts). |

The VM’s dispatch loop (`ceval.c`) uses a `switch` on the opcode and updates the program counter (`pc`) accordingly.

---

## 4. Optimisations Performed by the Compiler

1. **Peephole optimisation** – removes redundant `LOAD_CONST`/`POP_TOP` pairs, folds constant arithmetic, and eliminates dead code after unconditional jumps.
2. **String interning** – identical string literals are stored once in the constant pool, reducing memory pressure and speeding up dictionary look‑ups.
3. **Jump‑target coalescing** – consecutive jumps are merged into a single jump to minimise instruction count.
4. **Stack‑depth analysis** – the compiler computes the maximum stack depth for each function and validates against `NSN_MAX_STACK_SIZE` (configurable via `nsnconfig.h`).

---

## 5. Debugging Bytecode

* `nsn -b <script.nsn>` prints a human‑readable disassembly (opcode names, operand values, and constant‑pool entries).  This is useful for verifying optimisation passes.
* The VM can be built with `NSN_ENABLE_DEBUG` to emit additional runtime checks (stack underflow, type mismatches).

---

## 6. Extending the Instruction Set

When adding a new built‑in operation, follow these steps:
1. Choose an unused opcode value (keep it below `0x80` for core ops).  Extend the `enum` in `Nsn/vm.h`.
2. Implement the handler in the `switch` inside `ceval.c`.
3. Update the disassembler (`nsn -b`) to display the new mnemonic.
4. Add unit tests under `tests/vm/` to ensure correct behaviour.

---

*This document should be kept in sync with any changes to the VM or compiler.*
