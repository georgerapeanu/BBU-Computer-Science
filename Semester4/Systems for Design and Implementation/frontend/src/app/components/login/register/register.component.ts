import { Component } from '@angular/core';
import { ActivatedRoute, Route, Router } from '@angular/router';
import { FormBuilder } from '@angular/forms';
import { Validators, ValidatorFn, AbstractControl, ValidationErrors } from '@angular/forms';
import { Location } from '@angular/common';
import { ReviewCreate } from 'src/app/model/ReviewCreate';
import { User } from 'src/app/model/User';
import { LoginService } from 'src/app/services/login.service';
import { TokenResponseDTO } from 'src/app/dto/TokenResponseDTO';

@Component({
  selector: 'app-register',
  templateUrl: './register.component.html',
  styleUrls: ['./register.component.css']
})
export class RegisterComponent {
  checkPasswords: ValidatorFn = (group: AbstractControl):  ValidationErrors | null => { 
    let pass = group.get('password')?.value;
    let confirmPass = group.get('confirmPassword')?.value
    return pass === confirmPass ? null : { notSame: true }
  }
  
  createForm = this.formBuilder.group(
    {
      handle: ["", Validators.required],
      password: ["", [Validators.required, Validators.minLength(8)]],
      confirmPassword: ["", Validators.required]
    },
    {
      validators: this.checkPasswords
    }
  );

  serverResponse: TokenResponseDTO | null = null;

  constructor(
    private route: ActivatedRoute,
    private loginService: LoginService,
    private formBuilder: FormBuilder,
    private location: Location,
    private router: Router
  ) {}

  goBack() {
    this.location.back();
  }

  onSubmit() {
    if(this.createForm.valid){
      let user = this.createForm.value as User;
      this.loginService.register(user).subscribe({
        next: (value) => {this.serverResponse = value},
        error: (error) => {this.serverResponse = error.error}
      });
    }
  }
}
