# Sniffer

> **Cross‑platform MAC‑address frequency counter for Wi‑Fi sniffer logs**

This utility reads a plaintext log produced by a network sniffer, extracts MAC addresses that appear in the **RA**, **TA** or **SA** fields and prints a frequency table sorted by descending hit‑count.

---

\## Features

* 💻 **Pure C++17** code – only the standard library is used.
* 🎯 **Cross‑platform** – builds with **GCC 9+**, **MSVC 2019+** or **Clang 10+**.
* 📊 Stable ordering: same counts are broken by ascending MAC for reproducible output.
* 🔧 Single executable, zero run‑time dependencies.
* ✅ 1 GoogleTest that verifies the result on a sample log (optional).

---

\## Requirements

| Tool         | Minimum version              |
| ------------ | ---------------------------- |
| CMake        | 3.15                         |
| C++ compiler | GCC 9 / Clang 10 / MSVC 16.8 |
| GoogleTest   | † only for `make test`       |

> **Note** If you prefer C++14, replace generic lambdas with explicit parameter types.

---

\## Building

Clone and configure out‑of‑source:

```bash
# Windows + MSVC
cmake -S . -B build -G "Visual Studio 16 2019" -A x64 -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release

# Linux / macOS
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j$(nproc)
```

> Set `-DCMAKE_CXX_STANDARD=17` if your default toolchain is older.

---

\## Running

```bash
./sniffer <path/to/frames_parser.log>
```

Example (Windows PowerShell):

```powershell
PS> .\sniffer.exe data\frames_parser.log
b8:69:f4:7a:a5:ac 15235
34:1c:f0:d3:40:a2  5812
84:c5:a6:07:38:66   124
ff:ff:ff:ff:ff:ff    98
...
```

---

\## Testing

Unit tests live in **`test/`** and are enabled automatically if GoogleTest is found:

```bash
cmake --build build --target run_tests   # or just `ctest --test-dir build`
```

---

\## Project layout

```
include/   → public headers
src/       → implementation (.cpp)
data/      → sample log for manual run & tests
test/      → GoogleTest suite
CMakeLists.txt
```

---

\## License

MIT – see **LICENSE** for details.

---

Made with ❤ by Taburet

(ps от автора)
ура, я доволен. надеюсь что тест который я написал удоавлетворяет условиям.
