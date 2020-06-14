//
// Created by perci on 2020/6/14.
//

#ifndef COOK_SRC_UI_WINDOW_MAINWINDOW_H_
#define COOK_SRC_UI_WINDOW_MAINWINDOW_H_

#include <src/ui/widget/GameWidget.h>

#include <Qt>
#include <QtCore/QObject>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <memory>
class MainWindow : public QObject {
  Q_OBJECT
 public:
  MainWindow();

 private:
  std::unique_ptr<QPixmap> bkgnd;
  std::unique_ptr<QPalette> palette;
  std::unique_ptr<QMainWindow> mw;
  std::unique_ptr<QString> window_title;
  std::unique_ptr<QIcon> window_icon;
  std::unique_ptr<QWidget> central_widget;
  std::unique_ptr<GameWidget> gw;
  void setupUi();
};

#endif//COOK_SRC_UI_WINDOW_MAINWINDOW_H_
