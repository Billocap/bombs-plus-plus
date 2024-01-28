# Bombs++

Bombs++ is an implementation of Minesweeper in C++. It runs on the terminal window and can only be played with the keyboard.

## Previews

![preview menu](/doc/print-menu.png)
![preview in game](/doc/preview-game.png)
![preview end game](/doc/print-endgame.png)

## Install

This project only works on Linux (I mean Windows already comes with Minesweeper installed).

But if you are a Windows user and still wants to play this game you can install it on WSL.

### Dependencies

There are some dependencies you need in other to install this game. Those dependencies are:

- g++ - C++ Compiler.
- cmake - To simplify the compilation process.
- ncurses - Graphical library this project relies on.

If you don't have any of those dependencies you can install them with the command:

```sh
sudo apt install build-essential libssl-dev cmake libncurses5-dev libncursesw5-dev -y
```
### Installation

After all of the dependencies are sorted just run the command:

```sh
make
# or
make prod
```
After that the compiled project will be in `./bin/bomb++`.

### Alias

If you want you can copy the binary to `/usr/bin` so the game can be run from any folder or alias the project binary.
