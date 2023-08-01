import { Component } from '@angular/core';
import jwt_decode from 'jwt-decode';
import { LoginService } from 'src/app/services/login.service';

@Component({
  selector: 'app-login-status',
  templateUrl: './login-status.component.html',
  styleUrls: ['./login-status.component.css']
})
export class LoginStatusComponent {
  constructor(private loginService: LoginService) {

  }

  user_handle: string | null = null;

  ngOnInit(): void {
    let token: string | null = this.loginService.getAuthToken();
    if(token != null) {
      const {exp} = jwt_decode(token) as {exp: number};
      if(Date.now() >= exp * 1000) {
        this.loginService.deleteAuthToken();
      }
    }
    this.loginService.getUserHandleObservable().subscribe(value => this.user_handle=value);
  }
}
