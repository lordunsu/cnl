# Muller's Recurrence

[source](https://medium.com/@bellmar/is-cobol-holding-you-hostage-with-math-5498c0eb428b)

## Instructions

To build MullersRecurrence in *~/tmp/mr* where CNL is cloned in *~/cnl*:

1. Configure CNL in a subdirectory.

       mkdir -p ~/tmp/mr/cnl
       cd ~/tmp/mr/cnl
       cmake -DCMAKE_INSTALL_PREFIX=~/tmp/mr ~/cnl

2. Build and install CNL.

       cmake --build . -- -j 8 install

3. Configure MullersRecurrence.

       cd ~/tmp/mr
       cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH=~/tmp/mr ~/cnl/example/mullers_recurrence

4. Build and run MullersRecurrence.

       cmake --build .
       ./MullersRecurrence
