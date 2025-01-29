# MVerb VST Plugin


## Acknowledgments

- **Martin Eastwood**: Original creator of MVerb.
- Open-source contributors who have improved the plugin over the years.

---

## Overview

MVerb is a high-quality reverb plugin built for digital audio workstations (DAWs) that support the VST standard. It offers precise control over parameters such as size, damping, density, and mix, providing a flexible and efficient reverb solution for audio production.

This repository contains the source code and documentation for the MVerb plugin, including recent updates to enhance real-time parameter adjustments.

---

## Features

- **Reverb Size Control**: Smooth, real-time adjustments without introducing artifacts.
- **Customizable Presets**: Five built-in presets, with the ability to create and save custom ones.
- **Efficient DSP Engine**: Minimal CPU usage with high-quality sound.
- **Multi-Parameter Control**: Modify damping, density, decay, pre-delay, mix, and more.

---

## Recent Updates

1. **Smooth Transitions for ****\`\`**** Parameter**:

   - Gradual interpolation implemented for real-time adjustments.
   - Eliminated audible artifacts by avoiding buffer resets.

2. **Enhanced Buffer Management**:

   - Delay lines and filters now dynamically adjust without being cleared.

3. **Refactored Parameter Handling**:

   - Improved `setParameter` and `getParameter` methods for seamless interaction with DAWs.

---

## Repository Structure

```
├── src/
│   ├── MVerb.h          # Reverb DSP engine header
│   ├── VstPlugin.cpp    # Main plugin implementation
│   ├── VstPlugin.h      # Plugin interface definition
├── presets/             # Default preset configurations
├── README.md            # Project documentation
└── LICENSE              # GNU General Public License
```

---

## Installation

1. Clone this repository:

   ```bash
   git clone https://github.com/your-username/mverb-vst-plugin.git
   ```

2. Build the plugin using your preferred VST-compatible build system (e.g., Visual Studio, Xcode, or Makefile).

3. Copy the compiled plugin file (e.g., `.dll`, `.vst3`, or `.so`) to your DAW's plugin folder.

4. Rescan plugins in your DAW to load MVerb.

---

## Usage

### Parameters

| Parameter       | Description                              |
| --------------- | ---------------------------------------- |
| **Size**        | Adjusts the perceived room size.         |
| **DampingFreq** | Controls high-frequency attenuation.     |
| **Density**     | Modifies the density of the reflections. |
| **PreDelay**    | Introduces a delay before the reverb.    |
| **Decay**       | Sets the reverb tail duration.           |
| **Mix**         | Balances the wet/dry signal.             |
| **Gain**        | Controls the output gain.                |
| **EarlyMix**    | Balances early and late reflections.     |

### Presets

Five built-in presets are available: Subtle, Stadium, Cupboard, Dark, and Halves. Users can load, modify, and save custom presets as needed.

---

## Contributing

Contributions are welcome! To contribute:

1. Fork this repository.
2. Create a feature branch:
   ```bash
   git checkout -b feature-name
   ```
3. Commit your changes:
   ```bash
   git commit -m "Description of changes."
   ```
4. Push the branch:
   ```bash
   git push origin feature-name
   ```
5. Open a pull request.

---

## License

This project is licensed under the GNU General Public License v3. See the [LICENSE](LICENSE) file for details.

---




