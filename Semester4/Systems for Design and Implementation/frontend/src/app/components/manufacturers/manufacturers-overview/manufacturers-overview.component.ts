import { Component, OnInit } from '@angular/core';
import { ManufacturerService } from 'src/app/services/manufacturer.service';
import { Manufacturer } from 'src/app/model/Manufacturer';
import { ActivatedRoute, Router } from '@angular/router';
import { ManufacturerProductCountDTO } from 'src/app/dto/ManufacturerProductCountDTO';
import { AbstractPageContainerComponent } from '../../abstract/abstract-page-container/abstract-page-container.component';
import { UserPreferencesService } from 'src/app/services/user-preferences.service';
import { UserService } from 'src/app/services/user-service';
import { LoginService } from 'src/app/services/login.service';

@Component({
  selector: 'app-users-overview',
  templateUrl: './manufacturers-overview.component.html',
  styleUrls: ['./manufacturers-overview.component.css']
})
export class ManufacturersOverviewComponent extends AbstractPageContainerComponent{
  manufacturerProductCounts: ManufacturerProductCountDTO[] = [];
  constructor(
    private manufacturerService: ManufacturerService,
    router: Router,
    activatedRoute: ActivatedRoute,
    userPreferencesService: UserPreferencesService,
    userService: UserService,
    loginService: LoginService
  ) {
    super(router, activatedRoute, userPreferencesService, userService, loginService);
  }

  override pageUpdate(): void {
    this.manufacturerService.getManufacturersReviewCountPage(this.pageNumber, this.pageSize).subscribe(result => {
      this.manufacturerProductCounts = result.content;
      this.totalPages = result.totalPages;
      this.currentPage = this.pageNumber;
      this.currentSize = this.pageSize;
    });
  }
}
