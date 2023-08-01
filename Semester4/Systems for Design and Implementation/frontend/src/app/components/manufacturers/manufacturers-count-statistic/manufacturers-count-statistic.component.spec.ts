import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ManufacturersCountStatisticComponent } from './manufacturers-count-statistic.component';

describe('ManufacturersCountStatisticComponent', () => {
  let component: ManufacturersCountStatisticComponent;
  let fixture: ComponentFixture<ManufacturersCountStatisticComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ ManufacturersCountStatisticComponent ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(ManufacturersCountStatisticComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
