import { Component } from '@angular/core';
import { AbstractOverviewPageComponent } from '../../abstract/abstract-overview-page/abstract-overview-page.component';
import { ProductScoreDTO } from 'src/app/dto/ProductScoreDTO';

@Component({
  selector: 'app-product-score-page',
  templateUrl: './product-score-page.component.html',
  styleUrls: ['./product-score-page.component.css']
})
export class ProductScorePageComponent extends AbstractOverviewPageComponent<ProductScoreDTO> {

}
