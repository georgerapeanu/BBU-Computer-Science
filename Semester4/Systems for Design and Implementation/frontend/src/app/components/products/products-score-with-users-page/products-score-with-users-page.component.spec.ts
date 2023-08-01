import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ProductsScoreWithUsersPageComponent } from './products-score-with-users-page.component';

describe('ProductsScoreWithUsersPageComponent', () => {
  let component: ProductsScoreWithUsersPageComponent;
  let fixture: ComponentFixture<ProductsScoreWithUsersPageComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ ProductsScoreWithUsersPageComponent ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(ProductsScoreWithUsersPageComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
