#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"
#include "myTcpClient.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    int yaw_head = 10;
    int yaw_grop_box = 10;
    const QStringList buad_data = {"2400","4800","9600","115200","460800","576000",
    "921600","1152000"};
    ui->setupUi(this);
    //标签创建并对齐
    lablel_type = new QLabel("选择传感器类型",this);
    lablel_mode = new QLabel("选择传输模式",this);

    stackedWidgetMode = new QStackedWidget(this);
    GropBoxUart = new QGroupBox("uart", this);
    GropBoxTCP = new QGroupBox("tcp", this);
    GropBoxBLE = new QGroupBox("ble", this);

    //TCP标签
    lablel_port = new QLabel("TCP 监听端口",GropBoxTCP);
    lablel_IP = new QLabel("TCP 设置IP",GropBoxTCP);
    //串口标签
    lablel_com = new QLabel("串口端口",GropBoxUart);
    lablel_baud = new QLabel("波特率",GropBoxUart);

    //创建下拉box
    combox_type = new QComboBox(this);
    combox_mode = new QComboBox(this);
    //tcp
    lineEdit_ip = new QLineEdit(GropBoxTCP);
    lineEdit_port = new QLineEdit(GropBoxTCP);
    //uart
    combox_com = new myComboBox(GropBoxUart);
    combox_baud = new QComboBox(GropBoxUart);

    //button
    open_button = new QPushButton(this);
    label_connect_state = new QLabel("未连接",this);

    // 创建正则表达式，用于匹配IP地址格式
    QRegExp ipRegex("^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}"
                         "(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
    // 创建正则表达式，用于匹配端口号格式（0-65535）
    QRegExp portRegex("^(6553[0-5]|655[0-2][0-9]|65[0-4][0-9]"\
                          "{2}|6[0-4][0-9]{3}|[1-5][0-9]{4}|[0-9]{1,4})$");

    // 创建QRegExpValidator实例，并设置正则表达式
    QRegExpValidator *validator = new QRegExpValidator(ipRegex, this);
    // 创建QRegExpValidator实例，并设置正则表达式
    QRegExpValidator *validator_port = new QRegExpValidator(portRegex, this);

    lineEdit_ip->setValidator(validator);
    lineEdit_port->setValidator(validator_port);

    lablel_type->setFont(QFont("Arial", 10)); // 设置字体和大小
    lablel_type->setStyleSheet("color: black;"); // 设置文字颜色
    lablel_type->setAlignment(Qt::AlignLeft); // 设置文字居中对齐

    lablel_mode->setFont(QFont("Arial", 10)); // 设置字体和大小
    lablel_mode->setStyleSheet("color: black;"); // 设置文字颜色
    lablel_mode->setAlignment(Qt::AlignLeft); // 设置文字左对齐




    //添加combox组件
    combox_type->addItem("放大器");
    combox_type->addItem("外部设备");

    combox_mode->addItem("蓝牙");
    combox_mode->addItem("TCP 服务端");
    combox_mode->addItem("串口");

    open_button->setText("打开连接");

    combox_baud->addItems(buad_data);

    lablel_type->setGeometry(10, yaw_head, 200, 50); // 设置标签的位置和大小
    yaw_head += 30;
    combox_type->setGeometry(10,yaw_head,200,30);
    yaw_head += 30;
    lablel_mode->setGeometry(10, yaw_head, 200, 50); // 设置标签的位置和大小
    yaw_head += 30;
    combox_mode->setGeometry(10,yaw_head,200,30);

    yaw_head += 30;
    stackedWidgetMode->setGeometry(10,yaw_head,400,400);

    yaw_grop_box = 10;
    lablel_com->setGeometry(10,yaw_grop_box,100,30);
    lablel_port->setGeometry(10,yaw_grop_box,100,30);

    yaw_grop_box += 30;
    lineEdit_port->setGeometry(10,yaw_grop_box,100,30);
    combox_com->setGeometry(10,yaw_grop_box,100,30);

    yaw_grop_box += 30;
    lablel_baud->setGeometry(10,yaw_grop_box,100,30);
    lablel_IP->setGeometry(10,yaw_grop_box,100,30);

    yaw_grop_box += 30;
    lineEdit_ip->setGeometry(10,yaw_grop_box,100,30);
    combox_baud->setGeometry(10,yaw_grop_box,100,30);

    open_button->setGeometry(200,yaw_grop_box,200,30);
    label_connect_state->setGeometry(200,yaw_grop_box+30,200,30);

    stackedWidgetMode->addWidget(GropBoxBLE);
    stackedWidgetMode->addWidget(GropBoxTCP);
    stackedWidgetMode->addWidget(GropBoxUart);


    myTcpClient = new MyTcpClient;



    connect(combox_mode, QOverload<int>::of(&QComboBox::activated),
            stackedWidgetMode, &QStackedWidget::setCurrentIndex);
    // 连接按钮的clicked信号到处理函数
    connect(open_button, &QPushButton::clicked, this,
                    &MainWindow::handleButtonClick);


}

MainWindow::~MainWindow()
{
    delete ui;
}


