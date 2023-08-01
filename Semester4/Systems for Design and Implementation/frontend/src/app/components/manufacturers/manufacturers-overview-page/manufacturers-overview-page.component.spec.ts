import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ManufacturersOverviewPageComponent } from './manufacturers-overview-page.component';

describe('ManufacturersOverviewPageComponent', () => {
  let component: ManufacturersOverviewPageComponent;
  let fixture: ComponentFixture<ManufacturersOverviewPageComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ ManufacturersOverviewPageComponent ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(ManufacturersOverviewPageComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
