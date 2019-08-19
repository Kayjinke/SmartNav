#include "music.h"
#include "ui_music.h"
#include "widget.h"

using namespace std;

MusicWidget::MusicWidget(Widget *parent) :
    QWidget(parent),
    m_Parent(parent),    
    ui(new Ui::Music)
{
    ui->setupUi(this);
    connect(ui->btn_musicback, SIGNAL(clicked()), m_Parent, SLOT(on_btn_music_back_clicked()));
    
    mediaPlayer = new QMediaPlayer;
    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(setPosition(int)));
    connect(mediaPlayer,SIGNAL(positionChanged(qint64)), this, SLOT(updatePosition(qint64)));
    connect(mediaPlayer,SIGNAL(durationChanged(qint64)), this, SLOT(updateDuration(qint64)));
    //connect(mediaPlayer,SIGNAL(destroyed(QObject*)) , this, SLOT(change_by_mode()));
    mediaPlayer->setVolume(ui->verticalSlider->value());
    setWindowTitle("音乐播放器");
    setWindowIcon(QIcon("ccsu.png"));
    ui->label_playing->setVisible(false);
    ui->music_name->setVisible(false);
    mSysTrayIcon = new QSystemTrayIcon(this);
    QIcon icon = QIcon("ccsu.png");
    mSysTrayIcon->setIcon(icon);
    //mSysTrayIcon->setToolTip(QObject::trUtf8("测试系统托盘图标"));
    mSysTrayIcon->setToolTip("音乐播放器");
    creatActions();
    creatTrayIcon();
    mSysTrayIcon->show();

}

MusicWidget::~MusicWidget()
{
    delete ui;
}


void MusicWidget::on_start_clicked()
{
    if(pause_flag == 1)
    {
        mediaPlayer->play();
    }
    else
    {
        if(cur_music.isEmpty())
        {
            cur_index = 0;
            cur_music = filePath.at(cur_index);
        }
        QModelIndex index = ui->tableWidget->model()->index(cur_index,0);
        ui->tableWidget->setCurrentIndex(index);
        mediaPlayer->setMedia(QUrl::fromLocalFile(cur_music));
        ui->music_name->setText(cur_music.mid(music_file_path.length()+1,cur_music.length()-music_file_path.length()));
        mSysTrayIcon->setToolTip(ui->music_name->text());
        ui->label_playing->setVisible(true);
        ui->music_name->setVisible(true);
        mediaPlayer->play();
    }
    pause_flag = 0;
}

void MusicWidget::on_pause_clicked()
{
    mediaPlayer->pause();
    pause_flag = 1;
}

void MusicWidget::on_stop_clicked()
{
    ui->label_playing->setVisible(false);
    ui->music_name->setVisible(false);
    mediaPlayer->stop();
}

void MusicWidget::on_add_clicked()
{
    music_file_path = QFileDialog::getExistingDirectory(NULL, tr("选择文件夹"),"./",QFileDialog::ShowDirsOnly);
    filePath.clear();
    dir = new QDir(music_file_path);
    filter<<"*.mp3";
    dir->setNameFilters(filter);
    QList<QFileInfo> *fileInfo = new QList<QFileInfo>(dir->entryInfoList(filter));
    qDebug() << "file_count" << fileInfo->count();
    ui->tableWidget->setRowCount(fileInfo->count());
    ui->tableWidget->setColumnCount(1);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);    //将表格设置为禁止编辑
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);   //将表格设置为整行选择
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"歌曲名称");
    for(int i = 0; i < fileInfo->count(); i++)
    {
        ui->tableWidget->setItem(0,i,new QTableWidgetItem(fileInfo->at(i).fileName()));
        filePath.append(fileInfo->at(i).filePath());
        qDebug() << "file_Name" <<fileInfo->at(i).fileName();
        qDebug() << "file_filePath" <<fileInfo->at(i).filePath();
    }
    ui->tableWidget->resizeColumnsToContents(); //将列的大小设为与内容相匹配
    ui->tableWidget->resizeRowsToContents();    //将行的大小设为与内容相匹配
}

void MusicWidget::on_tableWidget_doubleClicked(const QModelIndex &index)
{
    cur_index = index.row();
    cur_music = filePath.at(cur_index);
    mediaPlayer->setMedia(QUrl::fromLocalFile(cur_music));
    ui->music_name->setText(cur_music.mid(music_file_path.length()+1,cur_music.length()-music_file_path.length()));
    mSysTrayIcon->setToolTip(ui->music_name->text());
    ui->label_playing->setVisible(true);
    ui->music_name->setVisible(true);
    mediaPlayer->play();
}

void MusicWidget::on_tableWidget_clicked(const QModelIndex &index)
{
    cur_index = index.row();
    cur_music = filePath.at(cur_index);
}

void MusicWidget::updateDuration(qint64 duration)
{
    qDebug()<<"duration:"<<duration;
    music_duration = duration;
    ui->horizontalSlider->setRange(0, duration);
    ui->horizontalSlider->setEnabled(duration > 0);
    ui->horizontalSlider->setPageStep(duration / 10);
}


void MusicWidget::updatePosition(qint64 position)
{
    qDebug()<<"position:"<<position;
    if(music_duration == position && music_duration != 0)
    {
        qDebug()<<"change_by_mode";
        change_by_mode();
    }
    ui->horizontalSlider->setValue(position);
    QTime duration(0, position / 60000, qRound((position % 60000) / 1000.0));
    ui->positionLabel->setText(duration.toString(tr("mm:ss")));
}

void MusicWidget::setPosition(int position)
{
    // avoid seeking when the slider value change is triggered from updatePosition()
    if (qAbs(mediaPlayer->position() - position) > 99)
        mediaPlayer->setPosition(position);
}

void MusicWidget::on_verticalSlider_valueChanged(int value)
{
    mediaPlayer->setVolume(value);
    QString vol = "音量:";
    vol += QString::number(value);
    ui->vol->setText(vol);
}


void MusicWidget::change_by_mode()
{
    qDebug()<<"success";
    switch(ui->mode->currentIndex())
    {
    case 0:                         //顺序播放
    {
        if(cur_index == filePath.length())
        {
            cur_index =0;
        }
        else
        {
            cur_index++;
        }
        QModelIndex index = ui->tableWidget->model()->index(cur_index,0);
        ui->tableWidget->setCurrentIndex(index);
        cur_music = filePath.at(cur_index);
        mediaPlayer->setMedia(QUrl::fromLocalFile(cur_music));
        ui->music_name->setText(cur_music.mid(music_file_path.length()+1,cur_music.length()-music_file_path.length()));
        mSysTrayIcon->setToolTip(ui->music_name->text());
        mediaPlayer->play();
        break;
    }
    case 1:                         //随机播放
    {
        cur_index = qrand()%filePath.length();
        qDebug()<<"cur_index"<<cur_index<<"lenthg"<<filePath.length();
        QModelIndex index = ui->tableWidget->model()->index(cur_index,0);
        ui->tableWidget->setCurrentIndex(index);
        cur_music = filePath.at(cur_index);
        mediaPlayer->setMedia(QUrl::fromLocalFile(cur_music));
        ui->music_name->setText(cur_music.mid(music_file_path.length()+1,cur_music.length()-music_file_path.length()));
        mSysTrayIcon->setToolTip(ui->music_name->text());
        mediaPlayer->play();
        break;
    }
    case 2:                         //单曲循环
    {
        cur_music = filePath.at(cur_index);
        mediaPlayer->setMedia(QUrl::fromLocalFile(cur_music));
        mSysTrayIcon->setToolTip(ui->music_name->text());
        ui->music_name->setText(cur_music.mid(music_file_path.length()+1,cur_music.length()-music_file_path.length()));
        mediaPlayer->play();
        break;
    default:
        break;
        }
    }
}

void MusicWidget::creatActions()
{
    minimizeAction = new QAction(tr("最小化 (&I)"), this);
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

    maximizeAction = new QAction(tr("最大化 (&X)"), this);
    connect(maximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized()));

    restoreAction = new QAction(tr("还原 (&R)"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction(tr("退出 (&Q)"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void MusicWidget::creatTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);
    mSysTrayIcon->setContextMenu(trayIconMenu);
}
#if 0
void MusicWidget::closeEvent(QCloseEvent *event)
{
    if( !mysetting->exit_type )
    {
        event->ignore();
        this->hide();
    connect(mSysTrayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this,SLOT(on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason)));
    }
}
#endif

void MusicWidget::on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
    qDebug()<<reason;
    switch(reason)
    {
        case QSystemTrayIcon::Context:
            break;
        case QSystemTrayIcon::Trigger:
                //单击托盘图标
            break;
        case QSystemTrayIcon::DoubleClick:
            //双击托盘图标
            //双击后显示主程序窗口
            this->show();
            break;
        default:
            break;
    }
}
