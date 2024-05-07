#include <iostream>
#include <stdio.h>
#include <conio.h>
#include"music.h"
#define ESC 27
#define ENTER 13
#define UP 80
#define DOWN 72
int main() {
	int index = 0;
	int addMenu = 0;
	int thisMenu = 0;
	SONG* songs = nullptr;
	int countSongs = loadMusic(songs);
	int key = 0;
	char const str = 45;
	char choice = '1';
	while (key != ESC) {
		system("cls");
		std::cout << "\033[33m" << "\033[3m" << "  menu:\n" << "\033[0m";
		if (choice == '1') {
			std::cout << "\033[5m" << "\033[33m"  << str << "\033[0m";
		}
		std::cout << "\033[36m" << "\033[3m"  << "Show all songs" << "\033[0m" << std::endl;
		if (choice == '2') {
			std::cout << "\033[5m" << "\033[33m"  << str << "\033[0m";
		}
		std::cout << "\033[36m" << "\033[3m" <<   "Add a new song" << "\033[0m" << std::endl;
		if (choice == '3') {
			std::cout << "\033[5m" << "\033[33m"  << str << "\033[0m";
		}
		std::cout << "\033[36m" << "\033[3m" << "Delete a song" << "\033[0m" << std::endl;
		if (choice == '4') {
			std::cout << "\033[5m" << "\033[33m"  << str << "\033[0m";
		}
		std::cout << "\033[36m" << "\033[3m" << "Edit a song" << "\033[0m" << std::endl;
		if (choice == '5') {
			std::cout << "\033[5m" << "\033[33m" << str << "\033[0m";
		}
		std::cout << "\033[36m" << "\033[3m" << "Exit" << "\033[0m" << std::endl;
		key = _getch();
		int stop = 0;
		int index = 0;
		addMenu = 0;
		SONG* song = nullptr;
		if (key == 224) {
			key = _getch();
			switch (key) {
			case DOWN:
				if (choice > '1') {
					choice--;
				}
				break;
			case UP:
				if (choice < '5') {
					choice++;
				}
				break;
			}
		}
		else if (key == ENTER) {
			switch (choice) {
			case '1':

				system("cls");
				std::cout << "\033[31m" << "press ESC for exit\n" << "\033[0m" << std::endl;
				index = chooseSong(songs, countSongs);
				if (index == -1) {
					break;
				}
				else {
					showSongsWithText(songs, countSongs, index);
					while (stop != ESC) stop = _getch();
				}
				break;
			case '2':
				addMenu = 0;
				while (addMenu != ESC) {
					system("cls");
					std::cout << "\033[3m" << "\033[31m" << "press ESC for exit\n" << "\033[0m" << std::endl;
					if (thisMenu == 0) std::cout << "\033[5m" << "\033[33m" << str << "\033[0m";
					std::cout << "\033[3m" << "\033[36m" << "input with keyboard" << "\033[0m" << std::endl;
					if (thisMenu == 1) std::cout << "\033[5m" << "\033[33m" << str << "\033[0m";
					std::cout << "\033[3m" << "\033[36m" << "input with the file " << "\033[0m" << std::endl;;
					addMenu = _getch();
					if (addMenu == DOWN) thisMenu--;
					if (addMenu == UP) thisMenu++;
					if (thisMenu < 0) thisMenu = 1;
					if (thisMenu > 1) thisMenu = 0;
					if (addMenu == ENTER) {
						switch (thisMenu) {
						case 0:
							system("cls");
							song = createSong();
							countSongs = addSong(songs, song, countSongs);
							saveMusic(songs, countSongs);
							break;
						case 1:
							system("cls");
							song = addSongInFile();
							countSongs = addSong(songs, song, countSongs);
							saveMusic(songs, countSongs);
							break;
						}
					}
				}
				break;
			case '3':
				while (addMenu != ESC) {
					system("cls");
					std::cout << "\033[3m" << "\033[31m" << "press ESC for exit\n" << "\033[0m" << std::endl;
					for (int i = 0; i < countSongs; i++) {
						if (i == index) {
							std::cout << "\033[3m" << "\033[33m" << songs[i].title << "\033[0m" << std::endl;
						}
						else {
							std::cout << "\033[3m" << "\033[36m" << songs[i].title << "\033[0m" << std::endl;
						}
					}
					addMenu = _getch();
					if (addMenu == UP) index++;
					else if (addMenu == DOWN) index--;
					if (index > countSongs) index = 0;
					if (index < 0)  index = countSongs - 1;
					if (addMenu == ENTER) {
						countSongs = deleteSong(songs, index, countSongs);
						saveMusic(songs, countSongs);
					}
				}
				break;
			case '4':
				int index = chooseSong(songs, countSongs);
				if (index != -1) {
					editSong(songs, countSongs, index);
					saveMusic(songs, countSongs);
				}
				else {
					break;
				}
				break;
			}
		}
	}
	return 0;
}