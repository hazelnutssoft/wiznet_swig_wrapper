
swig -c++ -python wiznet.i
g++ -c -fPLC wiznet_wrap.cxx swig_wrapper.c rpi.c socket.c wizchip_conf.c W5500/w5500.c -I./W5500 /usr/include/python2.7
g++ -shared wiznet_wrap.o swig_wrapper.o rpi.o socket.o wizchip_conf.o w5500.o -o _wiznet.so -lbcm2835