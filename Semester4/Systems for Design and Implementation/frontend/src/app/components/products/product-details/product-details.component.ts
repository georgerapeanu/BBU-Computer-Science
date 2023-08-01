import { Component } from '@angular/core';
import { ActivatedRoute, Router } from '@angular/router';
import { Product } from 'src/app/model/Product';
import { ProductService } from 'src/app/services/product.service';
import { Location } from '@angular/common';
import { Review } from 'src/app/model/Review';
import { AbstractPageContainerComponent } from '../../abstract/abstract-page-container/abstract-page-container.component';
import { UserPreferencesService } from 'src/app/services/user-preferences.service';
import { UserService } from 'src/app/services/user-service';
import { LoginService } from 'src/app/services/login.service';
import { ManufacturerService } from 'src/app/services/manufacturer.service';
import { Manufacturer } from 'src/app/model/Manufacturer';

@Component({
  selector: 'app-product-details',
  templateUrl: './product-details.component.html',
  styleUrls: ['./product-details.component.css']
})
export class ProductDetailsComponent extends AbstractPageContainerComponent {
  product: Product | null = null;
  reviews: Review[] = [];
  productId: number = 0;
  manufacturer: Manufacturer | null = null;

  constructor(
    private route: ActivatedRoute, 
    private productService: ProductService, 
    private location: Location,
    router: Router,
    activatedRoute: ActivatedRoute,
    userPreferencesService: UserPreferencesService,
    userService: UserService,
    loginService: LoginService,
    private manufactuererService: ManufacturerService
  ) {
    super(router, activatedRoute, userPreferencesService, userService, loginService);
  }

  override ngOnInit(): void {
    let productIdString: string | null = this.route.snapshot.paramMap.get('id');
    if(productIdString == null) {
      return;
    }
    this.productId = parseInt(productIdString);

    this.productService.getProductById(this.productId).subscribe(result => {
      this.product = result;
      this.manufactuererService.getManufacturerById(this.product.manufacturerId).subscribe(manufacturer => {
        this.manufacturer = manufacturer;
      });
    });

    super.ngOnInit();
  }

  override pageUpdate() {
    this.productService.getAllReviewsForProduct(this.productId, this.pageNumber, this.pageSize).subscribe(result => {
      this.reviews = result.content;
      this.totalPages = result.totalPages;
      this.currentPage = this.pageNumber;
      this.currentSize = this.pageSize;
    });
  }

  goBack(): void {
    this.location.back();
  }
}
