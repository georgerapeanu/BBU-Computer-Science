import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ProductsOverviewPageComponent } from './products-overview-page.component';

describe('ProductsOverviewPageComponent', () => {
  let component: ProductsOverviewPageComponent;
  let fixture: ComponentFixture<ProductsOverviewPageComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ ProductsOverviewPageComponent ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(ProductsOverviewPageComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
