import { Component } from '@angular/core';
import { AbstractOverviewPageComponent } from '../../abstract/abstract-overview-page/abstract-overview-page.component';
import UserReviewCountDTO from 'src/app/dto/UserReviewCountDTO';

@Component({
  selector: 'app-user-review-count-page',
  templateUrl: './user-review-count-page.component.html',
  styleUrls: ['./user-review-count-page.component.css']
})
export class UserReviewCountPageComponent extends AbstractOverviewPageComponent<UserReviewCountDTO> {

}
