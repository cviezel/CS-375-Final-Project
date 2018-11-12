all: project

project: project.cpp
	g++ -g project.cpp -o submission

clean:
	rm submission
