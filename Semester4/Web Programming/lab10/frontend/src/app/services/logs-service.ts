import { Injectable } from '@angular/core';
import { HttpClient, HttpParams } from '@angular/common/http';
import { Observable } from 'rxjs';
import { Log } from '../models/Log';
import { environment } from 'src/environments/environment';

@Injectable({
  providedIn: 'root'
})
export class LogsService {

  constructor(private httpClient: HttpClient) { }

  getLogsForPage(user: string, start_id: number, severity: string): Observable<Array<Log>> {
    let params = new HttpParams()
      .set('user', user)
      .set('start_id', start_id)
      .set('severity', severity);
    return this.httpClient.get<Array<Log>>(environment.API_URL + "/Logs", { params: params })
  }

  getLog(id: number): Observable<Log> {
    let params = new HttpParams()
      .set('id', id);
    return this.httpClient.get<Log>(environment.API_URL + "/Logs", { params: params });
  }

  addLog(log: Log): Observable<any> {
    return this.httpClient.post(environment.API_URL + "/Logs", log);
  }

  editLog(log: Log): Observable<any> {
    return this.httpClient.put(environment.API_URL + "/Logs", log);
  }

  deleteLog(id: number): Observable<any> {
    let params = new HttpParams()
      .set('id', id);
    return this.httpClient.delete<Log>(environment.API_URL + "/Logs", { params: params });
  }
}