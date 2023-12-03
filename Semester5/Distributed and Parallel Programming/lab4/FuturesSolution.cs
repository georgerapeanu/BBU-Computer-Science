using System.Collections;
using System.Collections.Generic;
using System.Runtime.CompilerServices;
using System.Threading;

namespace Lab4 {
  internal class FuturesSolution {
    public FuturesSolution() {}

    public void Run(List<string> urls) {
      List<Task> futures = new List<Task>();
      for(int i = 0; i < urls.Count; i++) {
        int j = i;
        string url = urls[j];
        futures.Add(Task.Run(() => Start(SocketHandler.Create(url, j))));
      }
      Task.WhenAll(futures).Wait();
    }


      private Task Start(SocketHandler socket)
      {
          socket.BeginConnectAsync().Wait();
          Console.WriteLine($"Futures-{socket.Id}: Socket connected to {socket.BaseUrl} ({socket.UrlPath})");

          var sendTask = socket.BeginSendAsync();
          sendTask.Wait();
          var numberOfSentBytes = sendTask.Result;
          Console.WriteLine($"Futures-{socket.Id}: Socket sent {numberOfSentBytes}");

          socket.BeginReceiveAsync().Wait();  
          Console.WriteLine($"Futures-{socket.Id}: Socket received content");

          socket.ShutdownAndClose();
          return Task.CompletedTask;
      }
  }
}
