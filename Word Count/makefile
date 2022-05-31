# CS315 Makefile for Program 4: Word Counter
# Feel free to modify as needed.
# Original author: Raphael Finkel 3/2020

CFLAGS = -Wall -g
CPPFLAGS = -Wall -g
GOAL = wordCount
DATA = data.txt
WORKING = workingWordCount

# compile and run the student program, placing the result in tmpRun.out
run: $(GOAL) $(DATA)
	./$(GOAL) < $(DATA) > tmpRun.out
	less tmpRun.out

zipAll: 
	zip toSubmit.zip $(GOAL).* Makefile README tmpRun.out
	
.PHONY: clean
clean:
	rm -f $(GOAL) $(DATA) tmp* toSubmit.zip