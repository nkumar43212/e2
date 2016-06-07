//
//  CmdOptions.hpp
//  e2
//
//  Created by NITIN KUMAR on 6/6/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#ifndef CmdOptions_hpp
#define CmdOptions_hpp

#include <stdio.h>
#include <string>

class CmdOptions {
    // Where logs should go
    char *_logfile;
    
    // Server connectivity options
    std::string _server_ip;
    u_int16_t   _server_port;
    
    bool _file_mode;
    char *_system_file_name;
    
    bool _null_mode;
    bool _proc_mode;
    
    char *_ini_config_file;
    
public:
    CmdOptions() {
        _logfile = NULL;
        _system_file_name = NULL;
        _file_mode = _null_mode = _proc_mode = false;
        _ini_config_file = NULL;
    }
    
    ~CmdOptions() {
    }
    
    char *      getLogFile(void)                { return _logfile;             }
    const char *getServerIpAddress(void)        { return _server_ip.c_str();   }
    uint16_t    getServerPort(void)             { return _server_port;         }
    
    char *getSystemFileName(void)   { return _system_file_name; }
    bool isSystemModeNull(void)     { return _null_mode; }
    bool isSystemModeProc(void)     { return _proc_mode; }
    bool isSystemModeFile(void)     { return _file_mode; }
    char *getIniConfigFile(void)    { return _ini_config_file; }
    
    void setLogFile(std::string logfile);
    void setFileMode(bool mode);
    void setFileName(std::string file);
    void setServerPort(u_int16_t port)                 { _server_port = port; }
    void setServerIpAddress(const std::string address) { _server_ip   = address; }
    void setNullMode(bool mode);
    void setProcMode(bool mode);
    void setINIConfigFile(std::string ini_config_file);
    void printUsage(void);
    bool parseArgs(int argc, const char *argv[]);
    void resetArgs(void);
};



#endif /* CmdOptions_hpp */
