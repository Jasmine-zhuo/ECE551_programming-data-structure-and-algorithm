ALL: cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4
cyoa-step1:cyoa-step1.cpp cyoa.cpp cyoa.h
	g++ -Wall -Werror -pedantic -std=c++03 -o cyoa-step1 cyoa-step1.cpp cyoa.cpp
cyoa-step2:cyoa-step2.cpp cyoa.cpp cyoa.h
	g++ -Wall -Werror -pedantic -std=c++03 -o cyoa-step2 cyoa-step2.cpp cyoa.cpp
cyoa-step3:cyoa-step3.cpp cyoa.cpp cyoa.h
	g++ -Wall -Werror -pedantic -std=c++03 -o cyoa-step3 cyoa-step3.cpp cyoa.cpp
cyoa-step4:cyoa-step4.cpp cyoa.cpp cyoa.h
	g++ -Wall -Werror -pedantic -std=c++03 -o cyoa-step4 cyoa-step4.cpp cyoa.cpp
.PHONY: clean
clean:
	rm cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4 *.cpp~ *.txt~ 
