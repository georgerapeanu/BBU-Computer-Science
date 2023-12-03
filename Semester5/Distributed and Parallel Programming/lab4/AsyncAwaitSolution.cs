using System.Collections;
using System.Collections.Generic;
using System.Runtime.CompilerServices;
using System.Threading;

namespace Lab4 {
  internal class AsyncAwaitSolution {
    public AsyncAwaitSolution() {}

    public void Run(List<string> urls) {
      List<Task> futures = new List<Task>();
      for(int i = 0; i < urls.Count; i++) {        
        int j = i;
        string url = urls[j];
        futures.Add(Task.Run(() => Start(SocketHandler.Create(url, j))));
      }
      Task.WhenAll(futures).Wait();
    }


      private async Task Start(SocketHandler socket)
      {
          await socket.BeginConnectAsync();
          Console.WriteLine($"AsyncAwait-{socket.Id}: Socket connected to {socket.BaseUrl} ({socket.UrlPath})");

          var numberOfSentBytes = await socket.BeginSendAsync();
          Console.WriteLine($"AsyncAwait-{socket.Id}: Socket sent {numberOfSentBytes}");

          await socket.BeginReceiveAsync();  
          Console.WriteLine($"AsyncAwait-{socket.Id}: Socket received content");

          socket.ShutdownAndClose();
      }
  }
}
