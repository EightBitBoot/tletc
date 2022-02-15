#ifndef __LOG_H__
#define __LOG_H__

#include <string>
#include <vector>

#include <stdio.h>
#include <stdarg.h>

#define TLETC_DEFAULT_LOG_LEVEL tletc::LogLevel::LOG_LEVEL_INFO

#ifndef TLETC_DISABLE_LOGS
#define TLETC_LOG(level, message, ...) tletc::Logger::getLogger()->log(level, message, ##__VA_ARGS__)
#else
#define TLETC_LOG(level, message, ...)
#endif

#define TLETC_CRIT(message, ...) TLETC_LOG(tletc::LogLevel::LOG_LEVEL_CRIT, message, ##__VA_ARGS__)
#define TLETC_ERR(message, ...)  TLETC_LOG(tletc::LogLevel::LOG_LEVEL_ERR,  message, ##__VA_ARGS__)
#define TLETC_WARN(message, ...) TLETC_LOG(tletc::LogLevel::LOG_LEVEL_WARN, message, ##__VA_ARGS__)
#define TLETC_INFO(message, ...) TLETC_LOG(tletc::LogLevel::LOG_LEVEL_INFO, message, ##__VA_ARGS__)
#define TLETC_DBG(message, ...)  TLETC_LOG(tletc::LogLevel::LOG_LEVEL_DBG,  message, ##__VA_ARGS__)

// TODO(Adin): Windows console will have to enable "Virtual Termainl Sequences"
#define ANSI_TEXT_COL_RED "\x1b[31m"
#define ANSI_TEXT_COL_BRIGHT_RED "\x1b[91m"
#define ANSI_TEXT_COL_BRIGHT_YELLOW "\x1b[93m"

// This is "intense" on windows console
#define ANSI_TEXT_FMT_BOLD "\x1b[1m"
#define ANSI_TEXT_FMT_RESET "\x1b[m"

namespace tletc {
    enum LogLevel{
        LOG_LEVEL_NONE = 0,
        LOG_LEVEL_CRIT = 1,
        LOG_LEVEL_ERR  = 2,
        LOG_LEVEL_WARN = 3,
        LOG_LEVEL_INFO = 4,
        LOG_LEVEL_DBG  = 5
    };

    /// Base class representing a single log message destination
    ///
    /// @see Logger
    ///
    class LoggerOutput {
    public:
        LoggerOutput() = default;
        virtual ~LoggerOutput() = default;

        /// Output a message to the message destination (called by Logger::log())
        /// 
        /// @param loglevel the message loglevel (severity)
        /// @param message the message to output (printf format)
        /// @param args the variadic formatting arguments passed to Logger::log()
        ///
        virtual void output(LogLevel loglevel, const char *message, va_list args) = 0;

        /// Flush the message destination.  This is left to the implimentation for the specific
        /// destination
        ///
        virtual void flush() = 0;
    };

    /// LoggerOutput to send log messages to the terminal
    ///
    /// @see Logger
    ///
    class TermLoggerOutput : public LoggerOutput {
    public:
        TermLoggerOutput() = default;
        virtual ~TermLoggerOutput() = default;

        virtual void output(LogLevel loglevel, const char *message, va_list args) override;
        virtual void flush() override;
    };

    /// LoggerOutput to send log messages to a specific file
    ///
    /// @see Logger
    ///
    class FileLoggerOutput : public LoggerOutput {
    public:
        FileLoggerOutput(const std::string &filePath, bool append);
        virtual ~FileLoggerOutput();

        virtual void output(LogLevel loglevel, const char *message, va_list args) override;
        virtual void flush() override;

    private:
        /// The file to send log messages to
        FILE *m_logFile;
    };

    // TODO(Adin): Set log level per output

    /// An extensible logging system with a plugin-like api
    ///
    /// The logger takes in log messages (and associated varadic formatting options)
    /// and sends them to zero or more LoggerOutputs.  Additionally, it stores the
    /// current log level and each message's loglevel must be <= to the current level
    /// for it to be output
    /// Each LoggerOutput represents a destination for log messages, meaning with one
    /// call to Logger::log(), a message can be sent to multiple targets (the terminal,
    /// a file, a webapi, etc.).  This system allows for a unified log call while
    /// sending messages to different destinations each with their own specific
    /// requirements.  Additionally, it allows for easy client extension of the system
    /// by implementing and registering a single class.
    ///
    class Logger {
    public:
        static Logger *getLogger();
        static void destroyLogger();

        void log(LogLevel loglevel, const char *message, ...);

        LogLevel getLogLevel();
        void setLogLevel(LogLevel level);

        void addOutput(LoggerOutput *output);

    private:
        Logger();
        ~Logger() = default;

        static Logger *s_loggerInstance;

        /// The current log level
        LogLevel m_logLevel;
        // TODO(Adin): Convert LoggerOutput * to object storage system
        /// Output destinations currently registered with the logger
        std::vector<LoggerOutput *> m_outputs;
    };
}

#endif