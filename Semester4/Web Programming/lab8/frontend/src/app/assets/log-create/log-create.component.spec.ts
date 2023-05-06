import { ComponentFixture, TestBed } from '@angular/core/testing';

import { LogCreateComponent } from './log-create.component';

describe('LogCreateComponent', () => {
  let component: LogCreateComponent;
  let fixture: ComponentFixture<LogCreateComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [LogCreateComponent]
    })
      .compileComponents();

    fixture = TestBed.createComponent(LogCreateComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
