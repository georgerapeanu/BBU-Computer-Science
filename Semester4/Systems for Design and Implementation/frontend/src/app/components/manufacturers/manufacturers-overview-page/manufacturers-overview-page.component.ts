import { Component } from '@angular/core';
import { Manufacturer } from 'src/app/model/Manufacturer';
import { AbstractOverviewPageComponent } from '../../abstract/abstract-overview-page/abstract-overview-page.component';

@Component({
  selector: 'app-manufacturers-overview-page',
  templateUrl: './manufacturers-overview-page.component.html',
  styleUrls: ['./manufacturers-overview-page.component.css']
})
export class ManufacturersOverviewPageComponent extends AbstractOverviewPageComponent<Manufacturer> {
  
}
