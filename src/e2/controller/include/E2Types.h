//
//  E2Types.h
//  e2
//
//  Created by NITIN KUMAR on 6/8/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#ifndef E2Types_h
#define E2Types_h

#define EOK     0
#define EFAIL  -1

typedef int status_t;


typedef std::map<std::string, std::string> ElementOpstateList;
typedef std::map<std::string, std::string>::iterator ElementOpstateListIterator;

#endif /* E2Types_h */
