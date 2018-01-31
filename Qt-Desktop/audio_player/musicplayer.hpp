#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QModelIndex>

namespace Ui {
class MusicPlayer;
}

class MusicPlayer : public QMainWindow
{
	Q_OBJECT

public:
	explicit MusicPlayer(QWidget *parent = 0);
	~MusicPlayer();

private slots:
	void positionChanged(qint64);								// zmiana (normalna) podczas grania utworu
	void durationChanged(qint64);								// zmiana utworu

	void statusChanged(QMediaPlayer::MediaStatus);				// obsuga zmian statusów

	void setPosition(int);										// ustawienie pozycji paska postępu

	void play();					// reakcje na wciśnięcie:	// odtwórz/pauza
	void stop();												// stop
	void next();												// następny utwór
	void prev();												// poprzedni utwór

	void add();													// dodawanie nowych utworów
	void remove();												// wyczyszczenie całej listy

	void playSelected(QModelIndex);								// uruchamia wybrany utwór z playlisty

private:
	Ui::MusicPlayer *ui;

	QMediaPlayer *player;										// odtwarzacz
	QMediaPlaylist *playlist;									// playlista utworów
};

#endif // MUSICPLAYER_H
