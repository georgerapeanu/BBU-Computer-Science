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
import { OnInit } from '@angular/core';

@Component({
  selector: 'app-logout',
  templateUrl: './logout.component.html',
  styleUrls: ['./logout.component.css']
})
export class LogoutComponent implements OnInit{
  constructor(
    private route: ActivatedRoute,
    private loginService: LoginService,
    private formBuilder: FormBuilder,
    private location: Location,
    private router: Router,
    private cookieService: CookieService,
  ) {}

  ngOnInit(): void {
    this.loginService.deleteAuthToken();
    this.location.back();
  }
}
