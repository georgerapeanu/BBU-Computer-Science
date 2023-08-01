import { Component } from '@angular/core';
import { AbstractOverviewPageComponent } from '../../abstract/abstract-overview-page/abstract-overview-page.component';
import { ManufacturerProductCountDTO } from 'src/app/dto/ManufacturerProductCountDTO';

@Component({
  selector: 'app-manufacturer-product-count-page',
  templateUrl: './manufacturer-product-count-page.component.html',
  styleUrls: ['./manufacturer-product-count-page.component.css']
})
export class ManufacturerProductCountPageComponent extends AbstractOverviewPageComponent<ManufacturerProductCountDTO> {

}
