#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <memory>

std::shared_ptr<spdlog::logger> g_default_logger;

#define DEBUG(format, ...) g_default_logger->debug(std::string("[{} : {}]") + format, __FILE__, __LINE__, ##__VA_ARGS__);
#define ERROR(format, ...) g_default_logger->error(std::string("[{} : {}]") + format, __FILE__, __LINE__, ##__VA_ARGS__);

void init_logger()
{
    g_default_logger = spdlog::stdout_color_mt<spdlog::async_factory>("g_default_logger");  
    g_default_logger->set_level(spdlog::level::level_enum::trace);
    g_default_logger->flush_on(spdlog::level::level_enum::trace);
    g_default_logger->set_pattern("[%n][%H:%M:%S][%t][%-8l] %v");
    g_default_logger->debug("hello{}", 1);
}
