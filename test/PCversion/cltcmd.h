
/*
 * Copyright (C) 2015 Fang-Kuei Hsieh
 *
 * This file is part of Hanitu.
 *
 * Hanitu is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Hanitu is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef CLTCMD_H
#define CLTCMD_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> /*用來定址 address family*/
#include <sys/types.h>
#include <netinet/tcp.h>
#include <netinet/in.h> /*用於in addr_t Address*/
#include <arpa/inet.h>
#include <netdb.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include <sys/stat.h>
#include <math.h>

#define SrvIP "127.0.0.1"
#define DefaultPort "8889"


static int sockfd=-1;
static struct sockaddr_in dest;
static std::string PORT = "-1";

int CltInit();
void CltClose();
void CltSigHdl(int);
char *CltCmd(char*, char*, char*);

#endif 





