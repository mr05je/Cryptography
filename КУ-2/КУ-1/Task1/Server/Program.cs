using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.Text;
using Logger;

namespace Server;

public static class Program
{
    [DllImport("Encryptor.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr encrypt(string msg, string key);

    public static async Task Main()
    {
        var logger = new Logger.Logger(LoggerType.Server);
        var dllTestMsg = encrypt("", "");
        var dllTest = Marshal.PtrToStringUni(dllTestMsg);
        if (dllTest != "2")
        {
            logger.PrintError("bad dll!");
            return;
        }

        var ctsSource = new CancellationTokenSource();
        Console.CancelKeyPress += (_, _) => { ctsSource.Cancel(false); };

        var tcpListener = new TcpListener(IPAddress.Parse("127.0.0.1"), 5555);

        tcpListener.Start();

        logger.PrintMessage("Waiting for client!");
        var clientTask = AcceptClientAsync(tcpListener, ctsSource.Token);
        logger.PrintMessage("Waiting for attacker!");
        var attackerTask = AcceptClientAsync(tcpListener, ctsSource.Token);

        var client = await clientTask;
        var attacker = await attackerTask;

        var key = logger.Input("Write your key: ");

        while (!ctsSource.Token.IsCancellationRequested)
        {
            var msg = logger.Input("type \"ckey\" for changing key or input message: ");

            if (msg == "ckey")
            {
                key = logger.Input("Insert new key: ");
                msg = logger.Input("input message: ");
            }

            msg = Marshal.PtrToStringUni(encrypt(msg!, key!));

            logger.PrintMessage($"encrypted message = {msg}");

            await SendDataAsync(client.GetStream(), msg, ctsSource.Token);
            await SendDataAsync(attacker.GetStream(), msg, ctsSource.Token);
        }
    }

    private static async Task<TcpClient> AcceptClientAsync(TcpListener listener, CancellationToken token)
    {
        try
        {
            return await listener.AcceptTcpClientAsync().WithCancellation(token);
        }
        catch (OperationCanceledException)
        {
            return null; // Handle cancellation gracefully
        }
    }

    private static async Task SendDataAsync(NetworkStream stream, string data, CancellationToken token)
    {
        var buf = Encoding.Default.GetBytes(data);
        await stream.WriteAsync(buf, token);
    }
}

public static class TaskExtensions
{
    public static async Task<T> WithCancellation<T>(this Task<T> task, CancellationToken cancellationToken)
    {
        var tcs = new TaskCompletionSource<bool>();
        using (cancellationToken.Register(s => ((TaskCompletionSource<bool>)s).TrySetResult(true), tcs))
        {
            if (task != await Task.WhenAny(task, tcs.Task))
                throw new OperationCanceledException(cancellationToken);
        }

        return await task;
    }
}
