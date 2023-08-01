import { ComponentFixture, TestBed } from '@angular/core/testing';

import { UsersOverviewPageComponent } from './users-overview-page.component';

describe('UsersOverviewPageComponent', () => {
  let component: UsersOverviewPageComponent;
  let fixture: ComponentFixture<UsersOverviewPageComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ UsersOverviewPageComponent ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(UsersOverviewPageComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
