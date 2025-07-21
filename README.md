# Chess in the terminal
Now you can finally play chess in the terminal!

This projects seeks to investiagte the wonders of [chess programming](https://www.chessprogramming.org/Main_Page). 

### Game modes
You can either play locally against a friend or against the computer in 5 different difficulties. Inspired from [this article](https://www.freecodecamp.org/news/simple-chess-ai-step-by-step-1d55a9266977).
#### 1. Baby mode 
Machine takes random choice each time from all possible moves

#### 2. Easy mode 
Machine takes random choice based on the value of the piece.
Improvement being it takes a piece if it can. 

#### 3. Normal
Machine uses search tree with Minimax. A recursive search with a given depth finds the best possible move. 

#### 4. Practised 
Machine uses alpha-beta pruning to disregard some branches of the tree and search with a greater depth, while using the same resources. Making minimax algo faster

#### 5. IMPOSSIBLE
Machine adds the factor of piece placement. Implemented using piece square tables.       


## Build natively
Compile using `g++ -o chess main.cpp` and then run it with `./chess`

## Build with cmake
Build with `cmake --build .`

Changes to build is configured in CMakeLists.txt. To apply changes do `cmake ./build`

You can also combine the command to a single command `cmake ./build && cmake --build .`
To also run it you can then do `cmake ./build && cmake --build . && ./chess`
If no changes has been made to CMakeLists.txt simply run the program with `cmake --build . && ./chess`



