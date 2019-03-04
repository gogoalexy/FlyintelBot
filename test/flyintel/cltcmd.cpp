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

#include "cltcmd.h"

using namespace std;

  int CltInit()
  {
    if(PORT == "-1") 
    	PORT = DefaultPort;  
   
    char buf32[32];
  
    if (sockfd == -1)
    {
      /* create socket */
      sockfd = socket(AF_INET, SOCK_STREAM, 0);
      
      if(sockfd != -1)
      {
	      /* initialize value in dest */
	      //bzero(&dest, sizeof(dest));
	      memset(&dest,0,sizeof(dest));
	      dest.sin_family = AF_INET;
	      dest.sin_port = htons(atoi(PORT.c_str()));
	      inet_aton(SrvIP, &dest.sin_addr);
	  
	      /* Connecting to server */
	     // connect(sockfd, (struct sockaddr*)&dest, sizeof(dest));
	      if(connect(sockfd, (struct sockaddr*)&dest, sizeof(dest))>=0)
	      {
		      int flag = 1; 
		      setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, (char *) &flag, sizeof(int));      /* Receive server acknowledge message */
		      read(sockfd, buf32, sizeof(buf32));
		      cout<<buf32<<endl;
		      memset(buf32,0,32);
	      }
	      else
	      {
	      		sockfd=-1;
	      }
      }
    }
    return sockfd;
  }
  
  void CltClose()
  {
    if(sockfd >= 0)
    {
      char buf32[32];
      memset(buf32,0,32);
      strcpy(buf32, "END_CLIENT");
      write(sockfd,buf32,sizeof(buf32));
  
      close(sockfd);
      sockfd = -1;
    }
  }
  
  void CltSigHdl(int sig)
  {
   printf("CltSigHdl caught signal %d\n",sig);
   CltClose();
   exit(sig);
  }

  char *CltCmd(char *cmd,char *s1,char *s2)
  {
    char buf16[16];
    char buf32[32];
    int rval=0;
    string str;
    char *dstr=nullptr;
  
  
  
    if(sockfd >=0)
    {
    /*sent command to server*/
    strcpy(buf32,cmd);
    write(sockfd,buf32,sizeof(buf32));
    memset(buf32,0,32);
  
      if(strcmp(cmd,"FILE_WRITE")==0)
      {
        /*sent file name to server*/
        strcpy(buf32,s1); //buf32=s1=filename
        write(sockfd,buf32,sizeof(buf32));
  
        /* Send file*/
        ifstream fin;
        fin.open(buf32);
  
        if(fin)
        {
          while(!fin.eof())
          {
            fin.get(buf16,15,EOF);
            write(sockfd,buf16,sizeof(buf16));
          }
  
        /*send end command to server*/
        memset(buf16,0,16);
        strcpy(buf16, "END_FILE_WRITE");
        write(sockfd,buf16,sizeof(buf16));
        }
        else
        { cout<<"open file error!"<<endl; }
  
        fin.close();
      }
      else if(strcmp(cmd,"FILE_SEND")==0) //???????????
      {
        /*sent file name to server*/
        strcpy(buf32,s1); //buf32=s1=filename
        write(sockfd,buf32,sizeof(buf32));
        memset(buf32,0,32);
  
        /* Send s2*/
        int length=0,count=0;
        string str=s2;

        while((length = str.copy(buf32,31,count))>0)
        {
          buf32[length]='\0';
          write(sockfd,buf32,sizeof(buf32));
          count+=length;
          memset(buf32,0,32);
        }

        /*send end command to server*/
        memset(buf32,0,32);
        strcpy(buf32, "END_FILE_SEND");
        write(sockfd,buf32,sizeof(buf32));
      }
      else if(strcmp(cmd,"FILE_READ")==0)
      {
        /*sent file name to server*/
        strcpy(buf32,s1); //buf32=s1=filename
        write(sockfd,buf32,sizeof(buf32));
  
        /* Receive message from the server and print to screen */
        ofstream fo;
        fo.open(buf32);
  
        while( (rval=read(sockfd, buf16, sizeof(buf16))) > 0  )
        {
          if(strcmp(buf16,"END_FILE_READ")==0) { break; }
          fo<<buf16;
          memset(buf16,0,16);
        }
  
        fo.close();
      }
      else if(strcmp(cmd,"ADD_WORM")==0)
      {
        /*sent conf file name to server*/
        strcpy(buf32,s1); //buf32=s1=filename
        write(sockfd,buf32,sizeof(buf32));
  
        /*wait server end command*/
        memset(buf32,0,32);
        read(sockfd, buf32, sizeof(buf32));
        cout<<buf32<<endl;
      }
      else if(strcmp(cmd,"DEL_WORM")==0)
      {
        /*sent WID to server*/
        strcpy(buf32,s1);
        write(sockfd,buf32,sizeof(buf32));
  
        /*wait server end command*/
        memset(buf32,0,32);
        read(sockfd, buf32, sizeof(buf32));
        cout<<buf32<<endl;
      }
      else if(strcmp(cmd,"DO_EVENTS")==0)
      {
        /*sent pro name to server*/
        strcpy(buf32,s1); //buf32=s1=filename
        write(sockfd,buf32,sizeof(buf32));

        /*sent WID to server*/
        memset(buf32,0,32);
        strcpy(buf32,s2);
        write(sockfd,buf32,sizeof(buf32));
  
        /*wait server end command*/
        memset(buf32,0,32);
        read(sockfd, buf32, sizeof(buf32));
        cout<<buf32<<endl;
  
      }
      else if(strcmp(cmd,"DATA_READ")==0)
      {
        /*sent data type to server*/
        strcpy(buf32,s1);
        write(sockfd,buf32,sizeof(buf32));

        if(
            !strcmp(s1,"Membrane_Potential_Header") ||
            !strcmp(s1,"Spikes_Header")
          )
        {
          while( (rval=read(sockfd, buf32, sizeof(buf32))) > 0  )
          {
            str+=buf32;
            if(strcmp(buf32,"END_DATA_HEADER")==0) { break; }
            memset(buf32,0,32);
  
          }
        }
        else if(
                 !strcmp(s1,"Membrane_Potential_Cont") ||
                 !strcmp(s1,"Spikes_Cont")
               )
        {
          /*sent repeat times to server*/
          memset(buf32,0,32);
          strcpy(buf32,s2);
          write(sockfd,buf32,sizeof(buf32));

          while( (rval=read(sockfd, buf32, sizeof(buf32))) > 0  )
          {
            str+=buf32;
            if(strcmp(buf32,"END_DATA_READ")==0) { break; }
            memset(buf32,0,32);
  
          }
        }
        else //single step Membrane_Potential & Spikes
        {
          while( (rval=read(sockfd, buf32, sizeof(buf32))) > 0  )
          {
            str+=buf32;
            if(strcmp(buf32,"END_DATA_READ")==0) { break; }
            memset(buf32,0,32);
  
          }
        }
  
        dstr = (char *) malloc(str.size()+1);
        strcpy(dstr,str.c_str());
        dstr[str.size()]='\0';
      }
    }
    else
    {  cout<<"socket error"<<endl;  }
  
    return dstr;
  }





