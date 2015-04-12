#include "graph.h"
#include "ui_graph.h"

Graph::Graph(QString report,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Graph)
{
    ui->setupUi(this);
    if(report == "Income"){
        ui->graphWidget->setLocale((QLocale(QLocale::English)));
        double now = QDateTime::currentDateTime().toTime_t();
        srand(8);
        ui->graphWidget->addGraph();

        //Gen walk data:
        QVector<double> time(250), value(250);
        for(int i = 0; i < 250; i++){
            time[i] = now + 24*3600*i;
            if(i == 0){
                value[i] = (i/50.0 + 1)*(rand()/(double)RAND_MAX-0.5);
            }
            else
                value[i] = fabs(value[i-1])*(1+0.02/4.0*(4-gi)) + (i/50.0+1)*(rand()/(double)RAND_MAX-0.5);
        }
        ui->graphWidget->graph()->setData(time,value);

        //Configure bottom axis to show date and time instead of number:
        ui->graphWidget->xAxis->setTickLabelType(QCPAxis::ltDateTime);
        ui->graphWidget->xAxis->setDateTimeFormat("M/d/yyyy");

        //Set compact font
        ui->graphWidget->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
        ui->graphWidget->yAxis->setTickLabelFont(QFont(QFont().family(), 8));

        //Set a fixed tick step to one tick per month:
        ui->graphWidget->xAxis->setAutoTickStep(false);
        ui->graphWidget->xAxis->setTickStep(2628000);
        ui->graphWidget->xAxis->setSubTickCount(3);

        //Apply manual tick and tick label for left axis:
        ui->graphWidget->yAxis->setAutoTicks(false);
        ui->graphWidget->yAxis->setAutoTickLabels(false);
        ui->graphWidget->yAxis->setTickVector(QVector<double>() << 5 << 55);
        ui->graphWidget->yAxis->setTickVectorLabels(QVector<QString>() << "Not so\nhigh" << "very\nhigh");

        //Set axis labels
        ui->graphWidget->xAxis->setLable("Date");
        ui->graphWidget->yAxis->setLabel("Random wobbly lines value");

        // make top and right axes visivle but without ticks and labels;
        ui->graphWidget->xAxis->setRange(now, now+24*3600*249);
        ui->graphWidget->yAxis->setRange(0, 60);

        ui->graphWidget->legend->setVisible(true);
    }
    else{

    }



}

Graph::~Graph()
{
    delete ui;
}
