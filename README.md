# kursach_2: programm for text analysis and visualization

A Qt-based app

## Features
- Text input and file-based word frequency analysis
- Line graph visualization (top 10 words with the most frequency)
- Interactive graph (scroll, zoom)
- Save analysis results to .txt or .csv formats, including comprehensive statistics
- Dark theme via 'MaterialDark.qss'
- Multithreaded analysis
- Caching: Stores analysis results to speed up repeated operations with the same input

## Requirements
- Qt: Version 6.9.0
- CMake: Version 3.16 or higher
- Compiler: MSVC 2022 (Windows) or GCC/Clang (Linux/macOS)
- Git

## Cloning the Repository
1. Open a terminal.
2. Navigate to your projects directory:
`cd ~/Projects  # Linux/macOS`
`cd C:\Projects  # Windows`
3. Clone the repository:
`git clone https://github.com/itisjustmeeee/kursachv3.0.git`
4. Enter the project directory:
`cd kursachv3.0`

## Building the Project
1. Create a build directory:
`mkdir build`
2. Navigate to the build directory:
`cd build`
3. Configure the project with CMake:
`cmake ..`
4. Build the project:
`cmake --build .`
