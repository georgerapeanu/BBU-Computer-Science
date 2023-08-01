import { Injectable } from '@angular/core';
import { CookieService } from 'ngx-cookie-service';
import { LoginService } from './login.service';
import { HttpClient } from '@angular/common/http';
import { environment } from 'src/environments/environment';
import { UserPreference } from '../model/UserPreference';
import { Observable } from 'rxjs';
import { flatMap } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class UserPreferencesService {

  constructor(
    private loginService: LoginService,
    private httpClient: HttpClient
    ) { 

  }

  savePreference(preference: UserPreference) {
    this.httpClient.post(environment.apiURL + "/users/" + preference.handle + "/preference", preference).subscribe({});
  }

  getPreference(handle: string): Observable<UserPreference> {
    return this.httpClient.get<UserPreference>(environment.apiURL + "/users/" + handle + "/preference");
  }
}
