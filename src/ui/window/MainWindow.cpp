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
  vLayout->addLayout(hLayout1);
  auto horizontalSpacer = new QSpacerItem(35, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

  auto btn1 = new QPushButton("普通模式");
  btn1->setStyleSheet("QPushButton {background-color: rgb(58,64,85); color:white; font-size:28px; border-radius:2px;} QPushButton:hover { background-color: rgb(82,89,111);}");
  connect(btn1, &QPushButton::released, [&]()->void{
    qDebug("hi");
    Config::Get()->GAME_MODE = Config::Get()->GAME_MODE_NORMAL;
    gw = std::make_unique<GameWidget>();
  });
  hLayout1->addItem(horizontalSpacer);
  hLayout1->addWidget(btn1);
  hLayout1->addItem(horizontalSpacer);

  mw->show();
}
