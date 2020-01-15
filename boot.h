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
using namespace Server_Side;
using namespace std;
#endif //HW4GALANDAMIT__BOOT_H_


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
  bool flag = true;

  virtual void open(int port, ClientHandler* c) {
    thread threadServer(MySerialServer::openServer, port, c);
    threadServer.join();
  }

  virtual void stop() {
    flag = false;
  }

  static void openServer(int port, ClientHandler* c) {
    int clientSocket;
    char buffer[1024] = {0};

    clientSocket = getClientInfo(port);
    read(clientSocket, buffer, 1024);
    cout << buffer << endl;
    if (strlen(buffer) != 0) {
      c->handleClient(buffer, "");
    }
  }


  static int getClientInfo(int port) {
    std::string::size_type sz;
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
      cerr << "Could not create a Socket" << endl;
      return -1;
    }
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
      std::cerr << "could not bind the socket to an IP" << std::endl;
      return -1;
    }
    if (listen(socketfd, 5) == -1) {
      std::cerr << "error during listening" << std::endl;
      return -2;
    }
    int client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &address);
    if ((client_socket) < 0) {
      std::cerr << "error accepting client" << std::endl;
      return -3;
    }
    return client_socket;
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