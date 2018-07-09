#include "mainwindow.h"
#include "ui_mainwindow.h"

using std::exception;
using std::cout;
using std::endl;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Authorization *aut= new  Authorization () ;
    if (aut->exec() == QDialog::Accepted){
        qDebug()<<"hello";
        brokers=(aut->getIpServer()).toStdString();
        group_id=(aut->getUserName()).toStdString();
        std::string name="mytopic";
        topic_name=name;
    }
    std::thread listening_deamon(&MainWindow::consumer, this);
    listening_deamon.detach();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::consumer(){
    Configuration config = {
                 { "metadata.broker.list", brokers },
                { "group.id", group_id },
                {"api.version.request", true}
     };
    Consumer consumer(config);
    consumer.subscribe({ topic_name });
    ui->listWidget_chat->addItem("You are connected to the chat! Start communicating now!");
    QApplication::processEvents();
    ui->listWidget_chat->scrollToBottom();
    while (true) {
      Message msg = consumer.poll();
      if (msg) {
        if (msg.get_error()) {
          if (!msg.is_eof()) {
            qDebug()<<"Error";
          }
        }else {
          cout << msg.get_payload() << endl;
          std::string mes =msg.get_payload();
          ui->listWidget_chat->addItem(QString::fromUtf8((mes.c_str())));
          QApplication::processEvents();
          ui->listWidget_chat->scrollToBottom();
          consumer.commit(msg);}
        }
      else{
    std::this_thread::sleep_for(std::chrono::milliseconds(15));}
    }
}
void MainWindow::producer(std::string msg){
    MessageBuilder builder(topic_name);
    builder.partition(0);
    Configuration config = {
          { "metadata.broker.list", brokers },
      };
    BufferedProducer<std::string> producer(config);
    std::string mes="["+group_id+"]"+": "+msg;
    builder.payload(mes);
    producer.add_message(builder);
    producer.flush();
    ;
}

void MainWindow::on_pushButton_send_clicked()
{
    producer((ui->lineEdit_send->text()).toStdString());
    ui->lineEdit_send->clear();
}
