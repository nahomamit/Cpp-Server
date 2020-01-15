//
// Created by nahomamit on 14/01/2020.
//

#include <string>
#ifndef HW4GALANDAMIT__SERVER_SIDE_H_
#define HW4GALANDAMIT__SERVER_SIDE_H_
using namespace std;

#endif //HW4GALANDAMIT__SERVER_SIDE_H_

namespace Server_Side {

class Solver {
 public:
  virtual Solver* solve(string problem) = 0;
  virtual string toString() = 0;
};

class CacheManager {
 public:

  virtual bool problemExist(std::string problem) = 0;
  virtual string getSolution(std::string problem) = 0;
  virtual void addSolution(std::string problem, Solver* solution) = 0;

};

class ClientHandler {
 protected:
  CacheManager* cm;
  Solver* solver;
 public:
  ClientHandler(Solver* solver1, CacheManager* cache_manager) : solver(solver1), cm(cache_manager) {}
  virtual void handleClient(string input, string output) = 0;
};

class Server {
 public:
  virtual void open(int port, ClientHandler* c) = 0;
  virtual void stop() = 0;
};


}