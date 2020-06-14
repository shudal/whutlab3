//
// Created by perci on 2020/6/14.
//

#ifndef COOK_SRC_UTILITY_CONNECTGAMECORE_H_
#define COOK_SRC_UTILITY_CONNECTGAMECORE_H_

#include <vector>
class ConnectGameCore {
 public:
  std::vector<std::pair<int,int>> success_path;
  // v的行列都是从0开始
  bool link(std::vector<std::vector<int>> &, std::pair<int,int>, std::pair<int,int>);
 private:
  int dx[4] = {0, 0, 1, -1};
  int dy[4] = {1, -1, 0, 0};
  bool ok;
  std::pair<int,int> to;
  // dfs的地图应该 在水果地图外面围一圈
  void dfs(std::vector<std::vector<int>> &, std::vector<std::pair<int,int>> &, std::pair<int,int>);
  bool validPath(std::vector<std::pair<int,int>> &);
  int judgeDirection(std::pair<int,int> &, std::pair<int,int> &);
};

#endif//COOK_SRC_UTILITY_CONNECTGAMECORE_H_
