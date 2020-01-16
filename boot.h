//
// Created by nahomamit on 14/01/2020.
//

#ifndef HW4GALANDAMIT__BOOT_H_
#define HW4GALANDAMIT__BOOT_H_
#include <iostream>
#include <string.h>
#include <fstream>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "Server_Side.h"
#include <queue>
using namespace Server_Side;
using namespace std;
#endif //HW4GALANDAMIT__BOOT_H_

bool flag = true;

class FileCacheManager: public CacheManager {
  virtual bool problemExist(string problem) {
    problem += ".txt";
    ifstream file;
    file.open(problem);
    if (file.is_open()) {
      file.close();
      return true;
    }
    return false;
  }

  virtual string getSolution(string problem) {
    string solution;
    problem += ".txt";
    ifstream file;
    file.open(problem);
    if (file.is_open()) {
      while (getline(file, solution));
      file.close();
      return solution;
    }
  }
  virtual void addSolution(string problem, Solver* solution) {
    problem += ".txt";
    ofstream file;
    file.open(problem);
    if (file.is_open()) {
      string solutionStr = solution->toString();
      file << solutionStr;
      file.close();
    }
  }

};

class MySerialServer: public Server {

  virtual void open(int port, ClientHandler* c) {
    queue<int> clientQueue;
    int clientSocket;
    char buffer[1024] = {0};
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
      cerr << "Could not create a Socket" << endl;
      //client_socket -1;
    }
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
      std::cerr << "could not bind the socket to an IP" << std::endl;
    }
    thread threadServer(MySerialServer::getClientInfo, port, &clientQueue, socketfd, address);
    sleep(12);
    while (!clientQueue.empty()) {
      read(clientQueue.front(), buffer, 1024);
      clientQueue.pop();
      cout << buffer << endl;
      if (strlen(buffer) != 0) {
        c->handleClient(buffer, "");
      }
    }
    threadServer.join();
  }

  static void getClientInfo(int port, queue<int>* queue, int socketfd, sockaddr_in address) {
    int client_socket;
    std::string::size_type sz;
    while (flag) {
      if (listen(socketfd, 5) == -1) {
        std::cerr << "error during listening" << std::endl;
        client_socket -2;
      }
      struct timeval tv;
      tv.tv_sec = 10;
      setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
      client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &address);
      if ((client_socket) < 0) {
        std::cerr << "error accepting client" << std::endl;
        flag = false;
      } else {
        queue->push(client_socket);
      }
    }
  }

  virtual void stop() {
    flag = false;
  }
};

class MyTestClientHandler: public ClientHandler {

 public:
  MyTestClientHandler(Solver* solver_, CacheManager* cache_manager_) : ClientHandler(solver_, cache_manager_) {}

  void handleClient(string input, string output) override {
    if (input == "end") {
      output = "end";
      return;
    } else {
      if (cm->problemExist(input)) {
        cout<<(cm->getSolution(input))<<endl;
      } else {
        Solver* solution = solver->solve(input);
        cout<<solution->toString() <<endl;
        cm->addSolution(input, solution);
      }
    }

  }
};

class StringReverser: public Solver {
  string solution = "";
 public:
  virtual Solver* solve(string problem) {
    for (int i = 0; i < problem.length() / 2; i++)
      swap(problem[i], problem[problem.length() - i - 1]);
    solution = problem;
    return this;
  }

  virtual string toString() {
    return solution;
  }


};