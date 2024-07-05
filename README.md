**See a short introduction to my numerical setup [here](https://youtu.be/ujMiZSAKlsg)**

**Note:** The code has only been tested on Windows and will likely not work without modifications on iOS.

**File structure:**
- `Example.ipynb`: Main execution file (Jupyter Notebook) from which the model is solved and simulated. Also contains plots.
- `Example.py`: Main Python module. This file defines the model class, initializes parameters (in `par` struct), allocates memory to store the solution in (`sol` struct), and allocates memory to store the simulated paths in (`sim` struct). This builds on the `EconModel` class.
- `cppfuncs`: Folder containing all c++ files. The main file linking to Python is the `cpp_link_file.cpp`. The `solve.cpp` files contains the solution algorithm and `simulate.cpp` contains the simulation module.
- `cpp_link_file.dll`: The executable file, constructed when compiling the c++ code in `Example.ipynb`. This is all done automatically once you have followed the installation guide below.


**Installation guide:**
1. Download [Anaconda](https://www.anaconda.com/download) using default options
2. Add the location of the Anaconda-installation to PATH in "environment variables".
3. Download [Git](https://git-scm.com/download/win)
4. Download [Visual Studio Code](https://code.visualstudio.com/download)
5. in VS-code, install the "Python" extension. 
6. Download [Visual Studio Community compiler](https://visualstudio.microsoft.com/vs/features/cplusplus/). Remember to add C/C++ features for installation.
7. Clone this repository from GitHub by i) opening the Anaconda Prompt, ii) navigating to the location on disk where you want the files cloned to, iii) write `git clone https://github.com/ThomasHJorgensen/NumericalSetup.git` and hit enter.
8. In Anaconda Prompt install required Python packages by typing `pip install econmodel consav`

To learn more about how this code uses OpenMP and NLopt to parallelize and solve numerical optimization problems, respectively, see e.g. [EconModelNotebooks](https://github.com/NumEconCopenhagen/EconModelNotebooks).
