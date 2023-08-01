import { Component } from '@angular/core';
import { LoginService } from './services/login.service';
import { UserService } from './services/user-service';
import { Role } from './model/Role';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  title = 'frontend';
  role: Role | null = null;

  constructor(
    private loginService: LoginService,
    private userService: UserService
  ) {
    this.loginService.getUserHandleObservable().subscribe({
      next: (handle) => {
        handle = handle || "visitor";
        this.userService.getUserRole(handle).subscribe({
          next: (role) => {
            this.role = role;
          }
        })
      }
    })
  }
}
