import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ManufacturerDeleteComponent } from './manufacturer-delete.component';

describe('ManufacturerDeleteComponent', () => {
  let component: ManufacturerDeleteComponent;
  let fixture: ComponentFixture<ManufacturerDeleteComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ ManufacturerDeleteComponent ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(ManufacturerDeleteComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
