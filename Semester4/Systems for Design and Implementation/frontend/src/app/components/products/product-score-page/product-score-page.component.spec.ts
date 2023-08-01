import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ProductScorePageComponent } from './product-score-page.component';

describe('ProductScorePageComponent', () => {
  let component: ProductScorePageComponent;
  let fixture: ComponentFixture<ProductScorePageComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ ProductScorePageComponent ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(ProductScorePageComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
