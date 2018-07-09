#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "authorization.h"
#include <QMainWindow>
#include <QDebug>
#include "cppkafka/consumer.h"
#include "cppkafka/configuration.h"
#include "cppkafka/utils/buffered_producer.h"
#include "cppkafka/configuration.h"
#include <iostream>
#include<thread>

using cppkafka::Consumer;
using cppkafka::Configuration;
using cppkafka::Message;
using cppkafka::TopicPartitionList;
using cppkafka::BufferedProducer;
using cppkafka::MessageBuilder;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_pushButton_send_clicked();

private:
    Ui::MainWindow *ui;
    void consumer();
    void producer(std::string messager);
    std::string topic_name;
    std::string brokers;
    std::string group_id;
};

#endif // MAINWINDOW_H
