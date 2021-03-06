/**
 * Copyright © 2020 AR-Fi Tech Ltd. https://www.ar-fi.com
 * 
 * Project:       SyncMount
 * Filename:      loggers.h
 * Author(s):     Stanislav Silnicki
 * Licence:       GPLv3
 * 
 **/

#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <map>
#include "options.h"
#include <chrono>

class AbstractLogger
{
public:
    AbstractLogger() : ready(false) {}
    AbstractLogger(const AbstractLogger &) = delete;
    AbstractLogger &operator=(const AbstractLogger &) = delete;
    bool isReady() { return ready; }
    virtual void Write(const std::string &, const std::string &) = 0;
    virtual void Init(const config_options_t &) = 0;
    virtual void DeInit() {}

protected:
    bool ready;
};

class Console : public AbstractLogger
{
public:
    void Init(const config_options_t &) override;
    void Write(const std::string &, const std::string &) override;
};

class LogFile : public AbstractLogger
{
public:
    void Init(const config_options_t &) override;
    void Write(const std::string &, const std::string &) override;

private:
    std::string filename;
};

class Syslog : public AbstractLogger
{
public:
    void Init(const config_options_t &) override;
    void Write(const std::string &, const std::string &) override;
    void DeInit() override;
};

class MQueue : public AbstractLogger
{
public:
    MQueue() : mq_fd(-1) {}
    void Init(const config_options_t &) override;
    void Write(const std::string &, const std::string &) override;
    void DeInit() override;

private:
    std::string mqueue_name;
    int mq_fd;
};
