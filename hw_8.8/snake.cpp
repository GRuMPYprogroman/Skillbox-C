#include <QDebug>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QRandomGenerator>
#include "snake.h"
#include <QPixmap>
#include <QKeyEvent>

void Snake::win(){
    disconnect(timer, &QTimer::timeout, this, &Snake::move);
    disconnect(timer, &QTimer::timeout, this, &Snake::eatApple);
    timer->stop();
    delete(timer);
    timer = nullptr;  

    for (auto part : snake_body)
    {
        delete part;
    }
    snake_body.clear();

    if (apl) {
        delete apl;
        apl = nullptr;
    }

    update();

    QLayout* oldLayout = layout();
    if (oldLayout) {
        QLayoutItem* item;
        while ((item = oldLayout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete oldLayout;
    }

    label = new QLabel(this);
    label->setAlignment(Qt::AlignCenter);

    QVBoxLayout *vbox = new QVBoxLayout(this);
    setLayout(vbox);

    vbox->addWidget(label);

    label->setText("ВСЕГО РАЗ Я ВИДЕЛ ТАКУЮ СИЛУ!");
    label->setFont(QFont("Purisa", 50));
    label->show();

}

void Snake::updateScore(int& score_numb) {
    score_numb+=10;
    score->setText("Score: " + QString::number(score_numb));
}

void Snake::restartGame()
{
    // Удаление сообщения и кнопки рестарта
    if (label) {
        layout()->removeWidget(label);
        delete label;
        label = nullptr;
    }

    if (restartBtn) {
        disconnect(restartBtn, &QPushButton::clicked, this, &Snake::restartGame);
        layout()->removeWidget(restartBtn);
        delete restartBtn;
        restartBtn = nullptr;
    }

    if (timer) {
        timer->stop();
    } else {
        timer = new QTimer(this);
    }

    // Сброс состояния игры
    snake_body.clear();

    dx = 3;
    dy = 0;
    direction = "right";

    if (apl) {
        delete apl;
        apl = nullptr;
    }

    apl = new Apple;
    QPoint centerPoint = this->rect().center();
    QRect windowRect = this->rect();

    int appleWidth = 100; 
    int appleHeight = 100;

    do 
    {
        apl->x = QRandomGenerator::global()->bounded(windowRect.width() - appleWidth);
        apl->y = QRandomGenerator::global()->bounded(windowRect.height() - appleHeight) + appleHeight / 2;
    } while (apl->x == centerPoint.x() && apl->y == centerPoint.y());


    Part* head_part = new Part;
    head_part->color = {255, 0, 0};
    head_part->x = (this->windowSize).width() / 2;
    head_part->y = (this->windowSize).height() / 2;

    snake_body.append(head_part);

    score_numb = 0;

    // Перезапуск таймера
    connect(timer, &QTimer::timeout, this, &Snake::move);
    connect(timer, &QTimer::timeout, this, &Snake::eatApple);
    timer->start(25);

    update();
}

void Snake::checkCollision()
{
    for (int i = 1; i < snake_body.size(); ++i)
    {
        int diffX = std::abs(snake_body[0]->x - snake_body[i]->x);
        int diffY = std::abs(snake_body[0]->y - snake_body[i]->y);
        if (diffX < 3 && diffY < 3)
        {
            disconnect(timer, &QTimer::timeout, this, &Snake::move);
            disconnect(timer, &QTimer::timeout, this, &Snake::eatApple);
            timer->stop();
            delete(timer);
            timer = nullptr;  

            for (auto part : snake_body)
            {
                delete part;
            }
            snake_body.clear();

            if (apl) {
                delete apl;
                apl = nullptr;
            }

            update();

            QLayout* oldLayout = layout();
            if (oldLayout) {
                QLayoutItem* item;
                while ((item = oldLayout->takeAt(0)) != nullptr) {
                    delete item->widget();
                    delete item;
                }
                delete oldLayout;
            }

            label = new QLabel(this);
            label->setAlignment(Qt::AlignCenter);

            QVBoxLayout *vbox = new QVBoxLayout(this);
            setLayout(vbox);

            vbox->addWidget(label);

            label->setText("LOOSER");
            label->setFont(QFont("Purisa", 50));
            label->show();

            vbox->addSpacing(20);

            restartBtn = new QPushButton("Restart", this);
            vbox->addWidget(restartBtn,0,Qt::AlignCenter);
            connect(restartBtn, &QPushButton::clicked, this, &Snake::restartGame);

            return;
        }
    }
}

void Snake::move()
{
    Part* prev = snake_body[0];  // Начинаем с головы змеи
    int prevX = prev->x;
    int prevY = prev->y;

    // Перемещаем голову змеи
    snake_body[0]->x += dx;
    snake_body[0]->y += dy;

    if (snake_body[0]->x >= this->width())
    {
        snake_body[0]->x = 0;
    }
    else if (snake_body[0]->x < 0)
    {
        snake_body[0]->x = this->width() - 1;
    }

    if (snake_body[0]->y >= this->height())
    {
        snake_body[0]->y = 0;
    }
    else if (snake_body[0]->y < 0)
    {
        snake_body[0]->y = this->height() - 1;
    }

    // Перемещаем остальные части тела змеи
    for (auto it = snake_body.begin() + 1; it != snake_body.end(); ++it)
    {
        Part* current = *it;
        int currentX = current->x;
        int currentY = current->y;

        // Перемещаем текущую часть на место предыдущей
        current->x = prevX;
        current->y = prevY;

        //Обновляем prev на текущие координаты для следующей итерации
        prevX = currentX;
        prevY = currentY;
    }

    checkCollision();
    update();
}

void Snake::eatApple()
{
    double distance = std::sqrt(std::pow(snake_body[0]->x - apl->x, 2) + std::pow(snake_body[0]->y - apl->y, 2));
    
    if (distance <= 20)
    {
        Part* part = new Part;

        if(direction == "right")
        {
            part->x = snake_body.last()->x - dx;
            part->y = snake_body.last()->y;
        }
        
        if(direction == "left")
        {
            part->x = snake_body.last()->x + dx;
            part->y = snake_body.last()->y;
        }

        if(direction == "up")
        {
            part->x = snake_body.last()->x;
            part->y = snake_body.last()->y + dy;
        }

        if(direction == "down")
        {
            part->x = snake_body.last()->x;
            part->y = snake_body.last()->y - dy;
        }

        part->color = {237,201,175};

        snake_body.append(part);

        //qDebug() << "New part added at:" << part->x << part->y << "Direction:" << direction;


        int appleWidth = 100; 
        int appleHeight = 100;
        QRect windowRect = this->rect();
        apl->x = QRandomGenerator::global()->bounded(windowRect.width() - appleWidth);
        apl->y = QRandomGenerator::global()->bounded(windowRect.height() - appleHeight) + appleHeight / 2;
        updateScore(score_numb);
        if (score_numb == 1000)
        {
            win();
        }
    }
    update();
}


Snake::Snake(QWidget *parent) : QWidget(parent), dx(3),dy(0)
{
    this->resize(400,400);
    
    setFocusPolicy(Qt::StrongFocus);
    QHBoxLayout *hbox = new QHBoxLayout(this);
    hbox->setSpacing(3);

    startBtn = new QPushButton("Start", this);
    hbox->addWidget(startBtn, 0, Qt::AlignCenter);

    connect(startBtn, &QPushButton::clicked, this, &Snake::onClick);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Snake::move);
    connect(timer, &QTimer::timeout, this, &Snake::eatApple);

}



void Snake::onClick()
{
    disconnect(startBtn, &QPushButton::clicked, this, &Snake::onClick);
    layout()->removeWidget(startBtn);
    delete startBtn;
    startBtn = nullptr;


    score = new QLabel;
    score->setAlignment(Qt::AlignTop|Qt::AlignRight);    
    score->setText("Score: " + QString::number(score_numb));
    score->setFont(QFont("Purisa", 10));
    score->setStyleSheet("color: black;");

    layout()->addWidget(score);

    apl = new Apple;
    QPoint centerPoint = this->rect().center();
    QRect windowRect = this->rect();

    int appleWidth = 100; 
    int appleHeight = 100;

    do 
    {
        apl->x = QRandomGenerator::global()->bounded(windowRect.width() - appleWidth);
        apl->y = QRandomGenerator::global()->bounded(windowRect.height() - appleHeight) + appleHeight / 2;
    } while (apl->x == centerPoint.x() && apl->y == centerPoint.y());


    Part* head_part = new Part;
    head_part->color = {255,0,0};
    
    head_part->x = centerPoint.x();
    head_part->y = centerPoint.y();

    snake_body.append(head_part);

    timer->start(25);

    update();
}


void Snake::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    if (apl != nullptr)
    {
        QPainter painter(this);

        QPixmap backgroundPixmap("/home/stepan/skillbox/hw_8.8/aerial-view-garden-background_1308-27471.jpg");
        painter.drawPixmap(0, 0, width(), height(), backgroundPixmap);

        QPixmap applePixmap("/home/stepan/skillbox/hw_8.8/apple-removebg-preview.png");

        QPixmap scaledApplePixmap = applePixmap.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        
        int drawX = apl->x - scaledApplePixmap.width() / 2;
        int drawY = apl->y - scaledApplePixmap.height() / 2;

        painter.drawPixmap(drawX, drawY, scaledApplePixmap);   


        for (auto part : snake_body)
        {
            QColor snake_color(part->color[0],part->color[1],part->color[2]);
            painter.setPen(snake_color);
            painter.setBrush(snake_color);
            //Рисуем точку как маленький круг с радиусом 5
            painter.drawEllipse(QPoint(part->x, part->y), 5, 5); 
        }
    }  
}

void Snake::keyPressEvent(QKeyEvent *event) 
{
    if (event->key() == Qt::Key_Right && direction != "left")
    {
        dx = 3;
        dy = 0;
        direction = "right";
    }
    else if (event->key() == Qt::Key_Left && direction != "right")
    {
        dx = -3;
        dy = 0;
        direction = "left";
    }
    else if (event->key() == Qt::Key_Up && direction != "down")
    {
        dx = 0;
        dy = -3;
        direction = "up";
    }
    else if (event->key() == Qt::Key_Down && direction != "up")
    {
        dx = 0;
        dy = 3;
        direction = "down";
    }
    else
    {
        QWidget::keyPressEvent(event); // Остальные события базовому классу
        return;
    }
}