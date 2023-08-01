import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { BehaviorSubject, Observable } from 'rxjs';
import { TokenResponseDTO } from '../dto/TokenResponseDTO';
import { environment } from 'src/environments/environment';
import { User } from '../model/User';
import { RegisterConfirmResponseDTO } from '../dto/RegisterConfirmResponseDTO';
import { CookieService } from 'ngx-cookie-service';
import jwt_decode from 'jwt-decode';


@Injectable({
  providedIn: 'root'
})
export class LoginService {

  private user_handle_subject = new BehaviorSubject<string | null>(null);
  private user_handle_observable = this.user_handle_subject.asObservable();

  constructor(
    private http: HttpClient, 
    private cookieService: CookieService) { 
    let token = this.getAuthToken();
    if(token != null) {
      this.setAuthToken(token);
    }
  }

  register(user: User): Observable<TokenResponseDTO> {
    return this.http.post<TokenResponseDTO>(environment.apiURL + "/register", user);
  }

  confirm(token: string): Observable<RegisterConfirmResponseDTO> {
    return this.http.post<RegisterConfirmResponseDTO>(environment.apiURL + "/register/" + token, null);
  }

  login(user: User): Observable<TokenResponseDTO> {
    return this.http.post<TokenResponseDTO>(environment.apiURL + "/login", user);
  }

  setAuthToken(token: string) {
    let {exp, user_handle} = jwt_decode(token) as {exp: number, user_handle: string};
    this.cookieService.set("auth-token", token, {expires: new Date(exp * 1000), path:"/"});
    this.user_handle_subject.next(user_handle);
    if(exp * 1000 <= Date.now()) {
      this.deleteAuthToken();
    }
  }

  getAuthToken(): string | null{
    return this.cookieService.get("auth-token") || null;
  }

  deleteAuthToken() {
    this.user_handle_subject.next(null);
    this.cookieService.delete("auth-token", "/");
  }

  getUserHandleObservable(): Observable<string | null> {
    return this.user_handle_observable;
  }
}
