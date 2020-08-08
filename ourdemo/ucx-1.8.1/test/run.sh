module add cosmo/changa/3.3-ucxml-2.4.0-intel-2018.5.274
export LD_LIBRARY_PATH=/global/home/users/liyiyuan/exe3/ucx-1.8.1/install/lib
gcc examples/CS.c -lm -lucp -lucs -o ucp_client_server -I/global/home/users/liyiyuan/exe3/ucx-1.8.1/src -I../install/include -L../install/lib
