# DBLP Co-author Graph Analysis

## Requirements
- pugixml library.
- gcc compiler.
- wget.

## Build program
    ```c++
    make
    ```
Be sure the local variables in the 'makefile' have coherence in your system.
## Program full run
    ```c++
    ./run_analysis
    ```
The results files will be created in the '/results' directory.
For each run you do, the csv results will be created in the 'article' and 'inproceedings' directories, with the actual date as name.
## Data
The DBLP dataset is too big to store it in a repository.

The run script will find for it in the project root. If it doesn't find it, it will download it with wget, and partition it in 8 different xml files.

## Tree visualization
tree -I 'article|inproceedings'

## Runtime
- 4 min aprox in macbook air M1 8GB.

## WIP
- Make the C++ compiled executable independent from the shell script.
- Make the C++ compiled executable independent from the project.
