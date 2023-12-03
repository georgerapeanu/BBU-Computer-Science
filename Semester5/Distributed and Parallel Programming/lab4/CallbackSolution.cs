using System.Collections.Generic;
using System.Threading;

namespace Lab4 {
  internal class CallbackSolution {
    public CallbackSolution() {}

    public void Run(List<string> urls) {
      for(int i = 0; i < urls.Count; i++) {
        Start(SocketHandler.Create(urls[i], i));
      }
      Thread.Sleep(5000);
    }


    private void Start(SocketHandler socket)
    {
        socket.BeginConnect(HandleConnected);
    }

    public void HandleConnected(SocketHandler socket) {
       Console.WriteLine($"Callback-{socket.Id}: Socket connected to {socket.BaseUrl} ({socket.UrlPath})");
       socket.BeginSend(HandleSent);
    }

    public void HandleSent(SocketHandler socket, int numberOfSentBytes) {
      Console.WriteLine($"Callback-{socket.Id}: Socket sent {numberOfSentBytes}");
      socket.BeginReceive(HandleReceived);
    }

    private void HandleReceived(SocketHandler socket) {
      Console.WriteLine($"Callback-{socket.Id}: Socket received content");
      socket.ShutdownAndClose();
    }
  }
}
