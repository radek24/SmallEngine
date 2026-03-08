//
// Created by Radovan Šťastný on 08.09.2025.
//

#include "Log.h"
#include <spdlog/sinks/stdout_color_sinks.h>

std::shared_ptr<spdlog::logger> Log::s_Logger;

void Log::Initialize()
{
    spdlog::set_pattern("%^[%T:%e] %n: %v%$");
    s_Logger = spdlog::stdout_color_mt("SmallEngine");
    s_Logger->set_level(spdlog::level::trace);
    LOG_INFO("Successfully initialized logging");
}
