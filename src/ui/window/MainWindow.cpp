//
// Created by perci on 2020/6/14.
//

#include "MainWindow.h"
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <src/config/Config.h>
MainWindow::MainWindow() {
  setupUi();
}
void MainWindow::setupUi() {
  mw = std::make_unique<QMainWindow>();
  mw->resize(Config::Get()->WINDOW_WIDTH, Config::Get()->WINDOW_HEIGHT);


  bkgnd = std::make_unique<QPixmap>(Config::Get()->MAIN_WINDOW_BG.c_str());
  *bkgnd = bkgnd->scaled(mw->size(), Qt::IgnoreAspectRatio);
  palette = std::make_unique<QPalette>();
  palette->setBrush(QPalette::Background, *bkgnd);
  mw->setPalette(*palette);

  window_title = std::make_unique<QString>(Config::Get()->MAIN_WINDOW_TITLE.c_str());
  mw->setWindowTitle(*window_title);
  window_icon = std::make_unique<QIcon>(Config::Get()->MAIN_ICON_SRC.c_str());
  mw->setWindowIcon(*window_icon);

  central_widget = std::make_unique<QWidget>();
  mw->setCentralWidget(central_widget.get());

  auto vLayout = new QVBoxLayout(central_widget.get());

  auto hLayout1 = new QHBoxLayout();
  auto horizontalSpacer = new QSpacerItem(35, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

  std::string btn_style = "QPushButton {background-color: rgb(58,64,85); color:white; font-size:28px; border-radius:2px;} QPushButton:hover { background-color: rgb(82,89,111);}";
  auto btn1 = new QPushButton("普通模式");
  btn1->setStyleSheet(btn_style.c_str());
  connect(btn1, &QPushButton::released, [&]()->void{
    qDebug("hi");
    Config::Get()->GAME_MODE = Config::Get()->GAME_MODE_NORMAL;
    gw = std::make_unique<GameWidget>();
  });
  auto btn2 = new QPushButton("休息模式");
  auto btn3 = new QPushButton("关卡模式");
  btn2->setStyleSheet(btn_style.c_str());
  btn3->setStyleSheet(btn_style.c_str());
  auto vLayout2 = new QVBoxLayout();
  vLayout2->addWidget(btn1);
  vLayout2->addWidget(btn2);
  vLayout2->addWidget(btn3);
  hLayout1->addItem(horizontalSpacer);
  hLayout1->addLayout(vLayout2);
  hLayout1->addItem(horizontalSpacer);

  auto hLayout2 = new QHBoxLayout();
  auto btn4 = new QPushButton("排行榜");
  auto btn5 = new QPushButton("设置");
  auto btn6 = new QPushButton("帮助");
  btn4->setStyleSheet(btn_style.c_str());
  btn5->setStyleSheet(btn_style.c_str());
  btn6->setStyleSheet(btn_style.c_str());
  hLayout2->addItem(horizontalSpacer);
  hLayout2->addWidget(btn4);
  hLayout2->addWidget(btn5);
  hLayout2->addWidget(btn6);

  vLayout->addLayout(hLayout1);
  vLayout->addLayout(hLayout2);
  mw->show();
}
