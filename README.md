# RequestTest
### GCC
> For a more detailed installation and runing tutorial, click [here](https://github.com/KRMisha/Makefile)
- Linux:
    - Debian/Ubuntu: `sudo apt install build-essential`
    - Fedora: `sudo dnf install gcc-c++ make`
    - Arch: `sudo pacman -S base-devel`
- macOS:
    1. Run the following command: `xcode-select --install`
    2. In the window which pops up, click "Install" and follow the instructions.
- Windows:
    1. Install Mingw-w64 via [SourceForge](https://sourceforge.net/projects/mingw-w64/).
    2. Add the path to Mingw-64's `bin` directory to Windows's system `PATH` environment variable.
        > You will need to use `mingw32-make` instead of `make` each time the `make` command is used in this README.
    3. Install Git Bash by installing [Git for Windows](https://git-scm.com/downloads).
        > You will need to use **Git Bash** over PowerShell or cmd.exe each time the `make` command is used in this README.

### Building
```
make
```

### Running
```
./bin/<platform>/debug/program -b <number of bins> -u <URL> -n <number of requests> -u <URL> -n <number of requests>
```
`<platform>` Current Operating system, should be either `linux`, `macos`, `windows32`, or `windows64`
`-b <number of bins>` The max number of bins to use in the histogram, default is 10
`-u <URL>` The URL to request, default is url1
`-n <number of requests>` The number of requests to make to previous URL, Immediately after `-u <URL>`, default is 100.
- Exmaple on MacOS
```
./bin/macos/debug/program -b 15 -u url1  -n 200 -u url2 -n 200
```
- Exmaple on Windows-64
```
./bin/windows64/debug/program.exe -b 15 -u url1  -n 200 -u url2 -n 200
```




