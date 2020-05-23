#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <string>
#include <memory>

#include "spdlog/spdlog.h"

#include "component.h"
#include "component_array.h"

#define SLOG_TRACE(...) SPDLOG_LOGGER_TRACE(&logger, __VA_ARGS__)
#define SLOG_DEBUG(...) SPDLOG_LOGGER_DEBUG(&logger, __VA_ARGS__)
#define SLOG_ERROR(...) SPDLOG_LOGGER_ERROR(&logger, __VA_ARGS__)
#define SLOG_WARN(...) SPDLOG_LOGGER_WARN(&logger, __VA_ARGS__)
#define SLOG_CRITICAL(...) SPDLOG_LOGGER_CRITICAL(&logger, __VA_ARGS__)
#define SLOG_INFO(...) SPDLOG_LOGGER_INFO(&logger, __VA_ARGS__)

class System
{
public:
    System():
        logger("default_log", {}) 
    {    
    }

    virtual void init_update() {};
    virtual void update(double dt) = 0;

    void _pre_init(std::function<ComponentArrayBase*(CompType)> f)
    {
        get_array_base = f;
    }

    CompType get_type() const
    {
        return _type;
    }
    template <class CompType>
    std::vector<CompType>& get_array()
    {
        return dynamic_cast<ComponentArray<CompType>*>(get_array_base(type_id<CompType>))->_array;
    } 

    std::string& get_type_name()
    {
        return _type_name;
    }

    std::string _type_name = "default";
    
    void _set_log_sinks(std::vector<std::shared_ptr<spdlog::sinks::sink>> in_sinks)
    {
        _sys_file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/" + _type_name + ".txt", true);
        _sys_file_sink->set_level(spdlog::level::trace);
        _sys_console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        _sys_console_sink->set_level(spdlog::level::info);
        _sys_console_sink->set_pattern(std::string("[") + _type_name + "] [%^%l%$] %v");
        in_sinks.push_back(_sys_file_sink); 
        in_sinks.push_back(_sys_console_sink); 
        logger = spdlog::logger(_type_name + "_log", in_sinks.begin(), in_sinks.end());
        logger.set_level(spdlog::level::trace);
        SLOG_TRACE("TEST!");
    }

protected:
    CompType _type;
    std::function<ComponentArrayBase*(CompType)> get_array_base;
    spdlog::logger logger;
    std::shared_ptr<spdlog::sinks::basic_file_sink_mt> _sys_file_sink;
    std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> _sys_console_sink;
};

#endif  // SYSTEM_H_
