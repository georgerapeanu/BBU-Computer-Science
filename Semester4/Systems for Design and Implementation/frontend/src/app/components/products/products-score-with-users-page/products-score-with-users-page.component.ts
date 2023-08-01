import { Component } from '@angular/core';
import { AbstractOverviewPageComponent } from '../../abstract/abstract-overview-page/abstract-overview-page.component';
import { ProductScoreWithUserHandleDTO } from 'src/app/dto/ProductScoreWithUserHandleDTO';

@Component({
  selector: 'app-products-score-with-users-page',
  templateUrl: './products-score-with-users-page.component.html',
  styleUrls: ['./products-score-with-users-page.component.css']
})
export class ProductsScoreWithUsersPageComponent extends AbstractOverviewPageComponent<ProductScoreWithUserHandleDTO> {

}
