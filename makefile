CC = g++ 
lib= /usr/local/lib
wwh:datestring.o -lpthread globalFunction.o RowObject.o RowBean.o ODBCDao.o 
	$(CC) -L$(lib) -ltrafodbc64 -o $@ $^
datestring.o:datestring.cpp
	g++ -g -c datestring.cpp
globalFunction.o:globalFunction.cpp
	g++ -g -c globalFunction.cpp
RowObject.o:RowObject.cpp
	g++ -g -c  RowObject.cpp
RowBean.o:RowBean.cpp
	g++ -g -c  RowBean.cpp
ODBCDao.o:ODBCDao.cpp
	g++ -g -c ODBCDao.cpp 
clean:
	rm wwh datestring.o RowObject.o RowBean.o ODBCDao.o globalFunction.o 	
