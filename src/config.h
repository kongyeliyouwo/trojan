/*
 * This file is part of the trojan project.
 * Trojan is an unidentifiable mechanism that helps you bypass GFW.
 * Copyright (C) 2017-2019  GreaterFire
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <cstdint>
#include <map>
#include <boost/property_tree/ptree.hpp>
#include "log.h"

class Config {
public:
    enum RunType {
        SERVER,
        CLIENT,
        FORWARD
    } run_type;
    std::string local_addr;
    uint16_t local_port;
    std::string remote_addr;
    uint16_t remote_port;
    std::string target_addr;
    uint16_t target_port;
    std::map<std::string, std::string> password;
    bool append_payload;
    int udp_timeout;
    Log::Level log_level;
    class SSLConfig {
    public:
        bool verify;
        bool verify_hostname;
        std::string cert;
        std::string key;
        std::string key_password;
        std::string cipher;
        bool prefer_server_cipher;
        std::string sni;
        std::string alpn;
        bool reuse_session;
        bool session_ticket;
        long session_timeout;
        std::string plain_http_response;
        std::string curves;
        std::string dhparam;
    } ssl;
    class TCPConfig {
    public:
        bool prefer_ipv4;
        bool no_delay;
        bool keep_alive;
        bool fast_open;
        int fast_open_qlen;
    } tcp;
    class MySQLConfig {
    public:
        bool enabled;
        std::string server_addr;
        uint16_t server_port;
        std::string database;
        std::string username;
        std::string password;
    } mysql;
    void load(const std::string &filename);
    void populate(const std::string &JSON);
    bool sip003();
    static std::string SHA224(const std::string &message);
private:
    void populate(const boost::property_tree::ptree &tree);
};

#endif // _CONFIG_H_
