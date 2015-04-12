#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>

namespace Ui {
class Graph;
}

class Graph : public QDialog
{
    Q_OBJECT

public:
    explicit Graph(QString report, QWidget *parent = 0);
    ~Graph();

private:
    Ui::Graph *ui;
};

#endif // GRAPH_H
