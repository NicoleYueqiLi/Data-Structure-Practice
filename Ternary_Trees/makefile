# CS315 Makefile for Program 2: ternary
# Feel free to modify as needed.
# Original author: Raphael Finkel 1/2020

CFLAGS = -Wall -g
CPPFLAGS = -Wall -g
GOAL = ternary

NUMPOINTS = 1000
SEED = 49
LIMIT = 10000


# compile and run the student program, placing the result in tmpRun.out
run: $(GOAL) randGen.pl
	./randGen.pl $(SEED) $(LIMIT) | ./$(GOAL) $(NUMPOINTS) > tmpRun.out
	less tmpRun.out

# compile and run a known working program, placing the result in tmpWorking.out
#runWorking: workingTernary randGen.pl
#	less tmpWorking.out

# get the randGen.pl program
#randGen.pl:
#	wget http://www.cs.uky.edu/~raphael/courses/CS315/utils/randGen.pl
#	chmod +x randGen.pl

# get the workingTernary program
#workingTernary:
#	wget http://www.cs.uky.edu/~raphael/courses/CS315/prog2/workingTernary
#	chmod +x workingTernary

# Modify the following recipe to zip exactly what you want to include.
zipAll: 
	zip toSubmit.zip $(GOAL).cpp Makefile README tmpRun.out
	
.PHONY: clean
clean:
	rm -f randGen.pl $(GOAL) workingTernary tmp* toSubmit.zip
