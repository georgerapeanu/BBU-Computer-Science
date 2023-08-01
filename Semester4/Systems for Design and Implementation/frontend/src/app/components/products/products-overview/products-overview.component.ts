import { Component } from '@angular/core';
import { ProductService } from 'src/app/services/product.service';
import { Product } from 'src/app/model/Product';
import { ActivatedRoute, Router } from '@angular/router';
import { ProductScoreDTO } from 'src/app/dto/ProductScoreDTO';
import { ProductScoreWithUserHandleDTO } from 'src/app/dto/ProductScoreWithUserHandleDTO';
import { AbstractPageContainerComponent } from '../../abstract/abstract-page-container/abstract-page-container.component';
import { UserPreferencesService } from 'src/app/services/user-preferences.service';
import { LoginService } from 'src/app/services/login.service';
import { UserService } from 'src/app/services/user-service';

@Component({
  selector: 'app-products-overview',
  templateUrl: './products-overview.component.html',
  styleUrls: ['./products-overview.component.css']
})
export class ProductsOverviewComponent extends AbstractPageContainerComponent{
  minWeight: number = -1;
  productScoreWithUsers: ProductScoreWithUserHandleDTO[] = [];
  constructor(
    private productService: ProductService,
    router: Router,
    activatedRoute: ActivatedRoute,
    userPreferencesService: UserPreferencesService,
    userService: UserService,
    loginService: LoginService
  ) {
    super(router, activatedRoute, userPreferencesService, userService, loginService);
  }

  override ngOnInit(): void {
    super.ngOnInit();
  }

  setWeight(minWeight: number): void {
    this.router.navigate(
      [],
      {
        relativeTo: this.activatedRoute,
        queryParams: {'pageSize': this.pageSize, 'pageNumber': this.pageNumber, 'weight': minWeight}
      }
    )
  }

  override pageUpdate() {
    this.productService.getProductScoreWithUserHandles(this.pageNumber, this.pageSize, this.minWeight).subscribe(result => {
      this.productScoreWithUsers = result.content;
      this.totalPages = result.totalPages;
      this.currentPage = this.pageNumber;
      this.currentSize = this.pageSize;
    });
  }
}
