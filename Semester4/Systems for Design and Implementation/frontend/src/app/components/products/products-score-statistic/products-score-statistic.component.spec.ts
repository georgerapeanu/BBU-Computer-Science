import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ProductsScoreStatisticComponent } from './products-score-statistic.component';

describe('ProductsScoreStatisticComponent', () => {
  let component: ProductsScoreStatisticComponent;
  let fixture: ComponentFixture<ProductsScoreStatisticComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ ProductsScoreStatisticComponent ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(ProductsScoreStatisticComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
