# kursach_2: programm for text analysis and visualization

A Qt-based app

##Features
- Text input and file-based word frequency analysis
- Line graph visualization (top 10 words with the most frequency)
- Interactive graph (scroll, zoom)
- Export results to '.txt' with Git commits
- Dark theme via 'MaterialDark.qss'
- Multithreaded analysis

## Requirements
- Qt 6.9.0
- CMake 3.16+
- MSVC 2022
- Git

## Build Instructions
`` `mkdir build` ``
cd build
cmake ..
cmake --build .
