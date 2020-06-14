//
// Created by perci on 2020/6/14.
//

#include "GameWidget.h"
#include <src/config/Config.h>
#include <src/utility/RandInt.h>
#include <thread>
GameWidget::GameWidget() {

  fruits.resize(Config::Get()->ROW_COUNT);
  for (int i=0; i<Config::Get()->ROW_COUNT; i++) {
    fruits[i].resize(Config::Get()->COL_COUNT);
  }
  setupUI();
  game_status = Config::Get()->GAME_STATUS_NOT_STARTED;
  processClick();
  timeCount();
}
void GameWidget::setupUI() {
  gw = std::make_unique<QWidget>();
  gw->resize(Config::Get()->WINDOW_WIDTH, Config::Get()->WINDOW_HEIGHT);

  window_title = std::make_unique<QString>(Config::Get()->MAIN_WINDOW_TITLE.c_str());
  gw->setWindowTitle(*window_title);
  window_icon = std::make_unique<QIcon>(Config::Get()->MAIN_ICON_SRC.c_str());
  gw->setWindowIcon(*window_icon);

  auto vLayout = new QVBoxLayout();
  gw->setLayout(vLayout);

  auto hLayout1 = new QHBoxLayout();
  timeLabel = new QLabel("时间");
  hLayout1->addWidget(timeLabel);
  auto helpBtn = new QPushButton("帮助");
  hLayout1->addWidget(helpBtn);

  auto hLayout2 = new QHBoxLayout();
  gridLayout = new QGridLayout();
  hLayout2->addLayout(gridLayout);
  auto vLayout2 = new QVBoxLayout();
  startGameBtn = new QPushButton("开始游戏");
  connect(startGameBtn, &QPushButton::released, [&]()->void {
    setRandomMap();
    applyMap();

    time_count = Config::Get()->GAME_LAST_SECONDS;
    game_status = Config::Get()->GAME_STATUS_STARTED;
    startGameBtn->setEnabled(false);
  });

  stopGameBtn = new QPushButton("暂停游戏");
  connect(stopGameBtn, &QPushButton::released, [&]()->void {
    if (game_status == Config::Get()->GAME_STATUS_STOPED) {
      game_status = Config::Get()->GAME_STATUS_STARTED;
      stopGameBtn->setText("暂停游戏");
    } else if (game_status == Config::Get()->GAME_STATUS_STARTED) {
      game_status = Config::Get()->GAME_STATUS_STOPED;
      stopGameBtn->setText("继续游戏");
    }
  });
  vLayout2->addWidget(startGameBtn);
  vLayout2->addWidget(stopGameBtn);
  hLayout2->addLayout(vLayout2);

  vLayout->addLayout(hLayout2);
  vLayout->addLayout(hLayout1);

  setRandomMap();
  applyMap();

  gw->show();
}
void GameWidget::setRandomMap() {
  RandInt ri(Config::Get()->FRUIT_IMG_ID_MIN, Config::Get()->FRUIT_IMG_ID_MAX);
  map_logic.resize(Config::Get()->ROW_COUNT);
  for (int i=0; i<Config::Get()->ROW_COUNT; i++) {
    map_logic[i].resize(Config::Get()->COL_COUNT);
    for (int k=0; k<Config::Get()->COL_COUNT; k++) {
      map_logic[i][k] = ri();
    }
  }
}
void GameWidget::applyMap() {
  int cell_h = (int) (Config::Get()->WINDOW_HEIGHT * 0.8 / Config::Get()->COL_COUNT);
  int cell_w = (int) (Config::Get()->WINDOW_WIDTH * 0.8 / Config::Get()->ROW_COUNT);
  int x = cell_w;
  if (cell_h < x) {
    x = cell_h;
  }
  for (int i=0; i<Config::Get()->ROW_COUNT; i++) {
    for (int k=0; k<Config::Get()->COL_COUNT; k++) {
      fruits[i][k] = new QPushButton();
      fruits[i][k]->setFixedSize(x,x);
      std::string ss = "border-image:url(static/img/";
      ss = ss + std::to_string(map_logic[i][k]);
      ss = ss + ".png);";
      fruits[i][k]->setStyleSheet(ss.c_str());
      connect(fruits[i][k], &QPushButton::released, [&,i,k]()->void {
        print("clicked, i=" + std::to_string(i) + ", k=" + std::to_string(k));
        clicks.push({i,k});
      });
      gridLayout->addWidget(fruits[i][k], i, k);
    }
  }
}
void GameWidget::print(std::string s) {
  qDebug(s.c_str());
}
void GameWidget::processClick() {
  qRegisterMetaType<std::function<void(void)>>("std::function<void(void)>");
  connect(this, &GameWidget::funcSignal, this, &GameWidget::funcSlot);
  std::thread t([&](GameWidget* gw)->void {
    static int clicked_count=0;
    while (true) {
      if (clicks.empty()) {
        // 100毫秒
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        continue;
      }
      auto p = clicks.front();
      clicks.pop();
      if (game_status != Config::Get()->GAME_STATUS_STARTED) {
        continue;
      }

      static int clicked_count = 0;
      static std::pair<int,int> c1;
      static std::pair<int,int> c2;
      if (clicked_count == 2) {
        clicked_count = 0;
        auto c3 = c1;
        auto c4 = c2;
        emit funcSignal([&, c3, c4]()->void {
          std::string ss;
          std::pair<int,int> c;

          c = c3;
          ss = "border-image:url(static/img/";
          ss = ss + std::to_string(map_logic[c.first][c.second]);
          ss = ss + ".png);";
          fruits[c.first][c.second]->setStyleSheet(ss.c_str());


          c = c4;
          ss = "border-image:url(static/img/";
          ss = ss + std::to_string(map_logic[c.first][c.second]);
          ss = ss + ".png);";
          fruits[c.first][c.second]->setStyleSheet(ss.c_str());
        });
      }
      clicked_count++;
      if (clicked_count == 1) {
        c1 = p;
      } else {
        c2 = p;

        auto c3 = c1;
        auto c4 = c2;
        std::thread t2([&,c3,c4]()->void {
          bool b = core.link(map_logic, c3, c4);
          print(std::to_string(b));
          if (b) {
            map_logic[c3.first][c3.second] = 0;
            map_logic[c4.first][c4.second] = 0;

            for (auto path_p : core.success_path) {
              int x = path_p.first - 1;
              int y = path_p.second - 1;
              emit funcSignal([&, x, y]()->void {
                if (x >= 0 && y >= 0 && x < fruits.size() && y < fruits[0].size()) {
                  std::string ss = "background-color: rgb(58,64,85);";
                  fruits[x][y]->setStyleSheet(ss.c_str());
                }
              });
            }
            std::thread t3([&]()->void {
              std::this_thread::sleep_for(std::chrono::milliseconds(500));
              for (auto path_p : core.success_path) {
                int x = path_p.first - 1;
                int y = path_p.second - 1;
                emit funcSignal([&, x, y]()->void {
                  if (x >= 0 && y >= 0 && x < fruits.size() && y < fruits[0].size()) {
                    std::string ss = "";
                    fruits[x][y]->setStyleSheet(ss.c_str());
                  }
                });
              }
            });
            t3.detach();
          }
        });
        t2.detach();
      }
      emit funcSignal([&, p]()->void {
        std::string ss = "background-color: rgb(58,64,85); border-image:url(static/img/";
        ss = ss + std::to_string(map_logic[p.first][p.second]);
        ss = ss + ".png);";
        fruits[p.first][p.second]->setStyleSheet(ss.c_str());
      });
    }
  }, this);
  t.detach();
}
void GameWidget::funcSlot(std::function<void(void)> f) {
  f();
}
void GameWidget::timeCount() {
  std::thread t([&]()->void {
    while (true) {
      if (game_status == Config::Get()->GAME_STATUS_STARTED) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        time_count--;
        if (time_count > 0) {
          emit funcSignal([&]()->void {
            std::string s = "剩余时间: " + std::to_string(time_count);
            timeLabel->setText(s.c_str());
          });
        } else {
          emit funcSignal([&]()->void {
            std::string s = "游戏结束";
            game_status = Config::Get()->GAME_STATUS_ENDED;
            timeLabel->setText(s.c_str());
          });
        }
      } else {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
      }
    }

  });
  t.detach();
}
