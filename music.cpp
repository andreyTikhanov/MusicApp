#include<iostream>
#include <iomanip>
#include <conio.h>
#include"music.h"
#define ESC 27
#define ENTER 13
#define UP 80
#define DOWN 72
SONG* createSong() {
	SONG* newSong = new SONG;
	char* temp = new char[255];
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cout << "\033[36m" << "\033[3m" << "input title the song: " << "\033[0m";
	std::cin.getline(temp, 255);
	newSong->setTittle(temp);
	std::cout << "\033[36m" << "\033[3m" << "input author the song: " << "\033[0m";
	std::cin.getline(temp, 255);
	newSong->setAuthor(temp);
	std::cout << "\033[36m" << "\033[3m" << "input date release the song: " << "\033[0m";
	std::cin >> newSong->dateRelease;
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cout << "\033[36m" << "\033[3m" << "input text the song: " << "\033[0m";
	char** tempS = new char* [50];
	for (int i = 0; i < 50; i++) {
		std::cin.getline(temp, 255);
		if (strlen(temp) != 0) {
			tempS[i] = new char[strlen(temp) + 1];
			strcpy_s(tempS[i], strlen(temp) + 1, temp);
		}
		else {
			newSong->sizeText = i;

			break;
		}
	}
	newSong->setText(tempS, newSong->sizeText);
	return newSong;
}
void SONG::setTittle(const char* title) {		
	if (SONG::title != nullptr) {			
		delete[]SONG::title;					
	}
	SONG::title = new char[strlen(title) + 1];	
	strcpy_s(SONG::title, strlen(title) + 1, title);	
}
void SONG::setAuthor(const char* author) {
	if (SONG::author != nullptr) {
		delete[]SONG::author;
	}
	SONG::author = new char[strlen(author) + 1];
	strcpy_s(SONG::author, strlen(author) + 1, author);
}
void SONG::setText(char** text,int sizeText) {
	if (SONG::text != nullptr) {
		for (int i = 0; i < sizeText; i++) {
			delete[] SONG::text[i];
		}
		delete[] SONG::text;
	}
	char* temp = new char[255];
	SONG::text = new char*[sizeText];
	for (int i = 0; i < sizeText; i++) {
		SONG::text[i] = new char[255];
		SONG::text[i] = text[i];
	}
}
void SONG::setStroka(const char* temp, int index) {
	if (SONG::text[index] != nullptr) {
		delete[]SONG::text[index];
		SONG::text[index] = new char[strlen(temp) + 1];
		strcpy_s(SONG::text[index], strlen(temp) + 1, temp);
	}
}
void saveMusic(SONG* songs, int countSong) {
	FILE* out;
	fopen_s(&out, path2, "w");
	if (out != NULL) {
		fwrite(&countSong, sizeof(int), 1, out);
		for (int i = 0; i < countSong; i++) {
			fwrite(&songs[i].dateRelease, sizeof(int), 1, out);
			fwrite(&songs[i].sizeText, sizeof(int), 1, out);
		}
		fclose(out);
	}
	FILE* outS;
	fopen_s(&outS, path, "w");
	if (outS != NULL) {
		for (int i = 0; i < countSong; i++) {
			fputc(strlen(songs[i].title), outS);
			fputs(songs[i].title, outS);
			fputc(strlen(songs[i].author), outS);
			fputs(songs[i].author, outS);
			for (int j = 0; j < songs[i].sizeText; j++) {
				fputc(strlen(songs[i].text[j]), outS);
				fputs(songs[i].text[j], outS);
			}
		}
		fclose(outS);
	}
}
void showSongs(SONG* songs, int countSongs) {
	for (int i = 0; i < countSongs; i++) {
	    std::cout << "\033[33m" << "\033[3m" << "Title: " << "\033[0m";
		std::cout << "\033[4m" << "\033[3m"<< songs[i].title << ", " << "\033[0m";
		std::cout << "\033[33m" << "Author: " << "\033[0m";
		std::cout << "\033[3m" << songs[i].author << "," << "\033[0m";
		std::cout << "\033[3m"<< "\033[33m" << "Date relise : " << "\033[0m";
		std::cout <<"\033[38m" << "\033[3m" << songs[i].dateRelease << "\033[0m" << std::endl;
	}
}
void showSongsWithText(SONG* songs, int countSongs, int index) {
	system("cls");
	char upMenu[33] = { 218,196,196,196,196,196,196,196,196,196,
	196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 
	196, 196, 196, 196, 196, 196, 196, 196, 196, 194};
	char downMenu[33] = { 192,196 ,196 ,196 ,196 ,196 ,196 ,196 ,196 ,196 ,196 ,196 ,196 ,196
	,196 ,196 ,196 ,196 ,196 ,196 ,196 ,196 ,196 ,196 ,196 ,196 ,196 ,196 ,196 ,196
	,196 ,196,217 };
	std::cout << "\033[3m" << "\033[31m" << "press ESC for exit\n" << "\033[0m";
	for (int i = 0; i < 33; i++) {
		std::cout << upMenu[i];
	}
	for (int i = 0; i <=85; i++) {
		if (i == 85) {
			std::cout << char(191);
		}
		else {
			std::cout << char(196);
		}
	}
	std::cout << std::endl;
	std::cout << char(179)<< "\033[33m" << "\033[3m" << "Title: " << "\033[0m";
	std::cout << "\033[35m" << "\033[3m" << songs[index].title << "\033[0m" <<std::setw(25- strlen(songs[index].title))  << char(179)<<  std::endl;
	std::cout << char(179)<< "\033[3m" << "\033[33m" << "Author: " << "\033[0m";
	std::cout << "\033[3m" << "\033[35m" << songs[index].author << "\033[0m"<<std::setw(24 - strlen(songs[index].author)) << char(179)<<std::endl;
	std::cout << char(179)<< "\033[3m" << "\033[33m" << "Date relise : " << "\033[0m";
	std::cout << "\033[35m" << "\033[3m" << songs[index].dateRelease << "\033[34m" << "\033[0m"  << std::setw(33 - 19) <<char(179) <<  std::endl;
	for (int i = 0; i < 33; i++) {
		std::cout << downMenu[i];
	}
	for (int i = 0; i < songs[index].sizeText; i++) {
		if (i == 0) {
			clearLine(3);
			std::cout << char(179) << "\033[33m" << "\033[3m" << "Title: " << "\033[0m";
			std::cout << "\033[35m" << "\033[3m" << songs[index].title << "\033[0m" << std::setw(25 - strlen(songs[index].title)) << char(179);
			std::cout <<"\033[3m" << songs[index].text[i] << std::setw(89 - strlen(songs[index].text[i])) << "\033[0m" << char(179) << std::endl;
		}
		if (i == 1) {
			clearLine(4);
			std::cout << char(179) << "\033[3m" << "\033[33m" << "Author: " << "\033[0m";
			std::cout << "\033[3m" << "\033[35m" << songs[index].author << "\033[0m" << std::setw(24 - strlen(songs[index].author)) << char(179);
			std::cout << "\033[3m" << songs[index].text[i] << std::setw(89 - strlen(songs[index].text[i])) << "\033[0m" << char(179) << std::endl;
		}
		if (i == 2) {
			clearLine(5);
			std::cout << char(179) << "\033[3m" << "\033[33m" << "Date relise : " << "\033[0m";
			std::cout << "\033[35m" << "\033[3m" << songs[index].dateRelease << "\033[34m" << "\033[0m" << std::setw(33 - 19) << char(179);
			std::cout << "\033[3m" << songs[index].text[i] << std::setw(89 - strlen(songs[index].text[i])) << "\033[0m" << char(179) << std::endl;
		}
		if (i == 3) {
			clearLine(6);
			for (int j = 0; j <= 32; j++) {
				if (j == 32) {
					std::cout << char(180);
				}
				else {
					std::cout << downMenu[j];
				}
			}
			std::cout << songs[index].text[i] << std::setw(89 - strlen(songs[index].text[i])) << char(179) << std::endl;
		}
		if (i > 3) {
			std::cout << std::setw(33)<<char(179) <<  "\033[3m"<< songs[index].text[i] << std::setw(89 -  strlen(songs[index].text[i])) << "\033[0m" << char(179) << std::endl;
		}
		if (i == songs[index].sizeText - 1) {
			for (int j = 0; j <= 86; j++) {
				if (j == 0) std::cout << std::setw(33) << char(192);
				else if (j > 0 && j < 86) std::cout << char(196);
				else if (j == 86) std::cout << char(217);
			}
		}
	}
}
void editSong(SONG* songs, int countSongs, int index) {
	char* temp = new char[255];
	int key = 0;
	int num = 0;
	while (key != ESC) {
		system("cls");
		if (num == 0) std::cout << "\033[32m";
		std::cout << "title:"<<"\033[0m";
		std::cout << songs[index].title << "\n";
		if (num == 1) std::cout << "\033[32m";
		std::cout << "author:  "<<"\033[0m";
		std::cout << songs[index].author << "\n";
		if (num == 2) std::cout << "\033[32m";
		std::cout << "date release: "<<"\033[0m";
		std::cout << songs[index].dateRelease << "\n";
		if (num == 3) std::cout << "\033[32m";
		std::cout << "text: "<<"\033[0m";
		key = _getch();
		key == DOWN && num > 0 ? num-- : key == UP && num < 3 ? num++ : num;
		if (key == ENTER) {
			switch (num) {
			case 0:
				clearLine(1);
				std::cout << "title:" ;
				std::cin.getline(temp, 255);
				songs[index].setTittle(temp);
				break;
			case 1:
				clearLine(2);
				std::cout << "author:";
				std::cin.getline(temp, 255);
				songs[index].setAuthor(temp);
				break;
			case 2:
				clearLine(3);
				std::cout << "date release:";
				std::cin >> songs[index].dateRelease;
				break;
			case 3:
				int num2 = 0;
				int key2 = 0;
				while (key2 != ESC) {
					system("cls");
					for (int i = 0; i < songs[index].sizeText; i++) {
						if (num2 == i) {
							std::cout << "\033[35m";
						}
						std::cout << songs[index].text[i]<<"\033[0m";
						std::cout << "\n";
					}
					key2 = _getch();
					key2 == DOWN && num2 > 0 ? num2-- : key2 == UP && num2 < songs[index].sizeText-1 ? num2++ : num2;
					if (key2 == ENTER) {
						if(num2==0) clearLine(num2);
						else clearLine(num2+1);
						std::cin.getline(temp, 255);
						songs[index].setStroka(temp, num2);
						key2 = 0;
					}
				}
				break;
			}
		}
	}
}
void clearLine(int line) {
	std::cout << "\033[" << line << ";1H";
	std::cout << std::string(120, ' ');
	std::cout << "\r";
	std::cout << "\033[0m";
}
int addSong(SONG*& songs, SONG* song, int countSongs) {
	SONG* newSong = new SONG[countSongs + 1];
	for (int i = 0; i < countSongs; i++) {
		newSong[i] = songs[i];
	}
	newSong[countSongs] = *song;
	delete[]songs;
	songs = newSong;
	countSongs++;
	return countSongs;
}
int loadMusic(SONG*& songs) {
	FILE* in;
	fopen_s(&in, path2, "r");
	int countSong = 0;
	if (in != NULL) {
		fread(&countSong, sizeof(int), 1, in);
		if (songs == nullptr) {
			songs = new SONG[countSong];
		}
		for (int i = 0; i < countSong; i++) {
			fread(&songs[i].dateRelease, sizeof(int), 1, in);
			fread(&songs[i].sizeText, sizeof(int), 1, in);
		}
		fclose(in);
	}
	fopen_s(&in, path, "r");
	if (in != NULL) {
		char* temp = new char[255];
		for (int i = 0; i < countSong; i++) {
			int sizeTitle = fgetc(in);
			fgets(temp, sizeTitle + 1, in);
			songs[i].setTittle(temp);

			int sizeAuthor = fgetc(in);
			fgets(temp, sizeAuthor + 1, in);
			songs[i].setAuthor(temp);
			char** tempSong = new char* [50];
			for (int j = 0; j < songs[i].sizeText; j++) {
				int sizeText = fgetc(in);
				tempSong[j] = new char[sizeText + 1];
				fgets(tempSong[j], sizeText + 1, in);
			}
			songs[i].setText(tempSong, songs[i].sizeText);
		}
		delete[] temp;
		fclose(in);
	}
	return countSong;
}
int deleteSong(SONG*& songs, int index, int countSongs) {
	SONG* newSongs = new SONG[countSongs - 1];
	for (int i = 0, j = 0; i < countSongs; i++) {
		if (i != index) {
			newSongs[j] = songs[i];
			j++;
		}
	}
	delete[] songs;
	songs = newSongs;
	countSongs--;
	return countSongs;
}
int chooseSong(SONG* songs, int countSongs) {
	int key = 0;
	int num = 0;
	while (key != ESC) {
		system("cls");
		for (int i = 0; i < countSongs; i++) {
			if (num == i) std::cout << "\033\[32m";
			std::cout << "\033\[3m" << "title: " << "\033[0m";
			std::cout << "\033\[3m" << songs[i].title << "\n";
			if (num == i) std::cout << "\033\[32m";
			std::cout << "\033\[3m" << "author: " << "\033[0m";
			std::cout << "\033\[3m" << songs[i].author << "\n";
			if (num == i) std::cout << "\033\[32m";
			std::cout << "\033\[3m" << "date release: " << "\033[0m";
			std::cout << "\033\[3m" << songs[i].dateRelease << "\n";
		}
		key = _getch();
		key == DOWN && num > 0 ? num-- : key == UP && num < countSongs - 1 ? num++ : num;
		if (key == ENTER) return num;
		if (key == ESC) return -1;
	}
}
SONG* addSongInFile() {
	const char* const pathTemp = "newSongs.txt";
	char* temp = new char[255];
	SONG* newSong = new SONG;
	FILE* in;
	fopen_s(&in, pathTemp, "r");
	if (in != NULL) {
		fgets(temp, 255, in);
		newSong->setTittle(temp);
		fgets(temp, 255, in);
		newSong->setAuthor(temp);
		int dataRelease = fgetc(in);
		newSong->dateRelease = dataRelease;
		fclose(in);
	}
	return newSong;
}