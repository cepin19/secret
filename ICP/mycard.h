#ifndef MYCARD_H
#define MYCARD_H


class myCard : public QGraphicsObject
{
public:
    myCard();

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;
};

#endif // MYCARD_H
