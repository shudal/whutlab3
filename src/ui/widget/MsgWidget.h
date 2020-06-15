//
// Created by perci on 2020/6/14.
//

#ifndef COOK_SRC_UI_WIDGET_MSGWIDGET_H_
#define COOK_SRC_UI_WIDGET_MSGWIDGET_H_

#include <Qt>
#include <QtCore/QObject>
#include <string>
#include <memory>
#include <QWidget>
class MsgWidget : public QObject {
 Q_OBJECT
 public:
  std::unique_ptr<QWidget> sw;
  MsgWidget(std::string);
 private:
  std::string msg;
};

#endif//COOK_SRC_UI_WIDGET_MSGWIDGET_H_
