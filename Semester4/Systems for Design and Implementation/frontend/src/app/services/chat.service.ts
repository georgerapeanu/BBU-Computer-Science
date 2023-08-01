import { Injectable, OnDestroy } from '@angular/core';
import { environment } from 'src/environments/environment';
import {Stomp, CompatClient} from '@stomp/stompjs';
import { BehaviorSubject, Observable, filter, first, switchMap } from 'rxjs';
import { MessageDTO } from '../dto/MessageDTO';
import * as SockJS from 'sockjs-client';
import { HttpClient } from '@angular/common/http';

enum SocketClientState{
  ATTEMPTING,
  CONNECTED
}

@Injectable({
  providedIn: 'root'
})
export class ChatService implements OnDestroy {
  private client: CompatClient;
  private state: BehaviorSubject<SocketClientState>;
  constructor(
    private httpClient: HttpClient
      ) {
    this.state = new BehaviorSubject<SocketClientState>(SocketClientState.ATTEMPTING);
    this.client = Stomp.over(new SockJS(environment.apiURL + '/stomp'));
    this.client.connect({}, () => {
      this.state.next(SocketClientState.CONNECTED);
    });
  }

  private connect(): Observable<CompatClient> {
    return new Observable<CompatClient> (observer => {
      this.state.pipe(filter(state => state === SocketClientState.CONNECTED)).subscribe(() => {
        observer.next(this.client);
      })
    });
  }

  ngOnDestroy(): void {
    this.connect().pipe(first()).subscribe(client => client.disconnect(() => {}));
  }

  onMessageObservable(): Observable<MessageDTO> {
    return this.connect().pipe(first(), switchMap(client => {
      return new Observable<MessageDTO>(observer => {
          const subscription = client.subscribe('/topic/chat', message => {
            observer.next(JSON.parse(message.body) as MessageDTO);
          });
          return () => client.unsubscribe(subscription.id);
      });
    }));
  }

  sendMessage(messageDTO: MessageDTO): void {
    console.log(environment.apiURL + "/store-messages");
    this.httpClient.post(environment.apiURL + "/store-messages", messageDTO).subscribe();
    this.connect().pipe(first()).subscribe(client => {
      client.send("/messages/chat", {}, JSON.stringify(messageDTO));
    });
  }

  getPreviousMessages() : Observable<MessageDTO[]> {
    return this.httpClient.get<MessageDTO[]>(environment.apiURL + "/restore-messages");
  }

  getSummary(): Observable<string> {
    return this.httpClient.get(environment.apiURL + "/chat-recent-summary", {responseType: 'text'});
  }
}
