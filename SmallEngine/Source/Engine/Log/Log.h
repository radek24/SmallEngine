#pragma once
#include <spdlog/spdlog.h>
#include "Engine/Core.h"

class SE_API Log {
private:
    static std::shared_ptr<spdlog::logger> s_Logger;

public:
    static void Initialize();
    [[nodiscard]] static inline std::shared_ptr<spdlog::logger>& GetLogger(){return s_Logger;}
};

#define LOG_INFO(...) Log::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...) Log::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) Log::GetLogger()->error(__VA_ARGS__)
#define LOG_DEBUG(...) Log::GetLogger()->debug(__VA_ARGS__)
#define LOG_FATAL(...) Log::GetLogger()->critical(__VA_ARGS__)
