# DBLP Co-author Graph Analysis

## Build program
    ```c++
    make
    ```
## Program full run
    ```c++
    ./run_analysis
    ```
## Data
The DBLP dataset is too big to store it in a repository.

The run script will find for it in the project root. If it doesn't find it, it will download it with wget, and partition it in 8 different xml files.

The partitions are not equally sized as I would wanted, but it does the job of dramatically speeding up the runtime.

## Tree visualization
tree -I 'article|inproceedings'

## Requirements
- pugixml library.

## Runtime
- 8 min aprox in macbook air M1 8GB.

## WIP
- Make the C++ compiled executable independent from the shell script.
- Make the C++ compiled executable independent from the project.
