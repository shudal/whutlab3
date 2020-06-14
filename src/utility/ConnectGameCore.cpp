//
// Created by perci on 2020/6/14.
//

#include "ConnectGameCore.h"

bool ConnectGameCore::link(std::vector<std::vector<int>> & v, std::pair<int, int> from, std::pair<int, int> to) {
  if (from.first == to.first && from.second == to.second) {
    return false;
  }
  if (v[from.first][from.second] != v[to.first][to.second]) {
    return false;
  }


  int rows = v.size(), cols = v[0].size();
  std::vector<std::vector<int>> v2(rows+2, std::vector<int>(cols+2, 0));
  /*
   * v1行从0到rows-1
   * v2行从0到rows+1
   *
   * v1列从0到cols-1
   * v2列从0到cols+1
   */
  for (int i=0; i<rows; i++) {
    for (int k=0; k<cols; k++) {
      v2[i+1][k+1] = v[i][k];
    }
  }


  ok = false;
  std::vector<std::pair<int,int>> path;
  this->to = {to.first+1, to.second+1};
  dfs(v2, path, {from.first+1, from.second+1});
  if (ok) {
    return true;
  } else {
    return false;
  }
}
void ConnectGameCore::dfs(std::vector<std::vector<int>> & v, std::vector<std::pair<int,int>> & path, std::pair<int, int> from) {
  if (ok) return;

  path.push_back(from);
  if (from.first==to.first && from.second==to.second) {
    bool b = validPath(path);
    if (b) {
      success_path = path;
      ok = true;
    }
    return;
  }

  for (int i=0; i<4; i++) {
    int subx = from.first + dx[i];
    int suby = from.second + dy[i];
    if (subx >= 0 && suby >= 0 && subx < v.size() && suby < v[0].size()) {
      if (subx == to.first && suby == to.second) {

      } else {
        if (v[subx][suby] != 0) {
          continue;
        }
      }

      bool b = true;
      for (auto p : path) {
        if (p.first == subx && p.second == suby) {
          b = false;
          break;
        }
      }
      if (b) {
        dfs(v, path, {subx, suby});
      }
    }
  }

  path.pop_back();
}
bool ConnectGameCore::validPath(std::vector<std::pair<int,int>> & path) {
  if (path.size() <= 2) {
    return true;
  }
  int last_dir = judgeDirection(path[0], path[1]);
  int dir_change = 0;
  for (int i=2; i<path.size(); i++) {
    int dir = judgeDirection(path[i-1], path[i]);
    if (dir != last_dir) {
      dir_change++;
      // 最多转两个弯
      if (dir_change > 3) {
        return false;
      }
    }
    last_dir = dir;
  }
  return true;
}
int ConnectGameCore::judgeDirection(std::pair<int,int> & from, std::pair<int,int> & to) {
  for (int i=0; i<4; i++) {
    int subx = from.first + dx[i];
    int suby = from.second + dy[i];
    if (to.first == subx && to.second == suby) {
      return i;
    }
  }
  return 0;
}
