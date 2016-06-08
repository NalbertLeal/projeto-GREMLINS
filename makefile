All:
	@echo "Compiling ..."
	@g++ -std=c++11 -g -I include src/main.cpp -o bin/gremlins
	@echo "finished."
