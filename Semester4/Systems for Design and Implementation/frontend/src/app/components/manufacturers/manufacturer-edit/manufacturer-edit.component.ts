import { Component } from '@angular/core';
import { FormBuilder, Validators } from '@angular/forms';
import { ActivatedRoute, Router } from '@angular/router';
import { ManufacturerService } from 'src/app/services/manufacturer.service';
import { Location } from '@angular/common';
import { Manufacturer } from 'src/app/model/Manufacturer';

@Component({
  selector: 'app-manufacturer-edit',
  templateUrl: './manufacturer-edit.component.html',
  styleUrls: ['./manufacturer-edit.component.css']
})
export class ManufacturerEditComponent {
  editForm = this.formBuilder.group(
    {
      id: [0],
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
    private router: Router
  ) {}

  ngOnInit(): void {
    let manufacturerIdString: string | null = this.route.snapshot.paramMap.get('id');
    if(manufacturerIdString == null) {
      return;
    }
    this.manufacturerService.getManufacturerById(parseInt(manufacturerIdString)).subscribe(result => {
      this.editForm.setValue(result);
    });
  }

  onSubmit(): void {
    if(this.editForm.valid) {
      this.manufacturerService.editManufacturer(this.editForm.value as Manufacturer).subscribe({
        next: response => {
          this.serverResponse="Ok";
        },
        error: error => {
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
