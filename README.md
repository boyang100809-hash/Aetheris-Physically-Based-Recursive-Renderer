# Aetheris-Physically-Based-Recursive-Renderer
![License](https://img.shields.io/badge/license-Anti--996-red.svg)
![Language](https://img.shields.io/badge/language-C11-00599C.svg)
![Platform](https://img.shields.io/badge/platform-Windows-lightgrey.svg)

**LuminaC** is a lightweight, interactive ray tracing engine written in pure C11. This repository is pre-configured for "Download & Run" convenience.

---

## 🚀 Quick Start (No Compilation Required)

For Windows users who want to experience the engine immediately:

1.  **Download** the repository as a ZIP file and extract it.
2.  **Run** `raytracer.exe` directly from the root folder.
    * *Note: Ensure `SDL2.dll` remains in the same directory as the executable.*

---

## 📸 Interactive Viewport
The engine renders complex reflections, shadows, and global illumination in real-time. 

*(Tip: Upload your screenshot to GitHub and replace this line with the image link!)*

---

## ✨ Key Features
* **Real-Time Navigation**: Use `WASD` and Mouse to fly through the ray-traced scene.
* **Recursive Path Tracing**: Multi-bounce reflections for metallic/dielectric materials.
* **Live Telemetry**: Real-time FPS and coordinate display in the window title.
* **Portable**: Zero-dependency runtime (provided via SDL2.dll).

---

## 🎮 Controls

| Key | Action |
| :--- | :--- |
| **W / A / S / D** | Move Forward / Left / Backward / Right |
| **Mouse** | Look Around (Yaw / Pitch) |
| **Space / Ctrl** | Fly Up / Down |
| **ESC** | Exit Application |

---

## 🛠️ Build from Source (For Developers)
If you wish to modify the code, you can recompile using the provided Makefile:
```bash
make clean
make
