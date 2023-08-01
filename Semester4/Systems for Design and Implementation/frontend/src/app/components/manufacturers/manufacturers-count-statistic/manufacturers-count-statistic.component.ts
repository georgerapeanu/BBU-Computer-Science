import { Component } from '@angular/core';
import { ManufacturerProductCountDTO } from 'src/app/dto/ManufacturerProductCountDTO';
import { ManufacturerService } from 'src/app/services/manufacturer.service';
import { ActivatedRoute } from '@angular/router';
import { Router } from '@angular/router';
import { AbstractPageContainerComponent } from '../../abstract/abstract-page-container/abstract-page-container.component';
import { UserPreferencesService } from 'src/app/services/user-preferences.service';
import { UserService } from 'src/app/services/user-service';
import { LoginService } from 'src/app/services/login.service';

@Component({
  selector: 'app-manufacturers-count-statistic',
  templateUrl: './manufacturers-count-statistic.component.html',
  styleUrls: ['./manufacturers-count-statistic.component.css']
})
export class ManufacturersCountStatisticComponent extends AbstractPageContainerComponent{
  manufacturerCounts: ManufacturerProductCountDTO[] = [];
  constructor(
    private manufacturerService: ManufacturerService,
    activatedRoute: ActivatedRoute,
    router: Router,
    userPreferencesService: UserPreferencesService,
    userService: UserService,
    loginService: LoginService
  ) {
    super(router, activatedRoute, userPreferencesService, userService, loginService)
  }

  override ngOnInit(): void {
    super.ngOnInit();
  }

  override pageUpdate(): void {
    this.manufacturerService.getManufacturerCountStatistic(this.pageNumber, this.pageSize).subscribe((result) => {
      this.manufacturerCounts = result.content;
      this.totalPages = result.totalPages;
      this.currentPage = this.pageNumber;
      this.currentSize = this.pageSize;
    });
  }
}
