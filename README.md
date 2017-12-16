# QtSearcher
Qt Gui for the libimse, a high performance library for searching bolides in the atmospheres of Jupiter and Saturn.
The source code of the library is availble at https://github.com/SSIP/ImpactSearcher. We're also planning
to create a command line client to improve the performance and not have Qt dependencies.

# Installation
We do not yet provide installation packages as the program is not 100% finished yet. Download links
will be available on https://ssip.info.

# How to compile
To compile the source code you need the Qt development files, CMake and a C++ compiler.
You also need the libimse with the development headers. We usually use the GNU C++ compiler.
The following steps describe the full compilation procedure on Linux:
1. `> git clone https://github.com/SSIP/ImpactSeracher.git`
2. `> cd ImpactSearcher`
3. `> cmake src`
4. `> make`
5. `> make install`
6. `> cd ..`
7. `> git clone https://github.com/SSIP/QtSearcher.git`
8. `> cd QtSearcher`
9. `> cmake src`
10. `> make`
Now you will have a `QtSearcher` binary in the project folder that is ready to run.

# Contributing
We welcome contributions to this project. Please be aware that you must MIT license your contributions.
If you want to contribute, create a pull request to this repository. Usually we will provide feedback within a
few days.