import { Component } from '@angular/core';
import { ActivatedRoute, Router } from '@angular/router';
import { ManufacturerService } from 'src/app/services/manufacturer.service';
import { Location } from '@angular/common';

@Component({
  selector: 'app-manufacturer-delete',
  templateUrl: './manufacturer-delete.component.html',
  styleUrls: ['./manufacturer-delete.component.css']
})
export class ManufacturerDeleteComponent {
  manufacturerId: number = 0
  serverResponse: String|null = null;
  constructor(
    private route: ActivatedRoute,
    private manufacturerService: ManufacturerService,
    private location: Location,
    private router: Router
  ) {}

  ngOnInit(): void {
    let manufacturerIdString: string | null = this.route.snapshot.paramMap.get('id');
    if(manufacturerIdString == null) {
      return;
    }
    this.manufacturerId = parseInt(manufacturerIdString);
  }

  goBack(): void {
    this.location.back();
  }

  goToManufacturers(): void {
    this.router.navigate(["/manufacturers"]);
  }

  deleteManufacturer(): void {
    this.manufacturerService.deleteManufacturer(this.manufacturerId).subscribe({
      next: response => {
        this.serverResponse="Operation was succesful!";
      },
      error: error => {
        this.serverResponse="An error occured!";
      }
    });
  }
}
