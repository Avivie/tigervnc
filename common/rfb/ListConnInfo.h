/* Copyright (C) 2002-2003 RealVNC Ltd.  All Rights Reserved.
 *    
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,
 * USA.
 */


#ifndef __RFB_LISTCONNINFO_INCLUDED__
#define __RFB_LISTCONNINFO_INCLUDED__

#include <list>

#include <rfb/util.h>

namespace rfb {

  struct ListConnInfo  {
    ListConnInfo() : disableClients(false) {}

    void Clear() {
      conn.clear();
      id.clear();
      IP_address.clear();
      endpoint.clear();
      user.clear();
      time_conn.clear();
      status.clear();
    }

    bool Empty() { return conn.empty();}

    void iBegin() {
      ci = conn.begin();
      ii = id.begin();
      Ii = IP_address.begin();
      ei = endpoint.begin();
      ui = user.begin();
      ti = time_conn.begin();
      si = status.begin();
    }

    bool iEnd() { return ci == conn.end();}

    void iNext() {
      ci++;
      ii++;
      Ii++;
      ei++;
      ui++;
      ti++;
      si++;
    }

    void addInfo(void* Conn, int Id, char* IP, char* Endpoint, char *User,
                 char* Time, int Status) {
      conn.push_back(Conn);
      id.push_back(Id);
      IP_address.push_back(strDup(IP));
      endpoint.push_back(strDup(Endpoint));
      user.push_back(strdup(User));
      time_conn.push_back(strDup(Time));
      status.push_back(Status);
    }

    void iGetCharInfo(char* buf[3]) {
      buf[0] = *Ii;
      buf[1] = *ti;
      switch (*si) {
      case 0:
        buf[2] = strDup("Full control");
        break;
      case 1:
        buf[2] = strDup("View only");
        break;
      case 2:
        buf[2] = strDup("Stop updating");
        break;
      default:
        buf[2] = strDup("Unknown");
      }
    }

    void* iGetConn() { return *ci;}
    int iGetId() { return *ii;}
    char* iGetEndpoint() { return *ei;}
    char* iGetUser() { return *ui;}

    int iGetStatus() { return *si;}

    void iSetStatus(int istatus) { *si = istatus;}

    void Copy(ListConnInfo* InputList) {
      Clear();
      if (InputList->Empty()) return;
      for (InputList->iBegin(); !InputList->iEnd(); InputList->iNext()) {
        iAdd(InputList);
      }
      setDisable(InputList->getDisable());
    }

    void iAdd (ListConnInfo* InputList) {
      char* buf[3];
      InputList->iGetCharInfo(buf);
      // iGetCharInfo ??
      addInfo(InputList->iGetConn(), InputList->iGetId(), buf[0],
              InputList->iGetEndpoint(), InputList->iGetUser(), buf[1],
              InputList->iGetStatus());
    }

    void setDisable(bool disable) {disableClients = disable;}

    bool getDisable() {return disableClients;}

    void setAllStatus(int stat) {
      std::list<int>::iterator st;
      for (st = status.begin(); st != status.end(); st++)
        *st = stat;
    }

  private:
    std::list<void*> conn;
    std::list<int> id;
    std::list<char*> IP_address;
    std::list<char*> endpoint;
    std::list<char*> user;
    std::list<char*> time_conn;
    std::list<int> status;
    std::list<void*>::iterator ci;
    std::list<int>::iterator ii;
    std::list<char*>::iterator Ii;
    std::list<char*>::iterator ei;
    std::list<char*>::iterator ui;
    std::list<char*>::iterator ti;
    std::list<int>::iterator si;
    bool disableClients;
  };
};
#endif

