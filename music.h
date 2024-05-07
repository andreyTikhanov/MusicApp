#pragma once
struct SONG {
	char* title = nullptr;
	char* author = nullptr;
	char** text = nullptr;
	int sizeText { 0 };
	int dateRelease{ 0 };
	void setTittle(const char* title);
	void setAuthor(const char* author);
	void setText(char** text,int sizeText);
	void setStroka(const char* temp, int index);
};
SONG* createSong();
SONG* addSongInFile();
const char* const path = "music.bin";
const char* const path2 = "data.bin";
void saveMusic(SONG* songs, int countSongs);
void showSongs(SONG* songs, int countSongs);
void editSong(SONG* songs, int countSongs, int index);
void showSongsWithText(SONG* songs, int countSongs,int index);
void clearLine(int line);
int addSong(SONG*& songs, SONG* song, int countSongs);
int loadMusic(SONG*& songs);
int deleteSong(SONG*& songs, int index, int countSongs);
int chooseSong(SONG* songs, int countSongs);
