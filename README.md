ENTER EACH OF THESE COMMAND LINES IN THE TERMINAL: 

g++ producer_process.cpp -pthread -lrt -o producer_process
g++ consumer_process.cpp -pthread -lrt -o consumer_process

./producer_process & ./consumer_process