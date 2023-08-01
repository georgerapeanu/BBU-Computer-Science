import { Component } from '@angular/core';
import { ActivatedRoute, Router } from '@angular/router';
import { Manufacturer } from 'src/app/model/Manufacturer';
import { Product } from 'src/app/model/Product';
import { ManufacturerService } from 'src/app/services/manufacturer.service';
import { Location } from '@angular/common';
import { AbstractPageContainerComponent } from '../../abstract/abstract-page-container/abstract-page-container.component';
import { UserPreferencesService } from 'src/app/services/user-preferences.service';
import { UserService } from 'src/app/services/user-service';
import { LoginService } from 'src/app/services/login.service';


@Component({
  selector: 'app-manufacturer-details',
  templateUrl: './manufacturer-details.component.html',
  styleUrls: ['./manufacturer-details.component.css']
})
export class ManufacturerDetailsComponent extends AbstractPageContainerComponent {

  manufacturer: Manufacturer | null = null;
  products: Product[] = [];
  manufacturerId: number = 0;

  constructor(
    private route: ActivatedRoute,
    private manufacturerService: ManufacturerService, 
    private location: Location,
    router: Router,
    activatedRoute: ActivatedRoute,
    userPreferencesService: UserPreferencesService,
    userService: UserService,
    loginService: LoginService
  ) {
    super(router, activatedRoute, userPreferencesService, userService, loginService);
  }

  override ngOnInit(): void {
    let manufacturerIdString: string | null = this.route.snapshot.paramMap.get('id');
    if(manufacturerIdString == null) {
      return;
    }
    this.manufacturerId = parseInt(manufacturerIdString);

    this.manufacturerService.getManufacturerById(this.manufacturerId).subscribe(result => {
      this.manufacturer = result;
    });
    
    super.ngOnInit();
  }

  override pageUpdate(): void {
    this.manufacturerService.getAllProductsForManufacturer(this.manufacturerId, this.pageNumber, this.pageSize).subscribe(result => {
      this.products = result.content;
      this.totalPages = result.totalPages;
      this.currentPage = this.pageNumber;
      this.currentSize = this.pageSize;
    });
  }

  goBack(): void {
    this.location.back();
  }
}
