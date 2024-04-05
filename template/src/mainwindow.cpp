#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    // -------------------------------------
    // QT Initialization
    // -------------------------------------
    ui->setupUi(this);

    // -------------------------------------
    // ROS Initialization
    // -------------------------------------
    rclcpp::init(0, nullptr);
    this->node_ = rclcpp::Node::make_shared("__NODE_NAME__");

    // -------------------------------------
    // ROS publisher
    // -------------------------------------
    this->publisher_ = this->node_->create_publisher<std_msgs::msg::String>("qt_pub_topic", 10);

    // -------------------------------------
    // ROS subscriber
    // -------------------------------------
    this->subscriber_ = node_->create_subscription<std_msgs::msg::String>(
        "sub_topic", 10,
        [&](const std_msgs::msg::String::SharedPtr msg)
        {
            // Handle received message
            QString receivedMsg = QString::fromStdString(msg->data);
            std::cout << msg->data << std::endl;
            ui->textBrowser->append(receivedMsg);
        });

    // -------------------------------------
    this->initSpin();
}

MainWindow::~MainWindow()
{
    // Stop the spin timer
    this->spin_timer_.stop();

    // Shutdown ROS
    rclcpp::shutdown();

    delete ui;
}

void MainWindow::initSpin(void)
{
    // Initialize spinning with a timer interval of 1 ms
    this->spin_timer_.setInterval(1);
    QObject::connect(&this->spin_timer_,
                     &QTimer::timeout,
                     [&]()
                     {
                         // Spin ROS for handling callbacks
                         rclcpp::spin_some(node_);
                     });
    this->spin_timer_.start();
}

void MainWindow::on_pushButton_clicked()
{
    QString text = ui->lineEdit->text();
    std::cout << text.toStdString() << std::endl;

    std_msgs::msg::String msg;
    msg.data = text.toStdString();

    // Publish the ROS message
    publisher_->publish(msg);
}