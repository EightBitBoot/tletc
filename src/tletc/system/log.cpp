
#include "log.h"

#include "tletc/internal_core.h"

namespace tletc {

    // Message prefixes for each log level
    static const char *LOG_LEVEL_NAMES[6] = {
        "NONE",
        "CRIT",
        "ERR",
        "WRN",
        "INF",
        "DBG"
    };

    // Singleton logger instance
    Logger *Logger::s_loggerInstance = nullptr;

    /// Get the singleton instance of Logger
    ///
    /// Creates a new Logger if one doesn't exist
    ///
    /// @return a pointer to the singleton instance
    ///
    Logger *Logger::getLogger() {
        if(s_loggerInstance == nullptr) {
            s_loggerInstance = new Logger();
        }

        return s_loggerInstance;
    }

    /// Destroy the singleton instance of Logger if it exists
    ///
    void Logger::destroyLogger() {
        if(s_loggerInstance != nullptr) {
            delete s_loggerInstance;
        }

        s_loggerInstance = nullptr;
    }

    /// Send a log message to the terminal
    ///
    /// @param loglevel the message level (severity)
    /// @param message the log message (printf format)
    /// @param args the variadic formating arguments passed to Logger::log()
    ///
    void TermLoggerOutput::output(LogLevel loglevel, const char *message, va_list args) {
        const char *messageColor;

        switch(loglevel) {
            case LOG_LEVEL_CRIT:
                // This uses C style string literal concatenation
                messageColor = ANSI_TEXT_COL_RED;
                break;

            case LOG_LEVEL_ERR:
                messageColor = ANSI_TEXT_COL_BRIGHT_RED;
                break;

            case LOG_LEVEL_WARN:
                messageColor = ANSI_TEXT_COL_BRIGHT_YELLOW;
                break;

            default:
                messageColor = "";
        }

        // TODO(Adin): Is there a way to compress this into one call without allocating memory for sprintf
        printf("%s[TLETC:%s] ", messageColor, LOG_LEVEL_NAMES[loglevel]);
        vprintf(message, args);
        printf(ANSI_TEXT_FMT_RESET "\n"); // String literal concatenation
    }

    /// Flush the terminal output
    ///
    void TermLoggerOutput::flush() {
        fflush(stdout);
    }

    /// Construct a new FileLoggerOutput, opening the destination file in the process
    ///
    /// NOTE: This currently doesn't check for missing files or paths, it will just fail
    ///       silently.  This will be remedied with the platform abstraction layer
    ///
    /// @param filepath the path to the destination file
    /// @param append whether to append to the file if it exists
    ///
    FileLoggerOutput::FileLoggerOutput(const std::string &filePath, bool append) {
        // TODO(Adin): Check for file validity, and add option to create if missing
        // TODO(Adin): Update documentation when above is implemented

        if(append) {
            m_logFile = fopen(filePath.c_str(), "a");
        }
        else {
            m_logFile = fopen(filePath.c_str(), "w");
        }
    }

    /// Destruct a FileLoggerOutput, closing the file in the process
    FileLoggerOutput::~FileLoggerOutput() {
        if(m_logFile) {
            fclose(m_logFile);
        }
    }

    /// Output a log message to the destination file
    ///
    /// @param loglevel the message level (severity)
    /// @param message the log message (printf format)
    /// @param args the variadic formating arguments passed to Logger::log()
    /// 
    void FileLoggerOutput::output(LogLevel loglevel, const char *message, va_list args) {
        // TODO(Adin): Is there a way to compress this into one call without allocating memory for sprintf
        if(m_logFile) {
            // TODO(Adin): This if is hacky, change it when implementing log file validity checks
            fprintf(m_logFile, "[TLETC:%s] ", LOG_LEVEL_NAMES[loglevel]);
            vfprintf(m_logFile, message, args);
            fprintf(m_logFile, "\n");
            fflush(m_logFile);
        }
    }

    /// Flush messages to the destination file
    ///
    void FileLoggerOutput::flush() {
        fflush(m_logFile);
    }

    Logger::Logger() :
        m_logLevel(TLETC_DEFAULT_LOG_LEVEL)
    {}

    /// Log a message
    ///
    /// Iterate over every LoggerOutput stored in Logger and forward the
    /// message to them.  If loglevel greater than Logger::m_logLevel it
    /// will not be forwarded.  The same applies if loglevel is
    /// LOG_LEVEL_NONE.
    ///
    /// @param loglevel the message level (severity)
    /// @param message the log message (printf format)
    /// @param ... formatting arguments (printf format)
    ///
    void Logger::log(LogLevel loglevel, const char *message, ...) {
        using OutIter = std::vector<LoggerOutput *>::iterator;

        // TODO(Adin): Make this an assert
        if(loglevel > 5) {
            return;
        }

        if(loglevel == LOG_LEVEL_NONE || loglevel > m_logLevel) {
            return;
        }
        
        va_list args;
        va_start(args, message);

        va_list argsToPass;

        for(OutIter iter = m_outputs.begin(); iter != m_outputs.end(); iter++) {
            va_copy(argsToPass, args);
            (*iter)->output(loglevel, message, argsToPass);
        }

        va_end(argsToPass);
        va_end(args);
    }

    /// Get the current log level
    ///
    /// @return the current log level
    ///
    LogLevel Logger::getLogLevel() {
        return m_logLevel;
    }

    /// Set the current log level
    ///
    /// @param level the new log level (in range [0, 5])
    void Logger::setLogLevel(LogLevel level) {
        if(level < 0 || level > 5) {
            // TODO(Adin): Make this an assert
            return;
        }

        m_logLevel = level;
    }

    /// Add a new LoggerOutput to the logger
    ///
    /// @param output the new LoggerOutput to add to the logger
    ///
    void Logger::addOutput(LoggerOutput *output) {
        m_outputs.push_back(output);
    }
}