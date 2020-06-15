//
// Created by perci on 2020/6/14.
//

#include "MsgWidget.h"
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QIcon>
#include <src/config/Config.h>
MsgWidget::MsgWidget(std::string s) {
  msg = s;
  sw = std::make_unique<QWidget>();
  auto l = new QVBoxLayout();
  auto h = new QHBoxLayout();

  auto horizontalSpacer = new QSpacerItem(35, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  h->addItem(horizontalSpacer);
  auto label = new QLabel();
  label->setText(msg.c_str());
  label->setStyleSheet("font-size:50px; font: bold; color:white");
  h->addWidget(label);
  h->addItem(horizontalSpacer);
  l->addLayout(h);
  sw->setStyleSheet("background-color: rgb(43,43,43);");
  sw->setLayout(l);

  sw->setWindowTitle(Config::Get()->MAIN_WINDOW_TITLE.c_str());
  auto window_icon = std::make_unique<QIcon>(Config::Get()->MAIN_ICON_SRC.c_str());
  sw->setWindowIcon(*window_icon);

  sw->resize(400,300);
  sw->show();
}
