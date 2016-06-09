All:
	@echo "compile with otimization:  make YES"
	@echo "compile without otimization:  make NO"
	@echo "compile for debbug:  make DEBBUG"
YES:
	@echo "Compiling ..."
	@g++ -std=c++11 -O3 -I include src/main.cpp -o bin/gremlins
	@echo "finished."
NO:
	@echo "Compiling ..."
	@g++ -std=c++11 -I include src/main.cpp -o bin/gremlins
	@echo "finished."
DEBBUG:
	@echo "Compiling ..."
	@g++ -std=c++11 -Wall -g -O0 -I include src/main.cpp -o bin/gremlins
	@echo "finished."