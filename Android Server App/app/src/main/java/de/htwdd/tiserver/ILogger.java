package de.htwdd.tiserver;

public interface ILogger {
    void writeLog(String msg);
    void writeError(String msg);
}
