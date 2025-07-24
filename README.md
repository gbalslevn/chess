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

GUI depends on the multimedia library [SFML](https://www.sfml-dev.org/). Which must be linked accordingly. I recommend configuring "CMakeLists.txt". 

# Build and run 
`make && ./chess` 
## Build natively
Compile using `g++ -o chess main.cpp` + link to SFML  and then run it with `./chess`. 
## Build with cmake
Changes to build is configured in CMakeLists.txt. To apply changes do `cmake ./build`



