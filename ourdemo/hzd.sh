module add cosmo/changa/3.3-ucxml-2.4.0-intel-2018.5.274
export LD_LIBRARY_PATH=/global/home/users/rdmaworkshop12/SPDK/ourdemo/ucx-1.8.1/install/lib
gcc server.c -lm -lucp -lucs -o ucp_client_server -I/global/home/users/rdmaworkshop12/SPDK/ourdemo/ucx-1.8.1/src -I/global/home/users/rdmaworkshop12/SPDK/ourdemo/install/include -L/global/home/users/rdmaworkshop12/SPDK/ourdemo/install/lib
