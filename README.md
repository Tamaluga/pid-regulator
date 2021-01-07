# PI-Temperature-Regulator

## Getting Started

### Prerequisites

- [git](https://git-scm.com/downloads)
- [Docker Desktop](https://www.docker.com/get-started)
- [Visual Studio Code](https://code.visualstudio.com/)
  - Add Extension `ms-vscode-remote.remote-containers`

### Installation

- Get the repo:
  ```ssh
  git clone https://github.com/Tamaluga/pi-regulator
  ```
- Start `Docker Desktop`
- Open the project folder in VS Code.  
  Press `ctrl+shift+p` to open the command palette and enter `Remote-Containers: Reopen in Container`.

### Build

- Open the internal terminal in VS Code
  Press `ctrl+shift+p` to open the command palette and enter `Toggle Integrated Terminal`.
- Build the tests
  - Over the control menu of vs code (choose a Kit/GCC first and then hit the build button)
  - With the scripts in the tools folder:
  ```ssh
  ./tools/build_tests.sh
  ```
  - Via the terminal
  ```ssh
  mkdir build
  cd build
  cmake -S ../tests/native -B .
  cmake --build .
  ```