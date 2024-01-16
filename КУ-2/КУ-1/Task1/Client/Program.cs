using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.Text;
using Logger;

namespace Client;

public static class Program
{
    [DllImport("Encryptor.dll", CharSet = CharSet.Unicode)]
    private static extern IntPtr decrypt(string msg, string key);
    
    public static async Task Main()
    {
        var logger = new Logger.Logger(LoggerType.Client);

        var isAttacker = logger.Input("Write \"t\" if you attacker")!;

        var key = "";
        
        if (isAttacker != "t")
            key = logger.Input("Insert your private key")!;
        
        var tcpClient = new TcpClient("127.0.0.1", 5555);

        //await tcpClient.ConnectAsync("127.0.0.1", 5555);
        
        var bytes = new byte[1024];
        var stream = tcpClient.GetStream();

        while (tcpClient.Connected)
        {
            var bytesRead = await stream.ReadAsync(bytes);
            if (bytesRead > 0)
            {
                var msg = Encoding.ASCII.GetString(bytes, 0, bytesRead);

                if (isAttacker != "t")
                    msg = Marshal.PtrToStringUni(decrypt(msg, key!));

                logger.PrintMessage(msg!);
            }
            else
            {
            }
        }

    }
}