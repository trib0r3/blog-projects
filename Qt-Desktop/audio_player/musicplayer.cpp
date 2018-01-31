#include "musicplayer.h"
#include "ui_musicplayer.h"
#include <QFileDialog>
#include <QMediaPlaylist>
#include <QStringList>
#include <QMessageBox>

MusicPlayer::MusicPlayer(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MusicPlayer)
{
	ui->setupUi(this);

	player = new QMediaPlayer(this);
	playlist = new QMediaPlaylist;


	connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(positionChanged(qint64)));
	connect(ui->lengthSlider,SIGNAL(valueChanged(int)),this,SLOT(setPosition(int)));
	connect(player,SIGNAL(durationChanged(qint64)),this,SLOT(durationChanged(qint64)));
	connect(player,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),this,SLOT(statusChanged(QMediaPlayer::MediaStatus)));

	// sygnaly przycisków
	connect(ui->bStart,SIGNAL(released()),this,SLOT(play()));
	connect(ui->bStop,SIGNAL(released()),this,SLOT(stop()));

	connect(ui->bNext,SIGNAL(released()),this,SLOT(next()));
	connect(ui->bPrev,SIGNAL(released()),this,SLOT(prev()));

	connect(ui->bAdd,SIGNAL(released()),this,SLOT(add()));
	connect(ui->bRemove,SIGNAL(released()),this,SLOT(remove()));

	connect(ui->playlist,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(playSelected(QModelIndex)));

	player->setPlaylist(playlist);
}


MusicPlayer::~MusicPlayer()
{
	delete player;
	delete playlist;

	delete ui;
}


void MusicPlayer::positionChanged(qint64 pitch)
{
	ui->lengthSlider->setValue(pitch);
}


void MusicPlayer::durationChanged(qint64 duration)
{
	ui->lengthSlider->setMaximum(duration);
	ui->lengthSlider->setValue(0);
}


void MusicPlayer::statusChanged(QMediaPlayer::MediaStatus status)
{
	switch(status)
	{
	case QMediaPlayer::NoMedia:
		QMessageBox::information(this,"No media available","Playlist is empty");
		stop();
		break;


	case QMediaPlayer::EndOfMedia:
		stop();
		break;


	case QMediaPlayer::InvalidMedia:
		QMessageBox::warning(this,"Invalid media","Format used in current media is not supported");
		break;

	default:
		break;
	}
}


void MusicPlayer::setPosition(int pos)
{
	player->setPosition(pos);
}


void MusicPlayer::play()
{
	// jeżeli nie odtwarzamy audio, to:
	if(player->state() != QMediaPlayer::PlayingState)
	{
		ui->bStart->setIcon(QIcon(":/rc/pause.png"));
		player->play();

		ui->lengthSlider->setMaximum(player->duration());
		ui->lengthSlider->setValue(0);
	}
	else
	{
		ui->bStart->setIcon(QIcon(":/rc/start.png"));
		player->pause();
	}
}


void MusicPlayer::stop()
{
	ui->bStart->setIcon(QIcon(":/rc/start.png"));
	player->stop();
}


void MusicPlayer::next()
{
	int tmp = playlist->currentIndex()+1;

	if(tmp >= ui->playlist->count())
		playlist->setCurrentIndex(0);
	else
		playlist->next();
}


void MusicPlayer::prev()
{
	int tmp = playlist->previousIndex();

	if(tmp < 0)
		playlist->setCurrentIndex(ui->playlist->count()-1);
	else
		playlist->previous();
}


void MusicPlayer::add()
{
	QFileDialog dialog(this);

	dialog.setNameFilter(tr("Music (*.mp3)"));
	dialog.setFileMode(QFileDialog::ExistingFiles);


	QStringList paths;
	if(dialog.exec())
		paths = dialog.selectedFiles();

	for(int i=0;i<paths.size();i++)
	{
		ui->playlist->addItem(paths[i]);

		playlist->addMedia(QUrl::fromLocalFile(paths[i]));
	}
}


void MusicPlayer::remove()
{
	ui->playlist->clear();

	stop();
	playlist->clear();
}


void MusicPlayer::playSelected(QModelIndex index)
{
	playlist->setCurrentIndex(index.row());

	if(player->state() != QMediaPlayer::PlayingState)
		play();
}
