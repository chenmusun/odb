CC=g++
CFLAGS= -std=c++11
objects = kpi_database_manager.o kpi_test.o
object	= kpi_view-odb.o
all:$(objects) $(object)
	g++ -std=c++11 -o kpi_test $(objects) $(object) -lodb-mysql -lodb
$(objects): %.o: %.cpp
	$(CC) -c -g $(CFLAGS) $< -o $@
$(object): %.o: %.cxx
	$(CC) -c -g $(CFLAGS) $< -o $@
clean:
	rm -f *.o kpi_test
