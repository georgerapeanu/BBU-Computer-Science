import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ReviewsOverviewPageComponent } from './reviews-overview-page.component';

describe('ReviewsOverviewPageComponent', () => {
  let component: ReviewsOverviewPageComponent;
  let fixture: ComponentFixture<ReviewsOverviewPageComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ ReviewsOverviewPageComponent ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(ReviewsOverviewPageComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
