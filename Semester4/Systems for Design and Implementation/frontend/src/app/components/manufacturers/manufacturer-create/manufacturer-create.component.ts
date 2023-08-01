import { Component } from '@angular/core';
import { FormBuilder, Validators } from '@angular/forms';
import { ActivatedRoute, Router } from '@angular/router';
import { ManufacturerService } from 'src/app/services/manufacturer.service';
import { Location } from '@angular/common';
import { ManufacturerCreate } from 'src/app/model/ManufacturerCreate';
import { LoginService } from 'src/app/services/login.service';

@Component({
  selector: 'app-manufacturer-create',
  templateUrl: './manufacturer-create.component.html',
  styleUrls: ['./manufacturer-create.component.css']
})
export class ManufacturerCreateComponent {
  createForm = this.formBuilder.group(
    {
      name: ['', Validators.required],
      description: ['', Validators.required],
      registerDate: [new Date(), Validators.required],
      userHandle: ['', Validators.required]
    }
  );
  serverResponse: string|null = null;

  constructor(
    private route: ActivatedRoute,
    private manufacturerService: ManufacturerService, 
    private formBuilder: FormBuilder,
    private location: Location,
    private router: Router,
    private loginService: LoginService
  ) {}

  ngOnInit(): void {
    this.loginService.getUserHandleObservable().subscribe(value => {
      if(value != null) {
        this.createForm.controls['userHandle'].setValue(value);
      }
    });
  }

  onSubmit(): void {
    if(this.createForm.valid) {
      this.manufacturerService.createManufacturer(this.createForm.value as ManufacturerCreate).subscribe({
        next: response => {
          console.log("ok");
          console.log(response);
          this.serverResponse="Ok";
        },
        error: error => {
          console.log("error");
          console.log(error);
          this.serverResponse="Error";
        }
      });
    }
  }

  goToManufacturers(): void {
    this.router.navigate(["/manufacturers"]);
  }

  goBack(): void {
    this.location.back();
  }
}
