#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QKeyEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

#include <QVideoWidget>
#include <QMediaPlayer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_videoWidget(new QVideoWidget(this)),
    m_mediaPlayer(new QMediaPlayer(this)),
    m_maxTime(0)
{
    ui->setupUi(this);
    ui->mainLayout->insertWidget(0, m_videoWidget);

    connect(m_mediaPlayer, &QMediaPlayer::durationChanged, [&](qint64 v){
        ui->timeSlider->setMaximum(static_cast<int>(v));
        m_maxTime = v;
    });
    connect(m_mediaPlayer, &QMediaPlayer::positionChanged, [&](qint64 v){
        ui->timeSlider->setValue(static_cast<int>(v));

        auto s = v / 1000;
        auto m = m_maxTime / 1000;

        ui->currentTime->setText(
            QString("%1:%2:%3.%4/%5:%6:%7.%8")
                .arg(QString::number(s / 3600), 2, '0').arg(QString::number((s / 60) % 60), 2, '0')
                .arg(QString::number(s % 60, 10), 2, '0').arg(QString::number(v % 1000), 3, '0')
                .arg(QString::number(m / 3600), 2, '0').arg(QString::number((m / 60) % 60), 2, '0')
                .arg(QString::number(m % 60, 10), 2, '0').arg(QString::number(m_maxTime % 1000), 3, '0'));
    });
    connect(ui->timeSlider, &QSlider::sliderMoved, m_mediaPlayer, &QMediaPlayer::setPosition);
    connect(ui->volumeSlider, &QSlider::valueChanged, m_mediaPlayer, &QMediaPlayer::setVolume);

    ui->volumeSlider->setValue(m_mediaPlayer->volume());

    m_mediaPlayer->setVideoOutput(m_videoWidget);

    setFocus();
    setAcceptDrops(true);

    centralWidget()->setStyleSheet("background-color: transparent");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_mediaPlayer;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_Space:
        if(m_mediaPlayer->state() == QMediaPlayer::PlayingState){
            m_mediaPlayer->pause();
        }else{
            m_mediaPlayer->play();
        }
        break;
    case Qt::Key_Left:
        if((event->modifiers() & Qt::AltModifier) && (event->modifiers() & Qt::ControlModifier)){
            auto pos = m_mediaPlayer->position();
            m_mediaPlayer->setPosition(pos - 10 * 60 * 1000);
        }
        else if(event->modifiers() & Qt::AltModifier){
            auto pos = m_mediaPlayer->position();
            m_mediaPlayer->setPosition(pos - 1 * 60 * 1000);
        }
        else if(event->modifiers() & Qt::ControlModifier){
            auto pos = m_mediaPlayer->position();
            m_mediaPlayer->setPosition(pos - 30 * 1000);
        }
        else{
            auto pos = m_mediaPlayer->position();
            m_mediaPlayer->setPosition(pos - 5 * 1000);
        }
        break;
    case Qt::Key_Right:
        if((event->modifiers() & Qt::AltModifier) && (event->modifiers() & Qt::ControlModifier)){
            auto pos = m_mediaPlayer->position();
            m_mediaPlayer->setPosition(pos + 10 * 60 * 1000);
        }
        else if(event->modifiers() & Qt::AltModifier){
            auto pos = m_mediaPlayer->position();
            m_mediaPlayer->setPosition(pos + 1 * 60 * 1000);
        }
        else if(event->modifiers() & Qt::ControlModifier){
            auto pos = m_mediaPlayer->position();
            m_mediaPlayer->setPosition(pos + 30 * 1000);
        }
        else{
            auto pos = m_mediaPlayer->position();
            m_mediaPlayer->setPosition(pos + 5 * 1000);
        }
        break;
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent *event)
{
    auto url = event->mimeData()->urls().first();
    m_mediaPlayer->setMedia(url);
}

