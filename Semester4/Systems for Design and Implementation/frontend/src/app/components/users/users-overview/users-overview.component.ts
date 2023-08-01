import { Component } from '@angular/core';
import { UserService } from 'src/app/services/user-service';
import { UserProfile } from 'src/app/model/UserProfile';
import { ActivatedRoute, Router } from '@angular/router';
import UserReviewCountDTO from 'src/app/dto/UserReviewCountDTO';
import { AbstractPageContainerComponent } from '../../abstract/abstract-page-container/abstract-page-container.component';
import { UserPreferencesService } from 'src/app/services/user-preferences.service';
import { LoginService } from 'src/app/services/login.service';

@Component({
  selector: 'app-users-overview',
  templateUrl: './users-overview.component.html',
  styleUrls: ['./users-overview.component.css']
})
export class UsersOverviewComponent extends AbstractPageContainerComponent {
  userReviewCounts: UserReviewCountDTO[] = [];
  constructor(
    userService: UserService,
    router: Router,
    activatedRoute: ActivatedRoute,
    userPreferencesService: UserPreferencesService,
    loginService: LoginService
  ) {
    super(router, activatedRoute, userPreferencesService, userService, loginService);
  }

  override pageUpdate(): void {
    
    this.userService.getUserReviewCountsPage(this.pageNumber, this.pageSize).subscribe(result => {
      this.userReviewCounts = result.content;
      this.totalPages = result.totalPages;
      this.currentPage = this.pageNumber;
      this.currentSize = this.pageSize;
    });
  }
}
