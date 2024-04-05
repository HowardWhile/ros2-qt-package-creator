#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "std_msgs/msg/string.hpp"
#include "rclcpp/rclcpp.hpp"

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_btn_pub_clicked();

private:
    Ui::MainWindow *ui;

private:
    // -------------------------------------
    // ROS Components
    // -------------------------------------
    // node
    rclcpp::Node::SharedPtr node_;

    // ROS publisher
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;

    // ROS subscriber
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscriber_;

    // -------------------------------------
    // Spin Function
    // -------------------------------------
    void initSpin(void);
    QTimer spin_timer_;
    // -------------------------------------
};
#endif // MAINWINDOW_H
