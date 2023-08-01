import { ComponentFixture, TestBed } from '@angular/core/testing';

import { UserReviewCountPageComponent } from './user-review-count-page.component';

describe('UserReviewCountPageComponent', () => {
  let component: UserReviewCountPageComponent;
  let fixture: ComponentFixture<UserReviewCountPageComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ UserReviewCountPageComponent ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(UserReviewCountPageComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
