# Life Battery Clock - Ticking Lifeclock

A multilingual desktop application that visualizes your remaining life time as a battery percentage, helping you understand how much time you have left based on different life expectancy scenarios.

I've built this program on a random day in my unemployed period. Thought about managing time and how much time is remaining. By visibly seeing the remaining days in our life, probably we can plan and prospect what can be done within certain time segment. I'm opened to collaboration with other persons whoever interested in this program. I'm very lazy person so there a pile of unshared programs, I decided to gradually share the programs. Some people likely had similar thought like this program, but some of others might have not thought in this way. Somehow this program may be quite silly, but I hope others to have awareness of their time as well as others'. From Korea, 2025-11-29, in the middle of sunset.

![Life Battery Clock](https://img.shields.io/badge/version-1.0-blue)
![License](https://img.shields.io/badge/license-MIT-green)
![Platform](https://img.shields.io/badge/platform-Windows-lightgrey)

## Features

- ⏱️ **Real-time countdown** showing remaining time (days, hours, minutes, seconds)
- 🕐 **Visual clock grid** with 8 circular clocks showing remaining life percentage (water-filling effect)
- 🌍 **13 languages supported**: Korean, English, German, Japanese, Simplified Chinese, Traditional Chinese, Russian, French, Italian, Portuguese, Spanish, Ukrainian, Dutch
- 📊 **Multiple life expectancy scenarios**: Calculate for 30, 40, 50, 60, 70, 80, 90, or custom years
- 💡 **Activity suggestions**: Shows what you could accomplish with remaining time (books, movies, trips, languages, skills)
- 🎨 **Clean, intuitive interface** with separate input fields for birth date (Year, Month, Day, Time)
- 🔍 **Font scaling** support (Ctrl + Mouse Wheel) for both C++ and Python versions

## Screenshots

The application displays:
- Current time
- Birth date input (separate fields for Year, Month, Day, Time)
- Life expectancy inputs for multiple scenarios
- Remaining time countdown for each scenario
- Visual clock grid: 8 circular clocks arranged in a row, with water-filling effect showing remaining life percentage
- Battery percentage with 2 decimal places
- Activity suggestions based on remaining time

## Requirements

### Python Version
- Python 3.6 or higher
- tkinter (usually included with Python)

### C++ Version
- Visual Studio 2019 or 2022
- Qt 6.9.0 or later with MSVC 2022 64-bit compiler
- Qt Visual Studio Tools extension

## Installation

### Python Version (Recommended for Quick Start)

1. **Clone the repository**:
   ```bash
   git clone https://github.com/yourusername/TickingLifeClock.git
   cd TickingLifeClock
   ```

2. **Run the application**:
   ```bash
   python Python/LCT-multilingual.py
   ```

3. **Or use the pre-built executable**:
   - Navigate to `Python/dist/`
   - Run `LCT-multilingual.exe`

### C++ Version

1. **Install Qt**:
   - Download Qt from https://www.qt.io/download-qt-installer
   - Install Qt 6.9.0 (or later) with MSVC 2022 64-bit compiler
   - Install Qt Visual Studio Tools extension in Visual Studio

2. **Open the project**:
   - Open `C++/TickingLifeclock.sln` in Visual Studio
   - Configure Qt in Project Properties → Qt Project Settings
   - Build the solution (F7)

3. **Run**:
   - The executable will be in `C++/x64/Release/TickingLifeclock.exe`

## Usage

1. **Select your language** from the dropdown menu
2. **Enter your birth date**:
   - Year: Your birth year (e.g., 1995)
   - Month: Birth month (e.g., 11)
   - Day: Birth day (e.g., 5)
   - Time: Birth time in HH:MM format (e.g., 13:27), or leave empty for 00:00
3. **Adjust life expectancy values** for different scenarios (default: 30, 40, 50, 60, 70, 80, 90, 1000 years)
4. **View results**:
   - Remaining time countdown
   - Battery percentage
   - Visual clock grid (8 clocks with water-filling effect)
   - Activity suggestions

## Building from Source

### Python

The Python version uses PyInstaller for creating executables:

```bash
cd Python
pyinstaller LCT-multilingual.spec
```

The executable will be in `dist/LCT-multilingual.exe`

### C++

1. Open `C++/TickingLifeclock.sln` in Visual Studio
2. Set configuration to **Release** and platform to **x64**
3. Build → Rebuild Solution
4. Executable: `C++/x64/Release/TickingLifeclock.exe`

## Creating an Installer

### WiX Toolset (MSI Installer)

1. **Build Release version** in Visual Studio:
   - Open `C++/TickingLifeclock.sln` in Visual Studio
   - Set configuration to **Release** and platform to **x64**
   - Build → Rebuild Solution
   - Ensure `C++/x64/Release/TickingLifeclock.exe` is up to date

2. **Collect Qt dependencies**:
   ```bash
   cd C:\Qt\6.9.0\msvc2022_64\bin
   windeployqt.exe --release "C:\path\to\TickingLifeclock.exe"
   ```
   This will copy all required Qt DLLs and plugins to the Release folder.

3. **Build MSI installer**:
   ```bash
   cd C++/TickingLifeclock/installer
   wix build -arch x64 LifeBatteryClock.wxs
   ```
   The MSI file will be generated in the `installer` folder.

**Important**: 
- Always rebuild the Release .exe in Visual Studio before creating the MSI installer to ensure the MSI contains the latest version of your application.
- The `-arch x64` flag ensures the MSI is built for 64-bit architecture and installs to `C:\Program Files\Life Battery Clock` (not `C:\Program Files (x86)`).
- The WiX file references `..\..\x64\Release\TickingLifeclock.exe` relative to the `installer` folder, which resolves to `C++/x64/Release/TickingLifeclock.exe`.

### Other Installer Options

- **Inno Setup**: Easy-to-use installer - https://jrsoftware.org/isdl.php
- **Qt Installer Framework**: Qt-specific installer (included with Qt)
- **NSIS**: Another popular option - https://nsis.sourceforge.io/

### Required Files for Installer

After using `windeployqt`, your installer should include:
- `TickingLifeclock.exe`
- Qt DLLs: `Qt6Core.dll`, `Qt6Gui.dll`, `Qt6Widgets.dll`, `Qt6Network.dll`, `Qt6Svg.dll`
- Platform plugin: `platforms/qwindows.dll`
- Image format plugins: `imageformats/` folder
- Icon engines: `iconengines/` folder
- Visual C++ Redistributable (bundle or check for existing installation)

### For Python Version

The Python version can be packaged using PyInstaller (already configured):
```bash
cd Python
pyinstaller LCT-multilingual.spec
```

## Project Structure

```
TickingLifeClock/
├── README.md                # Documentation (this file)
├── .gitignore               # Git ignore rules
├── Python/                  # Python implementation
│   ├── LCT-multilingual.py  # Main Python application
│   ├── life-clock-ticking.py # Original version
│   ├── LCT-multilingual.spec # PyInstaller spec
│   └── dist/                # Built executables (gitignored)
└── C++/                     # C++/Qt implementation
    ├── TickingLifeclock.sln # Visual Studio solution
    └── TickingLifeclock/    # Source files
        ├── LifeClockWindow.h
        ├── LifeClockWindow.cpp
        ├── main.cpp
        └── installer/
            └── LifeBatteryClock.wxs  # WiX installer source
```

## Supported Languages

- 한국어 (Korean)
- English
- Deutsch (German)
- 日本語 (Japanese)
- 简体中文 (Simplified Chinese)
- 繁體中文 (Traditional Chinese)
- Русский (Russian)
- Français (French)
- Italiano (Italian)
- Português (Portuguese)
- Español (Spanish)
- Українська (Ukrainian)
- Nederlands (Dutch)

## Features in Detail

### Visual Clock Grid
- 8 circular clocks arranged in a single row
- Each clock can show 0-100% fill (fractional filling)
- Water-filling effect with gradient and wave animation
- Clock design includes hour markers (12, 3, 6, 9 o'clock) and hour hand pointing to 12
- Shows percentage with 2 decimal places
- At least one clock partially filled if percentage > 0%

### Activity Suggestions
Based on remaining time, the app suggests:
- **Books**: ~X books (assuming 0.75 books/day)
- **Movies**: ~X movies (assuming 4 movies/day)
- **Trips**: ~X week-long trips (7 days per trip)
- **Languages**: ~X new languages (180 days per language)
- **Skills**: ~X new skills (90 days per skill)

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Disclaimer

This application is for informational and motivational purposes only. Life expectancy calculations are estimates and cannot account for accidents, diseases, or other unforeseen circumstances. The actual lifespan may vary significantly.

## Acknowledgments

- Built with Qt Framework (C++ version)
- Built with Tkinter (Python version)
- Inspired by the concept of visualizing life as a battery

## Version History

- **v1.0** (2025-11-29)
  - Initial release
  - 13 languages supported (Korean, English, German, Japanese, Simplified Chinese, Traditional Chinese, Russian, French, Italian, Portuguese, Spanish, Ukrainian, Dutch)
  - Separate birth date input fields (Year, Month, Day, Time)
  - Visual clock grid with 8 circular clocks and water-filling effect
  - Activity suggestions feature
  - Font scaling support (Ctrl + Mouse Wheel) for both versions
  - Both Python and C++ implementations

