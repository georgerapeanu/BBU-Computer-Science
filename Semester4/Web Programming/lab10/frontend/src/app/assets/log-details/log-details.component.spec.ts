import { ComponentFixture, TestBed } from '@angular/core/testing';

import { LogDetailsComponent } from './log-details.component';

describe('LogDetailsComponent', () => {
  let component: LogDetailsComponent;
  let fixture: ComponentFixture<LogDetailsComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [LogDetailsComponent]
    })
      .compileComponents();

    fixture = TestBed.createComponent(LogDetailsComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
