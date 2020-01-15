
#include "boot.h"
using namespace Server_Side;
using namespace std;




int main(int argc, char **argv) {
  Server* server = new MySerialServer();
  Solver* solver = new StringReverser();
  CacheManager* cache_manager = new FileCacheManager();
  ClientHandler* client_handler = new MyTestClientHandler(solver, cache_manager);
  int port = stoi(argv[1]);
  server->open(port, client_handler);
  return 0;
}
