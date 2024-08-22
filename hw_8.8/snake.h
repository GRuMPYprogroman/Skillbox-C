#pragma once
#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include <QString>
#include <QLabel>


class Part
{
public:
    int x;
    int y;
    QVector<int> color;
};

class Apple
{
public:
    int x;
    int y;
    QVector<int> color = {255, 0, 0};
};

class Snake : public QWidget
{
public:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void move();
    void eatApple();
    void checkCollision();
    void updateScore(int& score_numb); 
    void win();

    QSize windowSize = this->size();
    QVector<Part *> snake_body;
    Apple *apl = nullptr;
    QString direction = "right";
    int score_numb = 0;

    Snake(QWidget *parent = 0);
    ~Snake()
    {
        delete startBtn;
        for (auto i : snake_body)
        {
            delete i;
        }
    };
private slots:
    void onClick();
    void restartGame(); 

private:
    QPushButton *startBtn;
    QPushButton *restartBtn;
    QTimer *timer;
    QLabel *label;
    QLabel *score;
    int dx;
    int dy;
};
