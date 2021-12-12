# 2048 Clone 
A semestral project. Simple 2048 clone made in C language utilizing SDL2 library. 
### Features 
- Score counter
- Multiple grid sizes 
- Arrow keys controls

### How to play
- Use arrow keys to move the tiles on the board. All of the tiles then move to that direction.
- Try to merge tiles with same values to join them together.
- The goal is to reach 2048.

#### Installation 
>*Currently only available for Linux.*  
1. Insall SDL2 Libraries (command for Debian and Ubuntu based systems)
2. Clone the repository
3. Navigate into the created directory
4. Compile with Makefile (included)
5. Run the game specifying the size with **-s** argument followed by **rows**x**columns**.   
    - Size can range from 2 to 100 (although the higher the size, the lower the visibility)
```
sudo apt-get install libsdl2-dev libsdl2-ttf-dev
git clone https://github.com/Maro5ak/semestralproject
cd semestralproject
make
./2048 -s 4x4
```  

>*Note, address sanitizer is freaking out with SDL2 libraries. A known issue.*