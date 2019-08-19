#ifndef MUSIC_H
#define MUSIC_H

#include <QWidget>
#include <QMediaPlayer>
//#include <QtWinExtras>
#include <QFileDialog>
#include <QList>
#include <QDir>
#include <QTime>
#include <QDebug>
#include <QCloseEvent>
#include <QSystemTrayIcon>
#include <QMenu>


namespace Ui {
class Music;
}


class Widget;
class MusicWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MusicWidget(Widget *parent = 0);
    ~MusicWidget();

private slots:

    void on_start_clicked();

    void on_pause_clicked();

    void on_stop_clicked();

    void on_add_clicked();

    void on_tableWidget_doubleClicked(const QModelIndex &index);

    void on_tableWidget_clicked(const QModelIndex &index);

    void updatePosition(qint64 position);

    void updateDuration(qint64 duration);

    void setPosition(int position);

    void on_verticalSlider_valueChanged(int value);

    void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);
protected:
    void change_by_mode();//通过播放方式切换歌曲

    void creatActions();

    void creatTrayIcon();

public:
	
private:
	Ui::Music  *ui;
	Widget*    m_Parent;
    QMediaPlayer *mediaPlayer;
    QStringList filter;
    QList<QString> filePath;
    QString music_file_path;
    QString cur_music;
    int cur_index;
    int pause_flag;
    qint64 music_duration;
    QDir *dir;
    QSystemTrayIcon *mSysTrayIcon;
    QMenu *trayIconMenu;
    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;

};

#endif // MUSIC_H
