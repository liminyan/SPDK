/*
* Copyright (C) Mellanox Technologies Ltd. 2001-2015.  ALL RIGHTS RESERVED.
* See file LICENSE for terms.
*/


void ucp_get_version(unsigned *major_version, unsigned *minor_version,
                     unsigned *release_number)
{
    *major_version  = 1;
    *minor_version  = 8;
    *release_number = 1;
}

const char *ucp_get_version_string()
{
	return "1.8.1";
}
