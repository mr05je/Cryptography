namespace Logger;

public class Logger
{
    private readonly LoggerType _loggerType;
    
    public Logger(LoggerType loggerType)
    {
        _loggerType = loggerType;
    }

    private void PrintDateAndType()
    {
        Console.ForegroundColor = ConsoleColor.Black;
        Console.BackgroundColor = ConsoleColor.Cyan;
        Console.Write($"[{DateTime.Now:T}]");
        Console.BackgroundColor = _loggerType == LoggerType.Client ? ConsoleColor.Yellow : ConsoleColor.Magenta;
        Console.Write($"[{(_loggerType == LoggerType.Client ? "Client" : "Server")}]");
    }

    private static void FinishPrint()
    {
        Console.ForegroundColor = ConsoleColor.White;
        Console.BackgroundColor = ConsoleColor.Black;
    }

    public void PrintMessage(string msg)
    {
        PrintDateAndType();
        Console.ForegroundColor = ConsoleColor.Green;
        Console.BackgroundColor = ConsoleColor.Black;
        Console.Write(" Msg: ");
        Console.ForegroundColor = ConsoleColor.Red;
        Console.Write(msg);
        Console.Write("\n");
        FinishPrint();
    }
    
    public void PrintError(string msg)
    {
        PrintDateAndType();
        Console.ForegroundColor = ConsoleColor.Red;
        Console.BackgroundColor = ConsoleColor.Black;
        Console.Write("Err: ");
        Console.ForegroundColor = ConsoleColor.Red;
        Console.Write(msg);
        FinishPrint();
    }

    public string? Input(string msg)
    {
        PrintDateAndType();
        Console.ForegroundColor = ConsoleColor.Green;
        Console.BackgroundColor = ConsoleColor.Black;
        Console.Write(" " + msg + " ");
        FinishPrint();
        var res = Console.ReadLine();

        return res;
    }
    
}

public enum LoggerType
{
    Client,
    Server
}