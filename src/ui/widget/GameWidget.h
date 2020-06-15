//
// Created by perci on 2020/6/14.
//

#ifndef COOK_SRC_UI_WIDGET_GAMEWIDGET_H_
#define COOK_SRC_UI_WIDGET_GAMEWIDGET_H_

#include <src/utility/ConnectGameCore.h>
#include <Qt>
#include <QtCore/QObject>
#include <QtWidgets>
#include <memory>
#include <vector>
#include <queue>
class GameWidget : public QObject {
  Q_OBJECT
 public:
  GameWidget();
 private:
  std::unique_ptr<QWidget> gw;

  std::unique_ptr<QString> window_title;
  std::unique_ptr<QIcon> window_icon;
  QGridLayout* gridLayout;
  QLabel* timeLabel;
  QPushButton* stopGameBtn;
  QPushButton* startGameBtn;
  QPushButton* tipBtn;
  std::vector<std::vector<QPushButton*>> fruits;
  std::vector<std::vector<int>> map_logic;
  std::queue<std::pair<int,int>> clicks;
  int game_status;
  ConnectGameCore core;
  int time_count;
  std::pair<int,int> tip_from;
  std::pair<int,int> tip_to;

  void setupUI();
  void setRandomMap();
  void applyMap();
  void print(std::string);
  void processClick();
  void timeCount();
  void avaTest();

  signals:
  void funcSignal(std::function<void(void)>);
  public slots:
  void funcSlot(std::function<void(void)>);
};

#endif//COOK_SRC_UI_WIDGET_GAMEWIDGET_H_
