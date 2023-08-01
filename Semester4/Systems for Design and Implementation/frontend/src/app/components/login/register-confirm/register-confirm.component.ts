import { Component } from '@angular/core';
import { ActivatedRoute, Route, Router } from '@angular/router';
import { FormBuilder } from '@angular/forms';
import { Validators, ValidatorFn, AbstractControl, ValidationErrors } from '@angular/forms';
import { Location } from '@angular/common';
import { ReviewCreate } from 'src/app/model/ReviewCreate';
import { User } from 'src/app/model/User';
import { LoginService } from 'src/app/services/login.service';
import { TokenResponseDTO } from 'src/app/dto/TokenResponseDTO';
import { RegisterConfirmResponseDTO } from 'src/app/dto/RegisterConfirmResponseDTO';

@Component({
  selector: 'app-register-confirm',
  templateUrl: './register-confirm.component.html',
  styleUrls: ['./register-confirm.component.css']
})
export class RegisterConfirmComponent {

  constructor(
    private route: ActivatedRoute,
    private loginService: LoginService,
    private formBuilder: FormBuilder,
    private location: Location,
    private router: Router
  ) {}

  serverResponse: RegisterConfirmResponseDTO | null = null;

  ngOnInit() {
    let token: string | null = this.route.snapshot.paramMap.get('token');
    if(token == null) {
      this.serverResponse = {error: "Unexpected frontend error", message: null};
      return;
    }
    this.loginService.confirm(token).subscribe({
      next: (value) => {this.serverResponse = value;},
      error: (error) => {this.serverResponse = error.error;}
    });
  }

  goBack() {
    this.router.navigate(['/']);
  }
}
