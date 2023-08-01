import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ManufacturersOverviewComponent } from './manufacturers-overview.component';

describe('ManufacturersOverviewComponent', () => {
  let component: ManufacturersOverviewComponent;
  let fixture: ComponentFixture<ManufacturersOverviewComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ ManufacturersOverviewComponent ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(ManufacturersOverviewComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
