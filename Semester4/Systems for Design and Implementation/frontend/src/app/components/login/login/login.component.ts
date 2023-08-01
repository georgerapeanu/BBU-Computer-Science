import { Component } from '@angular/core';
import { ActivatedRoute, Route, Router } from '@angular/router';
import { FormBuilder } from '@angular/forms';
import { Validators, ValidatorFn, AbstractControl, ValidationErrors } from '@angular/forms';
import { Location } from '@angular/common';
import { ReviewCreate } from 'src/app/model/ReviewCreate';
import { User } from 'src/app/model/User';
import { LoginService } from 'src/app/services/login.service';
import { TokenResponseDTO } from 'src/app/dto/TokenResponseDTO';
import { CookieService } from 'ngx-cookie-service';

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LoginComponent {
  serverResponse: TokenResponseDTO | null = null;

  loginForm = this.formBuilder.group(
    {
      handle: ["", Validators.required],
      password: ["", Validators.required],
    }
  );

  goBack() {
    this.location.back();
  }

  constructor(
    private route: ActivatedRoute,
    private loginService: LoginService,
    private formBuilder: FormBuilder,
    private location: Location,
    private router: Router,
    private cookieService: CookieService,
  ) {}

  onSubmit() {
    if(this.loginForm.valid){
      let user = this.loginForm.value as User;
      this.loginService.login(user).subscribe({
        next: (value) => {
          console.log("im here");
          this.loginService.setAuthToken(value.token || "");
          this.goBack();
        },
        error: (error) => {
          console.log("im here2");
          this.serverResponse = error.error;
        }
      });
    }
  }
}
