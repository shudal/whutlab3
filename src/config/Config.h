//
// Created by perci on 2020/6/14.
//

#ifndef COOK_SRC_CONFIG_CONFIG_H_
#define COOK_SRC_CONFIG_CONFIG_H_

#include <string>
class Config {
 public:
  static Config* Get () {
     static Config c;
     return &c;
   }

  const int WINDOW_WIDTH = 800;
  const int WINDOW_HEIGHT = 600;
  const std::string MAIN_WINDOW_BG = "bg.jpg";
  const std::string MAIN_WINDOW_TITLE = "快乐连连看";
  const std::string MAIN_ICON_SRC = "bg.jpg";
  int GAME_MODE = 0;
  const int GAME_MODE_NORMAL = 1;
  const int ROW_COUNT = 16;
  const int COL_COUNT = 16;
  const std::string FRUIT_IMG_SRC_PREFIX = "static/img/";
  const int FRUIT_IMG_ID_MIN = 1;
  const int FRUIT_IMG_ID_MAX = 12;
  const int GAME_STATUS_NOT_STARTED = 1;
  const int GAME_STATUS_STARTED = 2;
  const int GAME_STATUS_STOPED = 3;
  const int GAME_STATUS_ENDED = 4;
  const int GAME_LAST_SECONDS = 500;
};
#endif//COOK_SRC_CONFIG_CONFIG_H_
