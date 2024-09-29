#!/bin/bash

path=$(pwd)
sudo pacman -Suy

sudo pacman -S --needed git base-devel && git clone https://aur.archlinux.org/yay.git && cd yay && makepkg -si
cd $path

sudo pacman -S make gcc g++ unrar  kitty alacritty unzip tree 

git clone https://github.com/hit9/todo.c/ 
cd todo.c 
make install 

sudo cp ./src/todo /usr/bin/

cd $path

## Everything related to $HOME/Documents/

mv ./vaults/ ~/Documents/
mv ./books ~/Documents/
mv ./ctf ~/ctf
## Configs
mv ./configs/vim.con ~/.vimrc
mv ./configs/tmux.conf ~/.tmux.conf
mv ./configs/kitty/ ~/.config/kitty
mv ./configs/alacritty/ ~/.config/alacritty/

yay -S obsidian flameshot spotify ani-cli


