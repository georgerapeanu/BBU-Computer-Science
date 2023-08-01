import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ManufacturerProductCountPageComponent } from './manufacturer-product-count-page.component';

describe('ManufacturerProductCountPageComponent', () => {
  let component: ManufacturerProductCountPageComponent;
  let fixture: ComponentFixture<ManufacturerProductCountPageComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ ManufacturerProductCountPageComponent ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(ManufacturerProductCountPageComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
