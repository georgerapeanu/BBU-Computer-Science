import { ComponentFixture, TestBed } from '@angular/core/testing';

import { AbstractOverviewPageComponent } from './abstract-overview-page.component';

describe('AbstractOverviewPageComponent', () => {
  let component: AbstractOverviewPageComponent;
  let fixture: ComponentFixture<AbstractOverviewPageComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ AbstractOverviewPageComponent ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(AbstractOverviewPageComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
